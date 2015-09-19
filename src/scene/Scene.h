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
// Scene.h - Created on 2008.12.06
//

#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include <map>
#include <string>

#include "Color.h"

class Object;
class Light;
class Material;
class CameraMount;
class Background;

class Scene
{
public:
	Scene(const CameraMount* camera);

	void setBackground(const Background* background);
	void setCameraMount(const CameraMount* camera);
	void addElement(Object *object);
	void addElement(Light *light);
	void addElement(Material *material);

	const Background* getBackground() const;
	const CameraMount* getCameraMount() const;
	const std::list<Object*>& getObjects() const;
	const std::list<Light*>& getLights() const;
	const Material* getMaterial(const std::string& material) const;

	void setAmbientLightColor(const double r, const double g, const double b) {m_ambientLightColor.set(r,g,b);}
	void setAmbientLightIntensity(const double intensity) {m_ambientLightIntensity=intensity;}
	const Color& getAmbientLightColor() const {return m_ambientLightColor;}
	double getAmbientLightIntensity() const {return m_ambientLightIntensity;}

	~Scene();

private:
	Color m_ambientLightColor;
	double m_ambientLightIntensity;
	const Background* m_background;
	const CameraMount* m_camera;
	std::list<Object*> m_objects;
	std::list<Light*> m_lights;
	mutable std::map<const std::string, Material*> m_materials;
};

#endif /* _SCENE_H */
