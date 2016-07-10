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
#include <utility>
#include "Variable.h"
#include "Constant.h"
#include "SimpleTerm.h"

namespace FlyingKiwi
{
    
    class Term
    {
        
    public:
        
        Term( const Variable& variable ) :
            m_variable( variable ), m_coefficient( 1.0 ) {}
        
        Term( const Variable& variable, const SimpleTerm& coefficient ) :
            m_variable( variable ), m_coefficient( coefficient ) {}
        
        ~Term() {}
        
        const Variable& variable() const
        {
            return m_variable;
        }
        
        const SimpleTerm& coefficient() const
        {
            return m_coefficient;
        }
        
    private:
        
        Variable m_variable;
        SimpleTerm m_coefficient;
    };
    
}
