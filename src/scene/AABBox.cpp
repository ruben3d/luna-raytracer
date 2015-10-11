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
// AABBox.cpp - Created on 2010.02.18
//

#include <algorithm>
#include <limits>
#include "AABBox.h"
#include "Ray.h"

AABBox::AABBox() :
	pMin(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
		 std::numeric_limits<double>::infinity()),
	pMax(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(),
		 -std::numeric_limits<double>::infinity())
{
	// Nothing
}

AABBox::AABBox(const Point& p) : pMin(p), pMax(p)
{
	// Nothing
}

AABBox::AABBox(const Point& min, const Point& max) : pMin(min), pMax(max)
{
	if (pMin.x > pMax.x) std::swap(pMin.x, pMax.x);
	if (pMin.y > pMax.y) std::swap(pMin.y, pMax.y);
	if (pMin.z > pMax.z) std::swap(pMin.z, pMax.z);
}

AABBox AABBox::join(const Point& p) const
{
	Point min, max;

	min.x = std::min(pMin.x, p.x);
	min.y = std::min(pMin.y, p.y);
	min.z = std::min(pMin.z, p.z);

	max.x = std::max(pMax.x, p.x);
	max.y = std::max(pMax.y, p.y);
	max.z = std::max(pMax.z, p.z);

	return AABBox(min, max);
}

AABBox AABBox::join(const AABBox& box) const
{
	Point min, max;

	min.x = std::min(pMin.x, box.pMin.x);
	min.y = std::min(pMin.y, box.pMin.y);
	min.z = std::min(pMin.z, box.pMin.z);

	max.x = std::max(pMax.x, box.pMax.x);
	max.y = std::max(pMax.y, box.pMax.y);
	max.z = std::max(pMax.z, box.pMax.z);

	return AABBox(min, max);
}

bool AABBox::intersects(const Point& p) const
{
	return ((pMin.x <= p.x) && (p.x <= pMax.x) &&
			(pMin.y <= p.y) && (p.y <= pMax.y) &&
			(pMin.z <= p.z) && (p.z <= pMax.z));
}

bool AABBox::intersects(const AABBox& box) const
{
	return ((pMax.x >= box.pMin.x) && (pMin.x <= box.pMax.x) &&
			(pMax.y >= box.pMin.y) && (pMin.y <= box.pMax.y) &&
			(pMax.z >= box.pMin.z) && (pMin.z <= box.pMax.z));
}

bool AABBox::intersects(const Ray& ray) const
{
	double tMin, tMax;
	return intersects(ray, tMin, tMax);
}

bool AABBox::intersects(const Ray& ray, double& tMin, double& tMax) const
{
	tMin = ray.tmin;
	tMax = ray.tmax;

	for (int axis=0; axis<=2; axis++)
	{
		double invray = 1.0 / ray.d[axis];
		double min = (pMin[axis] - ray.o[axis]) * invray;
		double max = (pMax[axis] - ray.o[axis]) * invray;

		if (min > max) std::swap(min, max);
		if (tMin < min) tMin = min;
		if (tMax > max) tMax = max;
		if (tMin > tMax) return false;
	}

	return true;
}
