//
//  BackwardChaining.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          12/05/2017
//

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/BC/BCatomic.hpp"
#include "InferenceEngine/BC/PremiseWrapper.hpp"

#include <vector>
#include <map>

namespace ie {


class BackwardChaining {
public:

    /// @brief returns result of back-chaining - returns empty str
    /// if not solvable or string of results
    bool bc_entails(std::vector<const ComplexSentence *> rules,
                    const std::string goal, std::map<std::string, bool> trueSymbols);

    /// @brief Gets the path taken to infer the result
    /// @return The path
    inline std::vector<std::string>& path()
    {
        return path_;
    }

private:

    bool check_to_add(std::string a, std::map<std::string, bool> trueSymbols);

    std::string goal_string_;

    bool true_symbols_contain_goal(std::map<std::string, bool>& trueSymbols);

    std::vector<std::string> path_;

    /// @brief concatanation of solving results
    std::string outputRes = "";
    /// @brief adds symbol in correct format to return output
    void add_to_solution_output(std::string add);
    /// @brief Converts sentences to wrapper for quicker access in search
    void fill_sentance_wrapper(std::vector<const ComplexSentence *>& rules,
                               std::vector<PremiseWrapper*>& premiseWrapperList);
    /// @brief Search through top of goal and find premises rhs who matches
    /// symbols in the goal lhs
    void find_symbol_premise_match(std::vector<PremiseWrapper*>& premWrapperList,
                                   std::stack<PremiseWrapper*>& goals,
                                   std::map<std::string, bool> trueSymbols);

    /// @brief heuristic search to
    /// a.) check if with out current set of premises the solutions is solvable
    ///     else BCing continues
    /// b.) calculate result
    bool get_result(std::vector<PremiseWrapper*> goalsCopy,
                    std::map<std::string, bool>& trueSymbols);

    /// @brief standard propositional logic calc
    bool calculate(TokenType logic_operator, bool lVal, bool rVal);

    /// @brief used for to find initial premise form the 'ask' symbol - this
    /// premise is the beginning of the back chaining
    PremiseWrapper* find_rule_with_symbol(std::vector<PremiseWrapper*>& rules,
                                          std::string searchSym);

};


}
