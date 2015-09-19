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
// Application.h - Created on 2008.12.10
//

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include "RenderProgressCallback.h"

class Display;
class Graphics2D;
class FrameBuffer;
class Core;
class Scene;
//class MultiChannelPixelQuantifier;
class SimplePixelQuantifier;


/// Abstract base class
class Application : public RenderProgressCallback
{
public:
	Application(const unsigned int width, const unsigned int height);
	void execute(const std::string& fileName, const unsigned int aaSamples);
	virtual ~Application();

	virtual void onRenderStart();
	virtual void onRenderEnd();
	virtual void onBucketStart(const Bucket& bucket);
	virtual void onBucketEnd(const Bucket& bucket);

	virtual Scene& createScene(Scene& scene, const double aspectRatio) = 0;

private:
	Display *m_display;
	Graphics2D *m_raster;
	FrameBuffer *m_frameBuffer;
	Core *m_core;
	//MultiChannelPixelQuantifier *m_quantifier;
	SimplePixelQuantifier *m_quantifier;
};

#endif /* _APPLICATION_H_ */
