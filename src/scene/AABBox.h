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
// AABBox.h - Created on 2010.02.18
//

#ifndef _AABBOX_H_
#define _AABBOX_H_

#include "Point.h"

class Ray;

class AABBox
{
public:
	Point pMin;
	Point pMax;

	AABBox();
	AABBox(const Point& p);
	AABBox(const Point& min, const Point& max);

	AABBox join(const Point& p) const;
	AABBox join(const AABBox& box) const;

	bool intersects(const Point& p) const;
	bool intersects(const AABBox& box) const;
	bool intersects(const Ray& ray) const;
	bool intersects(const Ray& ray, double& tMin, double& tMax) const;
};

#endif /* _AABBOX_H_ */
