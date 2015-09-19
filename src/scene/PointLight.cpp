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
// PointLight.cpp - Created on 2008.12.14
//

#include "PointLight.h"
#include "Ray.h"
#include "Object.h"

PointLight::PointLight(const Transform& tr, const double intensity, const Color& color,
						const Attenuation attenuation)
	: Light(tr, intensity,color), LightHasPosition(tr(Point(0,0,0))),
		LightHasAttenuation(attenuation)
{
	Light::addAttribute(LightHasPosition::ATTRIBUTE);
	Light::addAttribute(LightHasAttenuation::ATTRIBUTE);
}

void PointLight::computeIntensity(const Vector&, const Point& P,
							const std::list<Object*>& objects,
							std::list<Color>& Is, std::list<Vector>& Ls) const
{
	// Ray from point of intersection to light
	Vector L = T(Point(0,0,0))-P;	// We are working with world coordinates
	const double lightRayLength = L.length();
	L = L.normalize();
	Ray lightRay(P, L);
	lightRay.tmax = lightRayLength;

	// Test if the light ray is obstructed
	bool obstructed = false;
	std::list<Object*>::const_iterator obj;
	for (obj = objects.begin(); obj != objects.end(); obj++)
	{
		if (!(*obj)->castShadow()) continue;
		double t;
		const Ray lightRayT = (*obj)->T.applyInv(lightRay);
		bool intersects = (*obj)->getGeometry()->intersects(lightRayT,t);
		if (intersects)
		{
			obstructed = true;
			break;
		}
	}

	Is.push_back(obstructed
					?
					Color(0,0,0)
					:
					getColor()*getIntensity()*getAttFactor(lightRayLength)
				);
	Ls.push_back(L);
}
