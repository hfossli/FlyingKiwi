//
//  Expression.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//

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
