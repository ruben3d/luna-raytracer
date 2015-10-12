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
// Raytracer.cpp - Created on 2008.12.05
//

#include <cstdio>
#include <list>
#include "Raytracer.h"
#include "Ray.h"
#include "Light.h"
#include "LightHasPosition.h"
#include "LightHasDirection.h"
#include "Object.h"
#include "FrameBuffer.h"
#include "Material.h"
#include "Random.h"
#include "Scene.h"
#include "Background.h"

#define RND_SIGN (Random::Instance().generate(2) ? 1 : -1)

Raytracer::Raytracer(const Scene* scene)
	: m_scene(scene), m_secondaryRaysCount(0)
{
	// Nothing
}

Raytracer::~Raytracer()
{
	// Nothing
}

/*

The illumination equation:

For each color channel
	C = Ia·Ka·Ca + sum( S·Fatt·Id·[Kd·Cd·(N·L) + Ks·Cs·(R·V)^n] ) + Ks·Ir + Kt·It
where
	C	: Final color value (channel).
	Ia	: Ambient light color [0-1] (channel).
	Ka	: Ambient light intensity [0-1].
	Ca	: Ambient material color [0-1] (channel).
	sum	: Summatory of all visible lights.
	S	: Light visibility: 0: Fully blocked; 1: Fully visible [0-1].
	Fatt: Light attenuation (more on this later).
	Id	: Diffuse direct light color [0-1] (channel).
	Kd	: Diffuse direct light intensity.
	Cd	: Diffuse material color [0-1] (channel).
	N	: Surface normal unit vector.
	L	: Surface->Light unit vector.
	N·L	: Dot product.
	Ks	: Material specular intensity [0-1].
	Cs	: Material specular color [0-1] (channel).
	R	: L mirrored on N, unit vector.
	V	: Surface->Camera unit vector.
	R·V	: Dot product.
	n	: Specular glossiness [0,...).
	Ir	: Reflected ray color (channel).
	Kt	: Transmission coeficient.
	It	: Refracted ray color.
*/

Color Raytracer::traceRay(const Ray& ray, const unsigned int recursion, double& distance)
{
	// This is the variable that will store the return value
	Color color(0,0,0);		// C

	// Surface normal
	Vector N;

	// Vector PoI->ViewPoint
	Vector V = -ray.d;

	// We look for the nearest object that intersects the ray
	double nearestT = ray.tmax;
	Object *nearestObj = searchNearestObj(ray, N, nearestT);
	distance = nearestT;

	// If the ray is lost in the background...
	if (nearestObj == NULL)
	{
		const Background* background = m_scene->getBackground();
		return background ? background->getColor(ray) : Color(0,0,0);
	}

	const Material *material = m_scene->getMaterial(nearestObj->getMaterial());
	// If the object material is not defined...
	if (material == NULL)
	{
		distance = nearestT;
		return Color(0,0,0);	// Pitch black
	}

	// Point of intersection
	Point P = ray(nearestT);

	// If the surface is faced away...
	if (V.dot(N) < 0)
	{
		if (material->getRefraction())
		{
			N = -N;
			if (material->getAbsorption() > 0.0)
			{
				Color absorption = material->getDiffuseColor();

				absorption = absorption * material->getAbsorption() * -nearestT;
				absorption.r = exp(absorption.r);
				absorption.g = exp(absorption.g);
				absorption.b = exp(absorption.b);

				return absorption * computeRefraction(V, P, N, material->getIOR(), 1.0, recursion);
			}
			else
			{
				return computeRefraction(V, P, N, material->getIOR(), 1.0, recursion);
			}
		}
		else // Flip normal, whe are inside the object!
		{
			N = -N;
		}
	}

	// Calculate light intensity from all the lights
	Color sum(0,0,0);												// sum
	const std::list<Light*> lights = m_scene->getLights();
	std::list<Light*>::const_iterator lightIt;
	for (lightIt = lights.begin(); lightIt != lights.end(); lightIt++)
	{
		sum += computeDirectLightIntensity(*lightIt, material, P, N, V);
	}

	// Ir
	Color Ir(0,0,0);
	if (material->getReflection() && (recursion>0))
	{
		if (material->getGlossy() == false)
		{
			Ir = computeReflection(V, P, N, recursion-1);
		}
		else
		{
			Ir = computeGlossyReflection(V, P, N, material->getGlossyRoughness(), material->getGlossySamples(),
										recursion-1);
		}
	}

	// It
	Color It(0,0,0);
	if (material->getRefraction() && (recursion>0))
	{
		if (material->getGlossy() == false)
		{
			It = computeRefraction(V,P,N, 1.0, material->getIOR(), recursion-1);
		}
		else
		{
			It = computeGlossyRefraction(V, P, N, 1.0, material->getIOR(), 	material->getGlossyRoughness(),
										 material->getGlossySamples(), recursion-1);
		}
	}

	// Ia
	Color Ia = m_scene->getAmbientLightColor();
	// Ka
	double Ka = m_scene->getAmbientLightIntensity();
	// Ca
	Color Ca = material->getAmbientColor();


	color += Ia * Ka * Ca;
	color += sum;
	double fresnel = computeFresnelReflectance(V, N, 1.0, material->getIOR());
	if (material->getFresnelExponent() != 1.0)
	{
		fresnel = pow(fresnel, material->getFresnelExponent());
	}
	color += Ir * fresnel *material->getSpecularIntensity() /* Ks */;
	color += It * (1.0-fresnel) /* Kt */;

	return color;
}

