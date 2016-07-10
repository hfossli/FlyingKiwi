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


namespace FlyingKiwi
{
    
    class Variable
    {
        
    public:
        
        Variable( const std::string& name ) :
            m_data( new VariableData( name ) ) {}
        
        Variable( const char* name ) :
            m_data( new VariableData( name ) ) {}
        
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