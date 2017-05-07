//
// Created by mac on 5/05/17.
//

#include <iostream>
#include <map>


#include "InferenceEngine/Core/Agent.hpp"

namespace ie {

    Agent::Agent() {
        successfulEntailments_ = 0;
    }

    Response Agent::TTentails(std::vector <Symbol*> &modalA, std::vector <Symbol*> symbolsForRow,
                              std::vector <Symbol*> &rules, matrix knowledgeBase) {

        //Gets built upon as the tree depends
        std::vector <Symbol*> partialModelVal = std::vector<Symbol*>();

        //Creates full table rows of symbols + predicates/models
        std::vector <Symbol*> symbols = symbolsForRow;

        //Return response with result inside it - includes entailment number that is calculated throughout the algorithm
        return Response(EntailMentsNumber(),
                         TTCheckALL(modalA, symbols, partialModelVal, knowledgeBase)
        );
    }

    bool Agent::TTCheckALL(std::vector <Symbol*> &modalA, std::vector <Symbol*> symbols,
                           std::vector <Symbol*> partialModelVal, matrix knowledgeBase) {

        //debugging
        iterations++;

            //No more symbols from the symbol list - we have reach a leaf node of this branch
            if (symbols.empty()) {

                // std::cout << partialModelVal.size() << std::endl;

                //Now we check if the partialModel CAN exist with the rules we have calculated
                //For example - we are asking for world: partialModel = model U {Q = True}
                // Q | W | T | W => T |
                // Does a world where Q is True exist?
                if (PLtrueWorld(knowledgeBase, partialModelVal)) {

                    //if it CAN Exist we see if it corresponds to our query modal
                    //For example - we have asked IS 'Q' true in this world i.e. - is modalA = model U {Q = True} in this partialModel?
                    //And in this example the answer is YES, we have reached partialMode (Leaf node of our search tree) where Q is true
                    if (PLtrue(partialModelVal, modalA)) {
                        //return true;
                    } else {
                        //return false;
                    }
                } else
                    {
                        //This partialModel does not exist in this world
                        //return true;
                    }
                }
        else {
            // ------------------------------------------------------------------------- //
            //      Below we begin making our partial models
            //      These only become enumerated at the end of each branch
            //      Which will only be in the above statement when symbols list is empty
            // ------------------------------------------------------------------------- //


            // P <- First(symbols)
            Symbol *firstTrue = symbols[symbols.size() - 1];
            symbols.

                    pop_back();

            //Add P = True to partial model
            std::vector < Symbol * > partialModelTrue = partialModelVal;
            partialModelTrue.
                    push_back(firstTrue);

            //Create a true and false version
            firstTrue->SetValue(true);
            Symbol *firstFalse = new Symbol(firstTrue->GetSymbolName(), false);
            //Add P = False to Partial model
            std::vector < Symbol * > partialModelFalse = partialModelVal;
            partialModelFalse.
                    push_back(firstFalse);

            //Rest <- Rest(symbols)
            std::vector < Symbol * > rest = symbols;

            //Recursive check of binary tree results i.e. is our query true in either the symbol = true || symbol = false branches
            bool res = (TTCheckALL(modalA, rest, partialModelTrue, knowledgeBase)); // model U {P = true}
            bool res2 = TTCheckALL(modalA, rest, partialModelFalse, knowledgeBase); //model U {P = false}
            //return res && res2;
        }

        //return true;
    }

    bool Agent::PLtrue(std::vector <Symbol*> KB, std::vector <Symbol*> modelA) {

        //symbols_ are all calculated at this stage - therefore we just check for truth in an entire row/'modal'
        //We are searching through the entire pre-calculated truth table to find a row/'modal' that
        //modelA is true in

        bool result = false;

        for (auto& sym : KB) {
            //Iterate through each row to check
            bool correctComparisons = false;
            for (auto& sym2 : modelA) {

                if (sym->GetSymbolName() == sym2->GetSymbolName()) {
                    //check to see if the truth table row(mod) is identical to modalA
                    if (sym->GetValue() != sym2->GetValue()) {
                        correctComparisons = false;
                        break;
                    }
                    correctComparisons = true;
                }
            }
            if (correctComparisons) {
                successfulEntailments_++;
                return true;
            }
        }

        //No comparisons occured
        return result;
    }

    bool Agent::PLtrueWorld(matrix knowledgeBase, std::vector<Symbol*> modelA) {

        //symbols_ are all calculated at this stage - therefore we just check for truth in an entire row/'modal'
        //We are searching through the entire pre-calculated truth table to find a row/'modal' that
        //modelA is true in

        auto& symbolList = modelA;

        //size of row for comparison
//    double correctComparisons = modelA.size();
//    int correctModels = 0;

        bool result = false;


        for (auto& mod : knowledgeBase) {
            for (auto& sym : mod) {

                bool correctComparisons = false;
                //Iterate through each row to check
                for (auto& sym2 : modelA) {
                    if (sym->GetSymbolName() == sym2->GetSymbolName()) {
                        //check to see if the truth table row(mod) is identical to modalA
                        if (sym->GetValue() != sym2->GetValue()) {
                            correctComparisons = false;
                            break;
                        }
                    }

                    correctComparisons = true;
                }

                if (correctComparisons) {
                    return true;
                }
            }
        }

        return result;

    }

    std::vector<Symbol*> Agent::CombineSymbolLists(const std::vector<Symbol*> s1, const std::vector<Symbol*> s2) {
        std::vector <Symbol*> newSymbolList = s1;

        for (Symbol *sym : s2) {
            newSymbolList.push_back(sym);
        }

        return newSymbolList;
    }

    int Agent::EntailMentsNumber() {
        return successfulEntailments_;
    }

    bool Agent::rules_pass(std::vector<Symbol *> modelRow) {

        //there may be no rules
        bool rulesPass = true;

        //Iterate backwards through modal with each rule in it
        //Break if any rules are false or if at end of rules
        std::vector<Symbol*>::reverse_iterator rit = modelRow.rbegin();
        for(;rit != modelRow.rend(); --rit){
            //if its a rule we test it - otherwise its the end of the rules and we can break
            if((*rit)->GetSymbolName().find("rule")){
                if((*rit)->GetValue()){
                    rulesPass = true;
                }
                else{
                    return false;
                }
            }
            else {
                break;
            }
        }


        return rulesPass;

    }

}
