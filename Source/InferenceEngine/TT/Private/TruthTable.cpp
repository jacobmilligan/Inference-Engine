//
// Created by mac on 29/04/17.
//


#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {
    //Trial recursive algo for TT
    void TruthTable::ConstructTruthTableRecursive(std::vector<Symbol*> symbols,
                                                  matrix& tempMatrix, std::vector<Symbol*> partialModelVal, double modalSize )
    {
        if(modalSize == 0){
            tempMatrix.push_back(partialModelVal);
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

    TruthTable::TruthTable(std::vector<Symbol*>& symbols) {
        //Create new Truth Table
        symbolList_ = symbols;
        //matrixModals_ = ConstructTruthTable(symbols);
        matrixModals_ = std::vector<std::vector<Symbol*>>();
        std::vector<Symbol*> partialModel = std::vector<Symbol*>();
        ConstructTruthTableRecursive(symbols, matrixModals_, partialModel, symbols.size());
    }


}