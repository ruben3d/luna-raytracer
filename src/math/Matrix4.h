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
// Matrix4.h - Created on 2008.12.10
//

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <cstring>

class Matrix4
{
public:
	double matrix[4][4];

	Matrix4()
	{
		memset(matrix, 0, 16*sizeof(double));
	}

	Matrix4(const Matrix4& m)
	{
		memcpy(matrix, m.matrix, 16*sizeof(double));
	}

	Matrix4(const double n00, const double n01, const double n02, const double n03,
			const double n10, const double n11, const double n12, const double n13,
			const double n20, const double n21, const double n22, const double n23,
			const double n30, const double n31, const double n32, const double n33)
	{
		matrix[0][0] = n00;	// 1st row
		matrix[0][1] = n01;
		matrix[0][2] = n02;
		matrix[0][3] = n03;
		
		matrix[1][0] = n10;	// 2nd row
		matrix[1][1] = n11;
		matrix[1][2] = n12;
		matrix[1][3] = n13;
		
		matrix[2][0] = n20;	// 3rd row
		matrix[2][1] = n21;
		matrix[2][2] = n22;
		matrix[2][3] = n23;
		
		matrix[3][0] = n30;	// 4th row
		matrix[3][1] = n31;
		matrix[3][2] = n32;
		matrix[3][3] = n33;
	}

	Matrix4& operator=(const Matrix4& m)
	{
		if (this == &m) return *this;
		memcpy(matrix, m.matrix, 16*sizeof(double));
		return *this;
	}

	const Matrix4 operator*(const Matrix4& op) const
	{
		Matrix4 res;

		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				for (int r=0; r<4; r++)
				{
					res.matrix[i][j] += matrix[i][r] * op.matrix[r][j];
				}
			}
		}

		return res;
	}

	Matrix4& operator*=(const Matrix4& op)
	{
		Matrix4 tmp(*this);

		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				for (int r=0; r<4; r++)
				{
					matrix[i][j] += tmp.matrix[i][r] * op.matrix[r][j];
				}
			}
		}

		return *this;
	}
};

#endif /* _MATRIX4_H_ */
