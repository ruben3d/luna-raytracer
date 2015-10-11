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
// Triangle.h - Created on 2008.12.24
//

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Geometry.h"

class Triangle : public Geometry
{
public:
	/// Counter-clockwise
	Triangle(const Point& v0, const Point& v1, const Point& v2)
		: Geometry(AABBox(v0)), m_v0(v0), m_v1(v1), m_v2(v2)
	{
		m_normal = (m_v1-m_v0).cross(m_v2-m_v0).normalize();
		box = box.join(v1);
		box = box.join(v2);
	}

	Triangle(const Triangle& tri) : Geometry(tri)
	{
		m_v0 = tri.m_v0;
		m_v1 = tri.m_v1;
		m_v2 = tri.m_v2;
		m_normal = tri.m_normal;
	}

	~Triangle(){}

	//Vector surfaceNormalAt(const Point& point) const;

	bool intersects(const Ray& ray, double& t) const;

	bool checkIntersection(const Ray& ray, Vector& N, double& t) const;

private:
	Point m_v0;
	Point m_v1;
	Point m_v2;

	Vector m_normal;
};

#endif /* _TRIANGLE_H_ */
