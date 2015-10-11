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
// BasicExample.cpp - Created on 2014.06.02
//

#include "BasicExample.h"

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
#include "SolidBackground.h"

Scene& BasicExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new SolidBackground(0, 0, 0);
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-3,3.5) * Transform::RotateXdeg(80);
	Camera* camera = new PinholeCamera(aspectRatio);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "matte_white"));

	scene.addElement(new Object(Transform::Translate(-5.5, 14, 1), GeoPtr(new Sphere(2)), "white"));
	scene.addElement(new Object(Transform::Translate(-1, 12, 1), GeoPtr(new Sphere(2)), "white"));
	scene.addElement(new Object(Transform::Translate( 5, 11, 1), GeoPtr(new Sphere(2)), "white"));

	scene.addElement(new Object(Transform::Translate(-5, 25, 1), GeoPtr(new Sphere(2)), "red"));
	scene.addElement(new Object(Transform::Translate( 0, 23, 1), GeoPtr(new Sphere(2)), "green"));
	scene.addElement(new Object(Transform::Translate( 4, 22, 1), GeoPtr(new Sphere(2)), "blue"));

	scene.addElement(new PointLight(Transform::Translate(-6,2,7), 8, Color(1,0,0), PointLight::ATT_LINEAR));
	scene.addElement(new PointLight(Transform::Translate( 0,2,7), 8, Color(0,1,0), PointLight::ATT_LINEAR));
	scene.addElement(new PointLight(Transform::Translate( 6,2,7), 8, Color(0,0,1), PointLight::ATT_LINEAR));

	return scene;
}

Scene& BasicExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;

	mat = new Material("red", Color(1,0,0));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

	mat = new Material("green", Color(0,1,0));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

	mat = new Material("blue", Color(0,0,1));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

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
