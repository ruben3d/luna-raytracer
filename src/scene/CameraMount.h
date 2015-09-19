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
// CameraMount.h - Created on 2008.12.15
//

#ifndef _CAMERAMOUNT_H_
#define _CAMERAMOUNT_H_

#include "Entity.h"
#include "Camera.h"

class CameraMount : public Entity
{
public:
	CameraMount(const Transform& tr, Camera* camera) : Entity(tr), m_camera(camera) {}
	virtual ~CameraMount() {if (m_camera) delete m_camera;}

	Camera* getCamera() const {return m_camera;}

private:
	Camera* m_camera;
};

#endif /* _CAMERAMOUNT_H_ */
