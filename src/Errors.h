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
#include <exception>
#include <string>
#include "Constraint.h"

namespace FlyingKiwi
{
    
    class UnsatisfiableConstraint : public std::exception
    {
        
    public:
        
        UnsatisfiableConstraint( const Constraint& constraint ) :
        m_constraint( constraint ) {}
        
        ~UnsatisfiableConstraint() throw() {}
        
        const char* what() const throw()
        {
            return "The constraint can not be satisfied.";
        }
        
        const Constraint& constraint() const
        {
            return m_constraint;
        }
        
    private:
        
        Constraint m_constraint;
    };
    
    
    class UnknownConstraint : public std::exception
    {
        
    public:
        
        UnknownConstraint( const Constraint& constraint ) :
        m_constraint( constraint ) {}
        
        ~UnknownConstraint() throw() {}
        
        const char* what() const throw()
        {
            return "The constraint has not been added to the solver.";
        }
        
        const Constraint& constraint() const
        {
            return m_constraint;
        }
        
    private:
        
        Constraint m_constraint;
    };
    
    
    class DuplicateConstraint : public std::exception
    {
        
    public:
        
        DuplicateConstraint( const Constraint& constraint ) :
        m_constraint( constraint ) {}
        
        ~DuplicateConstraint() throw() {}
        
        const char* what() const throw()
        {
            return "The constraint has already been added to the solver.";
        }
        
        const Constraint& constraint() const
        {
            return m_constraint;
        }
        
    private:
        
        Constraint m_constraint;
    };
    
    
    class InternalSolverError : public std::exception
    {
        
    public:
        
        InternalSolverError() : m_msg( "An internal solver error ocurred." ) {}
        
        InternalSolverError( const char* msg ) : m_msg( msg ) {}
        
        InternalSolverError( const std::string& msg ) : m_msg( msg ) {}
        
        ~InternalSolverError() throw() {}
        
        const char* what() const throw()
        {
            return m_msg.c_str();
        }
        
    private:
        
        std::string m_msg;
    };
}
