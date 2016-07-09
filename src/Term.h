//
//  Term.h
//  Demo
//
//  Created by Maria Fossli on 08.07.2016.
//  Copyright © 2016 Acme. All rights reserved.
//

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
