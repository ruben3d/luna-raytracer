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
// Created on 2008.12.05
//

#include <string>
#include <iostream>

#include "BasicExample.h"
#include "GlossyExample.h"
#include "SkyLightExample.h"
#include "AreaLightExample.h"
#include "LensCameraExample.h"
#include "GlassModelExample.h"

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

void executeBasicExample()
{
	const unsigned int antiAliasingSamples = 6;

	Application *example = new BasicExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("basicExample.png", antiAliasingSamples);
	delete example;
}

void executeGlossyExample()
{
	const unsigned int antiAliasingSamples = 8;

	Application *example = new GlossyExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("glossyExample.png", antiAliasingSamples);
	delete example;
}

void executeSkyLightExample()
{
	const unsigned int antiAliasingSamples = 8;

	Application *example = new SkyLightExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("skyLightExample.png", antiAliasingSamples);
	delete example;
}

void executeAreaLightExample()
{
	const unsigned int antiAliasingSamples = 8;

	Application *example = new AreaLightExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("areaLightExample.png", antiAliasingSamples);
	delete example;
}

void executeLensCameraExample()
{
	const unsigned int antiAliasingSamples = 256;

	Application *example = new LensCameraExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("lensCameraExample.png", antiAliasingSamples);
	delete example;
}

void executeGlassModelExample()
{
	const unsigned int antiAliasingSamples = 8;

	Application *example = new GlassModelExample(SCREEN_WIDTH,SCREEN_HEIGHT);
	example->execute("glassModelExample.png", antiAliasingSamples);
	delete example;
}

int main(int, char*[])
{
	executeBasicExample();
	executeGlossyExample();
	executeSkyLightExample();
	executeAreaLightExample();
	executeLensCameraExample();
	executeGlassModelExample();

	return 0;
}
