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
// LightHasAttenuation.cpp - Created on 2008.12.23
//

#include "LightHasAttenuation.h"

double LightHasAttenuation::getAttFactor(const double distance) const
{
	double Fatt = 1.0;
	Fatt = 1.0 / (	m_d0 +
					m_d1 * distance +
					m_d2 * distance * distance);
	if (Fatt > 1.0) Fatt = 1.0;
	return Fatt;
}

void LightHasAttenuation::fixConstants()
{
	if (m_attenuation == ATT_NONE)
	{
		m_d0 = 1;
		m_d1 = 0;
		m_d2 = 0;
	}
	else if (m_attenuation == ATT_LINEAR)
	{
		m_d0 = 0;
		m_d1 = 1;
		m_d2 = 0;
	}
	else if (m_attenuation == ATT_QUADRATIC)
	{
		m_d0 = 0;
		m_d1 = 0;
		m_d2 = 1;
	}
}
