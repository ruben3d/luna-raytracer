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
// Random.cpp - Created on 2008.12.11
//

#include <time.h>
#include "Random.h"

Random Random::m_random((int)time(NULL));

Random::Random(const int seed)
{
	a = 16807;		// 7^5
	m = 2147483647;	// 2^31-1
	q = 127773;		// m div a
	r = 2836;		// m mod a

	m_seed = seed;
}

// int size must be >= 2^31-1
void Random::seed(const int seed)
{
	m_seed = seed;
}

// As described by Mark Allen Weiss, "Estructuras de datos y algoritmos", p. 413
float Random::generate()
{
	int seed_tmp;

	seed_tmp = a*(m_seed % q) - r*(m_seed / q);
	if (seed_tmp >= 0)
		m_seed = seed_tmp;
	else
		m_seed = seed_tmp + m;

	return (float) m_seed / (float) m;
}

int Random::generate(const int num)
{
	return (int) (num * generate());
}

double Random::haltonSeq(const unsigned int index, const unsigned int base)
{
	double ret = 0;
	double fraction = 1.0 / (double) base;
	unsigned int acc = index;

	while (acc != 0)
	{
		unsigned int mod = acc % base;
		ret = ret + mod * fraction;
		acc = (acc - mod) / base;
		fraction = fraction / (double)base;
	}

	return ret;
}
