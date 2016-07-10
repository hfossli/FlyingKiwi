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
#include "Constraint.h"
#include "SolverImpl.h"
#include "Strength.h"
#include "Variable.h"

namespace FlyingKiwi
{
    
    class Solver
    {
        
    public:
        
        Solver() {}
        
        ~Solver() {}
        
        /* Add a constraint to the solver.
         
         Throws
         ------
         DuplicateConstraint
         The given constraint has already been added to the solver.
         
         UnsatisfiableConstraint
         The given constraint is required and cannot be satisfied.
         
         InternalSolverError
         The objective is unbounded – can not optimize.
         
         */
        void addConstraint( const Constraint& constraint )
        {
            m_impl.addConstraint( constraint );
        }
        
        /* Remove a constraint from the solver.
         
         Throws
         ------
         UnknownConstraint
         The given constraint has not been added to the solver.
         
         InternalSolverError
         The objective is unbounded – can not optimize.
         
         */
        void removeConstraint( const Constraint& constraint )
        {
            m_impl.removeConstraint( constraint );
        }
        
        /* Test whether a constraint has been added to the solver.
         
         */
        bool hasConstraint( const Constraint& constraint )
        {
            return m_impl.hasConstraint( constraint );
        }
        
        /* Reevaluate will look for changes in constants and update constraints relying on them.
         
         Throws
         ------
         InternalSolverError
         The objective is unbounded – can not optimize.
         
         */
        void reevaluateConstants()
        {
            m_impl.reevaluateConstants();
        }
        
        /* Update the values of the external solver variables.
         
         */
        void updateVariables()
        {
            m_impl.updateVariables();
        }
        
        /* Reset the solver to the empty starting condition.
         
         This method resets the internal solver state to the empty starting
         condition, as if no constraints or edit variables have been added.
         This can be faster than deleting the solver and creating a new one
         when the entire system must change, since it can avoid unecessary
         heap (de)allocations.
         
         */
        void reset()
        {
            m_impl.reset();
        }
        
    private:
        
        Solver( const Solver& );
        
        Solver& operator=( const Solver& );
        
        impl::SolverImpl m_impl;
    };
    
}