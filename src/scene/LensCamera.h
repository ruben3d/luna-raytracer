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
// LensCamera.h - Created on 2012.10.24
//

#ifndef _LENSCAMERA_H_
#define _LENSCAMERA_H_

#include "Camera.h"

class LensCamera : public Camera
{
public:
	LensCamera(const float aspectRatio, const double focusDistance, const double focusRadius);
	~LensCamera();
	std::vector<Ray> makeSampleRays(const double x, const double y);

private:
	const double m_focusDistance;
	const double m_focusRadius;

	Ray makePerfectRay(const double x, const double y);
	void applyCircularNoise(Point& p);
};

#endif /* _LENSCAMERA_H_ */
