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
// SphereAreaLight.h - Created on 2009.01.15
//

#ifndef _SPHEREAREALIGHT_H_
#define _SPHEREAREALIGHT_H_

#include "Light.h"
#include "LightHasPosition.h"
#include "LightHasAttenuation.h"
#include "LightHasGeometry.h"

class SphereAreaLight : public Light, public LightHasPosition,
						public LightHasAttenuation, public LightHasGeometry
{
public:
	SphereAreaLight(const Transform& tr, const double intensity, const Color& color, const double radius,
					const bool show, const Attenuation attenuation = ATT_NONE);

	~SphereAreaLight(){}

	void setSampling(const unsigned int minSamples,
					const unsigned int maxSamples)
	{
		m_minSamples = minSamples;
		m_maxSamples = maxSamples;
	}

	void computeIntensity(const Vector& N, const Point& P,
							const std::list<Object*>& objects,
							std::list<Color>& I,
							std::list<Vector>& L) const;

	virtual Geometry* getGeometry() const;
	virtual Material* getMaterial() const;

private:
	double m_radius;
	double m_minSamples;
	double m_maxSamples;

	bool computeSample(const Point& P, const Vector& N,
					const std::list<Object*>& objects,
					unsigned int& haltonSeq,
					Color& I, Vector& L) const;

	unsigned int m_id;
	static unsigned int GlobalCounter;
};

#endif /* _SPHEREAREALIGHT_H_ */
