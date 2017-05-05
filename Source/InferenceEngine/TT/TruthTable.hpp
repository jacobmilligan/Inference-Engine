//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_TRUTHTABLE_HPP
#define PROJECT_TRUTHTABLE_HPP

#include <vector>

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"

namespace ie {

    using matrix = std::vector <std::vector<Symbol *>>;

    class TruthTable {
    private:

        double size_;
        //symbols_ list following construction of truth table
        std::vector<Symbol *> symbolList_;

        //Truth table matrix itself - containing models(rows) of symbols
        matrix matrixModals_;

        void ConstructTruthTableRecursive(std::vector<Symbol *> symbols,
                                          matrix& tempMatrix, std::vector<Symbol *> partialModelVal, double modalSize);

    public:

        //Constructor to truth table:
        //Truth table is calculated within the constructor
        TruthTable(std::vector<Symbol *>& symbols);

        //Return copy of truth table
        matrix GetTruthTableMatrix();

        //Return copy of symbols used in truth table
        std::vector<Symbol *> GetSymbolsList();

    };
}
#endif //PROJECT_TRUTHTABLE_HPP
