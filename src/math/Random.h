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
// Random.h - Created on 2008.12.11
//

#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{
public:
	Random(const int seed);

	void seed(const int seed);

	// [0.0-1.0)
	float generate();

	// [0-(num-1)]
	int generate(const int num);

	// [0.0-1.0)
	double haltonSeq(const unsigned int index, const unsigned int base);

	static Random &Instance() {return m_random;}
private:
	int m_seed, a, m, q, r;
	static Random m_random;
	Random(const Random&);
};

#endif /* _RANDOM_H_ */
