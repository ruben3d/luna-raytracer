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
// SimpleCameraMount.h - Created on 2008.12.18
//

#ifndef _SIMPLECAMERAMOUNT_H_
#define _SIMPLECAMERAMOUNT_H_

#include "CameraMount.h"

class SimpleCameraMount : public CameraMount
{
public:
	SimpleCameraMount(const Transform& tr, Camera* camera);
	~SimpleCameraMount();
};

#endif /* _SIMPLECAMERAMOUNT_H_ */
