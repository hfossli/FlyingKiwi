//
//  solverimpl.h
//  Pods
//
//  Created by Maria Fossli on 06.07.2016.
//
//

#pragma once
#include <memory>
#include <string>
#include "Constraint.h"
#include "Variable.h"
#include "Constant.h"
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
            
            // TODO: initialize everything
            SolverImpl() {}
            
            ~SolverImpl() {}
            
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
                reevaluateConstants();
                
                std::vector<Constant> editable = editableConstantsInConstraint( constraint );
                storeUnknownConstants( editable );
                
                kiwi::Constraint kiwiConstraint( constraintFromConstraint( constraint ) );
                m_constraintMap[ constraint ] = kiwiConstraint;
                m_solver.addConstraint( kiwiConstraint );
            }
            
            /* Remove a constraint from the solver.
             
             Throws
             ------
             UnknownConstraint
             The given constraint has not been added to the solver.
             
             */
            void removeConstraint( const Constraint& constraint )
            {
                reevaluateConstants();
                
                typedef ConstraintMap::iterator iter_t;
                iter_t end = m_constraintMap.end();
                iter_t tuple = m_constraintMap.find( constraint );
                if(tuple != end)
                {
                    m_solver.removeConstraint( tuple->second );
                    m_constraintMap.erase( tuple );
                }
                else
                {
                    // TODO: Catch and throw exception
                    std::cerr << "Error: Can not remove a constraint never added\n";
                    exit(-1);
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
                            m_solver.removeConstraint( it->second );
                            kiwi::Constraint c = constraintFromConstraint( it->first );
                            m_constraintMap[ it->first ] = c;
                            m_solver.addConstraint( c );
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