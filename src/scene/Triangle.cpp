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
// Triangle.cpp - Created on 2008.12.24
//

#include "Triangle.h"
#include "Ray.h"
/*
Vector Triangle::surfaceNormalAt(const Point&) const
{
	Vector N = (m_v1-m_v0).cross(m_v2-m_v0);
	return N.normalize();
}
*/

bool Triangle::intersects(const Ray& ray, double& t) const
{
	if (!box.intersects(ray)) return false;

	// Ray-triangle plane intersection

	double denominator = ray.d.dot(m_normal);
	if (denominator == 0) return false;

	double numerator = (ray.o - m_v0).dot(m_normal);

	double distance = - numerator/denominator;
	if ((distance < ray.tmin) || (ray.tmax < distance)) return false;

	// Point of intersection
	Point P = ray(distance);

	// Check if P in in the triangle
	if ( ((m_v1-m_v0).cross(P-m_v0)).dot(m_normal) < 0) return false;
	if ( ((m_v2-m_v1).cross(P-m_v1)).dot(m_normal) < 0) return false;
	if ( ((m_v0-m_v2).cross(P-m_v2)).dot(m_normal) < 0) return false;

	t = distance;

	return true;
}

bool Triangle::checkIntersection(const Ray& ray, Vector& N, double& t) const
{
	if (!box.intersects(ray)) return false;

	// Ray-triangle plane intersection

	double denominator = ray.d.dot(m_normal);
	if (denominator == 0) return false;

	double numerator = (ray.o - m_v0).dot(m_normal);

	double distance = - numerator/denominator;
	if ((distance < ray.tmin) || (ray.tmax < distance)) return false;

	// Point of intersection
	Point P = ray(distance);

	// Check if P in in the triangle
	if ( ((m_v1-m_v0).cross(P-m_v0)).dot(m_normal) < 0) return false;
	if ( ((m_v2-m_v1).cross(P-m_v1)).dot(m_normal) < 0) return false;
	if ( ((m_v0-m_v2).cross(P-m_v2)).dot(m_normal) < 0) return false;

	N = m_normal;
	t = distance;

	return true;
}
