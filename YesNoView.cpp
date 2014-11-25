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

#include <Alignment.h>

#include "HDialog.h"
#include "YesNoView.h"

YesNoView::YesNoView(BRect frame, BString title)
	:
	DialogView(frame, title)
{
	BGroupLayout* gl = new BGroupLayout(B_HORIZONTAL, B_USE_SMALL_SPACING);
	gl->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_UNSET));
	fLayout->AddItem(gl);

	BMessage* ymsg = new BMessage(MSG_SELECTED);
	ymsg->AddString("value", "yes");
	fYesBtn = new BButton("Yes", ymsg);
	fYesBtn->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_UNSET));
	gl->AddView(fYesBtn);

	BMessage* nmsg = new BMessage(MSG_SELECTED);
	nmsg->AddString("value", "no");
	fNoBtn = new BButton("No", nmsg);
	fNoBtn->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_UNSET));
	gl->AddView(fNoBtn);
}

YesNoView::~YesNoView()
{
}

void YesNoView::AttachedToWindow()
{
	fYesBtn->SetTarget(be_app);
	fNoBtn->SetTarget(be_app);
}
