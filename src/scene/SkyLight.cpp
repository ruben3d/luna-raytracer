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
// SkyLight.cpp - Created on 2008.12.23
//

#include <cmath>

#include "SkyLight.h"
#include "Object.h"
#include "Polar3.h"
#include "Random.h"
#include "Ray.h"

SkyLight::SkyLight(const double intensity, const Color& color)
	: Light(Transform::Identity(), intensity, color),m_minSamples(16),m_maxSamples(32),m_threshold(0.0)
{
	// Nothing
}

void SkyLight::computeIntensity(const Vector& N, const Point& P,
						const std::list<Object*>& objects, std::list<Color>& I,
						std::list<Vector>&) const
{
	double localIntensity = computeDirectSkyLightIntensity(P,N,objects);
	I.push_back(getColor()*getIntensity()*localIntensity);
}

double SkyLight::computeSkyLightSample(const Point& P, const Vector& N,
										unsigned int& haltonSeq,
										const std::list<Object*>& objects) const
{
	Vector v3;
	do
	{
		haltonSeq++;
		//double rotPhi = acos(Random::Instance().generate()*2-1);
		//double rotTheta = Random::Instance().generate()*PI*2;
		double rotPhi = acos(Random::Instance().haltonSeq(haltonSeq,2)*2-1);
		double rotTheta = Random::Instance().haltonSeq(haltonSeq,3)*PI*2;
		Polar3 p(1,rotPhi,rotTheta);
		v3=p;
	}
	while (N.dot(v3) <= 0);

	// Ray from point of intersection to infinity (Ray::default_tmax)
	Ray lightRay(P, v3);

	// Test if the light ray is obstructed
	std::list<Object*>::const_iterator obj;
	for (obj = objects.begin(); obj != objects.end(); obj++)
	{
		if (!(*obj)->castShadow()) continue;

		double t;

		const Ray lightRayT = (*obj)->T.applyInv(lightRay);
		bool intersects = (*obj)->getGeometry()->intersects(lightRayT,t);

		if (intersects)
		{
			return 0.0;
		}
	}
	return 1.0;
}

double SkyLight::computeDirectSkyLightIntensity(const Point& P,
					const Vector& N, const std::list<Object*>& objects) const
{
	double localIntensity = 0.0;
	unsigned int haltonSeq = Random::Instance().generate(1024);

	for (unsigned int i=0; i<m_minSamples; i++)
	{
		localIntensity += computeSkyLightSample(P,N,haltonSeq,objects);
	}

	unsigned int samples = m_minSamples;

	unsigned int adaptiveStep = (m_maxSamples/m_minSamples) * 2;

	double prev = localIntensity / (double)samples;
	bool keep = true;
	while (keep && (samples < m_maxSamples))
	{
		for (unsigned int i=0; i<adaptiveStep; i++)
		{
			localIntensity += computeSkyLightSample(P,N,haltonSeq,objects);
			samples++;
		}

		double current = localIntensity / (double)samples;
		if (fabs(current-prev)<m_threshold)
		{
			keep = false;
		}

		prev = current;
	}

	return localIntensity/(double)samples;
}
