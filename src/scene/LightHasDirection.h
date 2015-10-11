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
// LightHasDirection.h - Created on 2008.12.23
//

#ifndef _LIGHTHASDIRECTION_H_
#define _LIGHTHASDIRECTION_H_

#include "Vector.h"

class LightHasDirection
{
public:
	enum {ATTRIBUTE = 0x2};

	LightHasDirection(const Vector& direction, const double exponent) : m_direction(direction), m_exponent(exponent) {}

	//void setDirection(const Vector& direction) {m_direction = direction;}
	const Vector& getDirection() const {return m_direction;}
	double getExponent() const {return m_exponent;}

protected:
	~LightHasDirection() {}

private:
	Vector m_direction;
	double m_exponent;
};

#endif /* _LIGHTHASDIRECTION_H_ */
