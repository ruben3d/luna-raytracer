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
// GradientBackground.h - Created on 2014.06.01
//

#ifndef _GRADIENTBACKGROUND_H_
#define _GRADIENTBACKGROUND_H_

#include "Background.h"
#include "Vector.h"

class GradientBackground : public Background
{
public:
	GradientBackground(const Color& pole, const Color& equator)
		: m_pole(pole), m_equator(equator) {};

	Color getColor(const Ray& ray) const;

private:
	static const Vector UP;
	const Color m_pole;
	const Color m_equator;
};

#endif /* _GRADIENTBACKGROUND_H_ */
