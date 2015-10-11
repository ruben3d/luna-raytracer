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
// FrameBuffer.h - Created on 2008.12.08
//

#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "Color.h"

class FrameBuffer
{
public:
	FrameBuffer(const unsigned int width, const unsigned int height,
				const bool hasZBuffer = false);
	~FrameBuffer();

	bool hasZBuffer() const;
	unsigned int getWidth() const {return m_width;}
	unsigned int getHeight() const {return m_height;}

	void setColorAt(const unsigned int x, const unsigned int y,
					const Color& color);
	void setZValueAt(const unsigned int x, const unsigned int y,
						const double zvalue);

	const Color& getColorAt(const unsigned int x, const unsigned int y) const;
	double getZValueAt(const unsigned int x, const unsigned int y) const;

private:
	const unsigned int m_width, m_height;
	Color *m_color;
	double *m_zbuffer;
};

#endif /* _FRAMEBUFFER_H_ */
