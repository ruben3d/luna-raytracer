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
// Object.h - Created on 2008.12.06
//

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <boost/shared_ptr.hpp>

#include "Entity.h"
#include "Geometry.h"

typedef boost::shared_ptr<Geometry> GeoPtr;

class Object : public Entity
{
public:
	/// \param geometry	Now the object owns this memory and will release it. --No longer true! shared_ptr
	Object(const Transform& Tr, GeoPtr geometry, const std::string& material, const bool castShadow = true)
		: Entity(Tr), m_geometry(geometry), m_material(material), m_castShadow(castShadow) {}

	~Object() {}

	GeoPtr getGeometry() const {return m_geometry;}
	const std::string& getMaterial() const {return m_material;}

	bool castShadow() const {return m_castShadow;}

private:
	GeoPtr m_geometry;
	std::string m_material;
	bool m_castShadow;
};

#endif /* _OBJECT_H_ */
