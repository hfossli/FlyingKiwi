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
#include "Constraint.h"
#include "Expression.h"
#include "SimpleTerm.h"
#include "Term.h"
#include "Variable.h"


namespace FlyingKiwi
{
    
    
// Constant multiply, divide, and unary invert
// TODO: Remove excessive? Implicit casting
//inline
//SimpleTerm operator*( const Constant& constant, const Constant& constant2 )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_MULTIPLY, constant2 );
//}
//
//inline
//SimpleTerm operator/( const Constant& constant, const Constant& constant2 )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_DIVIDE, constant2 );
//}
//
//inline
//SimpleTerm operator-( const Constant& constant, const Constant& constant2 )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_SUBTRACT, constant2 );
//}
//
//inline
//SimpleTerm operator+( const Constant& constant, const Constant& constant2 )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_ADD, constant2 );
//}
//
inline
SimpleTerm operator-( const Constant& constant )
{
    return SimpleTerm( constant, SimpleTerm::OP_MULTIPLY, Constant( -1.0, false ) );
}
    
 
// SimpleTerm multiply, divide and unary invert
// TODO: Remove excessive ?
//inline
//SimpleTerm operator*( const SimpleTerm& term, const Constant& constant )
//{
//    return SimpleTerm( term, SimpleTerm::OP_MULTIPLY, constant );
//}
//
//inline
//SimpleTerm operator*( const Constant& constant, const SimpleTerm& term )
//{
//    return SimpleTerm( term, SimpleTerm::OP_MULTIPLY, constant );
//}
//
//inline
//SimpleTerm operator/( const SimpleTerm& term, const Constant& constant )
//{
//    return SimpleTerm( term, SimpleTerm::OP_DIVIDE, constant );
//}
//
//inline
//SimpleTerm operator/( const Constant& constant, const SimpleTerm& term )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_DIVIDE, term );
//}
//
//inline
//SimpleTerm operator-( const SimpleTerm& constant, const Constant& term )
//{
//    return SimpleTerm( term, SimpleTerm::OP_SUBTRACT, constant );
//}
//
//inline
//SimpleTerm operator+( const SimpleTerm& constant, const Constant& constant2 )
//{
//    return SimpleTerm( constant, SimpleTerm::OP_ADD, constant2 );
//}

// SimpleTerm multiply, divide and unary invert

inline
SimpleTerm operator*( const SimpleTerm& left, const SimpleTerm& right )
{
    return SimpleTerm( left, SimpleTerm::OP_MULTIPLY, right );
}
    
inline
SimpleTerm operator/( const SimpleTerm& left, const SimpleTerm& right )
{
    return SimpleTerm( left, SimpleTerm::OP_DIVIDE, right );
}
    
inline
SimpleTerm operator-( const SimpleTerm& left, const SimpleTerm& right )
{
    return SimpleTerm( left, SimpleTerm::OP_SUBTRACT, right );
}
    
inline
SimpleTerm operator+( const SimpleTerm& left, const SimpleTerm& right )
{
    return SimpleTerm( left, SimpleTerm::OP_ADD, right );
}
    
inline
SimpleTerm operator-( const SimpleTerm& term )
{
    return SimpleTerm( term, SimpleTerm::OP_MULTIPLY, Constant( -1.0, false) );
}
    
    
// Variable unary invert

inline
Term operator-( const Variable& variable )
{
    // TODO: Should be possible to write
    // return variable * -1.0;
	return Term( variable, Constant( -1.0, false ) );
}


// Term multiply, divide, and unary invert

inline
Term operator*( const Term& term, const SimpleTerm& coefficient )
{
	return Term( term.variable(), term.coefficient() * coefficient );
}

inline
Term operator*( const SimpleTerm& coefficient, const Term& term )
{
	return Term( term.variable(), term.coefficient() * coefficient );
}

inline
Term operator/( const Term& term, const SimpleTerm& denominator )
{
    return Term( term.variable(), term.coefficient() / denominator );
}

inline
Term operator/( const SimpleTerm& constant, const Term& denominator )
{
    SimpleTerm newTerm( Constant( 1.0, false ) / constant );
    return Term( denominator.variable(), denominator.coefficient() * newTerm );
}

inline
Term operator-( const Term& term )
{
	return Term( term.variable(), term.coefficient() * Constant( -1.0, false ) );
}


// Expression multiply, divide, and unary invert

inline
Expression operator*( const Expression& expression, const SimpleTerm& coefficient )
{
	std::vector<Term> terms;
	terms.reserve( expression.terms().size() );
	typedef std::vector<Term>::const_iterator iter_t;
	iter_t begin = expression.terms().begin();
	iter_t end = expression.terms().end();
	for( iter_t it = begin; it != end; ++it )
    {
        Term term( *it );
        Term newTerm( term.variable(), term.coefficient() * coefficient );
        terms.push_back( newTerm );
    }
	return Expression( terms, expression.constant() * coefficient );
}


inline
Expression operator/( const Expression& expression, const SimpleTerm& denominator )
{
	return expression * ( Constant( 1.0, false ) / denominator );
}


inline
Expression operator-( const Expression& expression )
{
	return expression * Constant( -1.0, false );
}


// Expression add and subtract

inline
Expression operator+( const Expression& first, const Expression& second )
{
	std::vector<Term> terms;
	terms.reserve( first.terms().size() + second.terms().size() );
	terms.insert( terms.begin(), first.terms().begin(), first.terms().end() );
	terms.insert( terms.end(), second.terms().begin(), second.terms().end() );
	return Expression( terms, first.constant() + second.constant() );
}


inline
Expression operator+( const Expression& first, const Term& second )
{
	std::vector<Term> terms;
	terms.reserve( first.terms().size() + 1 );
	terms.insert( terms.begin(), first.terms().begin(), first.terms().end() );
	terms.push_back( second );
	return Expression( terms, first.constant() );
}


inline
Expression operator+( const Expression& expression, const Variable& variable )
{
	return expression + Term( variable );
}


inline
Expression operator+( const Expression& expression, const SimpleTerm& constant )
{
	return Expression( expression.terms(), expression.constant() + constant );
}


inline
Expression operator-( const Expression& first, const Expression& second )
{
	return first + -second;
}


inline
Expression operator-( const Expression& expression, const Term& term )
{
	return expression + -term;
}


inline
Expression operator-( const Expression& expression, const Variable& variable )
{
	return expression + -variable;
}


inline
Expression operator-( const Expression& expression, const SimpleTerm& constant )
{
	return expression + -constant;
}


// Term add and subtract

inline
Expression operator+( const Term& term, const Expression& expression )
{
	return expression + term;
}


inline
Expression operator+( const Term& first, const Term& second )
{
	std::vector<Term> terms;
	terms.reserve( 2 );
	terms.push_back( first );
	terms.push_back( second );
	return Expression( terms );
}


inline
Expression operator+( const Term& term, const Variable& variable )
{
	return term + Term( variable );
}


inline
Expression operator+( const Term& term, const SimpleTerm& constant )
{
	return Expression( term, constant );
}


inline
Expression operator-( const Term& term, const Expression& expression )
{
	return -expression + term;
}


inline
Expression operator-( const Term& first, const Term& second )
{
	return first + -second;
}


inline
Expression operator-( const Term& term, const Variable& variable )
{
	return term + -variable;
}


inline
Expression operator-( const Term& term, const SimpleTerm& constant )
{
	return term + -constant;
}


// Variable add and subtract

inline
Expression operator+( const Variable& variable, const Expression& expression )
{
	return expression + variable;
}


inline
Expression operator+( const Variable& variable, const Term& term )
{
	return term + variable;
}


inline
Expression operator+( const Variable& first, const Variable& second )
{
	return Term( first ) + second;
}


inline
Expression operator+( const Variable& variable, const SimpleTerm& constant )
{
	return Term( variable ) + constant;
}


inline
Expression operator-( const Variable& variable, const Expression& expression )
{
	return variable + -expression;
}


inline
Expression operator-( const Variable& variable, const Term& term )
{
	return variable + -term;
}


inline
Expression operator-( const Variable& first, const Variable& second )
{
	return first + -second;
}


inline
Expression operator-( const Variable& variable, const SimpleTerm& constant )
{
	return variable + -constant;
}


// Double add and subtract

inline
Expression operator+( const SimpleTerm& constant, const Expression& expression )
{
	return expression + constant;
}


inline
Expression operator+( const SimpleTerm& constant, const Term& term )
{
	return term + constant;
}


inline
Expression operator+( const SimpleTerm& constant, const Variable& variable )
{
	return variable + constant;
}


inline
Expression operator-( const SimpleTerm& constant, const Expression& expression )
{
	return -expression + constant;
}


inline
Expression operator-( const SimpleTerm& constant, const Term& term )
{
	return -term + constant;
}


inline
Expression operator-( const SimpleTerm& constant, const Variable& variable )
{
	return -variable + constant;
}


// Expression relations

inline
Constraint operator==( const Expression& first, const Expression& second )
{
    return Constraint( first - second, Constraint::OP_EQ );
}


inline
Constraint operator==( const Expression& expression, const Term& term )
{
	return expression == Expression( term );
}


inline
Constraint operator==( const Expression& expression, const Variable& variable )
{
	return expression == Term( variable );
}


inline
Constraint operator==( const Expression& expression, const SimpleTerm& constant )
{
    std::vector<Term> terms;
	return expression == Expression( terms, constant );
}


inline
Constraint operator<=( const Expression& first, const Expression& second )
{
	return Constraint( first - second, Constraint::OP_LE );
}


inline
Constraint operator<=( const Expression& expression, const Term& term )
{
	return expression <= Expression( term );
}


inline
Constraint operator<=( const Expression& expression, const Variable& variable )
{
	return expression <= Term( variable );
}


inline
Constraint operator<=( const Expression& expression, const SimpleTerm& constant )
{
    std::vector<Term> terms;
	return expression <= Expression( terms, constant );
}


inline
Constraint operator>=( const Expression& first, const Expression& second )
{
	return Constraint( first - second, Constraint::OP_GE );
}


inline
Constraint operator>=( const Expression& expression, const Term& term )
{
	return expression >= Expression( term );
}


inline
Constraint operator>=( const Expression& expression, const Variable& variable )
{
	return expression >= Term( variable );
}


inline
Constraint operator>=( const Expression& expression, const SimpleTerm& constant )
{
    std::vector<Term> terms;
	return expression >= Expression( terms, constant );
}


// Term relations

inline
Constraint operator==( const Term& term, const Expression& expression )
{
	return expression == term;
}


inline
Constraint operator==( const Term& first, const Term& second )
{
	return Expression( first ) == second;
}


inline
Constraint operator==( const Term& term, const Variable& variable )
{
	return Expression( term ) == variable;
}


inline
Constraint operator==( const Term& term, const SimpleTerm& constant )
{
	return Expression( term ) == constant;
}


inline
Constraint operator<=( const Term& term, const Expression& expression )
{
	return expression >= term;
}


inline
Constraint operator<=( const Term& first, const Term& second )
{
	return Expression( first ) <= second;
}


inline
Constraint operator<=( const Term& term, const Variable& variable )
{
	return Expression( term ) <= variable;
}


inline
Constraint operator<=( const Term& term, const SimpleTerm& constant )
{
	return Expression( term ) <= constant;
}


inline
Constraint operator>=( const Term& term, const Expression& expression )
{
	return expression <= term;
}


inline
Constraint operator>=( const Term& first, const Term& second )
{
	return Expression( first ) >= second;
}


inline
Constraint operator>=( const Term& term, const Variable& variable )
{
	return Expression( term ) >= variable;
}


inline
Constraint operator>=( const Term& term, const SimpleTerm& constant )
{
	return Expression( term ) >= constant;
}


// Variable relations
inline
Constraint operator==( const Variable& variable, const Expression& expression )
{
	return expression == variable;
}


inline
Constraint operator==( const Variable& variable, const Term& term )
{
	return term == variable;
}


inline
Constraint operator==( const Variable& first, const Variable& second )
{
	return Term( first ) == second;
}


inline
Constraint operator==( const Variable& variable, const SimpleTerm& constant )
{
	return Term( variable ) == constant;
}


inline
Constraint operator<=( const Variable& variable, const Expression& expression )
{
	return expression >= variable;
}


inline
Constraint operator<=( const Variable& variable, const Term& term )
{
	return term >= variable;
}


inline
Constraint operator<=( const Variable& first, const Variable& second )
{
	return Term( first ) <= second;
}


inline
Constraint operator<=( const Variable& variable, const SimpleTerm& constant )
{
	return Term( variable ) <= constant;
}


inline
Constraint operator>=( const Variable& variable, const Expression& expression )
{
	return expression <= variable;
}


inline
Constraint operator>=( const Variable& variable, const Term& term )
{
	return term <= variable;
}


inline
Constraint operator>=( const Variable& first, const Variable& second )
{
	return Term( first ) >= second;
}


inline
Constraint operator>=( const Variable& variable, const SimpleTerm& constant )
{
	return Term( variable ) >= constant;
}


// Double relations

inline
Constraint operator==( const SimpleTerm& constant, const Expression& expression )
{
	return expression == constant;
}


inline
Constraint operator==( const SimpleTerm& constant, const Term& term )
{
	return term == constant;
}


inline
Constraint operator==( const SimpleTerm& constant, const Variable& variable )
{
	return variable == constant;
}


inline
Constraint operator<=( const SimpleTerm& constant, const Expression& expression )
{
	return expression >= constant;
}


inline
Constraint operator<=( const SimpleTerm& constant, const Term& term )
{
	return term >= constant;
}


inline
Constraint operator<=( const SimpleTerm& constant, const Variable& variable )
{
	return variable >= constant;
}


inline
Constraint operator>=( const SimpleTerm& constant, const Expression& expression )
{
	return expression <= constant;
}


inline
Constraint operator>=( const SimpleTerm& constant, const Term& term )
{
	return term <= constant;
}


inline
Constraint operator>=( const SimpleTerm& constant, const Variable& variable )
{
	return variable <= constant;
}


// Constraint strength modifier

inline
Constraint operator|( const Constraint& constraint, double strength )
{
	return Constraint( constraint, strength );
}


inline
Constraint operator|( double strength, const Constraint& constraint )
{
	return constraint | strength;
}

} // namespace kiwi
