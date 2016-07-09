//
//  SimpleTerm.h
//  Demo
//
//  Created by Maria Fossli on 08.07.2016.
//  Copyright © 2016 Acme. All rights reserved.
//

#pragma once
#include <utility>
#include "Constant.h"

namespace FlyingKiwi
{
    enum RelationalOperator { OP_MULTIPLY, OP_ADD, OP_DIVIDE, OP_SUBTRACT };
    
class SimpleTerm
{
    
public:
    
    SimpleTerm() :
        m_left( new SimpleTermData() ) {}
    
    SimpleTerm( double leaf ) :
        m_left( new SimpleTermData( leaf ) ), m_right( new SimpleTermData( 1.0 ) ), m_operator(OP_MULTIPLY) {}
    
    SimpleTerm( const Constant& leaf ) :
        m_left( new SimpleTermData( leaf ) ), m_right( new SimpleTermData( 1.0 ) ), m_operator(OP_MULTIPLY) {}
    
    SimpleTerm( const SimpleTerm& left, const RelationalOperator relationOperator, const SimpleTerm& right ) :
        m_left( new SimpleTermData( left ) ), m_right ( new SimpleTermData( right ) ), m_operator( relationOperator ) {}
    
    ~SimpleTerm() {}
    
    const bool leftIsLeaf() const
    {
        return m_left->isLeaf();
    }
    
    const bool rightIsLeaf() const
    {
        return m_right->isLeaf();
    }
    
    const SimpleTerm* leftTree() const
    {
        assert(m_left->m_tree != NULL);
        return m_left->m_tree;
    }
    
    const SimpleTerm* rightTree() const
    {
        assert(m_right->m_tree != NULL);
        return m_right->m_tree;
    }
    
    const Constant& leftLeaf() const
    {
        assert(m_left->m_tree == NULL);
        return m_left->m_leaf;
    }
    
    const Constant& rightLeaf() const
    {
        assert(m_right->m_tree == NULL);
        return m_right->m_leaf;
    }
    
    const RelationalOperator op() const
    {
        return m_operator;
    }
    
    const void editableConstantsInvolved( std::vector<Constant>& constants ) const
    {
        m_left->editableConstantsInvolved( constants );
        m_right->editableConstantsInvolved( constants );
    }
    
    const double value() const
    {
        double left = leftIsLeaf() ? leftLeaf().value() : (*leftTree()).value();
        double right = rightIsLeaf() ? rightLeaf().value() : (*rightTree()).value();
        
        switch (op())
        {
            case OP_MULTIPLY:
                return left * right;
            case OP_ADD:
                return left + right;
            case OP_DIVIDE:
                return left / right;
            case OP_SUBTRACT:
                return left - right;
            default:
                std::cerr << "Error: Unhandled relational operator in term\n";
                exit(-1);
                return 0.0;
        }
    }
    
    const bool contains( const Constant& constant ) const
    {
        return m_left->contains( constant ) || m_right->contains( constant );
    }
    
    // operator== is used for symbolics
    const bool equals( const SimpleTerm& other ) const
    {
        return m_left == other.m_left && m_right == other.m_right && m_operator == other.m_operator;
    }
    
    const bool operator<( const SimpleTerm& other ) const
    {
        return m_left < other.m_left && m_right < other.m_right;
    }
    
private:

	class SimpleTermData : public SharedData
	{

	public:
        
        SimpleTermData() :
            m_tree( nullptr ), m_leaf( 0.0 ) {}
        
        SimpleTermData( double leaf ) :
            m_tree( nullptr ), m_leaf( leaf ) {}
        
        SimpleTermData( const Constant& leaf ) :
            m_tree( nullptr ), m_leaf( leaf ) {}
        
        SimpleTermData( const SimpleTerm& tree ) :
            m_tree( new SimpleTerm( tree ) ), m_leaf( 0.0 ) {}

		~SimpleTermData() {}
        
        const bool isLeaf() const
        {
            return m_tree == NULL;
        }
        
        const void editableConstantsInvolved( std::vector<Constant>& constants ) const
        {
            if( isLeaf() )
            {
                if( m_leaf.editable() )
                {
                    constants.push_back(m_leaf);
                }
            }
            else
            {
                m_tree->editableConstantsInvolved(constants);
            }
        }
        
        const bool contains( const Constant& constant ) const
        {
            if( isLeaf() )
            {
                if( m_leaf == constant )
                {
                    return true;
                }
                return false;
            }
            else
            {
                return m_tree->contains( constant );
            }
        }
        
        Constant m_leaf;
        SimpleTerm *m_tree;

	private:

		SimpleTermData( const SimpleTermData& other );

		SimpleTermData& operator=( const SimpleTermData& other );
	};
    
    SharedDataPtr<SimpleTermData> m_left;
    SharedDataPtr<SimpleTermData> m_right;
    RelationalOperator m_operator;
};
    
}