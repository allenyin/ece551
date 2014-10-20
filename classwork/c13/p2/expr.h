#include <iostream>
#include <sstream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#pragma once
class Expression {
    public:
        Expression() {}
        virtual ~Expression() {}
        virtual long evaluate() const = 0;
        virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
    protected:
        long num;

    public:
        NumExpression(long n) : num(n) {}
        virtual ~NumExpression() {} // nothing to deallocate, just the number.
        virtual long evaluate() const {
            return num;
        }
        virtual std::string toString() const{
            std::stringstream s;
            s << num;
            return s.str();
        }
};

class PlusExpression : public Expression {
    protected:
        Expression * lhs;
        Expression * rhs;

    public:
        PlusExpression(Expression * l, Expression *r) : lhs(l), rhs(r) {}
        virtual ~PlusExpression() {
            delete lhs;
            delete rhs;
        }
        virtual long evaluate() const {
            return (lhs->evaluate() + rhs->evaluate());
        }
        virtual std::string toString() const {
            std::stringstream s;
            s << "(" << lhs->toString() << " + " << rhs->toString() << ")";
           return s.str();
        } 
};

class MinusExpression : public Expression {
    protected:
        Expression * lhs;
        Expression * rhs;

    public:
        MinusExpression(Expression * l, Expression *r) : lhs(l), rhs(r) {}
        virtual ~MinusExpression() {
            delete lhs;
            delete rhs;
        }
        virtual long evaluate() const {
            return (lhs->evaluate() - rhs->evaluate());
        }
        virtual std::string toString() const {
            std::stringstream s;
            s << "(" << lhs->toString() << " - " << rhs->toString() << ")";
           return s.str();
        } 
};

class TimesExpression : public Expression {
    protected:
        Expression * lhs;
        Expression * rhs;

    public:
        TimesExpression(Expression * l, Expression *r) : lhs(l), rhs(r) {}
        virtual ~TimesExpression() {
            delete lhs;
            delete rhs;
        }
        virtual long evaluate() const {
            return (lhs->evaluate() * rhs->evaluate());
        }
        virtual std::string toString() const {
            std::stringstream s;
            s << "(" << lhs->toString() << " * " << rhs->toString() << ")";
           return s.str();
        } 
};

class DivExpression : public Expression {
    protected:
        Expression * lhs;
        Expression * rhs;

    public:
        DivExpression(Expression * l, Expression *r) : lhs(l), rhs(r) {}
        virtual ~DivExpression() {
            delete lhs;
            delete rhs;
        }
        virtual long evaluate() const {
            // cannot divide by 0
            assert(rhs->evaluate() != 0);
            return (lhs->evaluate() / rhs->evaluate());
        }
        virtual std::string toString() const {
            std::stringstream s;
            s << "(" << lhs->toString() << " / " << rhs->toString() << ")";
           return s.str();
        } 
};
