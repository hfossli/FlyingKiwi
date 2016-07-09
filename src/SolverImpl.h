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
        typedef kiwi::impl::MapType<Constant, SimpleTerm>::Type ConstantValueMap;
            
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
                kiwi::Constraint c( constraintFromConstraint( constraint ) );
                m_constraintMap[ constraint ] = c;
                m_solver.addConstraint( c );
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
            
            /* Remove a constraint from the solver.
             
             Throws
             ------
             UnknownConstraint
             The given constraint has not been added to the solver.
             
             */
            void removeConstraint( const Constraint& constraint )
            {
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
            
            void setConstantValue( const Constant& constant, double value )
            {
                SimpleTerm term( value );
                m_constantValues[ constant ] = term;
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
            
            
            
            SolverImpl( const SolverImpl& );
            
            SolverImpl& operator=( const SolverImpl& );
            
            ConstantValueMap m_constantValues;
            ConstraintMap m_constraintMap;
            VariableMap m_variableMap;
            kiwi::Solver m_solver;
        };
        
    }
    
}