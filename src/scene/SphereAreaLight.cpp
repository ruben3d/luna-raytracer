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
// SphereAreaLight.cpp - Created on 2009.01.15
//

#include <cmath>
#include <string>
#include <boost/lexical_cast.hpp>
#include "SphereAreaLight.h"
#include "Object.h"
#include "Polar3.h"
#include "Random.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"

unsigned int SphereAreaLight::GlobalCounter = 0;

SphereAreaLight::SphereAreaLight(const Transform& tr, const double intensity, const Color& color,
								const double radius, const bool show, const Attenuation attenuation)
	: Light(tr, intensity, color), LightHasPosition(tr(Point(0,0,0))),
		LightHasAttenuation(attenuation), LightHasGeometry(show), m_radius(radius),
		m_minSamples(16), m_maxSamples(32)
{
	Light::addAttribute(LightHasPosition::ATTRIBUTE);
	Light::addAttribute(LightHasAttenuation::ATTRIBUTE);
	Light::addAttribute(LightHasGeometry::ATTRIBUTE);

	m_id = ++GlobalCounter;
}

bool SphereAreaLight::computeSample(const Point& P, const Vector& N,
							const std::list<Object*>& objects,
							unsigned int& haltonSeq,
							Color& I, Vector& L) const
{
	// Light surface normal at sample point
	Vector LN;

	// Generates a random sample. We don't want a sample facing away
	do
	{
		haltonSeq++;
		double rotPhi = acos(Random::Instance().haltonSeq(haltonSeq,2)*2-1);
		double rotTheta = Random::Instance().haltonSeq(haltonSeq,3)*PI*2;
		Polar3 p(1,rotPhi,rotTheta);
		LN=p;
	}
	while (N.dot(LN) <= 0);

	// Point at the light surface
	Point LP = /*getPosition() +*/ Point(LN * m_radius);

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

	I = obstructed ? Color(0,0,0) : getColor()*getIntensity()*getAttFactor(lightRayLength)*L.dot(LN);
	return obstructed;
}

void SphereAreaLight::computeIntensity(const Vector& N, const Point& P,
							const std::list<Object*>& objects,
							std::list<Color>& Is, std::list<Vector>& Ls) const
{
	bool penumbra = false;
	unsigned int haltonSeq = Random::Instance().generate(1024);

	Vector tN = T.applyInv(N);	// World to local
	Point tP = T.applyInv(P);
	Color I;
	Vector L;
	bool shadow = computeSample(tP,tN,objects,haltonSeq,I,L);
	Is.push_back(I);
	Ls.push_back(T(L));	// Local to world

	for (int i=1; i<m_minSamples; i++)
	{
		Color I;
		Vector L;
		bool blocked = computeSample(tP,tN,objects,haltonSeq,I,L);
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
			computeSample(tP,tN,objects,haltonSeq,I,L);
			Is.push_back(I);
			Ls.push_back(T(L));	// Local to world
		}
	}
}

Geometry* SphereAreaLight::getGeometry() const
{
	return new Sphere(m_radius);
}

Material* SphereAreaLight::getMaterial() const
{
	Material *m = new Material(std::string("_sal_")+boost::lexical_cast<std::string>(m_id), getColor());
	m->setEmission(getIntensity());
	m->setSpecularIntensity(0.0);
	m->setSpecularGlossiness(0.0);
	return m;
}
