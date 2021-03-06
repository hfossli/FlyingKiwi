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
#include "Constraint.h"
#include "Variable.h"
#include "Constant.h"
#include "Errors.h"
#include "../kiwi/kiwi/maptype.h"
#include "../kiwi/kiwi/AssocVector.h"
#include "../kiwi/kiwi/kiwi.h"


namespace FlyingKiwi
{
    
    namespace impl
    {
        
        class SolverImpl
        {
        
        typedef kiwi::impl::MapType<Constraint, kiwi::Constraint>::Type ConstraintMap;
        typedef kiwi::impl::MapType<Variable, kiwi::Variable>::Type VariableMap;
        typedef kiwi::impl::MapType<Constant, double>::Type ConstantValues;
            
        public:
            
            SolverImpl() {}
            
            ~SolverImpl() {}
            
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
                reevaluateConstants();
                
                std::vector<Constant> editable = editableConstantsInConstraint( constraint );
                storeUnknownConstants( editable );
                
                ConstraintMap::iterator tuple = m_constraintMap.find( constraint );
                if(tuple != m_constraintMap.end())
                {
                    throw DuplicateConstraint( constraint );
                }
                else
                {
                    kiwi::Constraint kiwiConstraint( constraintFromConstraint( constraint ) );
                    m_constraintMap[ constraint ] = kiwiConstraint;
                    
                    try {
                        m_solver.addConstraint( kiwiConstraint );
                    } catch ( kiwi::UnsatisfiableConstraint &exception ) {
                        throw UnsatisfiableConstraint( constraint );
                    } catch ( kiwi::DuplicateConstraint &exception ) {
                        throw DuplicateConstraint( constraint );
                    } catch ( std::exception &exception ) {
                        throw InternalSolverError( exception.what() );
                    }
                }
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
                reevaluateConstants();
                
                ConstraintMap::iterator tuple = m_constraintMap.find( constraint );
                if(tuple != m_constraintMap.end())
                {
                    try {
                        m_solver.removeConstraint( tuple->second );
                    } catch ( kiwi::UnknownConstraint &exception ) {
                        throw UnknownConstraint( constraint );
                    } catch ( std::exception &exception ) {
                        throw InternalSolverError( exception.what() );
                    }
                    m_constraintMap.erase( tuple );
                }
                else
                {
                    throw UnknownConstraint( constraint );
                }
            }
            
            /* Test whether a constraint has been added to the solver.
             
             */
            bool hasConstraint( const Constraint& constraint )
            {
                if( m_constraintMap.find( constraint ) != m_constraintMap.end() )
                {
                    return true;
                }
                return false;
            }
            
            /* Reevaluate will look for changes in constants and update constraints relying on them.
             
             Throws
             ------
             InternalSolverError
             The objective is unbounded – can not optimize.
             
             */
            void reevaluateConstants()
            {
                std::vector<Constant> known = knownEditableConstants();
                std::vector<Constant> outdated = outdatedEditableConstants( known );
                
                updateConstraintRelyingOnConstants( outdated );
                
                for( auto const &constant : outdated )
                {
                    m_constantValues[ constant ] = constant.value();
                }
            }
            
            /* Update the values of the external solver variables.
             
             */
            void updateVariables()
            {
                m_solver.updateVariables();
                
                typedef VariableMap::iterator var_iter_t;
                var_iter_t var_end = m_variableMap.end();
                for( var_iter_t var_it = m_variableMap.begin(); var_it != var_end; ++var_it )
                {
                    Variable& var( const_cast<Variable&>( var_it->first ) );
                    kiwi::Variable& kiwiVar( const_cast<kiwi::Variable&>( var_it->second ) );
                    var.setValue( kiwiVar.value() );
                }
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
                m_constraintMap.clear();
                m_variableMap.clear();
                m_constantValues.clear();
                m_solver.reset();
            }
            
        private:
            
