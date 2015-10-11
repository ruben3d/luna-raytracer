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
// LensCameraExample.cpp - Created on 2014.06.01
//

#include "LensCameraExample.h"

#include <iostream>
#include "Scene.h"
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "SimpleCameraMount.h"
#include "Camera.h"
#include "LensCamera.h"
#include "SkyLight.h"
#include "SphereAreaLight.h"
#include "GradientBackground.h"

Scene& LensCameraExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new GradientBackground(Color(1, 1, 1), Color(0.0, 0.0, 0.0));
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-3,3.5) * Transform::RotateXdeg(80);
	Camera* camera = new LensCamera(aspectRatio, 8, 0.2);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "white"));

	for (int i=-4; i<8; i++)
	{
		scene.addElement(new Object(Transform::Translate(2, i*8, 1), GeoPtr(new Sphere(2)), "white"));
		scene.addElement(new Object(Transform::Translate(-2, i*8+4, 1), GeoPtr(new Sphere(2)), "black"));
	}

 	SkyLight* skyLight = new SkyLight(0.3, Color(0.800, 0.930, 1));
 	skyLight->setSampling(1,1,0.05);
 	scene.addElement(skyLight);

	SphereAreaLight *areaLight = NULL;
	areaLight = new SphereAreaLight(Transform::Translate(-6,-2,7),1.0, Color(0.8,0.7,0.6), 1, true, SphereAreaLight::ATT_NONE);
	areaLight->setSampling(1,1);
	scene.addElement(areaLight);

	return scene;
}

Scene& LensCameraExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;

	mat = new Material("white", Color(0.9,0.9,0.9));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

	mat = new Material("black", Color(0.0,0.0,0.0));
	mat->setReflection(true);
	mat->setSpecularIntensity(0.2);
	mat->setSpecularGlossiness(256);
	mat->setIOR(1.1);
	scene.addElement(mat);

	mat = NULL;

	return scene;
}
