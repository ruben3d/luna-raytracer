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
// LightHasGeometry.h - Created on 2010.02.21
//

#ifndef _LIGHTHASGEOMETRY_H_
#define _LIGHTHASGEOMETRY_H_

class Geometry;
class Material;

class LightHasGeometry
{
public:
	enum {ATTRIBUTE = 0x8};

	LightHasGeometry(const bool showGeometry) : m_showGeometry(showGeometry) {};
	bool showGeometry() const {return m_showGeometry;}

	/// Now the caller owns this memory.
	virtual Geometry* getGeometry() const = 0;

	/// Now the caller owns this memory.
	virtual Material* getMaterial() const = 0;

protected:
	virtual ~LightHasGeometry() {}

private:
	bool m_showGeometry;
};

#endif /* _LIGHTHASGEOMETRY_H_ */
