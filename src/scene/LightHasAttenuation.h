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
// LightHasAttenuation.h - Created on 2008.12.23
//

#ifndef _LIGHTHASATTENUATION_H_
#define _LIGHTHASATTENUATION_H_

class LightHasAttenuation
{
public:
	enum {ATTRIBUTE = 0x4};

	enum Attenuation
	{
		ATT_NONE,
		ATT_LINEAR,
		ATT_QUADRATIC,
		ATT_CFG
	};

	LightHasAttenuation(const Attenuation attenuation)
		: m_attenuation(attenuation), m_d0(1),m_d1(0),m_d2(0) {fixConstants();}

	double getAttFactor(const double distance) const;

	Attenuation getAttenuation() const {return m_attenuation;}
	void setAttenuation(const Attenuation attenuation)
	{
		m_attenuation = attenuation;
		fixConstants();
	}

	void setConstants(const double d0, const double d1, const double d2)
	{
		m_d0 = d0;
		m_d1 = d1;
		m_d2 = d2;
		m_attenuation = ATT_CFG;
	}

	double getD0() const {return m_d0;}
	double getD1() const {return m_d1;}
	double getD2() const {return m_d2;}

protected:
	~LightHasAttenuation() {}

private:
	Attenuation m_attenuation;
	double m_d0, m_d1, m_d2;

	void fixConstants();
};

#endif /* _LIGHTHASATTENUATION_H_ */
