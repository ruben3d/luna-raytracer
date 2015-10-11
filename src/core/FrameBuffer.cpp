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
// FrameBuffer.cpp - Created on 2008.12.08
//

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const unsigned int width, const unsigned int height,
							const bool hasZBuffer)
	: m_width(width), m_height(height), m_zbuffer(0)
{
	m_color = new Color[width * height];
	if (hasZBuffer)
	{
		m_zbuffer = new double[width * height];
	}
}

FrameBuffer::~FrameBuffer()
{
	if (m_zbuffer != 0) delete[] m_zbuffer;
	delete[] m_color;
}

bool FrameBuffer::hasZBuffer() const
{
	return (m_zbuffer != 0);
}

void FrameBuffer::setColorAt(const unsigned int x, const unsigned int y,
								const Color& color)
{
	m_color[x+y*m_width] = color;
}

void FrameBuffer::setZValueAt(const unsigned int x, const unsigned int y,
								const double zvalue)
{
	m_zbuffer[x+y*m_width] = zvalue;
}

const Color& FrameBuffer::getColorAt(const unsigned int x,
										const unsigned int y) const
{
	return m_color[x+y*m_width];
}

double FrameBuffer::getZValueAt(const unsigned int x,
										const unsigned int y) const
{
	return m_zbuffer[x+y*m_width];
}
