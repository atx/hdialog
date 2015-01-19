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

#ifndef _COLORVIEW_H
#define _COLORVIEW_H

#include <Button.h>
#include <Message.h>
#include <String.h>
#include <ColorControl.h>

#include "DialogView.h"

class ColorView : public DialogView {
public:
						ColorView(BRect frame, BString title, BString bstr="OK");
	virtual				~ColorView();

	virtual void		MessageReceived(BMessage* msg);
	virtual void		AttachedToWindow();

private:
	BColorControl*		fColorControl;
	BButton*			fButton;
};

#endif

