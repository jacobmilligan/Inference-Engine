//
// Created by mac on 29/04/17.
//


#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {
    //Trial recursive algo for TT
    void TruthTable::ConstructTruthTableRecursive(std::vector<Symbol*> symbols,
                                                  matrix& tempMatrix, std::vector<Symbol*> partialModelVal, double modalSize )
    {
        if(modalSize == 0){

            std::map<std::string, bool> map = ConvertToMap(partialModelVal);

            ResolutionVisitor r;

            for(auto rule : rules_) {
                bool ruleValue = r.GetSolution(map, *rule);

                //add new rule and its result as a single symbol to the truth table 'row'
                partialModelVal.push_back(
                        new Symbol("r" + std::to_string(ruleNumber_), ruleValue)
                );

                //add completed row
                tempMatrix.push_back(partialModelVal);
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
        ConstructTruthTableRecursive(rest, tempMatrix, partialModelTrue, modalSize); // model U {P = true}
        ConstructTruthTableRecursive(rest, tempMatrix,  partialModelFalse, modalSize); //model U {P = false}
        }

    }

    std::vector<std::vector<Symbol*>> TruthTable::GetTruthTableMatrix() {
        return matrixModals_;
    }

    std::vector<Symbol*> TruthTable::GetSymbolsList() {
        return symbolList_;
    }

    TruthTable::TruthTable(std::vector<Symbol*>& symbols, std::vector<const ComplexSentence*> kb_rules) {

        //Add current set of rules
        rules_ = kb_rules;

        //Create new Truth Table

        symbolList_ = symbols;
        //matrixModals_ = ConstructTruthTable(symbols);
        matrixModals_ = std::vector<std::vector<Symbol*>>();
        std::vector<Symbol*> partialModel = std::vector<Symbol*>();
        ConstructTruthTableRecursive(symbols, matrixModals_, partialModel, symbols.size());
    }

    std::map<std::string, bool> TruthTable::ConvertToMap(const std::vector<Symbol*> symbolList){
        std::map<std::string, bool> returnMap;

        for(Symbol* s : symbolList){
            returnMap[s->GetSymbolName()] = s->GetValue();
        }

        return returnMap;
    }

    const ComplexSentence* TruthTable::PopRule() {
        auto* rule = rules_[rules_.size()-1];
        rules_.pop_back();
        ruleNumber_++;
        return rule;
    }

    bool TruthTable::is_rules(){
        return rules_.empty();
    }


}