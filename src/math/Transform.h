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
// Transform.h - Created on 2010.02.12
//

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Matrix4.h"

class Vector;
class Point;
class Ray;

class Transform
{
public:
	// Constructors

	static Transform Identity();

	static Transform Translate(const double dx, const double dy, const double dz);
	static Transform Translate(const Vector& v);

	static Transform Scale(const double s);
	static Transform Scale(const double sx, const double sy, const double sz);
	static Transform Scale(const Vector& v);

	// positive value -> counter-clockwise rotation.
	static Transform RotateXrad(const double rad);
	static Transform RotateYrad(const double rad);
	static Transform RotateZrad(const double rad);

	static Transform RotateXdeg(const double deg);
	static Transform RotateYdeg(const double deg);
	static Transform RotateZdeg(const double deg);

	// Apply transform

	Point apply(const Point& p) const;
	Vector apply(const Vector& v) const;
	Ray apply(const Ray& r) const;

	Point operator()(const Point& p) const;
	Vector operator()(const Vector& v) const;
	Ray operator()(const Ray& r) const;

	Point applyInv(const Point& p) const;
	Vector applyInv(const Vector& v) const;
	Ray applyInv(const Ray& r) const;

	// Compose

	Transform operator*(const Transform& t) const;

private:
	Matrix4 M;
	Matrix4 Minv;

	Transform(const Matrix4& matrix, const Matrix4& invMatrix);
};

#endif /* _TRANSFORM_H_ */
