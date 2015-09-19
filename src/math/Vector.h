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
// Vector.h - Created on 2008.12.05
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <cassert>

class Point;
class Polar3;

class Vector
{
public:
	double x, y, z;

	Vector() : x(0.0), y(0.0), z(0.0) {}

	Vector(const double x0, const double y0, const double z0)
		: x(x0), y(y0), z(z0) {}

	explicit Vector(const Point& p);

	Vector(const Vector& v)
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

	/// Vector pointing from p0 to p1.
	Vector(const Point& p1, const Point& p0);

	Vector(const Polar3& p);

	// Magnitude
	double lengthSq() const {return x*x + y*y + z*z;}
	double length() const {return sqrt(lengthSq());}

	// Unit vector
	Vector normalize() const
	{
		return Vector(*this) *= (1.0/this->length());
	}

	// Dot product
	double dot(const Vector& v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	// Cross product
	const Vector cross(const Vector& v) const
	{
		double vx = y * v.z - z * v.y;
		double vy = z * v.x - x * v.z;
		double vz = x * v.y - y * v.x;
		return Vector(vx,vy,vz);
	}

	// Mirror
	Vector mirrorOn(const Vector& mirror) const
	{
		return mirror * 2 * mirror.dot(*this) - *this;
	}

	//
	// Vector operations
	//

	// Check equality
	bool operator==(const Vector& right) const
	{
		return (x == right.x) && (y == right.y) && (z == right.z);
	};

	// Inverse vector
	Vector operator-() const
	{
		return Vector(-x,-y,-z);
	};

	// Assign
	Vector& operator=(const Vector& right)
	{
		if (this == &right) return *this;
		x = right.x;
		y = right.y;
		z = right.z;
		return *this;
	};

	// Addition
	const Vector operator+(const Vector& right) const
	{
		return Vector(x + right.x, y + right.y, z + right.z);
	};

	// Substraction
	const Vector operator-(const Vector& right) const
	{
		return Vector(x - right.x, y - right.y, z - right.z);
	};

	// Addition
	Vector& operator+=(const Vector& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	};

	// Substraction
	Vector& operator-=(const Vector& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	};

	//
	// Scalar operations
	//

	// Scale
	const Vector operator*(const double right) const
	{
		return Vector(x*right, y*right, z*right);
	};

	// Inverse scale
	const Vector operator/(const double right) const
	{
		const double inv = 1.0/right;
		return Vector(x*inv, y*inv, z*inv);
	};

	// Scale
	Vector& operator*=(const double right)
	{
		x *= right;
		y *= right;
		z *= right;
		return *this;
	};

	// Inverse scale
	Vector& operator/=(const double right)
	{
		const double inv = 1.0/right;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	};
};

inline Vector operator-(const Point& p1, const Point& p0)
{
	return Vector(p1,p0);
}

#endif /* _VECTOR_H_ */
