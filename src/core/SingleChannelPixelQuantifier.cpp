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
// SingleChannelPixelQuantifier.cpp - Created on 2008.12.14
//

#include "SingleChannelPixelQuantifier.h"
#include "FrameBuffer.h"

SingleChannelPixelQuantifier::SingleChannelPixelQuantifier(
						const FrameBuffer* fb,
						const enum PixelQuantifier::FrameBufferChannel channel)
	: PixelQuantifier(fb), m_channel(channel)
{
	// Nothing
}

SingleChannelPixelQuantifier::~SingleChannelPixelQuantifier()
{
	// Nothing
}

unsigned int SingleChannelPixelQuantifier::getQuantifiedPixelAt(
											const unsigned int x,
											const unsigned int y) const
{
	unsigned int pixel = 0;
	if (m_channel == PixelQuantifier::CHANNEL_Z)
	{
		// TODO
	}
	else
	{
		Color color = m_frameBuffer->getColorAt(x,y);
		color.applyUpperLimit(1.0);

		if (m_channel == PixelQuantifier::CHANNEL_R)
		{
			pixel = COLOR(	(unsigned char) (255),
							(unsigned char) (255*color.r+0.5),
							(unsigned char) (255*color.r+0.5),
							(unsigned char) (255*color.r+0.5));
		}
		else if (m_channel == PixelQuantifier::CHANNEL_G)
		{
			pixel = COLOR(	(unsigned char) (255),
							(unsigned char) (255*color.g+0.5),
							(unsigned char) (255*color.g+0.5),
							(unsigned char) (255*color.g+0.5));
		}
		else if (m_channel == PixelQuantifier::CHANNEL_B)
		{
			pixel = COLOR(	(unsigned char) (255),
							(unsigned char) (255*color.b+0.5),
							(unsigned char) (255*color.b+0.5),
							(unsigned char) (255*color.b+0.5));
		}
		else if (m_channel == PixelQuantifier::CHANNEL_A)
		{
			pixel = COLOR(	(unsigned char) (255),
							(unsigned char) (255),
							(unsigned char) (255),
							(unsigned char) (255));
		}
	}
	return pixel;
}
