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
// BucketOrder.h - Created on 2008.12.10
//

#ifndef _BUCKETORDER_H_
#define _BUCKETORDER_H_

#include <list>
#include "Bucket.h"

class BucketOrder
{
public:
	// size -> 2^size * 2^size
	BucketOrder(const unsigned int width, const unsigned int height,
				const unsigned int size)
		: m_width(width), m_height(height), m_size(size) {}

	unsigned int remainingBuckets() const {return m_buckets.size();}

	/// Returns the next bucket to be rendered. If there is no more buckets
	/// pending returns a Bucket::INVALID constant.
	Bucket getNextBucket()
	{
		if (m_buckets.size() > 0)
		{
			Bucket front = m_buckets.front();
			m_buckets.pop_front();
			return front;
		}
		else
		{
			return Bucket::INVALID;
		}
	}

	virtual ~BucketOrder() {}
protected:
	std::list<Bucket> m_buckets;
	const unsigned int m_width;
	const unsigned int m_height;
	const unsigned int m_size;
};

#endif /* _BUCKETORDER_H_ */
