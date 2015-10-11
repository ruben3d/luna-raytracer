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
// Plane.cpp - Created on 2008.12.06
//

#include <cmath>
#include <limits>
#include "Plane.h"
#include "Ray.h"

Plane::Plane()
	: Geometry(AABBox(	Point(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), 0),
						Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), 0)))
{
	// Nothing
}

Plane::Plane(const Plane& p) : Geometry(p)
{
	//Nothing
}

bool Plane::intersects(const Ray& ray, double& t) const
{
	double denominator = ray.d.z;

	if (denominator == 0)
	{
		return false;
	}

	double numerator = -ray.o.z;

	t = numerator / denominator;
	if ((t > ray.tmin) && (t < ray.tmax))
	{
		return true;
	}
	else	// Es una semirrecta, no una recta
	{
		return false;
	}
}

bool Plane::checkIntersection(const Ray& ray, Vector& N, double& t) const
{
	double denominator = ray.d.z;

	if (denominator == 0)
	{
		return false;
	}

	double numerator = -ray.o.z;

	double t0 = numerator / denominator;
	if ((t0 > ray.tmin) && (t0 < ray.tmax))
	{
		t = t0;
		N = Vector(0,0,1);
		return true;
	}
	else	// Es una semirrecta, no una recta
	{
		return false;
	}
}
