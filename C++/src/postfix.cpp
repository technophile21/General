//
//  postfix.cpp
//  Practice
//
//  Created by Manik Singhal on 6/7/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include "postfix.h"
#include "stacks.h"
#include "Exceptions.h"
#include <math.h>

namespace Postfix {
    using DS::Stack;
    
    enum Precedence {LOWER, EQUAL, HIGHER};
    
    //opr1' precedence is <Precedence> from opr2
    Precedence comparePrecedence(int opr1, int opr2);
    bool isValidOperator(int c);
    
    double evalExpr(int op1, int op2, char operand) {
        double result;
        switch (operand) {
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            case '*':
                result = op1 * op2;
                break;
            case '/':
                if(op2)
                    result = op1 / op2;
                else
                    throw Exceptions::DivideByZero();
                break;
            case '$':
                result = pow(op1, op2);
                break;
            default:
                throw Exceptions::InvalidArgumentException();
                break;
        }
        
        return result;
    }

    double evalPostfix(const std::string& expr) {
        if(expr.empty()) throw Exceptions::InvalidArgumentException();
        
        Stack<double> stk((int)expr.length());
        
        for(size_t i = 0; i < expr.length(); ++i) {
            char curChar = expr[i];
            if(isdigit((int)curChar)) {
                stk.push(std::atof(&curChar));
            } else {
                double op2 = stk.pop();
                double op1 = stk.pop();
                double exprVal = evalExpr(op1, op2, curChar);
                stk.push(exprVal);
            }
        }
        
        return stk.pop();
        
    }
    
    std::string convInfixToPostfix(const std::string& infixExpr) {
        std::string postfixExpr = "";
        DS::Stack<int> stk((int)infixExpr.length());
        
        for (size_t i = 0; i < infixExpr.length(); ++i) {
            int curChar = (int)infixExpr[i];
            if(isalnum(curChar)) {
                postfixExpr += (char)curChar;
            } else if(isValidOperator(curChar)) {
                if(stk.isEmpty())
                    stk.push(curChar);
                else {
    
                    int topVal = stk.getTop();
                    while(topVal != (int)('(') && comparePrecedence(curChar, topVal) != HIGHER) {
                        postfixExpr += (char)(stk.pop());
                        if(stk.isEmpty())
                            break;
                        topVal = stk.getTop();
                    }
                    stk.push(curChar);
                }
                
            } else if(curChar == (int)('('))
                stk.push(curChar);
            else if(curChar == (int)(')')) {
                while(stk.getTop() != '(') {
                    postfixExpr += (char)(stk.pop());
                }
                stk.pop(); //pop out '('
            }
        }
        
        while (!stk.isEmpty() && !(stk.getTop() == '(')) {
            postfixExpr += (char)(stk.pop());
        }
        
        return postfixExpr;
    }
    
    bool isValidOperator(int c) {
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '$':
                return true;
                
                break;
                
            default:
                return false;
                break;
        }
    }
    
    int getPrecedenceLevel(int opr) {
        switch (opr) {
            case '+':
            case '-':
                return 1;
                break;
            case '*':
            case '/':
                return 2;
                break;
            case '$':
                return 3;
                break;
                
            default:
                throw Exceptions::InvalidArgumentException();
                break;
        }
    }
    
    Precedence comparePrecedence(int opr1, int opr2) {
        int prcd1 = getPrecedenceLevel(opr1);
        int prcd2 = getPrecedenceLevel(opr2);
        
        if(prcd1 > prcd2) return HIGHER;
        else if (prcd1 == prcd2) return EQUAL;
        else return LOWER;
    }
    
    
}

namespace Practice {
    double evalPostfix(const std::string& expr) {
        return Postfix::evalPostfix(expr);
    }
    
    std::string getPostfixFromInfix(const std::string& infixExpr) {
        return Postfix::convInfixToPostfix(infixExpr);
    }
}