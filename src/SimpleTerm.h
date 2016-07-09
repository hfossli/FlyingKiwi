//
//  SimpleTerm.h
//  Demo
//
//  Created by Maria Fossli on 08.07.2016.
//  Copyright © 2016 Acme. All rights reserved.
//

#include <utility>
#include "Constant.h"

namespace FlyingKiwi
{
    
class SimpleTerm
{
    
public:
    
    enum RelationalOperator { multiply, add };
    
    SimpleTerm() :
        m_data( new SimpleTermData() ) {}
    
    SimpleTerm( const Constant& leaf ) :
        m_data( new SimpleTermData( leaf ) ) {}
    
    SimpleTerm( const SimpleTerm& tree, const RelationalOperator relationOperator, const Constant& leaf ) :
        m_data( new SimpleTermData( tree, relationOperator, leaf ) ) {}
    
    ~SimpleTerm() {}
    
    const SimpleTerm* tree() const
    {
        assert(m_data->m_tree != NULL);
        return m_data->m_tree;
    }
    
    const Constant& leaf() const
    {
        return m_data->m_leaf;
    }
    
    const RelationalOperator relationOperator() const
    {
        return m_data->m_operator;
    }
    
    const bool isLeaf() const
    {
        return m_data->m_tree == NULL;
    }
    
    // operator== is used for symbolics
    const bool equals( const SimpleTerm& other ) const
    {
        return m_data == other.m_data;
    }
    
    const bool operator<( const SimpleTerm& other ) const
    {
        return m_data < other.m_data;
    }
    
private:

	class SimpleTermData : public SharedData
	{

	public:
        
        SimpleTermData( ) :
            m_tree( nullptr ), m_leaf( 0.0 ) {}
        
        SimpleTermData( const Constant& leaf ) :
            m_tree( nullptr ), m_leaf( leaf ) {}
        
        SimpleTermData( const SimpleTerm& tree, const RelationalOperator relationOperator, const Constant& leaf ) :
            m_tree( new SimpleTerm( tree ) ), m_operator(relationOperator), m_leaf( leaf ) {}

		~SimpleTermData() {}
        
        Constant m_leaf;
        SimpleTerm *m_tree;
        RelationalOperator m_operator;

	private:

		SimpleTermData( const SimpleTermData& other );

		SimpleTermData& operator=( const SimpleTermData& other );
	};
    
    SharedDataPtr<SimpleTermData> m_data;
};
    
}