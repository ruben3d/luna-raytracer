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
// Geometry.h - Created on 2008.12.06
//

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Vector.h"
#include "Point.h"
#include "AABBox.h"

class Ray;

class Geometry
{
public:
	AABBox box;	///< Object space bounding box.

	Geometry(const AABBox& b) : box(b) {}
	Geometry(const Geometry& g) {box = g.box;}
	virtual ~Geometry(){}

	Geometry& operator=(const Geometry& g)
	{
		box = g.box;
		return *this;
	};

	/// Computes fast intersection.
	/// \param ray	Ray to be checked for intersections.
	/// \param t If an intersection takes place the minor t to solve the
	///			parametric equation of the ray for the intersection point is
	///			stored.
	virtual bool intersects(const Ray& ray, double& t) const = 0;

	/// \param ray	Ray to be checked for intersections.
	/// \param N	Surface normal at point of intersection.
	/// \param t	If an intersection takes place the minor t to solve the
	///				parametric equation of the ray for the intersection point is
	///				stored.
	/// \return	\b true if the ray intersects the object, \b false otherwise.
	virtual bool checkIntersection(const Ray& ray, Vector& N, double& t) const = 0;
};

#endif /* _GEOMETRY_H_ */
