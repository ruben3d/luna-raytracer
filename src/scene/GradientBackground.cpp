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
// GradientBackground.cpp - Created on 2014.06.01
//

#include "GradientBackground.h"

#include <cmath>
#include "Ray.h"

const Vector GradientBackground::UP(0.0,0.0,1.0);

#define interpolate(v0, v1, t) (v0 + (v1-v0) * t)

Color GradientBackground::getColor(const Ray& ray) const
{
	double value = 1 - std::abs( UP.dot(ray.d) );
	return Color (	interpolate(m_equator.r, m_pole.r, value),
					interpolate(m_equator.g, m_pole.g, value),
					interpolate(m_equator.b, m_pole.b, value));
}