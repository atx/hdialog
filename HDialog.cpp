/* 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Josef Gajdusek
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#include <OS.h>
#include <Screen.h>
#include <TextView.h>
#include <GroupLayout.h>
#include <StringView.h>
#include <ObjectList.h>
#include <Button.h>

#include "HDialog.h"
#include "InfoView.h"
#include "InputView.h"
#include "StatusView.h"
#include "RadioView.h"
#include "CheckBoxView.h"
#include "YesNoView.h"

#include <iostream>

using namespace std;

const char* kSignature = "application/hnotify";

const char* kUsage = \
					 "Usage:\n"
					 "\thdialog <type> [arguments]...\n"
					 "Display a GUI dialog.\n"
					 "\n"
					 "  -h, --help       display this help\n"
					 "  -w, --width      width of the dialog\n"
					 "  -h, --height     height of the dialog\n"
					 "  -t, --title      title of the window\n"
					 "  -m, --modal      set the type of the window to modal\n"
					 "\n"
					 "Dialog types:\n"
					 "  --info text...\n"
					 "  --input text...\n"
					 "  --status text...\n"
					 "  --radio text opt1 opt2 opt3...\n"
					 "  --checkbox text opt1 opt2 opt3...\n"
					 "  --status text...\n"
					 "\n"
					 "GitHub: https://github.com/atalax/hdialog\n";

HDialogApp::HDialogApp()
	:
	BApplication(kSignature)
{
}

status_t HDialogApp::StdinThread(void* arg)
{
	HDialogApp* app = static_cast<HDialogApp*>(arg);
	BMessenger messenger(app);
	string str;

	while (true) {
		getline(cin, str);

		BMessage msg(MSG_READLINE);
		BMessage reply;
		msg.AddString("value", str.c_str());

		messenger.SendMessage(&msg, &reply,
				B_INFINITE_TIMEOUT, B_INFINITE_TIMEOUT);
		if (app->fStdinThrShouldTerminate)
			break;
	}

	return 0;
}

void HDialogApp::ReadyToRun()
{
	BRect frame(0, 0, fWidth, fHeight);
	BWindow* win = new BWindow(frame, fTitle,
			fIsModal ? B_MODAL_WINDOW : B_TITLED_WINDOW,
			B_NOT_ANCHORED_ON_ACTIVATE | B_NOT_CLOSABLE | B_NOT_RESIZABLE);

	switch(fType) {
	case DIALOG_INFO:
		fView = new InfoView(frame, fText);
		break;
	case DIALOG_INPUT:
		fView = new InputView(frame, fText);
		break;
	case DIALOG_STATUS:
		fView = new StatusView(frame, fText);
		break;
	case DIALOG_RADIO:
		fView = new RadioView(frame, fText, *fArgs);
		break;
	case DIALOG_CHECKBOX:
		fView = new CheckBoxView(frame, fText, *fArgs);
		break;
	case DIALOG_YESNO:
		fView = new YesNoView(frame, fText);
		break;
	default:
		Quit();
		return;
	}
	win->AddChild(fView);

	if (!fForceSize) {
		BSize size = fView->GetLayout()->PreferredSize();
		win->ResizeTo(size.width, size.height);
	}

	win->CenterOnScreen();
	win->Show();

	if (fType == DIALOG_STATUS) {
		// We only need to start the thread in this case
		fStdinThr = spawn_thread(StdinThread, "StdinThread",
				B_NORMAL_PRIORITY, this);
		resume_thread(fStdinThr);
	}
}

void HDialogApp::HandleReadline(BString str)
{
	if (str == "quit") {
		fStdinThrShouldTerminate = true;
		Quit();
	}

	switch(fType) {
	case DIALOG_STATUS: {
		int i = 0;
		if (sscanf(str.String(), "%d", &i) == 0)
			break;
		BStatusBar* st = static_cast<StatusView*>(fView)->fStatusBar;
		// TODO: I do not think this is the correct way to change the progress
		st->LockLooper();
		st->Update(i - st->CurrentValue());
		st->UnlockLooper();
		break;
	}
	default:
		break;
	}
}

void HDialogApp::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	case MSG_SELECTED:
		cout << msg->GetString("value", "") << endl;
		Quit();
		break;
	case MSG_READLINE:
		HandleReadline(msg->GetString("value", ""));
		msg->SendReply(new BMessage(MSG_READLINE));
		break;
	default:
		BApplication::MessageReceived(msg);
	}
}

void HDialogApp::ArgvReceived(int32 argc, char** argv)
{
	static struct option longopts[] = {
		{ "help", no_argument, NULL, 'p'},
		{ "width", required_argument, NULL, 'w' },
		{ "height", required_argument, NULL, 'h' },
		{ "title", required_argument, NULL, 't' },
		{ "modal", no_argument, NULL, 'm' },
		{ "info", no_argument, (int *)(&fType), DIALOG_INFO },
		{ "input", no_argument, (int *)(&fType), DIALOG_INPUT },
		{ "status", no_argument, (int *)(&fType), DIALOG_STATUS },
		{ "radio", no_argument, (int *)(&fType), DIALOG_RADIO },
		{ "checkbox", no_argument, (int *)(&fType), DIALOG_CHECKBOX },
		{ "yesno", no_argument, (int *)(&fType), DIALOG_YESNO },
		{ 0, 0, 0, 0 }
	};

	bool selected = false;
	while (true) {
		int option_index;

		int c = getopt_long(argc, argv, "mw:h:t:", longopts, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (selected) {
				cerr << "Multiple types selected!" << endl;
				Quit();
			}
			selected = true;
			break;
		case 'p':
			cout << kUsage;
			Quit();
			break;
		case 'w':
			fWidth = atoi(optarg);
			fForceSize = true;
			break;
		case 'h':
			fHeight = atoi(optarg);
			fForceSize = true;
			break;
		case 'm':
			fIsModal = true;
			break;
		case 't':
			fTitle = optarg;
			break;
		default:
			Quit();
		}
	}

	if (fWidth <= 0 || fHeight <= 0) {
		cerr << "Invalid dimensions specified!" << endl;
		Quit();
	}

	switch(fType) {
	case DIALOG_INFO:
	case DIALOG_INPUT:
	case DIALOG_STATUS:
	case DIALOG_YESNO:
		for (int i = optind; i < argc; i++) {
			fText += argv[i];
			fText += ' ';
		}
		break;
	case DIALOG_RADIO:
	case DIALOG_CHECKBOX:
	default:
		int i = optind;
		fText += argv[i];
		i++;
		fArgs = new BObjectList<BString>(true);
		for (; i < argc; i++)
			fArgs->AddItem(new BString(argv[i]));
	}

	if (fText == "") {
		cerr << "No text specified!" << endl;
		Quit();
	}
}

HDialogApp::~HDialogApp()
{
	delete fArgs;
}

int main(int argc, char**)
{
	// We need to check here as ArgvReceived is not called for argc < 2
	if (argc < 2) {
		cout << kUsage;
		return -1;
	}

	HDialogApp app;
	app.Run();

	return 0;
}
