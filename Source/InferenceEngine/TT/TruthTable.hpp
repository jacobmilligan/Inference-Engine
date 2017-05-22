//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_TRUTHTABLE_HPP
#define PROJECT_TRUTHTABLE_HPP

#include <vector>
#include <map>
#include <InferenceEngine/AST/ClauseFinder.hpp>

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {

using matrix = std::vector <std::vector<Symbol *>>;

class Response {
public:
    bool result = false;
    int models_inferred = 0;
    Response(int mods, bool res)
        : models_inferred(mods), result(res)
    {};
};

class TruthTable {
private:
    //Will eventually be refactor to not need to be passed all symbols around and just just clauseFinder ref
    std::vector<const Sentence*> rules_;

    double size_;
    //symbols_ list following construction of truth table
    std::vector<Symbol*> symbolList_;

    //Truth table matrix itself - containing models(rows) of symbols
    matrix matrixModals_;

    void ConstructTruthTableRecursive(std::vector<Symbol *> symbols,
                                      matrix& tempMatrix, std::vector<Symbol *> partialModelVal, double modalSize);

    std::map<std::string, bool> ConvertToMap(std::vector<Symbol*> symbolList);


    bool modalMatch(const std::vector<Symbol*> row, const std::vector<Symbol*> askModal);

public:

    //Constructor to truth table:
    //Truth table is calculated within the constructor
    TruthTable(std::vector<Symbol *>& symbols, std::vector<const Sentence*> kb_rules);

    //Return copy of truth table
    matrix GetTruthTableMatrix();

    //Return copy of symbols used in truth table
    std::vector<Symbol *> GetSymbolsList();

    Response Ask(const std::vector<Symbol*> symbolList);


};
}
#endif //PROJECT_TRUTHTABLE_HPP