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
// Bucket.h - Created on 2008.12.10
//

#ifndef _BUCKET_H_
#define _BUCKET_H_

struct Bucket
{
	Bucket(const unsigned int _x0, const unsigned int _y0,
			const unsigned int _xd, const unsigned int _yd)
		: x0(_x0), y0(_y0), xd(_xd), yd(_yd) {}
	Bucket(const Bucket& right)
		: x0(right.x0), y0(right.y0), xd(right.xd), yd(right.yd) {}

	unsigned int x0, y0, xd, yd;

	static const Bucket INVALID;

	bool operator==(const Bucket& right) const;
	bool operator!=(const Bucket& right) const;
};

#endif /* _BUCKET_H_ */
