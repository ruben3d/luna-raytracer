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
// SkyLight.h - Created on 2008.12.21
//

#ifndef _SKYLIGHT_H_
#define _SKYLIGHT_H_

#include "Light.h"

class SkyLight : public Light
{
public:
	SkyLight(const double intensity, const Color& color);

	~SkyLight(){}

	void computeIntensity(const Vector& N, const Point& P,
							const std::list<Object*>& objects,
							std::list<Color>& I,
							std::list<Vector>& L) const;

	void setSampling(const unsigned int minSamples,
					const unsigned int maxSamples,
					const double threshold)
	{
		m_minSamples = minSamples;
		m_maxSamples = maxSamples;
		m_threshold = threshold;
	}

private:
	unsigned int m_minSamples;
	unsigned int m_maxSamples;
	double m_threshold;

	double computeSkyLightSample(const Point& P, const Vector& N,
									unsigned int& haltonSeq,
									const std::list<Object*>& objects) const;

	double computeDirectSkyLightIntensity(const Point& P, const Vector& N,
									const std::list<Object*>& objects) const;
};

#endif /* _SKYLIGHT_H_ */
