//
// Created by mac on 12/05/17.
//

#ifndef IENGINE_BC_HPP
#define IENGINE_BC_HPP

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <vector>
#include <queue>
#include <unordered_map>
#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include <algorithm>
#include <InferenceEngine/Parsing/Private/Lexer.hpp>

namespace ie {


    class BC {

    public:

        std::string outputRes = "";
        std::string recentOperator = "";

        bool bc_entails(std::vector<const ComplexSentence *> rules, const std::string goal,
                        std::map<std::string, bool> trueSymbols) {
            std::stack<std::vector<const ComplexSentence *>> goals;

            ClauseFinder clause;

            //first rule to search is the goal rule
            auto* sent = find_rule_with_symbol(rules, goal, clause);

            std::vector<const ComplexSentence *> complList;
            complList.push_back(sent);

            //Now in our list of unsolved
            goals.push(complList);

            //find symbols in a clause
            while(!rules.empty()) {

                //Goal check
                auto goalsCopy = goals;

//                //make copy of true symbols
//                std::map<std::string, bool> trueSymbolsCopy;
//                for(auto p : trueSymbols){
//                    trueSymbolsCopy.insert(p);
//                }

                bool res = get_result(goalsCopy, trueSymbols);
                if(res){
                    return true;
                }


                search(rules, goals, trueSymbols);



                //Print current goals

            }

            return false;

        }

        void search(std::vector<const ComplexSentence *>& rules, std::stack<std::vector<const ComplexSentence*>>& goals,
                     std::map<std::string, bool> trueSymbols){


                ClauseFinder clause;
                bool res = find_symbol_premise_match(trueSymbols, clause, rules, goals);

        }


        bool find_symbol_premise_match(std::map<std::string, bool> trueSymbols, ClauseFinder clause,
                                       std::vector<const ComplexSentence*>& rules,
                                       std::stack<std::vector<const ComplexSentence*>>& goals){

            std::vector<const ComplexSentence*> top;
            std::vector<const ComplexSentence*> rulesToAdd;

            //create vector of compl sent
            for(auto t : goals.top()){
                top.push_back(t);
            }

            std::vector<const ComplexSentence*> newTop;

            for(auto c : top){
                c->left()->accept(clause);
                auto symList = clause.symbols();
                clause.clear();
                for(auto r : rules){

                    auto con = r->connective();

                    r->right()->accept(clause);
                    for(auto rhsSym : clause.symbols()){
                        for(auto lhsSym : symList){
                            if(lhsSym == rhsSym){
                                //no duplicates
                                bool canAdd = true;
                                for(auto it = rulesToAdd.begin(); it != rulesToAdd.end(); it++){
                                    if(*it == r){
                                        canAdd = false;
                                    }
                                }
                                if(canAdd){

                                    rulesToAdd.push_back(r);
                                }

                            }
                        }
                    }
                    clause.clear();
                }
            }

            ClauseFinder c;
            for(auto newGoalTop : rulesToAdd){
                newGoalTop->accept(c);
                newTop.push_back(newGoalTop);

                std::cout << "new goal symbols: ";
                for(auto g : c.symbols()){
                    std::cout << g << " ";
                }
                std::cout << std::endl;

                c.clear();
            }



            //new vector of compl sentences for next goal
            goals.push(newTop);

        }


