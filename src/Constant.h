//
//  constants.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//


#pragma once
#include <memory>
#include <string>
#include "SharedData.h"

namespace FlyingKiwi
{
    
class Constant
{
        
public:

	Constant( const std::string& name ) :
        m_data( new ConstantData( name ) ) {}
    
    Constant( const char* name ) :
        m_data( new ConstantData( name ) ) {}

	Constant( double value ) :
		m_data( new ConstantData( value ) ) {}

	~Constant() {}
    
	const std::string& name() const
	{
		return m_data->m_name;
	}

	void setName( const char* name )
	{
		m_data->m_name = name;
	}

	void setName( const std::string& name )
	{
		m_data->m_name = name;
	}

	double value() const
	{
		return m_data->m_value;
	}

	void setValue( double value )
	{
        if(!m_data->editable)
        {
            std::cerr << "Error: Can not change value of a plain double container\n";
            exit(-1);
        }
        else
        {
            m_data->m_value = value;
        }
	}
    
    const bool editable() const
    {
        return m_data->editable;
    }
    
    bool operator==( const Constant& other ) const
    {
        return m_data == other.m_data;
    }

	bool operator<( const Constant& other ) const
	{
		return m_data < other.m_data;
	}

private:

    class ConstantData : public SharedData
	{

	public:

		ConstantData( const std::string& name ) :
			SharedData(),
			m_name( name ),
			m_value( 0.0 ),
            editable( true ) {}

		ConstantData( const char* name ) :
			SharedData(),
			m_name( name ),
			m_value( 0.0 ),
            editable( true ) {}

		ConstantData( double value ) :
			SharedData(),
			m_name( "" ),
			m_value( value ),
            editable( false ) {}

		~ConstantData() {}

		std::string m_name;
		double m_value;
        bool editable;

	private:

		ConstantData( const ConstantData& other );

		ConstantData& operator=( const ConstantData& other );
	};

    SharedDataPtr<ConstantData> m_data;
};
    
}
