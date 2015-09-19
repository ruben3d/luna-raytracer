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
// GlossyExample.cpp - Created on 2014.06.02
//

#include "GlossyExample.h"

#include <iostream>
#include "Scene.h"
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "SimpleCameraMount.h"
#include "Camera.h"
#include "PinholeCamera.h"
#include "PointLight.h"
#include "GradientBackground.h"

Scene& GlossyExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new GradientBackground(Color(1, 1, 1), Color(0.0, 0.0, 0.0));
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-3,3.5) * Transform::RotateXdeg(80);
	Camera* camera = new PinholeCamera(aspectRatio);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "glossy"));

 	scene.addElement(new Object(Transform::Translate(-5.5, 14, 1), GeoPtr(new Sphere(2)), "rmirror"));
	scene.addElement(new Object(Transform::Translate(-1, 12, 1), GeoPtr(new Sphere(2)), "gmirror"));
 	scene.addElement(new Object(Transform::Translate( 5, 11, 1), GeoPtr(new Sphere(2)), "bmirror"));

 	scene.addElement(new PointLight(Transform::Translate(-6,0,7), 8, Color(1,1,1), PointLight::ATT_LINEAR));

	return scene;
}

Scene& GlossyExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;

	mat = new Material("rmirror", Color(0.15,0,0));
	mat->setReflection(true);
	mat->setSpecularIntensity(0.9);
	mat->setReflection(true);
	mat->setSpecularGlossiness(64);
	scene.addElement(mat);

	mat = new Material("gmirror", Color(0,0.15,0));
	mat->setReflection(true);
	mat->setSpecularIntensity(0.9);
	mat->setReflection(true);
	mat->setSpecularGlossiness(64);
	scene.addElement(mat);

	mat = new Material("bmirror", Color(0,0,0.15));
	mat->setReflection(true);
	mat->setSpecularIntensity(0.9);
	mat->setReflection(true);
	mat->setSpecularGlossiness(64);
	scene.addElement(mat);

	mat = new Material("glossy", Color(0.0,0.0,0.0));
	mat->setReflection(true);
	mat->setSpecularIntensity(0.6);
	mat->setSpecularGlossiness(64);
	mat->setGlossy(true);
	mat->setGlossyRoughness(0.1);
	mat->setGlossySamples(8);
	scene.addElement(mat);

	mat = NULL;

	return scene;
}
