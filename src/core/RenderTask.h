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
// RenderTask.h - Created on 2009.01.15
//

#ifndef _RENDERTASK_H_
#define _RENDERTASK_H_

class RenderProgressCallback;
class Scene;
class FrameBuffer;
class BucketOrder;

class RenderTask
{
public:
	RenderTask(BucketOrder *order, const Scene *scene, FrameBuffer* frameBuffer, const unsigned int aaSamples)
		: m_order(order), m_scene(scene), m_frameBuffer(frameBuffer), m_aaSamples(aaSamples) {};
	void operator()(const unsigned int depth, RenderProgressCallback* callback);

private:
	BucketOrder *m_order;
	const Scene *m_scene;
	FrameBuffer *m_frameBuffer;
	const unsigned int m_aaSamples;

	double XScreenToViewPlane(const double x) const;
	double YScreenToViewPlane(const double y) const;
};

#endif /* _RENDERTASK_H_ */
