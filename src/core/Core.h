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
// Core.h - Created on 2008.12.18
//

#ifndef _CORE_H_
#define _CORE_H_

#include <cstdlib>

class FrameBuffer;
class Scene;
class RenderProgressCallback;
class BucketOrder;

class Core
{
public:
	enum {JOBS_AUTO = 0};

	Core(BucketOrder *order);
	~Core();

	void render(FrameBuffer* frameBuffer, const Scene* scene, const unsigned int maxDepth,
				const unsigned int aaSamples, const unsigned int jobs = JOBS_AUTO,
				RenderProgressCallback* callback = NULL);

	unsigned int getPrimaryRaysCount() const {return m_primaryRaysCount;}
	unsigned int getSecondaryRaysCount() const {return m_secondaryRaysCount;}

private:
	BucketOrder *m_order;
	unsigned int m_primaryRaysCount;
	unsigned int m_secondaryRaysCount;
};

#endif /* _CORE_H_ */
