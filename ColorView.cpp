/* 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Josef Gajdusek
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

#include "ColorView.h"

#include <Alignment.h>
#include <GroupLayout.h>
#include <StringView.h>
#include <TextControl.h>

#include "HDialog.h"

#include <iostream>

ColorView::ColorView(BRect frame, BString title, BString bstr)
	:
	DialogView(frame, title)
{
	fColorControl = new BColorControl(BPoint(0, 0), B_CELLS_32x8, 10, "");
	fLayout->AddView(fColorControl);

	fButton = new BButton(bstr, new BMessage(MSG_PRESS));
	fButton->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_UNSET));
	fLayout->AddView(fButton);
}

ColorView::~ColorView()
{
}

void ColorView::AttachedToWindow()
{
	fButton->SetTarget(this);
	Window()->SetDefaultButton(fButton);
}

void ColorView::MessageReceived(BMessage* msg)
{
	switch(msg->what) {
		case MSG_PRESS: {
			BMessage msg(MSG_SELECTED);
			rgb_color color = fColorControl->ValueAsColor();
			msg.SetString("value", BString().SetToFormat("#%02X%02X%02X",
						color.red, color.green, color.blue));
			be_app->PostMessage(&msg);
			break;
		}
		default:
			DialogView::MessageReceived(msg);
	}
}
