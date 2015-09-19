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
// Color.h - Created on 2008.12.07
//

#ifndef _COLOR_H_
#define _COLOR_H_

#define COLOR(a,r,g,b)	((unsigned int)(	( (a) & 0xff ) << 24 |	\
											( (r) & 0xff ) << 16 |	\
											( (g) & 0xff ) << 8  |	\
											( (b) & 0xff ) ))
#define COLOR_A(a) (((a) >> 24) & 0xFF)
#define COLOR_R(r) (((r) >> 16) & 0xFF)
#define COLOR_G(g) (((g) >>8) & 0xFF)
#define COLOR_B(b) ((b) & 0xFF)

class Color
{
public:
	double r,g,b;

	Color() : r(0), g(0), b(0) {}

	Color(const double _r, const double _g, const double _b)
			: r(_r), g(_g), b(_b) {}

	Color(const Color& right)
	{
		r = right.r;
		g = right.g;
		b = right.b;
	}

	void set(const double _r, const double _g, const double _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	void applyUpperLimit(const double upper)
	{
		if (r > upper) r = upper;
		if (g > upper) g = upper;
		if (b > upper) b = upper;
	}

	unsigned int getPacketUInt() const
	{
		return COLOR(	(unsigned char) (255),
						(unsigned char) (r*255 + 0.5),
						(unsigned char) (g*255 + 0.5),
						(unsigned char) (b*255 + 0.5));
	}

	// Check equality
	bool operator==(const Color& right) const
	{
		return (r == right.r) && (g == right.g) && (b == right.b);
	};

	// Assign
	Color& operator=(const Color& right)
	{
		if (this == &right) return *this;
		r = right.r;
		g = right.g;
		b = right.b;
		return *this;
	};

	// Addition
	const Color operator+(const Color& right) const
	{
		return Color(r + right.r,
					 g + right.g,
					 b + right.b);
	}

	// Addition
	Color& operator+=(const Color& right)
	{
		r += right.r;
		g += right.g;
		b += right.b;
		return *this;
	}

	// Scale
	const Color operator*(const Color& right) const
	{
		return Color(r * right.r,
					 g * right.g,
					 b * right.b);
	}

	// Scale
	Color& operator*=(const Color& right)
	{
		r *= right.r;
		g *= right.g;
		b *= right.b;
		return *this;
	}

	// Scale
	const Color operator*(const double right) const
	{
		return Color(r*right, g*right, b*right);
	}

	// Scale
	Color& operator*=(const double right)
	{
		r *= right;
		g *= right;
		b *= right;
		return *this;
	}
};

#endif /* _COLOR_H_ */
