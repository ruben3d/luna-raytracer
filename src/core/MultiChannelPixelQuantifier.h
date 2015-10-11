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
// MultiChannelPixelQuantifier.h - Created on 2008.12.14
//

#ifndef _MULTICHANNELPIXELQUANTIFIER_H_
#define _MULTICHANNELPIXELQUANTIFIER_H_

#include <list>
#include "PixelQuantifier.h"

class MultiChannelPixelQuantifier : public PixelQuantifier
{
public:
	MultiChannelPixelQuantifier(const FrameBuffer* fb);
	~MultiChannelPixelQuantifier();

	void addChannel(const enum PixelQuantifier::FrameBufferChannel channel);

	unsigned int getQuantifiedPixelAt(const unsigned int x,
										const unsigned int y) const;
private:
	std::list<enum PixelQuantifier::FrameBufferChannel> m_channels;
};

#endif /* _MULTICHANNELPIXELQUANTIFIER_H_ */
