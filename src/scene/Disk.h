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
// Disk.h - Created on 2010.02.16
//

#ifndef _DISK_H_
#define _DISK_H_

#include "Geometry.h"

// The disk is centered at the origin with the normal pointing +z.

class Disk : public Geometry
{
public:
	Disk(const double radius)
		: Geometry(AABBox(Point(-radius,-radius,0.0), Point(radius,radius,0.0))),
		m_radius(radius), m_radiusSq(radius*radius) {}
	Disk(const Disk& d) : Geometry(d)
	{
		m_radius = d.m_radius;
		m_radiusSq = d.m_radiusSq;
	}

	double getRadius() const {return m_radius;}
	// Assign
	Disk& operator=(const Disk& d)
	{
		Geometry::operator=(d);
		m_radius = d.m_radius;
		m_radiusSq = d.m_radiusSq;
		return *this;
	};

	bool intersects(const Ray& ray, double& t) const;
	bool checkIntersection(const Ray& ray, Vector& N, double& t) const;

private:
	double m_radius;
	double m_radiusSq;
};

#endif /* _DISK_H_ */
