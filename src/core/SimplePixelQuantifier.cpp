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
// SimplePixelQuantifier.cpp - Created on 2010.02.18
//

#include "SimplePixelQuantifier.h"
#include "FrameBuffer.h"

SimplePixelQuantifier::SimplePixelQuantifier(const FrameBuffer* fb)
	: PixelQuantifier(fb)
{
	// Nothing
}

SimplePixelQuantifier::~SimplePixelQuantifier()
{
	// Nothing
}

unsigned int SimplePixelQuantifier::getQuantifiedPixelAt(
										const unsigned int x,
										const unsigned int y) const
{
	Color color = m_frameBuffer->getColorAt(x,y);
	color.applyUpperLimit(1.0);

	return color.getPacketUInt();
}
