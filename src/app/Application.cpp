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
// Application.cpp - Created on 2008.12.10
//

#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Application.h"

#include "Vector.h"
#include "Point.h"
#include "Sphere.h"
#include "Disk.h"
#include "Plane.h"
#include "Ray.h"
#include "Display.h"
#include "Graphics2D.h"
#include "Core.h"
#include "PNGWriter.h"
#include "FrameBuffer.h"
#include "PointLight.h"
#include "Object.h"
#include "Material.h"
#include "FifoBucketOrder.h"
#include "RandomBucketOrder.h"
//#include "MultiChannelPixelQuantifier.h"
#include "SimplePixelQuantifier.h"
#include "PinholeCamera.h"
#include "LensCamera.h"
#include "SimpleCameraMount.h"
#include "Scene.h"
#include "SkyLight.h"
#include "Random.h"
#include "Triangle.h"
#include "SphereAreaLight.h"
#include "DiskAreaLight.h"
#include "TriangleMesh.h"
#include "LoadASC.h"

Application::Application(const unsigned int width, const unsigned int height)
{
	std::cout << "Initializing Display..." << std::endl;
	m_display = new Display(width,height);
	m_raster = new Graphics2D();
	m_raster->init(m_display->getBackBuffer(), width, height);

	std::cout << "Initializing FrameBuffer..." << std::endl;
	m_frameBuffer = new FrameBuffer(width,height);

	std::cout << "Initializing Core..." << std::endl;
	m_core = new Core(new RandomBucketOrder(width,height,6));

	m_quantifier = new SimplePixelQuantifier(m_frameBuffer);
// 	m_quantifier = new MultiChannelPixelQuantifier(m_frameBuffer);
// 	m_quantifier->addChannel(PixelQuantifier::CHANNEL_A);
// 	m_quantifier->addChannel(PixelQuantifier::CHANNEL_R);
// 	m_quantifier->addChannel(PixelQuantifier::CHANNEL_G);
// 	m_quantifier->addChannel(PixelQuantifier::CHANNEL_B);
}

Application::~Application()
{
	std::cout << "Clean up..." << std::endl;
	delete m_quantifier;
	std::cout << "  core" << std::endl;
	delete m_core;
	std::cout << "  raster" << std::endl;
	delete m_raster;
	std::cout << "  frameBuffer" << std::endl;
	delete m_frameBuffer;
	std::cout << "  display" << std::endl;
	delete m_display;
	std::cout << "end" << std::endl;
}

void Application::onRenderStart()
{
	std::cout << "Raytracing scene..." << std::endl;
}

void Application::onRenderEnd()
{
	std::cout << "Raytracing complete" << std::endl;
	std::cout << "  Primary rays: " <<
				m_core->getPrimaryRaysCount() << std::endl;

	std::cout << "  Secondary rays: " <<
				m_core->getSecondaryRaysCount() << std::endl;
}

void Application::onBucketStart(const Bucket& bucket)
{
/*
	m_raster->putPixel(bucket.x0, bucket.y0, COLOR(255, 255,255,255));
	m_raster->putPixel(bucket.x0, bucket.yd, COLOR(255, 255,0,0));
	m_raster->putPixel(bucket.xd, bucket.yd, COLOR(255, 0,255,0));
	m_raster->putPixel(bucket.xd, bucket.y0, COLOR(255, 0,0,255));
*/
	unsigned int color = 0;
	int n = Random::Instance().generate(19);

	if (n==0) color = COLOR(255, 255,0,0);
	else if (n==1) color = COLOR(255, 0,255,0);
	else if (n==2) color = COLOR(255, 0,0,255);
	else if (n==3) color = COLOR(255, 255,255,0);
	else if (n==4) color = COLOR(255, 255,0,255);
	else if (n==5) color = COLOR(255, 0,255,255);
	else if (n==6) color = COLOR(255, 255,255,255);
	else if (n==7) color = COLOR(255, 255,128,128);
	else if (n==8) color = COLOR(255, 128,255,128);
	else if (n==9) color = COLOR(255, 128,128,255);
	else if (n==10) color = COLOR(255, 255,255,128);
	else if (n==11) color = COLOR(255, 128,255,255);
	else if (n==12) color = COLOR(255, 255,128,255);
	else if (n==13) color = COLOR(255, 255,128,0);
	else if (n==14) color = COLOR(255, 255,0,128);
	else if (n==15) color = COLOR(255, 128,255,0);
	else if (n==16) color = COLOR(255, 0,255,128);
	else if (n==17) color = COLOR(255, 128,0,255);
	else if (n==18) color = COLOR(255, 0,128,255);

	unsigned int x,y;

	for (x=bucket.x0; x<=bucket.xd; x++)
	{
		m_raster->putPixel(x, bucket.y0, color);
		m_raster->putPixel(x, bucket.yd, color);
	}

	for (y=bucket.y0+1; y<=bucket.yd-1; y++)
	{
		m_raster->putPixel(bucket.x0, y, color);
		m_raster->putPixel(bucket.xd, y, color);
	}

	m_display->swapBuffers(bucket.x0, bucket.y0, bucket.xd, bucket.yd);
}

void Application::onBucketEnd(const Bucket& bucket)
{
	for (unsigned int j=bucket.y0; j<=bucket.yd; j++)
	{
		for (unsigned int i=bucket.x0; i<=bucket.xd; i++)
		{
			m_raster->putPixel(i, j, m_quantifier->getQuantifiedPixelAt(i,j));
		}
	}
	m_display->swapBuffers(bucket.x0, bucket.y0, bucket.xd, bucket.yd);
}

void Application::execute(const std::string& fileName, const unsigned int aaSamples)
{
	Scene scene(NULL);

	const double ratio = m_frameBuffer->getWidth()/(double)m_frameBuffer->getHeight();

	createScene(scene, ratio);

	boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();

	m_core->render(m_frameBuffer, &scene, 4, aaSamples, Core::JOBS_AUTO, this);

	boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();

	std::cout << "  Render time: " << (t2-t1) << std::endl;

	std::cout << "Writing image to disk..." << std::endl;

	writePNG(m_display->getBackBuffer(), m_frameBuffer->getWidth(), m_frameBuffer->getHeight(), fileName);
	std::cout << "  > " << fileName << std::endl;
}
