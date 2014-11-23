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

#ifndef _HDIALOG_H
#define _HDIALOG_H

#include <OS.h>
#include <ObjectList.h>
#include <Application.h>
#include <StringList.h>
#include <String.h>
#include <Window.h>
#include <Box.h>

enum HDialogType {
	DIALOG_INFO,
	DIALOG_INPUT,
	DIALOG_STATUS,
	DIALOG_RADIO,
	DIALOG_CHECKBOX,
	DIALOG_YESNO,
};

class HDialogApp : public BApplication {
public:
							HDialogApp();
	virtual					~HDialogApp();

	virtual void			ReadyToRun();

	virtual void			ArgvReceived(int32 argc, char** argv);
	virtual void			MessageReceived(BMessage* msg);

private:
	static status_t			StdinThread(void *);
	void					HandleReadline(BString line);

	enum HDialogType		fType;
	int						fWidth = 300;
	int						fHeight = 100;
	BString					fText;
	BObjectList<BString>*	fArgs = NULL;
	BView*					fView;
	bool					fIsModal = false;
	BString					fTitle = "Dialog";
	thread_id				fStdinThr;
	bool					fStdinThrShouldTerminate = false;
	BHandler				fStdinThrHandler;
};

enum {
	MSG_SELECTED = 'sel0',
	MSG_PRESS = 'btnp',
	MSG_READLINE = 'rdln',
};

#endif
