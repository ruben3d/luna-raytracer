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
// RenderProgressCallback.h - Created 2008.12.10
//

#ifndef _RENDERPROGRESSCALLBACK_H_
#define _RENDERPROGRESSCALLBACK_H_

#include "Bucket.h"

class RenderProgressCallback
{
public:
	virtual void onRenderStart() = 0;
	virtual void onRenderEnd() = 0;
	virtual void onBucketStart(const Bucket& bucket) = 0;
	virtual void onBucketEnd(const Bucket& bucket) = 0;
protected:
	virtual ~RenderProgressCallback(){}
};

#endif /* _RENDERPROGRESSCALLBACK_H_ */
