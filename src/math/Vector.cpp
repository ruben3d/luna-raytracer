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
// Vector.cpp - Created on 2008.12.11
//

#include "Vector.h"
#include "Polar3.h"
#include "Point.h"

Vector::Vector(const Point& p1, const Point& p0)
{
	x = p1.x - p0.x;
	y = p1.y - p0.y;
	z = p1.z - p0.z;
}

Vector::Vector(const Polar3& p)
{
	x = p.rho * sin(p.phi) * cos(p.theta);
	y = p.rho * sin(p.phi) * sin(p.theta);
	z = p.rho * cos(p.phi);
}

Vector::Vector(const Point& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}