double Raytracer::computeFresnelReflectance(const Vector& V, const Vector& N, const double ni, const double nt)
{
	Vector T;
	if ((-V).refract(N, ni, nt, T))
	{
		const double cosi = V.dot(N);
		const double cost = T.dot(-N);
		const double parallel = (nt * cosi - ni * cost) / (nt * cosi + ni * cost);
		const double perpendicular = (ni * cosi - nt * cost) / (ni * cosi + nt * cost);
		return (parallel*parallel + perpendicular*perpendicular) / 2.0;
	}
	else
	{
		return 1.0;
	}
}

// The input ray and output normal are in world coordinates
Object* Raytracer::searchNearestObj(const Ray& ray, Vector& N, double& nearestT) const
{
	Object* nearestObj = NULL;

	const std::list<Object*> objects = m_scene->getObjects();
	std::list<Object*>::const_iterator objIt;
	for (objIt = objects.begin(); objIt != objects.end(); objIt++)
	{
		double t;
		Vector normal;
		Ray rayT = (*objIt)->T.applyInv(ray);
		rayT.tmax = nearestT;
		bool intersects = (*objIt)->getGeometry()->checkIntersection(rayT,normal,t);

		if (intersects)
		{
			nearestT = t;
			N = normal;
			nearestObj = *objIt;
		}
	}
	if (nearestObj != NULL)
	{
		N = nearestObj->T(N);
	}
	return nearestObj;
}

Color Raytracer::computeDirectLightIntensity(const Light* light,
											const Material* material,
											const Point& P, const Vector& N,
											const Vector& V)
{
	Color totalIntensity(0,0,0);
	std::list<Color> I;
	std::list<Vector> L;

	light->computeIntensity(N, P, m_scene->getObjects(), I,L);

	std::list<Color>::const_iterator itI = I.begin();
	std::list<Vector>::const_iterator itL = L.begin();

	unsigned int i = 0;
	for (i = 0; i<I.size(); i++)
	{
		Color intensity(0,0,0);
		if ((light->getAttribute(LightHasPosition::ATTRIBUTE) == 0) &&
			(light->getAttribute(LightHasDirection::ATTRIBUTE) == 0))
		{
			intensity = (*itI) * material->getDiffuseColor();
		}
		else
		{
			// N dot L
			double NdotL = N.dot(*itL);
			if (NdotL < 0.0) NdotL = 0.0;

			// R dot V
			// R = N·2·(N·L)-L
			Vector R = (*itL).mirrorOn(N).normalize();
			double RdotV = R.dot(V);
			if (RdotV < 0.0) RdotV = 0.0;

			// Calculate illumination term:

			Color diffuseConstant = material->getDiffuseColor();			// Cd
			//diffuseConstant *= light->getIntensity();						// Kd
			diffuseConstant *= NdotL;										// N·L
		
			Color specularConstant = material->getSpecularColor();			// Cs
			specularConstant *= material->getSpecularIntensity();			// Ks
			specularConstant*=pow(RdotV,material->getSpecularGlossiness());	//(R·V)^n

			intensity = specularConstant;
			intensity += diffuseConstant;
			if (light->getAttribute(LightHasDirection::ATTRIBUTE))
			{
				const LightHasDirection *dirLight = dynamic_cast<const LightHasDirection*>(light);
				// Id * Fatt * S <- *itI
				intensity *= *itI * pow((-*itL).dot(dirLight->getDirection()), dirLight->getExponent());
			}
			else
			{
				intensity *= *itI;											// Id * Fatt * S
			}
			itL++;
		}
		itI++;
		totalIntensity += intensity;
	}
	if (i > 0)
	{
		totalIntensity *= 1.0/(double)i;
	}

	return totalIntensity + material->getDiffuseColor()*material->getEmission();
}

