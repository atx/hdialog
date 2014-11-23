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

#include "HDialog.h"
#include "RadioView.h"

RadioView::RadioView(BRect frame, BString title, BObjectList<BString> choices,
			BString bstr)
	:
	DialogView(frame, title)
{
	for (int i = 0; i < choices.CountItems(); i++) {
		BRadioButton* rad = new BRadioButton(*choices.ItemAt(i), NULL);
		fRadios.AddItem(rad);
		fLayout->AddView(rad);
	}

	fButton = new BButton(bstr, new BMessage(MSG_PRESS));
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
	case MSG_PRESS:
		for(int i = 0; i < fRadios.CountItems(); i++) {
			BRadioButton* radio = fRadios.ItemAt(i);
			if (radio->Value() == B_CONTROL_ON) {
				BMessage* nmsg = new BMessage(MSG_SELECTED);
				nmsg->SetString("value", radio->Label());
				be_app->PostMessage(nmsg);
				break;
			}
		}
		break;
	default:
		DialogView::MessageReceived(msg);
	}
}
