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

#include "DialogView.h"

DialogView::DialogView(BRect frame, BString title)
	:
	BView(frame, NULL, B_FOLLOW_ALL_SIDES, 0)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fLayout = new BGroupLayout(B_VERTICAL);
	fLayout->SetInsets(5, 5, 5, 5);
	fLayout->SetSpacing(10);
	SetLayout(fLayout);

	fStringView = new BStringView(NULL, title);
	fStringView->SetAlignment(B_ALIGN_CENTER);
	fLayout->AddView(fStringView);
}

DialogView::~DialogView()
{
}
