/*
   Copyright 2015 Ruben Moreno Montoliu <ruben3d at gmail dot com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//
// Display.h - Created on 2008.12.05
//

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

struct DisplayStruct;

class Display
{
public:
	Display(const unsigned int width, const unsigned int height);
	~Display();

	unsigned int *getBackBuffer();
	void swapBuffers();
	void swapBuffers(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1);
private:
	DisplayStruct* display;
};

#endif /* _DISPLAY_H_ */
