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
// Raytracer.h - Created on 2008.12.05
//

#ifndef _RAYTRACER_
#define _RAYTRACER_

#include "Color.h"
#include "Vector.h"
#include "Point.h"

class FrameBuffer;
class Scene;
class BucketOrder;
class Geometry;
class Object;
class Ray;
class Scene;
class Light;
class Material;

class Raytracer
{
public:
	Raytracer(const Scene* scene);
	~Raytracer();

	Color traceRay(const Ray& ray, const unsigned int recursion,
					double& distance);

	unsigned int getSecondaryRaysCount() const {return m_secondaryRaysCount;}

private:
	const Scene* m_scene;
	unsigned int m_secondaryRaysCount;

	const Ray buildRay(const double x, const double y) const;

	Object* searchNearestObj(const Ray& ray, Vector& N, double& nearestT)const;

	Color computeDirectLightIntensity(const Light* light, const Material* material, const Point& P, const Vector& N,
									  const Vector& V);

	Color computeReflection(const Vector& V, const Point& P, const Vector& N, const unsigned int recursion);

	Color computeGlossyReflection(const Vector& V, const Point& P, const Vector& N,
								  const double roughness, const unsigned int samples, const unsigned int recursion);


	/// \param N	Surface normal.
	/// \param I	Incoming ray.
	/// \param n1	Incoming medium index of refraction.
	/// \param n2	Outgoing medium index of refraction.
	/// \param T	Outgoing refracted ray.
	/// \return		\b true if there is no total internal reflection.
	bool refract(const Vector& N, const Vector& I, const double n1, const double n2, Vector& T) const;

	Color computeRefraction(const Vector& V, const Point& P, const Vector& N, const double ior1, const double ior2,
							const unsigned int recursion);

	Color computeGlossyRefraction(const Vector& V, const Point& P, const Vector& N, const double ior1, 	const double ior2,
								  const double roughness, const unsigned int samples, const unsigned int recursion);
};

#endif /* _RAYTRACER_ */
