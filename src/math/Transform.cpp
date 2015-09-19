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
// Transform.cpp - Created on 2010.02.12
//

#include <cmath>
#include "Transform.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"

#define PI 3.1415926535897

static const double PI180 = PI / 180.0;

// Statics

Transform Transform::Identity()
{
	Matrix4 m(	1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1);

	return Transform(m,m);
}

Transform Transform::Translate(const double dx, const double dy, const double dz)
{
	Matrix4 m(	1, 0, 0, dx,
				0, 1, 0, dy,
				0, 0, 1, dz,
				0, 0, 0, 1);

	Matrix4 im(	1, 0, 0, -dx,
				0, 1, 0, -dy,
				0, 0, 1, -dz,
				0, 0, 0,  1);

	return Transform(m, im);
}

Transform Transform::Translate(const Vector& v)
{
	Matrix4 m(	1, 0, 0, v.x,
				0, 1, 0, v.y,
				0, 0, 1, v.z,
				0, 0, 0, 1);

	Matrix4 im(	1, 0, 0, -v.x,
				0, 1, 0, -v.y,
				0, 0, 1, -v.z,
				0, 0, 0,  1);

	return Transform(m, im);
}

Transform Transform::Scale(const double s)
{
	Matrix4 m(	s, 0, 0, 0,
				0, s, 0, 0,
				0, 0, s, 0,
				0, 0, 0, 1);

	double is = 1.0/s;

	Matrix4 im(	is,  0,  0, 0,
				 0, is,  0, 0,
				 0,  0, is, 0,
				 0,  0,  0, 1);

	return Transform(m, im);
}

Transform Transform::Scale(const double sx, const double sy, const double sz)
{
	Matrix4 m(	sx,  0,  0, 0,
				 0, sy,  0, 0,
				 0,  0, sz, 0,
				 0,  0,  0, 1);

	Matrix4 im(	1.0/sx,      0,      0, 0,
				     0, 1.0/sy,      0, 0,
				     0,      0, 1.0/sz, 0,
				     0,      0,      0, 1);

	return Transform(m, im);
}

Transform Transform::Scale(const Vector& v)
{
	return Scale(v.x, v.y, v.z);
}

Transform Transform::RotateXrad(const double rad)
{
	double ncos = cos(rad);
	double nsin = sin(rad);

	Matrix4 m(	1,    0,     0, 0,
				0, ncos, -nsin, 0,
				0, nsin,  ncos, 0,
				0,    0,     0, 1);

	Matrix4 im(	1,     0,    0, 0,
				0,  ncos, nsin, 0,
				0, -nsin, ncos, 0,
				0,     0,    0, 1);

	return Transform(m, im);
}

Transform Transform::RotateYrad(const double rad)
{
	double ncos = cos(rad);
	double nsin = sin(rad);

	Matrix4 m(	 ncos, 0, nsin, 0,
				    0, 1,    0, 0,
				-nsin, 0, ncos, 0,
				    0, 0,    0, 1);

	Matrix4 im(	ncos, 0, -nsin, 0,
				   0, 1,     0, 0,
				nsin, 0,  ncos, 0,
				   0, 0,     0, 1);

	return Transform(m, im);
}

Transform Transform::RotateZrad(const double rad)
{
	double ncos = cos(rad);
	double nsin = sin(rad);

	Matrix4 m(	ncos, -nsin, 0, 0,
				nsin,  ncos, 0, 0,
				   0,     0, 1, 0,
				   0,     0, 0, 1);

	Matrix4 im(	  ncos, nsin,  0, 0,
				 -nsin, ncos,  0, 0,
				     0,     0, 1, 0,
				     0,     0, 0, 1);

	return Transform(m, im);
}

Transform Transform::RotateXdeg(const double deg)
{
	return RotateXrad(deg * PI180);
}

Transform Transform::RotateYdeg(const double deg)
{
	return RotateYrad(deg * PI180);
}

Transform Transform::RotateZdeg(const double deg)
{
	return RotateZrad(deg * PI180);
}

// Non-statics

Transform::Transform(const Matrix4& matrix, const Matrix4& invMatrix)
	: M(matrix), Minv(invMatrix)
{
	// Nothing
}

// The homogeneous 'w' coordinate of the point is 1
Point Transform::apply(const Point& p) const
{
	Point po;
	po.x = 		M.matrix[0][0] * p.x + M.matrix[0][1] * p.y + M.matrix[0][2] * p.z + M.matrix[0][3];
	po.y = 		M.matrix[1][0] * p.x + M.matrix[1][1] * p.y + M.matrix[1][2] * p.z + M.matrix[1][3];
	po.z = 		M.matrix[2][0] * p.x + M.matrix[2][1] * p.y + M.matrix[2][2] * p.z + M.matrix[2][3];
	double pw = M.matrix[3][0] * p.x + M.matrix[3][1] * p.y + M.matrix[3][2] * p.z + M.matrix[3][3];

	if (pw != 1.0) po /=  pw;

	return po;
}

// The homogeneous 'w' coordinate of the vector is 0
Vector Transform::apply(const Vector& v) const
{
	Vector vo;
	vo.x = M.matrix[0][0] * v.x + M.matrix[0][1] * v.y + M.matrix[0][2] * v.z;
	vo.y = M.matrix[1][0] * v.x + M.matrix[1][1] * v.y + M.matrix[1][2] * v.z;
	vo.z = M.matrix[2][0] * v.x + M.matrix[2][1] * v.y + M.matrix[2][2] * v.z;
	return vo;
}

Ray Transform::apply(const Ray& r) const
{
	return Ray(apply(r.getOrigin()), apply(r.getDirection()));
}

Point Transform::operator()(const Point& p) const
{
	return apply(p);
}

Vector Transform::operator()(const Vector& v) const
{
	return apply(v);
}

Ray Transform::operator()(const Ray& r) const
{
	return apply(r);
}

Point Transform::applyInv(const Point& p) const
{
	Point po;
	po.x = 		Minv.matrix[0][0] * p.x + Minv.matrix[0][1] * p.y + Minv.matrix[0][2] * p.z + Minv.matrix[0][3];
	po.y = 		Minv.matrix[1][0] * p.x + Minv.matrix[1][1] * p.y + Minv.matrix[1][2] * p.z + Minv.matrix[1][3];
	po.z = 		Minv.matrix[2][0] * p.x + Minv.matrix[2][1] * p.y + Minv.matrix[2][2] * p.z + Minv.matrix[2][3];
	double pw = Minv.matrix[3][0] * p.x + Minv.matrix[3][1] * p.y + Minv.matrix[3][2] * p.z + Minv.matrix[3][3];

	if (pw != 1.0) po /=  pw;

	return po;
}

Vector Transform::applyInv(const Vector& v) const
{
	Vector vo;
	vo.x = Minv.matrix[0][0] * v.x + Minv.matrix[0][1] * v.y + Minv.matrix[0][2] * v.z;
	vo.y = Minv.matrix[1][0] * v.x + Minv.matrix[1][1] * v.y + Minv.matrix[1][2] * v.z;
	vo.z = Minv.matrix[2][0] * v.x + Minv.matrix[2][1] * v.y + Minv.matrix[2][2] * v.z;
	return vo;
}

Ray Transform::applyInv(const Ray& r) const
{
	return Ray(applyInv(r.getOrigin()), applyInv(r.getDirection()));
}

Transform Transform::operator*(const Transform& t) const
{
	Matrix4 matrix = M * t.M;
	Matrix4 invMatrix = t.Minv * Minv;
	return Transform(matrix, invMatrix);
}
