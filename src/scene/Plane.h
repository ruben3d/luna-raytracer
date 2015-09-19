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
// Plane.h - Created on 2008.12.05
//

#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"

// The plane is centered at the origin with the normal pointing +z.

class Plane : public Geometry
{
public:
	Plane();
	Plane(const Plane& p);

	// Assign
	Plane& operator=(const Plane&)
	{
		return *this;
	};

	bool intersects(const Ray& ray, double& t) const;
	bool checkIntersection(const Ray& ray, Vector& N, double& t) const;
};

#endif /* _PLANE_H_ */
