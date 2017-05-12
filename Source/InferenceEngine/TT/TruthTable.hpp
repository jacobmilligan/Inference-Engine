//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_TRUTHTABLE_HPP
#define PROJECT_TRUTHTABLE_HPP

#include <vector>
#include <InferenceEngine/AST/ClauseFinder.hpp>
#include <InferenceEngine/Core/Response.hpp>
#include "InferenceEngine/AST/SymbolFinder.hpp"
#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {

using matrix = std::vector <std::vector<Symbol *>>;

class TruthTable {
private:

    std::vector<const ComplexSentence*> rules_;

    //symbols_ list following construction of truth table
    std::vector<Symbol*> symbolList_;

    //Truth table matrix itself - containing models(rows) of symbols
    matrix matrixModals_;

    //Constructs entire truth table given symbols and rules
    void construct_truth_table_recursive(std::vector<Symbol *> symbols,
                                         matrix& tempMatrix, std::vector<Symbol *> partialModelVal, double modalSize);

    std::map<std::string, bool> ConvertToMap(std::vector<Symbol*> symbolList);


    bool modal_match(const std::vector<Symbol *> row, const std::vector<Symbol *> askModal);

    //Checks if a symbol is in our symbol list
    bool ask_symbols_match(const std::vector<Symbol *> modal);

public:

    //Constructor to truth table:
    //Truth table is calculated within the constructor
    TruthTable(const ie::SymbolFinder& symFind, std::vector<const ComplexSentence*> kb_rules);

    //Return copy of truth table
    matrix GetTruthTableMatrix();

    //Return copy of symbols used in truth table
    std::vector<Symbol *> GetSymbolsList();

    Response ask(const std::vector<Symbol *> symbolList);


};
}
#endif //PROJECT_TRUTHTABLE_HPP
