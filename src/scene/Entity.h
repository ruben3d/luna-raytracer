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
// Entity.h - Created on 2010.02.13
//

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Transform.h"

class Entity
{
public:
	Transform T;
	Entity(const Transform& tr) : T(tr) {}
	virtual ~Entity() {}
};

#endif /* _ENTITY_H_ */
