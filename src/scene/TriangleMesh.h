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
// TriangleMesh.h - Created on 2010.02.19
//

#ifndef _TRIANGLEMESH_H_
#define _TRIANGLEMESH_H_

#include "Geometry.h"
#include "Vector.h"
#include "Point.h"

class TriangleMesh : public Geometry
{
public:
	class Triangle : public Geometry
	{
	public:
		TriangleMesh *mesh;
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
		Vector normal;

		Triangle(TriangleMesh* parent, const unsigned int V0, const unsigned int V1, const unsigned int V2);
		~Triangle(){}

		bool intersects(const Ray& ray, double& t) const;

		bool checkIntersection(const Ray& ray, Vector& N, double& t) const;

	private:
		Triangle(const Triangle& tri) : Geometry(tri) {}
	};

	TriangleMesh(const unsigned int nvertices, const unsigned int nfaces);
	~TriangleMesh();

	// Updates de bbox.
	void setVertex(const unsigned int index, const Point& p);

	// Call only after all the vertices have been set up.
	void setFace(const unsigned int index, const unsigned int v0, const unsigned int v1, const unsigned int v2);

	bool intersects(const Ray& ray, double& t) const;
	bool checkIntersection(const Ray& ray, Vector& N, double& t) const;

private:
	TriangleMesh(const TriangleMesh& tri) : Geometry(tri) {}

	unsigned int m_nVertices;
	unsigned int m_nFaces;
	Point *vertices;
	TriangleMesh::Triangle **faces;
};

#endif /* _TRIANGLEMESH_H_ */
