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
// Graphics2D.h - Created on 2008.12.05
//

#ifndef _GRAPHICS2D_H_
#define _GRAPHICS2D_H_

class Graphics2D
{
public:
	/// Inicializa la clase de graficos 2D.
	/// \param pBackBuffer	Puntero al backbuffer en donde pintar.
	/// \param nWidth		Anchura del display (en pixeles).
	/// \param nHeight		Altura del display (en pixeles).
	void init(unsigned int *pBackBuffer, const int width, const int height);

	/// Pinta un pixel sin comprobar si esta dentro de la pantalla.
	/// \param x		Coordenada X del pixel.
	/// \param y		Coordenada Y del pixel.
	/// \param color	Color del pixel.
	void putPixel(const int x, const int y, const unsigned int color)
	{
		m_pBackBuffer[x+y*m_width] = color;
	}

	/// Pinta un pixel comprobando que esta dentro de la pantalla.
	/// \param x		Coordenada X del pixel.
	/// \param y		Coordenada Y del pixel.
	/// \param color	Color del pixel.
	void putClippedPixel(const int x, const int y, const unsigned int color)
	{
		if (x < 0 || y < 0 || x >= m_width || y >= m_height) return;
		m_pBackBuffer[x+y*m_width] = color;
	}

	/// Obtiene el color de un pixel del display.
	/// \param x		Coordenada X del pixel.
	/// \param y		Coordenada Y del pixel.
	/// \return			El color del pixel.
	unsigned int getPixel(const int x, const int y) const
	{
		return m_pBackBuffer[x+y*m_width];
	}

private:
	/// Puntero al backbuffer donde se va a pintar.
	unsigned int *m_pBackBuffer;

	int m_width,	///< Anchura del display (en pixeles).
		m_height;	///< Altura del display (en pixeles).
};

#endif /* _GRAPHICS2D_H_ */
