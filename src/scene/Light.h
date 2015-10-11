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
// Light.h - Created on 2008.12.21
//

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <list>
#include "Entity.h"
#include "Color.h"
#include "Vector.h"
#include "Point.h"

class Object;

class Light : public Entity
{
public:
	Light(const Transform& tr, const double intensity, const Color& color)
		: Entity(tr), m_attributes(0), m_intensity(intensity), m_color(color) {};
	virtual ~Light() {};

	bool getAttribute(const unsigned int attr) const {return m_attributes&attr;}
	double getIntensity() const {return m_intensity;}
	const Color& getColor() const {return m_color;}

	void setIntensity(const double intensity) {m_intensity = intensity;}
	void setColor(const Color& color) {m_color = color;}

	/// All the parameters must be provided in world space
	virtual void computeIntensity(const Vector& N, const Point& P,
									const std::list<Object*>& objects,
									std::list<Color>& I,
									std::list<Vector>& L) const = 0;

protected:
	void addAttribute(const unsigned int attr) {m_attributes |= attr;}

private:
	unsigned int m_attributes;
	double m_intensity;
	Color m_color;
};

#endif /* _LIGHT_H_ */