        bool get_result(std::stack<std::vector<const ComplexSentence*>>& goalsCopy, std::map<std::string, bool>& trueSymbols){

            //if we have made it to a fully emptied stack of premises then we have solved it
            if(goalsCopy.empty()){
                return true;
            }


            ClauseFinder clause;
            ResolutionVisitor r;
            bool result = false;

            // ---------------------------------------------
            //we check if we can solve the top of the stack
            // ---------------------------------------------

            std::vector<const ComplexSentence*> topCopy;
            for(auto a :goalsCopy.top()){
                topCopy.push_back(a);
            }
            std::cout << "topCopy size: " << topCopy.size() << std::endl;
            //remove from stack copy
            goalsCopy.pop();

            // --------------------------------------------------------------------------------
            //Create a map of our top of stack copy so we can check them off as being solvable
            // --------------------------------------------------------------------------------

            std::map<const ComplexSentence*, bool> copyChecks;
            for(auto comp : topCopy){
                copyChecks.insert(std::make_pair(comp, false));
            }

            // -------------------------------------------------------------------------------------
            //Check lhs symbols of each complex & then see if we have all the symbols to solve them
            // -------------------------------------------------------------------------------------

            for(auto& complex : copyChecks){
                complex.first->left()->accept(clause);
                auto lhsSymbols = clause.symbols();

                //if we loop a lhs symbol against our trueSymbols and it is not known - we break, as we cannot solve
                for(auto sym : lhsSymbols){
                    bool symIsKnown = false;
                    for(auto tSym : trueSymbols){
                        if(sym == tSym.first){
                            symIsKnown = true;
                        }
                    }

                    if(!symIsKnown){
                        return false;
                    }
                }

                //If it makes it here then we the sym is known1
                complex.second = true;
                clause.clear();
            }

            // ---------------------------------------------------------------------------------
            //if any of our sentences were unsolvable we return false (no solving at this point)
            // ---------------------------------------------------------------------------------

            for(auto res : copyChecks){
                //if any are unsolvable we return false
                if(!res.second){
                    return false;
                }
            }

            // ---------------------------------------------------------------------------------------------------------
            //              TIME TO CALCULATE THE RESULT FOR NEXT STACK ITEM - WE CAN SOLVE FROM HERE
            //We now have the ability to solve this complex, we will now solve it and pop the next complex of the stack!
            // ---------------------------------------------------------------------------------------------------------
            ClauseFinder c;
            ClauseFinder c2;
            std::vector<std::string> resultList;
            const std::vector<std::string> lhsSymbols;
            const std::vector<std::string> rhsSymbols;

            //WE ARE ASSUMING THE RHS IS ONLY GOING TO BE 1!
            TokenType conLHS;
            for(auto complex : topCopy) {
                //get left and right side
                complex->left()->accept(c);

                std::cout << "Symbols LHS: ";
                for(auto pr : c.symbols()){
                    std::cout << pr << " ";
                }
                std::cout <<std::endl;

                complex->right()->accept(c2);
                std::cout << "Symbols LHS: ";
                for(auto pr : c2.symbols()){
                    std::cout << pr << " ";
                }
                std::cout <<std::endl;

                conLHS = complex->connective();

                //ISSUE

                if(conLHS == TokenType::disjunction || conLHS == TokenType::conjunction){
                    //CONNECTIVE NOT COMING THORUGH AS ANYTHING BUT IMPLCIATION?

                }

                bool resRHS;
                if(c.symbols().size() == 1){
                    //should be in look up if we have reached here
                    resRHS = calculate(conLHS, trueSymbols[c.symbols()[0]]);
                    outputRes += c.symbols()[0] + " ";
                }
                else{
                    //get res of l & r side
                    resRHS = calculate(conLHS, trueSymbols[c.symbols()[0]], trueSymbols[c.symbols()[1]]);
                    outputRes += c.symbols()[0] + " " + recentOperator + " " + c.symbols()[1];
                }

                //assume RHS is only 1
                trueSymbols.insert(std::make_pair(c2.symbols()[0], resRHS));
                outputRes += " => " + c2.symbols()[0] + " ; ";

                c.clear();
                c2.clear();
            }

            return get_result(goalsCopy, trueSymbols);

        };

        bool calculate(TokenType logic_operator, bool lVal, bool rVal){

            switch (logic_operator){
                //Must be at the top because if negation then rVal has not been calculated
                case TokenType ::negation:
                    return !rVal;
                case TokenType ::conjunction:
                    recentOperator = "&";
                    return lVal && rVal;
                case TokenType ::disjunction:
                    recentOperator = "|";
                    return lVal || rVal;
                case TokenType ::implication:
                    recentOperator = "=>";
                    // A => B |  Truth table - full and complete truth-table options for brevity
                    if(lVal && rVal){
                        return true;
                    }
                    else if(!lVal && !rVal){
                        return true;
                    }
                    else if(lVal && !rVal){
                        return false;
                    }
                    else if(!lVal && rVal){
                        return true;
                    }

                default:
                    std::cerr << "Error with operator calculation " << std::endl;
                    break;
            }
        }

        bool calculate(TokenType logic_operator, bool lVal){

            //any result on LHS of implication is a RHS True
            switch (logic_operator){
                case TokenType ::implication:
                    recentOperator = "=>";
                    return true;
                default:
                std::cerr << "single operator calc error";
                    break;
            }
        }


        void copy_stack(std::stack<const ComplexSentence*> oldStack, std::stack<const ComplexSentence *>& newStack)
        {
            while(!oldStack.empty()) {
                newStack.push((oldStack.top()));
                oldStack.pop();
            }
        }

        const ComplexSentence* find_rule_with_symbol(std::vector<const ComplexSentence*>& rules, std::string searchSym, ClauseFinder clause){
            //Look through rules searching for the one that contains the symbol we are querying for
            // return that rule
            for(auto* rule : rules){

                auto con = rule->connective();

                rule->right()->accept(clause);




                for(auto sym : clause.symbols()){
                    //if this symbol exisit in this rule return it
                    if(sym == searchSym){


                        std::cout << std::endl;

                        auto* ruleCopy = (ComplexSentence*)rule;

                        //delete specific rule from list (we have now 'popped it off)
                        for(auto it = rules.begin(); it != rules.end(); it++){
                            if(*it == rule){
                                rules.erase(it);
                                break;
                            }
                        }

                        clause.clear();
                        ruleCopy->accept(clause);
                        auto b = clause.symbols();

                        return ruleCopy;
                    }
                }
            }

            clause.clear();

            std::cerr << "rule does not exist";

        }

    };


}

#endif //IENGINE_BC_HPP
