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
// SkyLightExample.cpp - Created on 2014.06.02
//

#include "SkyLightExample.h"

#include <iostream>
#include "Scene.h"
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "SimpleCameraMount.h"
#include "Camera.h"
#include "PinholeCamera.h"
#include "SkyLight.h"
#include "SphereAreaLight.h"
#include "SolidBackground.h"
#include "TriangleMesh.h"

Scene& SkyLightExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new SolidBackground(1, 1, 1);
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-6,4) * Transform::RotateYdeg(-20) * Transform::RotateXdeg(70)  * Transform::RotateZdeg(10) * Transform::Translate(0,0,5);
	Camera* camera = new PinholeCamera(aspectRatio);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "matte_white"));

	TriangleMesh *mesh = new TriangleMesh(8,8);
	mesh->setVertex(0, Point(-2,-2,-2));
	mesh->setVertex(1, Point( 2,-2, 2));
	mesh->setVertex(2, Point( 2,-2,-2));
	mesh->setVertex(3, Point( 2, 2,-2));
	mesh->setVertex(4, Point(-2, 2,-2));
	mesh->setVertex(5, Point(-2, 2, 2));
	mesh->setVertex(6, Point(-2,-2, 2));
	mesh->setVertex(7, Point( 2, 2, 2));
	mesh->setFace(0, 1,3,7);
	mesh->setFace(1, 1,2,3);
	mesh->setFace(2, 7,3,5);
	mesh->setFace(3, 3,4,5);
	mesh->setFace(4, 1,5,6);
	mesh->setFace(5, 1,7,5);
	mesh->setFace(6, 1,6,0);
	mesh->setFace(7, 2,1,0);
	GeoPtr pMesh(mesh);

	scene.addElement(new Object(Transform::Translate(0,2,1) * Transform::RotateZdeg(60), pMesh, "matte_white"));

	scene.addElement(new Object(Transform::Translate( 6, 4, 2.5), GeoPtr(new Sphere(4)), "matte_white"));

 	SkyLight* skyLight = new SkyLight(1, Color(1, 1, 1));
 	skyLight->setSampling(32,128,0.05);
 	scene.addElement(skyLight);

	return scene;
}

Scene& SkyLightExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;

	mat = new Material("matte_white", Color(1,1,1));
	mat->setSpecularIntensity(0.0);
	mat->setSpecularGlossiness(0.0);
	scene.addElement(mat);

	mat = NULL;

	return scene;
}
