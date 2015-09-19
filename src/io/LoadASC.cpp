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
// LoadASC.cpp - Created on 2010.02.20
//

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "LoadASC.h"
#include "TriangleMesh.h"

std::vector<std::string> Split(const std::string& line, char c = ' ')
{
	std::vector<std::string> result;

	const char *begin = NULL;
	const char *str = line.c_str();
	while(1)
	{
		begin = str;
		while((*begin == c) && *begin)
			begin++;
		str = begin;
		while((*str != c) && *str)
			str++;

		result.push_back(std::string(begin,str));
		
		if(0 == *str++) break;
	}

	return result;
}

template <class T>
bool Parse(const std::string& str, T& num)
{
	std::stringstream ss(str);
	if((ss >> num).fail()) return false;
	return true;
}

template <>
bool Parse<double>(const std::string& str, double& num) 
{
	std::vector<std::string> result = Split(str, ',');
	if (result.size() != 2) return false;
	int a,b;
	if (!Parse(result[0],a)) return false;
	if (!Parse(result[1],b)) return false;
	if (result[0][0] == '-')
		num = a - b / pow(10, result[1].length());
	else
		num = a + b / pow(10, result[1].length());
	return true;
}

TriangleMesh *LoadASC(const std::string& file, const double scale)
{
	TriangleMesh *mesh = NULL;

	std::ifstream model(file.c_str(), std::ios::in);

	if (!model)
	{
		return NULL;
	}

	std::string line;
	std::vector<std::string> result;

	std::getline(model,line);	// Blank
	std::getline(model,line);	// Name
	std::getline(model,line);	// Info

	result = Split(line,' ');
	unsigned int vertices, faces;
	Parse(result[2], vertices);
	Parse(result[4], faces);

	mesh = new TriangleMesh(vertices, faces);

	std::getline(model,line);	// "Vertex list:"

	unsigned int i = 0;
	for (i=0; i<vertices; i++)
	{
		std::getline(model,line);
		// HACK A bug in the Split function returns an additional char in the last token (probably endl).
		line = line.substr(0,line.length()-1);
		result = Split(line,' ');
		double x=0, y=0, z=0;
		Parse(result[3],x);
		Parse(result[5],y);
		Parse(result[7],z);
		mesh->setVertex(i, Point(x*scale,y*scale,z*scale));
	}

	std::getline(model,line);	// "Face list:"

	for (i=0; i<faces; i++)
	{
		std::getline(model,line);
		result = Split(line,' ');
		unsigned int v0=0, v1=0, v2=0;
		Parse(result[2].substr(2),v0);
		Parse(result[3].substr(2),v1);
		Parse(result[4].substr(2),v2);
		mesh->setFace(i, v0,v1,v2);
		std::getline(model,line);
	}

	return mesh;
}
