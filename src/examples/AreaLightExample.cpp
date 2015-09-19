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
// AreaLightExample.cpp - Created on 2014.06.02
//

#include "AreaLightExample.h"

#include <iostream>
#include "Scene.h"
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "SimpleCameraMount.h"
#include "Camera.h"
#include "PinholeCamera.h"
#include "SphereAreaLight.h"
#include "DiskAreaLight.h"
#include "SolidBackground.h"

Scene& AreaLightExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new SolidBackground(0, 0, 0);
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-3,9) * Transform::RotateXdeg(60);
	Camera* camera = new PinholeCamera(aspectRatio);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "matte_white"));

	SphereAreaLight *areaLight = NULL;
	areaLight = new SphereAreaLight(Transform::Translate(-7,9,4),80, Color(0.8,0.7,0.6), 0.5, true, SphereAreaLight::ATT_QUADRATIC);
	areaLight->setSampling(32,128);
	scene.addElement(areaLight);
	areaLight = NULL;

	DiskAreaLight *diskLight = NULL;
	diskLight = new DiskAreaLight(Transform::Translate(7,12,5)*Transform::RotateYdeg(-120), 80, 2, Color(0.8,0.7,0.6), 0.5, true, DiskAreaLight::ATT_QUADRATIC);
	diskLight->setSampling(8,16);
	scene.addElement(diskLight);

 	scene.addElement(new Object(Transform::Translate(-5.5, 14, 1), GeoPtr(new Sphere(2)), "white"));
	scene.addElement(new Object(Transform::Translate(-1, 12, 1), GeoPtr(new Sphere(2)), "white"));
 	scene.addElement(new Object(Transform::Translate( 5, 11, 1), GeoPtr(new Sphere(2)), "white"));

	return scene;
}

Scene& AreaLightExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;

	mat = new Material("white", Color(0.9,0.9,0.9));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

	mat = new Material("matte_white", Color(1,1,1));
	mat->setSpecularIntensity(0.0);
	mat->setSpecularGlossiness(0.0);
	scene.addElement(mat);

	mat = NULL;

	return scene;
}