            void updateConstraintRelyingOnConstants( const std::vector<Constant> changedConstants )
            {
                for( auto const &constant : changedConstants )
                {
                    typedef ConstraintMap::iterator iter_t;
                    iter_t end = m_constraintMap.end();
                    for( iter_t it = m_constraintMap.begin(); it != end; ++it )
                    {
                        if( it->first.expression().contains( constant ) )
                        {
                            try {
                                kiwi::Constraint c = constraintFromConstraint( it->first );
                                m_solver.removeConstraint( it->second );
                                m_constraintMap[ it->first ] = c;
                                m_solver.addConstraint( c );
                            } catch ( std::exception &exception ) {
                                throw InternalSolverError( exception.what() );
                            }
                        }
                    }
                }
            }
        
            const std::vector<Constant> knownEditableConstants()
            {
                std::vector<Constant> constants;
                for( ConstantValues::iterator it = m_constantValues.begin(); it != m_constantValues.end(); ++it )
                {
                    constants.push_back( it->first );
                }
                return constants;
            }
            
            const std::vector<Constant> editableConstantsInConstraint( const Constraint& constraint )
            {
                std::vector<Constant> editableConstants;
                constraint.expression().constant().editableConstantsInvolved( editableConstants );
                for( auto const &term : constraint.expression().terms() )
                {
                    term.coefficient().editableConstantsInvolved( editableConstants );
                }
                return editableConstants;
            }
            
            void storeUnknownConstants( std::vector<Constant>& constants )
            {
                for( auto const &constant : constants )
                {
                    ConstantValues::iterator it = m_constantValues.find( constant );
                    if( it == m_constantValues.end() )
                    {
                        m_constantValues[ constant ] = constant.value();
                    }
                }
            }
            
            const std::vector<Constant> outdatedEditableConstants( std::vector<Constant>& constants )
            {
                std::vector<Constant> outdated;
                for( auto const &constant : constants )
                {
                    ConstantValues::iterator it = m_constantValues.find( constant );
                    if( it != m_constantValues.end() && it->second != it->first.value() )
                    {
                        outdated.push_back( constant );
                    }
                }
                return outdated;
            }
            
            kiwi::Variable variableFromVariable( const Variable& variable )
            {
                VariableMap::iterator it = m_variableMap.find( variable );
                if( it != m_variableMap.end() )
                {
                    return it->second;
                }
                kiwi::Variable var( variable.name() );
                m_variableMap[ variable ] = var;
                return var;
            }
            
            kiwi::Term termFromTerm( const Term& term )
            {
                double coefficient = term.coefficient().value();
                kiwi::Variable var( variableFromVariable( term.variable() ) );
                return kiwi::Term(var, coefficient);
            }
            
            kiwi::Expression expressionFromExpression( const Expression& expr )
            {
                std::vector<kiwi::Term> terms;
                typedef std::vector<Term>::const_iterator iter_t;
                for (auto const &x : expr.terms())
                {
                    terms.push_back( termFromTerm( x ) );
                }
                double constant = expr.constant().value();
                return kiwi::Expression( terms, constant );
            }
            
            kiwi::RelationalOperator operatorFromConstraint( const Constraint& constraint )
            {
                switch ( constraint.op() ) {
                    case Constraint::OP_LE:
                        return kiwi::OP_LE;
                    case Constraint::OP_GE:
                        return kiwi::OP_GE;
                    case Constraint::OP_EQ:
                        return kiwi::OP_EQ;
                    default:
                        return kiwi::OP_EQ;
                }
            }
            
            kiwi::Constraint constraintFromConstraint( const Constraint& constraint )
            {
                kiwi::Expression expr( expressionFromExpression( constraint.expression() ) );
                kiwi::RelationalOperator op( operatorFromConstraint( constraint ) );
                return kiwi::Constraint( expr, op, constraint.strength() );
            }
            
            SolverImpl( const SolverImpl& );
            
            SolverImpl& operator=( const SolverImpl& );
            
            ConstraintMap m_constraintMap;
            VariableMap m_variableMap;
            ConstantValues m_constantValues;
            kiwi::Solver m_solver;
        };
        
    }
    
}