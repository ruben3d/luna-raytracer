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
// Ray.h - Created on 2008.12.05
//

#ifndef _RAY_H_
#define _RAY_H_

#include "Vector.h"
#include "Point.h"

class Ray
{
public:
	static const double default_tmin;
	static const double default_tmax;

	Point o;		///< Origin
	Vector d;		///< Direction
	double tmin;	///< Near clip (to avoid precision problems at intersections).
	double tmax;	///< Far clip

	Ray(const Point& origin, const Vector& direction)
		: o(origin), d(direction), tmin(default_tmin), tmax(default_tmax) {}
	Ray(const Ray& ray)
	{
		o = ray.o;
		d = ray.d;
		tmin = ray.tmin;
		tmax = ray.tmax;
	}

	const Point& getOrigin() const {return o;}
	const Vector& getDirection() const {return d;}

	// Assign
	Ray& operator=(const Ray& ray)
	{
		if (this == &ray) return *this;
		o = ray.o;
		d = ray.d;
		tmin = ray.tmin;
		tmax = ray.tmax;
		return *this;
	}

	Point solve(const double t) const
	{
		return o + (d * t);
	}

	Point operator()(const double t) const
	{
		return solve(t);
	}
};

#endif /* _RAY_H_ */
