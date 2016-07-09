//
//  Variable.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//

#pragma once
#include <memory>
#include <string>


namespace FlyingKiwi
{
    
    class Variable
    {
        
    public:
        
        Variable( const std::string& name ) :
            m_data( new VariableData( name ) ) {}
        
        Variable( const char* name ) :
            m_data( new VariableData( name ) ) {}
        
        Variable( double value ) :
            m_data( new VariableData( value) ) {}
        
        ~Variable() {}
        
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
            assert(!m_data->locked);
            m_data->m_value = value;
        }
        
        // operator== is used for symbolics
        bool equals( const Variable& other )
        {
            return m_data == other.m_data;
        }
        
        bool operator<( const Variable& other ) const
        {
            return m_data < other.m_data;
        }
        
    private:
        
        class VariableData : public SharedData
        {
            
        public:
            
            VariableData( const std::string& name ) :
                SharedData(),
                m_name( name ),
                m_value( 0.0 ),
                locked( false )  {}
                
            VariableData( const char* name ) :
                SharedData(),
                m_name( name ),
                m_value( 0.0 ),
                locked( false )  {}
                
            VariableData( double value ) :
                SharedData(),
                m_name( "" ),
                m_value( value ),
                locked( true ) {}
            
            ~VariableData() {}
            
            std::string m_name;
            double m_value;
            bool locked;
            
        private:
            
            VariableData( const VariableData& other );
            
            VariableData& operator=( const VariableData& other );
        };
        
        SharedDataPtr<VariableData> m_data;
    };
    
}