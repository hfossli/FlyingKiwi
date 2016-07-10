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
#include <memory>
#include <string>
#include "Expression.h"
#include "Strength.h"

namespace FlyingKiwi
{
 
class Constraint
{

public:
    
    enum RelationalOperator { OP_LE, OP_GE, OP_EQ };

	Constraint() : m_data( 0 ) {}

	Constraint( const Expression& expr,
				RelationalOperator op,
				double strength = strength::required ) :
		m_data( new ConstraintData( expr, op, strength ) ) {}

	Constraint( const Constraint& other, double strength ) :
		m_data( new ConstraintData( other, strength ) ) {}

	~Constraint() {}

	const Expression& expression() const
	{
		return m_data->m_expression;
	}

	RelationalOperator op() const
	{
		return m_data->m_op;
	}

	double strength() const
	{
		return m_data->m_strength;
	}

	bool operator<( const Constraint& other ) const
	{
		return m_data < other.m_data;
	}

	bool operator==( const Constraint& other ) const
	{
		return m_data == other.m_data;
	}

	bool operator!=( const Constraint& other ) const
	{
		return m_data != other.m_data;
	}

	bool operator!() const
	{
		return !m_data;
	}

private:

	class ConstraintData : public SharedData
	{

	public:

		ConstraintData( const Expression& expr,
					    RelationalOperator op,
					    double strength ) :
			SharedData(),
			m_expression( expr ),
			m_strength( strength::clip( strength ) ),
			m_op( op ) {}

		ConstraintData( const Constraint& other, double strength ) :
			SharedData(),
			m_expression( other.expression() ),
			m_strength( strength::clip( strength ) ),
			m_op( other.op() ) {}

		~ConstraintData() {}

		Expression m_expression;
		double m_strength;
		RelationalOperator m_op;

	private:

		ConstraintData( const ConstraintData& other );

		ConstraintData& operator=( const ConstraintData& other );
	};

	SharedDataPtr<ConstraintData> m_data;
};
    
}
