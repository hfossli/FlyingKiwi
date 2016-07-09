//
//  Constraint.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//

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
