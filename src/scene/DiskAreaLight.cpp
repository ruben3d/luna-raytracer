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
// DiskAreaLight.cpp - Created on 2010.02.21
//

#include <cmath>
#include <string>
#include <boost/lexical_cast.hpp>
#include "DiskAreaLight.h"
#include "Object.h"
#include "Polar3.h"
#include "Random.h"
#include "Ray.h"
#include "Disk.h"
#include "Material.h"

unsigned int DiskAreaLight::GlobalCounter = 0;

DiskAreaLight::DiskAreaLight(const Transform& tr, const double intensity, const double exponent, const Color& color,
								const double radius, const bool show, const Attenuation attenuation)
		: Light(tr, intensity, color), LightHasPosition(tr(Point(0,0,0))), LightHasAttenuation(attenuation),
		LightHasGeometry(show), LightHasDirection(tr(Vector(0,0,1)),exponent), m_radius(radius),
		m_radiusSq(radius*radius), m_minSamples(16), m_maxSamples(32)
{
	Light::addAttribute(LightHasPosition::ATTRIBUTE);
	Light::addAttribute(LightHasDirection::ATTRIBUTE);
	Light::addAttribute(LightHasAttenuation::ATTRIBUTE);
	Light::addAttribute(LightHasGeometry::ATTRIBUTE);

	m_id = ++GlobalCounter;
}

bool DiskAreaLight::computeSample(const Point& P, const std::list<Object*>& objects, unsigned int& haltonSeq,
									Color& I, Vector& L) const
{
	// Point at the light surface
	Point LP(0,0,0);

	// Generates a random sample.
	do
	{
		haltonSeq++;
		LP.x = Random::Instance().haltonSeq(haltonSeq,2)*m_radius;
		LP.y = Random::Instance().haltonSeq(haltonSeq,3)*m_radius;
	}
	while ((LP.x*LP.x + LP.y*LP.y)>m_radiusSq);

	// Ray from point of intersection to light surface
	L = LP - P;
	const double lightRayLength = L.length();
	L = L.normalize();
	Ray lightRay = T(Ray(P, L));	// <- Local to World
	lightRay.tmax = lightRayLength;

	// Test if the light ray is obstructed
	bool obstructed = false;
	std::list<Object*>::const_iterator obj;
	for (obj = objects.begin(); obj != objects.end(); obj++)
	{
		if (!(*obj)->castShadow()) continue;

		double t;
		const Ray lightRayT = (*obj)->T.applyInv(lightRay);	// World to object
		bool intersects = (*obj)->getGeometry()->intersects(lightRayT,t);
		if (intersects)
		{
			obstructed = true;
			break;
		}
	}

	I = obstructed ? Color(0,0,0) : getColor()*getIntensity()*getAttFactor(lightRayLength);
	return obstructed;
}

void DiskAreaLight::computeIntensity(const Vector&, const Point& P,
							const std::list<Object*>& objects,
							std::list<Color>& Is, std::list<Vector>& Ls) const
{
	if (getDirection().dot(P-getPosition()) <= 0.0) return;	// The normal is not facing the P.

	bool penumbra = false;
	unsigned int haltonSeq = Random::Instance().generate(1024);

	Point tP = T.applyInv(P); // World to local
	Color I;
	Vector L;
	bool shadow = computeSample(tP,objects,haltonSeq,I,L);
	Is.push_back(I);
	Ls.push_back(T(L));	// Local to world

	for (int i=1; i<m_minSamples; i++)
	{
		Color I;
		Vector L;
		bool blocked = computeSample(tP,objects,haltonSeq,I,L);
		Is.push_back(I);
		Ls.push_back(T(L));	// Local to world

		if (blocked != shadow) penumbra = true;
	}

	if (penumbra)
	{
		for (int n=0; n<m_maxSamples; n++)
		{
			Color I;
			Vector L;
			computeSample(tP,objects,haltonSeq,I,L);
			Is.push_back(I);
			Ls.push_back(T(L));	// Local to world
		}
	}
}

Geometry* DiskAreaLight::getGeometry() const
{
	return new Disk(m_radius);
}

Material* DiskAreaLight::getMaterial() const
{
	Material *m = new Material(std::string("_dal_")+boost::lexical_cast<std::string>(m_id), getColor());
	m->setEmission(getIntensity());
	m->setSpecularIntensity(0.0);
	m->setSpecularGlossiness(0.0);
	return m;
}
