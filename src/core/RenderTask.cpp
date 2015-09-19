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
// RenderTask.cpp - Created on 2009.01.15
//

#include <boost/thread.hpp>
#include "RenderTask.h"
#include "Raytracer.h"
#include "RenderProgressCallback.h"
#include "Bucket.h"
#include "Scene.h"
#include "BucketOrder.h"
#include "Camera.h"
#include "CameraMount.h"
#include "Random.h"
#include "FrameBuffer.h"

#define GAMMA(color, gamma) (pow((color),1.0/(gamma)))

boost::mutex mutexCallback;
boost::mutex mutexBuckets;

void RenderTask::operator()(const unsigned int depth, RenderProgressCallback* callback)
{
	double pixelWidth = 1.0/m_frameBuffer->getWidth();
	double pixelHeight = 1.0/m_frameBuffer->getHeight();

	Raytracer* rt = new Raytracer(m_scene);

	mutexBuckets.lock();
		Bucket bucket = m_order->getNextBucket();
	mutexBuckets.unlock();

	while (bucket != Bucket::INVALID)
	{
		if (callback)
		{
			mutexCallback.lock();
				callback->onBucketStart(bucket);
			mutexCallback.unlock();
		}

		for (unsigned int y=bucket.y0; y<=bucket.yd; y++)
		{
		for (unsigned int x=bucket.x0; x<=bucket.xd; x++)
		{
			Color rawColor(0,0,0);

			Camera* camera = m_scene->getCameraMount()->getCamera();
			double normX = XScreenToViewPlane(x);
			double normY = YScreenToViewPlane(y);

			unsigned int haltonSeq = 0/*Random::Instance().generate(256)*/;
			for (unsigned int i=1; i<=m_aaSamples; i++)
			{
				haltonSeq++;
				std::vector<Ray> rays = camera->makeSampleRays(
					normX+Random::Instance().haltonSeq(haltonSeq,2)*pixelWidth-pixelWidth*0.5,
					normY+Random::Instance().haltonSeq(haltonSeq,3)*pixelHeight-pixelHeight*0.5);
				for (unsigned int r=0; r<rays.size(); r++)
				{
					//m_primaryRaysCount++;
					rays[r] = m_scene->getCameraMount()->T(rays[r]);	// Local to World
					double distance;
					rawColor += rt->traceRay(rays[r], depth, distance) * (1.0/(double)rays.size());
				}
			}
			rawColor.r /= (double)m_aaSamples;
			rawColor.g /= (double)m_aaSamples;
			rawColor.b /= (double)m_aaSamples;

			rawColor.r = GAMMA(rawColor.r, 2.2);
			rawColor.g = GAMMA(rawColor.g, 2.2);
			rawColor.b = GAMMA(rawColor.b, 2.2);
			m_frameBuffer->setColorAt(x,y, rawColor);
		}
		}

		if (callback)
		{
			mutexCallback.lock();
				callback->onBucketEnd(bucket);
			mutexCallback.unlock();
		}

		mutexBuckets.lock();
			bucket = m_order->getNextBucket();
		mutexBuckets.unlock();
	}

	delete rt;
}

double RenderTask::XScreenToViewPlane(const double x) const
{
	double width = m_frameBuffer->getWidth();
	return ((x+0.5) - (double)width / 2.0) / (double)width;
}

double RenderTask::YScreenToViewPlane(const double y) const
{
	double height = m_frameBuffer->getHeight();
	return (((double)(height-1) - (y+0.5)) - (double)height / 2.0) /
			(double)height;
}
