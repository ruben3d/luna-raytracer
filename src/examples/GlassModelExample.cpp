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
// GlassModelExample.cpp - Created on 2014.06.02
//

#include "GlassModelExample.h"

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
#include "GradientBackground.h"
#include "TriangleMesh.h"
#include "LoadASC.h"

Scene& GlassModelExample::createScene(Scene& scene, const double aspectRatio)
{
	scene = createMaterials(scene);

	std::cout << "Creating scene..." << std::endl;

	Background* background = new GradientBackground(Color(1, 1, 1), Color(0.0, 0.0, 0.0));
	scene.setBackground(background);

	Transform Tcam =  Transform::Translate(0,-3,2) * Transform::RotateXdeg(80);
	Camera* camera = new PinholeCamera(aspectRatio);
	SimpleCameraMount* mount = new SimpleCameraMount(Tcam, camera);

	scene.setCameraMount(mount);

	scene.addElement(new Object(Transform::Translate(0,0,-1), GeoPtr(new Plane()), "white"));

	TriangleMesh *mesh = LoadASC("nudobult.asc", 0.02);
	if (mesh)
	{
		GeoPtr pMesh(mesh);
		scene.addElement(new Object(Transform::Translate(0,4,0.5) *Transform::RotateZdeg(15), pMesh, "glass"));
	}

 	SkyLight* skyLight = new SkyLight(0.5, Color(0.800, 0.930, 1));
 	skyLight->setSampling(4,16,0.05);
 	scene.addElement(skyLight);

	SphereAreaLight *areaLight = NULL;
	areaLight = new SphereAreaLight(Transform::Translate(-6,-2,7),1.0, Color(0.8,0.7,0.6), 1, true, SphereAreaLight::ATT_NONE);
	areaLight->setSampling(4,16);
	scene.addElement(areaLight);

	return scene;
}

Scene& GlassModelExample::createMaterials(Scene& scene)
{
	std::cout << "Creating materials..." << std::endl;

	Material* mat = NULL;


	mat = new Material("white", Color(1,1,1));
	mat->setSpecularIntensity(1.0);
	mat->setSpecularGlossiness(32);
	scene.addElement(mat);

	mat = new Material("glass", Color(0.04,0.02,0.04));
	mat->setReflection(true);
	mat->setRefraction(true);
	mat->setIOR(1.3);
	mat->setAbsorption(10);
	mat->setSpecularIntensity(0.15);
	mat->setSpecularGlossiness(64);
	scene.addElement(mat);

	mat = new Material("glossy_glass", Color(0.04,0.02,0.04));
	mat->setReflection(true);
	mat->setRefraction(true);
	mat->setIOR(1.3);
	mat->setAbsorption(0);
	mat->setSpecularIntensity(0.2);
	mat->setSpecularGlossiness(64);
	mat->setGlossy(true);
	mat->setGlossyRoughness(0.01);
	scene.addElement(mat);

	mat = NULL;

	return scene;
}
