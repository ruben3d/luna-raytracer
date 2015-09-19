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
// SkyLightExample.h - Created on 2014.06.02
//

#ifndef _SKYLIGHTEXAMPLE_H_
#define _SKYLIGHTEXAMPLE_H_

#include "Application.h"

class SkyLightExample : public Application
{
public:
	SkyLightExample(const unsigned int width, const unsigned int height) : Application(width, height) {};
	virtual Scene& createScene(Scene& scene, const double aspectRatio);

private:
	Scene& createMaterials(Scene& scene);
};

#endif /* _SKYLIGHTEXAMPLE_H_ */
