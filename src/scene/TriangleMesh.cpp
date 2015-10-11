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
// TriangleMesh.cpp - Created on 2010.02.19
//

#include "TriangleMesh.h"
#include "Ray.h"

// --== TriangleMesh::Triangle ==--

TriangleMesh::Triangle::Triangle(TriangleMesh* parent, const unsigned int V0, const unsigned int V1,
								 const unsigned int V2)
	: Geometry(AABBox(parent->vertices[V0])), mesh(parent), v0(V0), v1(V1), v2(V2)
{
	normal = (mesh->vertices[v1]-mesh->vertices[v0]).cross(mesh->vertices[v2]-mesh->vertices[v0]).normalize();
	box = box.join(mesh->vertices[V1]);
	box = box.join(mesh->vertices[V2]);
}

bool TriangleMesh::Triangle::intersects(const Ray& ray, double& t) const
{
	if (!box.intersects(ray)) return false;

	// Ray-triangle plane intersection

	double denominator = ray.d.dot(normal);
	if (denominator == 0) return false;

	double numerator = (ray.o - mesh->vertices[v0]).dot(normal);

	double distance = - numerator/denominator;
	if ((distance < ray.tmin) || (ray.tmax < distance)) return false;

	// Point of intersection
	Point P = ray(distance);

	// Check if P in in the triangle
	if ( ((mesh->vertices[v1]-mesh->vertices[v0]).cross(P-mesh->vertices[v0])).dot(normal) < 0) return false;
	if ( ((mesh->vertices[v2]-mesh->vertices[v1]).cross(P-mesh->vertices[v1])).dot(normal) < 0) return false;
	if ( ((mesh->vertices[v0]-mesh->vertices[v2]).cross(P-mesh->vertices[v2])).dot(normal) < 0) return false;

	t = distance;

	return true;
}

bool TriangleMesh::Triangle::checkIntersection(const Ray& ray, Vector& N, double& t) const
{
	if (!box.intersects(ray)) return false;

	// Ray-triangle plane intersection

	double denominator = ray.d.dot(normal);
	if (denominator == 0) return false;

	double numerator = (ray.o - mesh->vertices[v0]).dot(normal);

	double distance = - numerator/denominator;
	if ((distance < ray.tmin) || (ray.tmax < distance)) return false;

	// Point of intersection
	Point P = ray(distance);

	// Check if P in in the triangle
	if ( ((mesh->vertices[v1]-mesh->vertices[v0]).cross(P-mesh->vertices[v0])).dot(normal) < 0) return false;
	if ( ((mesh->vertices[v2]-mesh->vertices[v1]).cross(P-mesh->vertices[v1])).dot(normal) < 0) return false;
	if ( ((mesh->vertices[v0]-mesh->vertices[v2]).cross(P-mesh->vertices[v2])).dot(normal) < 0) return false;

	N = normal;
	t = distance;

	return true;
}

// --== TriangleMesh ==--

TriangleMesh::TriangleMesh(const unsigned int nvertices, const unsigned int nfaces)
	: Geometry(AABBox()), m_nVertices(nvertices), m_nFaces(nfaces)
{
	vertices = new Point[m_nVertices];
	faces = new TriangleMesh::Triangle*[m_nFaces];

	for (unsigned int i=0; i<m_nFaces; i++) faces[i] = static_cast<TriangleMesh::Triangle*>(0);
}

TriangleMesh::~TriangleMesh()
{
	if (vertices)
	{
		delete[] vertices;
	}

	if (faces)
	{
		for (unsigned int i=0; i<m_nFaces; i++)
		{
			if (faces[i])
			{
				delete faces[i];
			}
		}
		delete[] faces;
	}
}

void TriangleMesh::setVertex(const unsigned int index, const Point& p)
{
	vertices[index] = p;
	box = box.join(p);
}

// Call only after all the vertices have been set up.
void TriangleMesh::setFace(const unsigned int index, const unsigned int v0, const unsigned int v1, const unsigned int v2)
{
	if (faces[index]) delete faces[index];

	faces[index] = new TriangleMesh::Triangle(this,v0,v1,v2);
}

bool TriangleMesh::intersects(const Ray& ray, double& t) const
{
	if (!box.intersects(ray)) return false;

	Ray localRay(ray);
	bool any = false;
	double nearestT = ray.tmax;

	for (unsigned int i=0; i<m_nFaces; i++)
	{	
		bool intersects = faces[i]->intersects(localRay,nearestT);

		if (intersects)
		{
			t = nearestT;
			localRay.tmax = nearestT;
			any = true;
		}
	}
	return any;
}

bool TriangleMesh::checkIntersection(const Ray& ray, Vector& N, double& t) const
{
	if (!box.intersects(ray)) return false;

	Ray localRay(ray);
	bool any = false;
	double nearestT = ray.tmax;
	Vector normal;

	for (unsigned int i=0; i<m_nFaces; i++)
	{
		bool intersects = faces[i]->checkIntersection(localRay, normal, nearestT);

		if (intersects)
		{
			t = nearestT;
			localRay.tmax = nearestT;
			N = normal;
			any = true;
		}
	}
	return any;
}
