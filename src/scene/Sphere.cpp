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
// Sphere.cpp - Created on 2008.12.06
//

#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(const double radius)
	: Geometry(AABBox(Point(-radius,-radius,-radius), Point(radius,radius,radius))), m_radius(radius)
{
	m_radiusSqFixed = (m_radius-Ray::default_tmin)*(m_radius-Ray::default_tmin);
}

bool Sphere::intersects(const Ray& ray, double& t) const
{
/* This works fine but... no t value :(
	// If the ray points away from the sphere...
	if (ray.getDirection().dot(Vector(ray.getOrigin())) >= 0)
	{
		// Maybe the origin lays betgeen the center and the surface
		if (Vector(ray.getOrigin()).lengthSq() < m_radiusSqFixed)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// The sphere is in front of the ray
	Vector R = ray.getDirection().cross(Vector(ray.getOrigin()));
	if (R.lengthSq() < m_radiusSqFixed)
	{
		return true;
	}
	else
	{
		return false;
	}
*/
	//if (!box.intersects(ray)) return false;

	Vector vO(ray.o);
	double b = 2 * ray.d.dot(vO);
	double c = vO.lengthSq() - m_radius*m_radius;

	double rootArg = b*b - 4*c;
	if (rootArg < 0)
	{
		return false;
	}
	else if (rootArg == 0)
	{
		t = (-b)/2.0f;
		if ((t > ray.tmin) && (t < ray.tmin))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		double root = sqrt(rootArg);
		double t1 = (-b+root)/2.0;
		double t2 = (-b-root)/2.0;
		if ((ray.tmin < t1) && (t1 < ray.tmax) && 
			(ray.tmin < t2) && (t2 < ray.tmax))
		{
			t = (t1 < t2) ? t1 : t2;
			return true;
		}
		else if ((ray.tmin < t1) && (t1 < ray.tmax))
		{
			t = t1;
			return true;
		}
		else if ((ray.tmin < t2) && (t2 < ray.tmax))
		{
			t = t2;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Sphere::checkIntersection(const Ray& ray, Vector& N, double& t) const
{
	if (!box.intersects(ray)) return false;

	Vector vO(ray.o);
	double b = 2 * ray.d.dot(vO);
	double c = vO.lengthSq() - m_radius*m_radius;

	double rootArg = b*b - 4*c;
	if (rootArg < 0)
	{
		return false;
	}
	else if (rootArg == 0)
	{
		t = (-b)/2.0f;
		if ((t > ray.tmin) && (t < ray.tmin))
		{
			N = surfaceNormalAt(ray(t));
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		double root = sqrt(rootArg);
		double t1 = (-b+root)/2.0;
		double t2 = (-b-root)/2.0;
		if ((ray.tmin < t1) && (t1 < ray.tmax) && 
			(ray.tmin < t2) && (t2 < ray.tmax))
		{
			t = (t1 < t2) ? t1 : t2;
			N = surfaceNormalAt(ray(t));
			return true;
		}
		else if ((ray.tmin < t1) && (t1 < ray.tmax))
		{
			t = t1;
			N = surfaceNormalAt(ray(t));
			return true;
		}
		else if ((ray.tmin < t2) && (t2 < ray.tmax))
		{
			t = t2;
			N = surfaceNormalAt(ray(t));
			return true;
		}
		else
		{
			return false;
		}
	}
}
