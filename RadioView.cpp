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

#include <RadioButton.h>
#include <CheckBox.h>
#include <Alignment.h>

#include "HDialog.h"
#include "RadioView.h"

RadioView::RadioView(BRect frame, BString title, BObjectList<BString> choices,
			bool radio, BString bstr)
	:
	DialogView(frame, title)
{
	fIsRadios = radio;

	BGroupLayout* grp = new BGroupLayout(B_VERTICAL, 0);
	fLayout->AddItem(grp);

	for (int i = 0; i < choices.CountItems(); i++) {
		BControl* cnt;
		if (fIsRadios)
			cnt = new BRadioButton(*choices.ItemAt(i), NULL);
		else
			cnt = new BCheckBox(*choices.ItemAt(i), NULL);
		fControls.AddItem(cnt);
		grp->AddView(cnt);
	}

	fButton = new BButton(bstr, new BMessage(MSG_PRESS));
	fButton->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_UNSET));
	fLayout->AddView(fButton);
}

RadioView::~RadioView()
{
}

void RadioView::AttachedToWindow()
{
	fButton->SetTarget(this);
}

void RadioView::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	case MSG_PRESS: {
		BMessage* nmsg = new BMessage(MSG_SELECTED);
		BString acc = "";
		bool chosen = false;
		for(int i = 0; i < fControls.CountItems(); i++) {
			BControl* cnt = fControls.ItemAt(i);
			if (cnt->Value() == B_CONTROL_ON) {
				if (chosen)
					acc << '\n';
				acc << cnt->Label();
				chosen = true;
			}
		}
		// Force a choice for radio buttons
		if (fIsRadios && !chosen)
			break;
		nmsg->SetString("value", acc);
		be_app->PostMessage(nmsg);
		break;
	}
	default:
		DialogView::MessageReceived(msg);
	}
}
