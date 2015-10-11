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
// Sphere.h - Created on 2008.12.05
//

#ifndef _SPHERE_H_
#define  _SPHERE_H_

#include "Geometry.h"

class Sphere : public Geometry
{
public:
	Sphere(const double radius);

	Sphere(const Sphere& sphere) : Geometry(sphere)
	{
		m_radius = sphere.m_radius;
		m_radiusSqFixed = sphere.m_radiusSqFixed;
	}

	double getRadius() const {return m_radius;}

	// Check equality
	bool operator==(const Sphere& right) const
	{
		return (m_radius == right.m_radius);
	};

	// Assign
	Sphere& operator=(const Sphere& right)
	{
		if (this == &right) return *this;
		Geometry::operator=(right);
		m_radius = right.m_radius;
		m_radiusSqFixed = right.m_radiusSqFixed;
		return *this;
	};

	bool intersects(const Ray& ray, double& t) const;

	/// Checks if a ray intersects the sphere.
	/// \param ray	Ray to be checked for intersections.
	/// \param t	If an intersection takes place the minor t to solve the
	///				parametric equation of the ray for the intersection point is
	///				stored.
	/// \return	\b true if the ray intersects the sphere, \b false otherwise.
	bool checkIntersection(const Ray& ray, Vector& N, double& t) const;

private:
	double m_radius;
	double m_radiusSqFixed;

	/// \param point	Point on the sphere surface.
	/// \return			Normal vector at the given point.
	Vector surfaceNormalAt(const Point& point) const
	{
		return Vector(point / m_radius);
	}
};

#endif /*  _SPHERE_H_ */
