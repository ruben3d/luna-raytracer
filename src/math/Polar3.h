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
// Polar3.h - Created on 2008.12.12
//

#ifndef _POLAR3_H_
#define _POLAR3_H_

#include <cmath>
#include "Vector.h"

#define PI 3.1415926535897

class Polar3
{
public:
	double rho, phi, theta;

	Polar3() : rho(0), phi(0), theta(0) {};
	Polar3 (const double Rho, const double Phi, const double Theta)
		: rho(Rho), phi(Phi), theta(Theta) {};
	Polar3(const Vector& v)
	{
		/*
		rho = v.length();
		theta = atan2(v.y,v.x);
		phi = acos(v.z/rho);
		*/
		rho = v.length();
		double S = sqrt(v.x*v.x+v.y*v.y);
		phi = acos(v.z/rho);
		theta = (0 <= v.x) ? asin(v.y/S) : PI-asin(v.y/S);
	}
};

#endif /* _POLAR3_H_ */
