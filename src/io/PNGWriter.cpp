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
// PNGWriter.cpp - Created on 2008.12.7
//

#include <png.h>
#include "PNGWriter.h"
#include "Color.h"

bool writePNG(unsigned int* imageBuffer, const unsigned int width, 	const unsigned int height, const std::string& fileName)
{
	// HACK !!!
	for (unsigned int i=0; i<width*height; i++)
	{
		imageBuffer[i] = COLOR(	
								COLOR_A(imageBuffer[i]),
								COLOR_B(imageBuffer[i]),
								COLOR_G(imageBuffer[i]),
								COLOR_R(imageBuffer[i])
								);
	}

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING,
												NULL,NULL,NULL);
	if (png == NULL)
	{
		return false;	// Sin memoria
	}

	png_infop info = png_create_info_struct(png);
	if (info == NULL)
	{
		png_destroy_write_struct(&png, NULL);
		return false;	// Sin memoria
	}

	FILE* outFile = fopen(fileName.c_str(), "w");
	png_init_io(png, outFile);

	png_set_compression_level(png, Z_BEST_COMPRESSION);

	//int colorType = PNG_COLOR_TYPE_RGB;
	int colorType = PNG_COLOR_TYPE_RGB_ALPHA;
	int interlaced = PNG_INTERLACE_NONE;

	png_set_IHDR(png, info, width, height, 8, colorType, interlaced,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png, info);

	for (unsigned int i=0; i<height; i++)
	{
		png_write_row(png, (png_byte*)(imageBuffer+i*width));
	}

	png_write_end(png, NULL);

	png_destroy_write_struct(&png, &info);
	fclose(outFile);

	return true;
}
