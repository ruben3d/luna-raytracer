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
// PixelQuantifier.h - Created on 2008.12.14
//

#ifndef _PIXELQUANTIFIER_H_
#define _PIXELQUANTIFIER_H_

class FrameBuffer;

class PixelQuantifier
{
public:
	enum FrameBufferChannel
	{
		CHANNEL_R,
		CHANNEL_G,
		CHANNEL_B,
		CHANNEL_A,
		CHANNEL_Z
	};

	PixelQuantifier(const FrameBuffer* fb) : m_frameBuffer(fb) {};
	virtual ~PixelQuantifier() {};
	virtual unsigned int getQuantifiedPixelAt(const unsigned int x,
												const unsigned int y) const=0;
protected:
	const FrameBuffer* m_frameBuffer;
};

#endif /* _PIXELQUANTIFIER_H_ */