Color Raytracer::computeReflection(const Vector& V, const Point& P,
								const Vector& N, const unsigned int recursion)
{
	m_secondaryRaysCount++;
	Ray reflectedRay(P, V.mirrorOn(N));
	double t;
	return traceRay(reflectedRay, recursion, t);
}

Color Raytracer::computeGlossyReflection(const Vector& V, const Point& P, const Vector& N,
										 const double roughness, const unsigned int samples, const unsigned int recursion)
{
	Color reflection(0,0,0);
	unsigned int haltonSeq = Random::Instance().generate(4096);
	const double r2 = roughness/2.0;

	for (unsigned int i=0; i<samples; i++)
	{
		haltonSeq++;
		m_secondaryRaysCount++;
		Vector normal = N;

		normal.x += Random::Instance().haltonSeq(haltonSeq,2)*roughness-r2;
		normal.y += Random::Instance().haltonSeq(haltonSeq,3)*roughness-r2;
		normal.z += Random::Instance().haltonSeq(haltonSeq,5)*roughness-r2;
/*
		normal.x += RND_SIGN * Random::Instance().generate()*roughness/2.0;
		normal.y += RND_SIGN * Random::Instance().generate()*roughness/2.0;
		normal.z += RND_SIGN * Random::Instance().generate()*roughness/2.0;
*/
		Ray reflectedRay(P, V.mirrorOn(normal.normalize()));
		double t;
		reflection += traceRay(reflectedRay, recursion, t);
	}
	reflection *= 1.0/samples;
	return reflection;
}

Color Raytracer::computeRefraction(const Vector& V, const Point& P, const Vector& N,
								   const double ior1, const double ior2, const unsigned int recursion)
{
	m_secondaryRaysCount++;

	Vector T;
	if ((-V).refract(N,ior1,ior2,T))
	{
		Ray refractedRay(P,T);
		double t;
		return traceRay(refractedRay, recursion, t);
	}
	else
	{
		Ray reflectedRay(P, V.mirrorOn(N));
		double t;
		return traceRay(reflectedRay, recursion, t);
	}
}

Color Raytracer::computeGlossyRefraction(const Vector& V, const Point& P, const Vector& N,
										 const double ior1, const double ior2,
										 const double roughness, const unsigned int samples, const unsigned int recursion)
{
	Color refraction(0,0,0);
	unsigned int haltonSeq = Random::Instance().generate(4096);
	const double r2 = roughness/2.0;
	for (unsigned int i=0; i<samples; i++)
	{
		haltonSeq++;
		m_secondaryRaysCount++;
		Vector normal = N;

		normal.x += Random::Instance().haltonSeq(haltonSeq,2)*roughness-r2;
		normal.y += Random::Instance().haltonSeq(haltonSeq,3)*roughness-r2;
		normal.z += Random::Instance().haltonSeq(haltonSeq,5)*roughness-r2;
		/*
		normal.x += RND_SIGN * Random::Instance().generate()*roughness/2.0;
		normal.y += RND_SIGN * Random::Instance().generate()*roughness/2.0;
		normal.z += RND_SIGN * Random::Instance().generate()*roughness/2.0;
		*/
		refraction += computeRefraction(V, P, normal.normalize(), ior1, ior2, recursion);
	}
	refraction *= 1.0/samples;
	return refraction;
}
