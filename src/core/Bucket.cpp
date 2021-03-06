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
// Bucket.cpp - Created on 2009.01.15
//

#include "Bucket.h"

const Bucket Bucket::INVALID = Bucket(0,0,0,0);

bool Bucket::operator==(const Bucket& right) const
{
	return (x0 == right.x0) && (y0 == right.y0) &&
			(xd == right.xd) && (yd == right.yd);
}

bool Bucket::operator!=(const Bucket& right) const
{
	return !(*this == right);
}
