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
// Camera.h - Created on 2008.12.15
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>
#include "Ray.h"

class Camera
{
public:
	const float ASPECT_RATIO;

	Camera(const float aspectRatio) : ASPECT_RATIO(aspectRatio) {};
	virtual ~Camera() {}

	virtual std::vector<Ray> makeSampleRays(const double x, const double y) = 0;
};

#endif /* _CAMERA_H_ */
