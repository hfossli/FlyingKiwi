// Author: Håvard Fossli <hfossli@gmail.com>
//
// Copyright (c) 2013 Agens AS (http://agens.no/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include <algorithm>


namespace FlyingKiwi
{

namespace strength
{

inline double create( double a, double b, double c, double w = 1.0 )
{
	double result = 0.0;
	result += std::max( 0.0, std::min( 1000.0, a * w ) ) * 1000000.0;
	result += std::max( 0.0, std::min( 1000.0, b * w ) ) * 1000.0;
	result += std::max( 0.0, std::min( 1000.0, c * w ) );
	return result;
}


const double required = create( 1000.0, 1000.0, 1000.0 );

const double strong = create( 1.0, 0.0, 0.0 );

const double medium = create( 0.0, 1.0, 0.0 );

const double weak = create( 0.0, 0.0, 1.0 );


inline double clip( double value )
{
	return std::max( 0.0, std::min( required, value ) );
}

}

}
