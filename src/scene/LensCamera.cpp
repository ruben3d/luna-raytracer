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
// LensCamera.cpp - Created on 2012.10.24
//

#include "Random.h"
#include "LensCamera.h"

LensCamera::LensCamera(const float aspectRatio, const double focusDistance, const double focusRadius)
	: Camera(aspectRatio), m_focusDistance(focusDistance), m_focusRadius(focusRadius)
{
	// Nothing
}

LensCamera::~LensCamera()
{
	// Nothing
}

std::vector<Ray> LensCamera::makeSampleRays(const double x, const double y)
{
	Ray perfectRay = makePerfectRay(x,y);

	Point rayTarget = perfectRay.solve(m_focusDistance);

	Point rayOrigin(0,0,0);
	applyCircularNoise(rayOrigin);
	
	Vector rayDirection(rayTarget, rayOrigin);

	Ray ray(rayOrigin, rayDirection.normalize());

	std::vector<Ray> rays;
	rays.push_back(ray);
	return rays;
}

Ray LensCamera::makePerfectRay(const double x, const double y)
{
	Vector posY2D(0,y,0);	// Up
	Vector posX2D(x*ASPECT_RATIO,0,0);	// Right

	Vector rayDirection = posX2D + posY2D;
	rayDirection += Vector(0,0,-1.0);	// Forward

	return Ray(Point(0,0,0), rayDirection.normalize());
}

void LensCamera::applyCircularNoise(Point& p)
{
	float x, y = 0;
	
	int haltonSeq = Random::Instance().generate(256) + 64;
	do
	{
		x = Random::Instance().haltonSeq(haltonSeq,2) * 2 - 1;
		y = Random::Instance().haltonSeq(haltonSeq,3) * 2 - 1;
		haltonSeq++;
	} while ((x*x + y*y) > 1);
	
	p.x += x * m_focusRadius;
	p.y += y * m_focusRadius;
}