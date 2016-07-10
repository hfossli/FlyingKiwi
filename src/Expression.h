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
#include <vector>
#include "Constant.h"
#include "Term.h"

namespace FlyingKiwi
{

class Expression
{

public:

	Expression( double constant = 0.0 ) : m_constant( constant ) {}

	Expression( const Term& term ) :
		m_terms( 1, term ), m_constant( 0.0 ) {}

	Expression( const std::vector<Term>& terms ) :
		m_terms( terms ), m_constant( 0.0 ) {}

	Expression( const Term& term, const SimpleTerm& constant ) :
		m_terms( 1, term ), m_constant( constant ) {}

	Expression( const std::vector<Term>& terms, const SimpleTerm& constant ) :
		m_terms( terms ), m_constant( constant ) {}

	~Expression() {}

	const std::vector<Term>& terms() const
	{
		return m_terms;
	}

	const SimpleTerm& constant() const
	{
		return m_constant;
	}
    
    const bool contains( const Constant& constant ) const
    {
        if( m_constant.contains( constant ) )
        {
            return true;
        }
        
        for( auto const &term : m_terms )
        {
            if( term.coefficient().contains( constant ) )
            {
                return true;
            }
        }
        
        return false;
    }

private:

	std::vector<Term> m_terms;
	SimpleTerm m_constant;
};

}
