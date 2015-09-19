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
// MultiChannelPixelQuantifier.cpp - Created on 2008.12.14
//

#include "MultiChannelPixelQuantifier.h"
#include "FrameBuffer.h"

MultiChannelPixelQuantifier::MultiChannelPixelQuantifier(const FrameBuffer* fb)
	: PixelQuantifier(fb)
{
	// Nothing
}

MultiChannelPixelQuantifier::~MultiChannelPixelQuantifier()
{
	// Nothing
}

void MultiChannelPixelQuantifier::addChannel(
						const enum PixelQuantifier::FrameBufferChannel channel)
{
	m_channels.push_back(channel);
}

unsigned int MultiChannelPixelQuantifier::getQuantifiedPixelAt(
										const unsigned int x,
										const unsigned int y) const
{
	unsigned int pixel = 0;
	std::list<enum PixelQuantifier::FrameBufferChannel>::const_iterator it;
	for (it = m_channels.begin(); it != m_channels.end(); it++)
	{
		if (*it == PixelQuantifier::CHANNEL_Z)
		{
			// TODO
		}
		else
		{
			Color color = m_frameBuffer->getColorAt(x,y);
			color.applyUpperLimit(1.0);
	
			if (*it == PixelQuantifier::CHANNEL_R)
			{
				if (it != m_channels.begin()) pixel = (pixel<<8)&0xFFFFFF00;
				pixel |= (unsigned char) (255*color.r+0.5);
			}
			else if (*it == PixelQuantifier::CHANNEL_G)
			{
				if (it != m_channels.begin()) pixel = (pixel<<8)&0xFFFFFF00;
				pixel |= (unsigned char) (255*color.g+0.5);
			}
			else if (*it == PixelQuantifier::CHANNEL_B)
			{
				if (it != m_channels.begin()) pixel = (pixel<<8)&0xFFFFFF00;
				pixel |= (unsigned char) (255*color.b+0.5);
			}
			else if (*it == PixelQuantifier::CHANNEL_A)
			{
				if (it != m_channels.begin()) pixel = (pixel<<8)&0xFFFFFF00;
				pixel |= (unsigned char) (255);
			}
		}
	}
	return pixel;
}
