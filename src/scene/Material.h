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
// Material.h - Created on 2008.12.09
//

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>
#include "Color.h"

class Material
{
public:
	enum Shading
	{
		SHADING_CONSTANT,
		SHADING_PHONG,
		SHADING_BLINN
	};

	Material(const std::string& name)
		: m_name(name), m_specularIntensity(0.5), m_specularGlossiness(16),
		m_specularColor(Color(1.0,1.0,1.0)), m_diffuseColor(Color(0.9,0.9,0.9)),
		m_ambientColor(Color(0.5,0.5,0.5)),
		m_reflection(false), m_refraction(false), m_fresnelExponent(1.0), m_ior(1.0), m_absorption(0.0),
		m_glossy(false), m_glossyRoughness(0.0), m_glossySamples(4), m_emission(0.0) {}

	Material(const std::string& name, const Color& diffuse)
		: m_name(name), m_specularIntensity(0.5), m_specularGlossiness(16),
		m_specularColor(Color(1.0,1.0,1.0)), m_diffuseColor(diffuse),
		m_ambientColor(diffuse),
		m_reflection(false), m_refraction(false), m_fresnelExponent(1.0), m_ior(1.0), m_absorption(0.0),
		m_glossy(false), m_glossyRoughness(0.0), m_glossySamples(4), m_emission(0.0) {}

	void setSpecularIntensity(const double specularIntensity)
									{m_specularIntensity=specularIntensity;}
	void setSpecularGlossiness(const unsigned int specularGlossiness)
									{m_specularGlossiness=specularGlossiness;}
	void setSpecularColor(const Color& specular) {m_specularColor=specular;}
	void setDiffuseColor(const Color& diffuse) {m_diffuseColor=diffuse;}
	void setAmbientColor(const Color& ambient) {m_ambientColor=ambient;}
	void setReflection(const bool reflection) {m_reflection=reflection;}
	void setRefraction(const bool refraction) {m_refraction=refraction;}
	void setFresnelExponent(const double fresnelExponent) {m_fresnelExponent=fresnelExponent;}
	void setIOR(const double ior) {m_ior=ior;}
	void setAbsorption(const double absorption) {m_absorption=absorption;}
	void setGlossy(const bool glossy) {m_glossy=glossy;}
	void setGlossyRoughness(const double value) {m_glossyRoughness=value;}
	void setGlossySamples(const unsigned int samples) {m_glossySamples=samples;}
	void setEmission(const double emission) {m_emission=emission;}

	const std::string& getName() const {return m_name;}
	double getSpecularIntensity() const {return m_specularIntensity;}
	unsigned int getSpecularGlossiness() const {return m_specularGlossiness;}
	const Color& getSpecularColor() const {return m_specularColor;}
	const Color& getDiffuseColor() const {return m_diffuseColor;}
	const Color& getAmbientColor() const {return m_ambientColor;}
	bool getReflection() const {return m_reflection;}
	bool getRefraction() const {return m_refraction;}
	double getFresnelExponent() const {return m_fresnelExponent;}
	double getIOR() const {return m_ior;}
	double getAbsorption() const {return m_absorption;}
	bool getGlossy() const {return m_glossy;}
	double getGlossyRoughness() const {return m_glossyRoughness;}
	unsigned int getGlossySamples() const {return m_glossySamples;}
	double getEmission() const {return m_emission;}

private:
	const std::string m_name;
	double m_specularIntensity;
	unsigned int m_specularGlossiness;
	Color m_specularColor;
	Color m_diffuseColor;
	Color m_ambientColor;
	bool m_reflection;
	bool m_refraction;
	double m_fresnelExponent;
	double m_ior;
	double m_absorption;
	bool m_glossy;
	double m_glossyRoughness;
	unsigned int m_glossySamples;
	double m_emission;
};

#endif /* _MATERIAL_H_ */
