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
// Point.h - Created on 2009.09.23
//

#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>
#include <cassert>
#include "Vector.h"

class Point
{
public:
	double x, y, z;

	Point() : x(0.0), y(0.0), z(0.0) {}

	Point(const double x0, const double y0, const double z0)
		: x(x0), y(y0), z(z0) {}

	explicit Point(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Point(const Point& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	double operator[](int i) const
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			assert((i>=0) && (i<=2));
			return 0.0;
		}
	}

	//
	// Vector operations
	//

	// Check equality
	bool operator==(const Point& right) const
	{
		return (x == right.x) && (y == right.y) && (z == right.z);
	};

	// Assign
	Point& operator=(const Point& right)
	{
		if (this == &right) return *this;
		x = right.x;
		y = right.y;
		z = right.z;
		return *this;
	};

	// Addition
	const Point operator+(const Vector& right) const
	{
		return Point(x + right.x, y + right.y, z + right.z);
	};

	// Substraction
	const Point operator-(const Vector& right) const
	{
		return Point(x - right.x, y - right.y, z - right.z);
	};

	//
	// Scalar operations
	//

	// Scale
	const Point operator*(const double right) const
	{
		return Point(x*right, y*right, z*right);
	};

	// Inverse scale
	const Point operator/(const double right) const
	{
		const double inv = 1.0/right;
		return Point(x*inv, y*inv, z*inv);
	};

	// Scale
	Point& operator*=(const double right)
	{
		x *= right;
		y *= right;
		z *= right;
		return *this;
	};

	// Inverse scale
	Point& operator/=(const double right)
	{
		const double inv = 1.0/right;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	};
};

#endif /* _POINT_H_ */
