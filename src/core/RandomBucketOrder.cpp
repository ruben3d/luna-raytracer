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
// RandomBucketOrder.cpp - Created on 2009.01.15
//

#include <vector>
#include <algorithm>
#include "RandomBucketOrder.h"

template<typename T>
void shuffle_list(std::list<T>& l)
{
	std::vector<T> v(l.begin(), l.end());
	std::random_shuffle(v.begin(), v.end());
	l.assign( v.begin(), v.end());
}

RandomBucketOrder::RandomBucketOrder(const unsigned int width,
									const unsigned int height,
									const unsigned int size)
	: BucketOrder(width, height, size)
{
	unsigned int sqSize = 1 << size;

	unsigned int completeWidth = width/sqSize;
	unsigned int fragmentWidth = width%sqSize;

	unsigned int completeHeight = height/sqSize;
	unsigned int fragmentHeight = height%sqSize;

	unsigned int x=0;
	unsigned int y=0;
	for (y=0; y<completeHeight; y++)
	{
		for (x=0; x<completeWidth; x++)
		{
			Bucket b(x*sqSize, y*sqSize, x*sqSize+sqSize-1, y*sqSize+sqSize-1);
			m_buckets.push_back(b);
		}
		if (fragmentWidth)
		{
			m_buckets.push_back(Bucket(x*sqSize, y*sqSize,
										x*sqSize+fragmentWidth-1, y*sqSize+sqSize-1));
		}
	}
	if (fragmentHeight)
	{
		for (x=0; x<completeWidth; x++)
		{
			m_buckets.push_back(Bucket(x*sqSize, y*sqSize,
										x*sqSize+sqSize-1, y*sqSize+fragmentHeight-1));
		}
		if (fragmentWidth)
		{
			m_buckets.push_back(Bucket(x*sqSize, y*sqSize,
										x*sqSize+fragmentWidth-1, y*sqSize+fragmentHeight-1));
		}
	}

	shuffle_list(m_buckets);
}
