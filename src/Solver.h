//
//  solver.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//

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