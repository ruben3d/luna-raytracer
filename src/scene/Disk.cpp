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
// Disk.cpp - Created on 2010.02.16
//

#include "Disk.h"
#include "Ray.h"

bool Disk::intersects(const Ray& ray, double& t) const
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
		// The ray interesects the plane but... does it intersect close enough to the disk center?
		Point p = ray(t);
		if ((p.x*p.x + p.y*p.y + p.z*p.z) <= m_radiusSq)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else	// Es una semirrecta, no una recta
	{
		return false;
	}
}

bool Disk::checkIntersection(const Ray& ray, Vector& N, double& t) const
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
		// The ray interesects the plane but... does it intersect close enough to the disk center?
		Point p = ray(t);
		if ((p.x*p.x + p.y*p.y + p.z*p.z) <= m_radiusSq)
		{
			N = Vector(0,0,1);
			return true;
		}
		else
		{
			return false;
		}
	}
	else	// Es una semirrecta, no una recta
	{
		return false;
	}
}
