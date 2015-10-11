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
// Scene.cpp - Created on 2008.12.06
//

#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Material.h"
#include "CameraMount.h"
#include "LightHasGeometry.h"

Scene::Scene(const CameraMount* camera)
	: m_ambientLightColor(0,0,0), m_ambientLightIntensity(0.0), m_background(NULL), m_camera(camera)
{
	// Nothing
}

void Scene::setBackground(const Background* background)
{
	m_background = background;
}

void Scene::setCameraMount(const CameraMount* camera)
{
	m_camera = camera;
}

void Scene::addElement(Object *object)
{
	m_objects.push_back(object);
}

void Scene::addElement(Light *light)
{
	m_lights.push_back(light);

	if (light->getAttribute(LightHasGeometry::ATTRIBUTE))
	{
		LightHasGeometry *geoLight = dynamic_cast<LightHasGeometry*>(light);
		if (geoLight->showGeometry())
		{
			Material *mat = geoLight->getMaterial();
			Geometry *geo = geoLight->getGeometry();
			Object *obj = new Object(light->T, GeoPtr(geo), mat->getName(), false);
			addElement(mat);
			addElement(obj);
		}
	}
}

void Scene::addElement(Material *material)
{
	m_materials[material->getName()] = material;
}

const Background* Scene::getBackground() const
{
	return m_background;
}

const CameraMount* Scene::getCameraMount() const
{
	return m_camera;
}

const std::list<Object*>& Scene::getObjects() const
{
	return m_objects;
}

const std::list<Light*>& Scene::getLights() const
{
	return m_lights;
}

const Material* Scene::getMaterial(const std::string& material) const
{
	return m_materials[material];
}

Scene::~Scene()
{
	if (m_camera) delete m_camera;

	std::list<Object*>::iterator i;
	for (i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete (*i);
	}

	std::list<Light*>::iterator j;
	for (j = m_lights.begin(); j != m_lights.end(); j++)
	{
		delete (*j);
	}

	std::map<const std::string,Material*>::iterator k;
	for (k = m_materials.begin(); k != m_materials.end(); k++)
	{
		delete k->second;
	}
}
