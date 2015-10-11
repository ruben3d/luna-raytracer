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
// Core.cpp - Created on 2008.12.18
//

#include <boost/thread.hpp>
#include "Core.h"
#include "RenderTask.h"
#include "RenderProgressCallback.h"
#include "BucketOrder.h"

Core::Core(BucketOrder *order)
	: m_order(order), m_primaryRaysCount(0), m_secondaryRaysCount(0)
{
	// Nothing
}

Core::~Core()
{
	if (m_order)
	{
		delete m_order;
	}
}

void Core::render(FrameBuffer* frameBuffer, const Scene* scene, const unsigned int maxDepth,
				  const unsigned int aaSamples, const unsigned int jobs, RenderProgressCallback* callback)
{
	if (callback) callback->onRenderStart();

	unsigned int taskCount = 0;
	if (jobs == Core::JOBS_AUTO)
	{
		taskCount = boost::thread::hardware_concurrency();
		if (taskCount == 0)
		{
			taskCount = 1;
		}
	}
	else
	{
		taskCount = jobs;
	}

	boost::thread_group tasks;
	for (unsigned int i=0; i<taskCount; i++)
	{
		tasks.add_thread(new boost::thread(
					RenderTask(m_order, scene, frameBuffer, aaSamples), maxDepth, callback));
	}

	tasks.join_all();

	if (callback) callback->onRenderEnd();

	//m_secondaryRaysCount += rt->getSecondaryRaysCount();
}
