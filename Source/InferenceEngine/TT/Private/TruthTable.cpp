//
// Created by mac on 29/04/17.
//


#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include <InferenceEngine/AST/SymbolFinder.hpp>
#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {
    //Trial recursive algo for TT
void TruthTable::construct_truth_table_recursive(std::vector<Symbol *> symbols,
                                                 matrix& tempMatrix, std::vector<Symbol *> partialModelVal,
                                                 double modalSize)
{
    if(modalSize == 0){

        std::map<std::string, bool> map = ConvertToMap(partialModelVal);

        ResolutionVisitor r;

        int ruleNum = 1;

        for(auto rule : rules_) {

            //result of rule for this model
            bool ruleValue = r.get_solution(map, *rule);

            //Only need knowledge modal that adheres to the KB rules
            if(ruleValue) {
                //add new rule and its result as a single symbol to the truth table 'row'
                partialModelVal.push_back(
                        new Symbol("rule" + std::to_string(ruleNum++), ruleValue)
                );

                //add completed row
                tempMatrix.push_back(partialModelVal);
            }

        }
        return;
    }
    else{

    // P <- First(symbols)
    Symbol* firstTrue = symbols[symbols.size()-1];
    symbols.pop_back();
    //Add P = True to partial model
    std::vector<Symbol*> partialModelTrue = partialModelVal;
    partialModelTrue.push_back(firstTrue);

    //Create a true and false version
    firstTrue->SetValue(true);
    Symbol* firstFalse = new Symbol(firstTrue->GetSymbolName(), false);
    //Add P = False to Partial model
    std::vector<Symbol*> partialModelFalse = partialModelVal;
    partialModelFalse.push_back(firstFalse);

    //Rest <- Rest(symbols)
    std::vector<Symbol*> rest = symbols;

    //2 x branches through tree below
    modalSize -= 1;

    //Recursive check of binary tree results i.e. is our query true in either the symbol = true || symbol = false branches
        construct_truth_table_recursive(rest, tempMatrix, partialModelTrue, modalSize); // model U {P = true}
        construct_truth_table_recursive(rest, tempMatrix, partialModelFalse, modalSize); //model U {P = false}
    }

}

std::vector<std::vector<Symbol*>> TruthTable::GetTruthTableMatrix() {
    return matrixModals_;
}

std::vector<Symbol*> TruthTable::GetSymbolsList() {
    return symbolList_;
}

TruthTable::TruthTable(const ie::SymbolFinder& symFind, std::vector<const ComplexSentence*> kb_rules) {

    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();

    for(auto& str : symFind.get_symbols()){
        ie::Symbol* s = new ie::Symbol(str, true);
        observations.push_back(s);
    }

    //Add current set of rules
    rules_ = kb_rules;

    //Create new Truth Table

    symbolList_ = observations;
    //matrixModals_ = ConstructTruthTable(symbols);
    matrixModals_ = std::vector<std::vector<Symbol*>>();
    std::vector<Symbol*> partialModel = std::vector<Symbol*>();


    construct_truth_table_recursive(observations, matrixModals_, partialModel, observations.size());
}

std::map<std::string, bool> TruthTable::ConvertToMap(const std::vector<Symbol*> symbolList){
    std::map<std::string, bool> returnMap;

    for(Symbol* s : symbolList){
        returnMap[s->GetSymbolName()] = s->GetValue();
    }

    return returnMap;
}

Response TruthTable::ask(const std::vector<Symbol *> askModal) {
    //symbols_ are all calculated at this stage - therefore we just check for truth in an entire row/'modal'
    //We are searching through the entire pre-calculated truth table to find a row/'modal' that
    //modelA is true in

    //We must responde false if we do not know a symbol (i.e. we are unsure)
    if(!ask_symbols_match(askModal)){
        return Response(0, false);
    }

    auto& symbolList = askModal;
    double correctModals = 0;

    for (auto& mod : matrixModals_) {
        if(modal_match(mod, askModal)){
            correctModals++;
        }
    }

    Response res (correctModals, correctModals > 0);

    return res;
}

bool TruthTable::modal_match(const std::vector<Symbol *> row, const std::vector<Symbol *> askModal){
    //if there is no symbols equal then there is no match to confirm
    bool correctComparisons = false;

    for (auto& sym : row) {

        //Iterate through each row to check
        for (auto& sym2 : askModal) {

            if (sym->GetSymbolName() == sym2->GetSymbolName()) {
                //check to see if the truth table row(mod) is identical to modalA

                if (sym->GetValue() != sym2->GetValue()) {
                    return false;
                }else{
                    correctComparisons = true;
                }
            }
        }
    }

    return correctComparisons;
}

bool TruthTable::ask_symbols_match(const std::vector<Symbol *> model){
    for(auto* a : model){
        for(auto* b : symbolList_){
            if(a->GetSymbolName() != b->GetSymbolName()){
                return false;
            }
        }
    }
    return true;
}

}



