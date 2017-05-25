//
// Created by mac on 12/05/17.
//


#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <queue>
#include <InferenceEngine/BC/BackwardChaining.hpp>

namespace ie {

//TODO: test further variations of connectives to test initial wrapper set up
void BackwardChaining::add_to_solution_output(std::string add){
    outputRes +=  add + ", ";
    path_.push_back(add);
}

///Converts sentences to wrapper for quicker access in search
void BackwardChaining::fill_sentance_wrapper(std::vector<const ComplexSentence *>& rules, std::vector<PremiseWrapper*>& premiseWrapperList){
    ClauseFinder cl;
    std::stack<TokenType> connectives;
    std::vector<std::string> symbols;
    for(auto* comp: rules){

        //rhs should always be result
        comp->right()->accept(cl);
        auto rhs = cl.symbols()[0];
        cl.clear();

        //get lhs symbols
        comp->left()->accept(cl);
        auto lhs = cl.symbols();
        for(auto sym : lhs){
            symbols.push_back(sym);
        }

        connectives = cl.connectives();
        cl.clear();

        BCatomic bc_atom = BCatomic(symbols, connectives);

        PremiseWrapper* premWrap = new PremiseWrapper(rhs, bc_atom);
        premiseWrapperList.push_back(premWrap);
        symbols.clear();


    }
}

///returns result of back-chaining - returns empty str if not solvable or string of results
bool BackwardChaining::bc_entails(std::vector<const ComplexSentence *> rules, const std::string goal,
                       std::map<std::string, bool> trueSymbols) {
    goal_string_ = goal;
    path_.clear();

    //for when KB already knows the goal in atomic truth values
    if(true_symbols_contain_goal(trueSymbols)){
        add_to_solution_output(goal);
        return true;
    }

    //add the complex sentence rules to an easy to read wrapper
    std::vector<PremiseWrapper *> premWrapperList;
    fill_sentance_wrapper(rules, premWrapperList);


    std::stack<PremiseWrapper *> goals;

    ClauseFinder clause;

    //first rule to search is the goal rule
    auto sent = find_rule_with_symbol(premWrapperList, goal);
    goals.push(sent);

    //find symbols in a clause
    while (!rules.empty()) {

        //need it to be vector now to pass into search
        std::vector<PremiseWrapper*> goalsCopyVec;
        auto goalsCopy = goals;
        while(!goalsCopy.empty()){
            goalsCopyVec.push_back(goalsCopy.top());
            goalsCopy.pop();
        }

        bool res = get_result(goalsCopyVec, trueSymbols);
        if(res){
            //add_to_solution_output(goal);
            return true;
        }

        int size = goals.size();
        find_symbol_premise_match(premWrapperList, goals, trueSymbols);
        if(size == goals.size()){
            //we have not found any further solvable premises so we break
            return false;
        }
    }

    return false;

}

/// -----------------------------------------------------------------------------------
///Search through top of goal and find premises rhs who matches symbols in the goal lhs
/// -----------------------------------------------------------------------------------
void BackwardChaining::find_symbol_premise_match(std::vector<PremiseWrapper*>& premWrapperList,
                               std::stack<PremiseWrapper*>& goals,
                               std::map<std::string, bool> trueSymbols){

    auto top = goals.top();
    std::vector<PremiseWrapper*> toAddList;


    for(auto prem : premWrapperList){
        for(auto sym : top->lhs_.symbol_lhs_){
            if(prem->rhs_ == sym){
                //check not already in list - if not then add
                bool notInList = true;
                for(auto it = toAddList.begin(); it != toAddList.end(); it++){
                    if(*it == prem){
                        notInList = false;
                    }
                }
                if(notInList){
                    toAddList.push_back(prem);
                }
            }
        }
    }

    for(auto newPrem : toAddList){
        goals.push(newPrem);
    }
}

bool BackwardChaining::true_symbols_contain_goal(std::map<std::string, bool>& trueSymbols){
    for(auto str : trueSymbols){
        if(str.first == goal_string_){
            return true;
        }
    }
    return false;
}

bool BackwardChaining::get_result(std::vector<PremiseWrapper*> goalsCopy, std::map<std::string, bool>& trueSymbols){

    //if we have made it to a fully emptied stack of premises then we have solved it
    if(goalsCopy.empty() || true_symbols_contain_goal(trueSymbols)){
        return true;
    }

    PremiseWrapper* searchPrem;
    bool searchFoundPrem = false;
    bool solvable_by_all_dysjunctions = false;

    for(auto prem : goalsCopy) {

        //sanity check - incase we already have this prem
        bool willContinue = false;
        for(auto s : trueSymbols) {
            if (prem->rhs_ == s.first) {
                willContinue = true;
            }
        }
        if(willContinue){
            continue;
        }

        // -------------------------------------------------------------------------------------
        //Check lhs symbols of each complex & then see if we have all the symbols to solve them
        // -------------------------------------------------------------------------------------

        int count = prem->lhs_.symbol_lhs_.size();
        for (auto lhsSym : prem->lhs_.symbol_lhs_) {
            for (auto trueSym : trueSymbols) {
                if (lhsSym == trueSym.first) {
                    count--;
                }
            }
        }

        //Special cases for all dysjunctions
        int dysjunctionCount = 0;
        auto tokenStack = prem->lhs_.token;
        while (!tokenStack.empty()){
            auto tok = tokenStack.top();
            if(tok == TokenType::disjunction){
                dysjunctionCount++;
            }
            else if(tok == TokenType::conjunction){
                //we cannot get an early solve if there is a conjunction
                break;
            }
            tokenStack.pop();
        }

        if(dysjunctionCount == prem->lhs_.token.size()
           && count != prem->lhs_.symbol_lhs_.size()){// <- means we has at least a symbol
            solvable_by_all_dysjunctions = true;
        }



        //if we had all the symbols the count will be 0 so we can solve this for the next search!
        if (count == 0) {
            //remove from our copies list
            for(auto it = goalsCopy.begin(); it != goalsCopy.end(); it++){
                if(*it == prem){
                    if(goalsCopy.size() == 1){
                        goalsCopy.pop_back();
                        break;
                    }
                    else {
                        goalsCopy.erase(it);
                    }
                }
            }
            searchPrem = prem;
            searchFoundPrem = true;
            break;
        }
        else if(count < prem->lhs_.symbol_lhs_.size() && solvable_by_all_dysjunctions){
            searchPrem = prem;
            searchFoundPrem = true;
            break;
        }
    }

    //if not special 'all dysjuncts case'
    if(!solvable_by_all_dysjunctions) {
        //no viable search premise was found
        if (!searchFoundPrem) {
            return false;
        }
    }

    bool res;
    if(searchPrem->lhs_.symbol_lhs_.size() == 1){
        res = trueSymbols[searchPrem->lhs_.symbol_lhs_[0]];
    }
    else if(solvable_by_all_dysjunctions){
        for(auto sym : searchPrem->lhs_.symbol_lhs_){
            for(auto symMap : trueSymbols){
                if(symMap.first == sym){
                    res = symMap.second;
                }
            }
        }
    }
    else {
        std::string sym1;
        std::string sym2;
        for (int i = 0; i < searchPrem->lhs_.symbol_lhs_.size(); i++) {

            if(i == 0) {
                sym1 = searchPrem->lhs_.symbol_lhs_[i];
            }
            if (i == 1) {
                sym2 = searchPrem->lhs_.symbol_lhs_[i];
                res = calculate(searchPrem->lhs_.token.top(), trueSymbols[sym1], trueSymbols[sym2]);
                searchPrem->lhs_.token.pop();
            } else if (i > 1) {
                res = calculate(searchPrem->lhs_.token.top(), trueSymbols[sym1], res);
            }
        }
    }

    //if empty we need the LHS results we used to beginning values in the chain
    if(path().empty()) {
        for (auto str : searchPrem->lhs_.symbol_lhs_) {
            for (auto it = trueSymbols.begin(); it != trueSymbols.end(); it++) {
                if ((*it).first == str) {
                    add_to_solution_output(str);
                }
            }

        }
    }


    //the result is now the value for the right hand side! which we add to the true symbols list
    for(auto sym : searchPrem->lhs_.symbol_lhs_){
        if(check_to_add(sym ,trueSymbols)) {
            add_to_solution_output(sym);
        }
    }

    trueSymbols.insert(std::make_pair(searchPrem->rhs_, res));


    add_to_solution_output(searchPrem->rhs_);



    return get_result(goalsCopy, trueSymbols);

};

bool BackwardChaining::check_to_add(std::string a, std::map<std::string, bool> trueSymbols){

    //if known value then we can add to our path
    bool addtoPath = false;
    for(auto m : trueSymbols){
        if(m.first == a){
            addtoPath = true;
        }
    }

    //if not already in path
    for(auto sym: path()){
        if(sym == a){
            addtoPath = false;
        }
    }

    return addtoPath;
}

bool BackwardChaining::calculate(TokenType logic_operator, bool lVal, bool rVal){

    switch (logic_operator){
        //Must be at the top because if negation then rVal has not been calculated
        case TokenType ::negation:
            return !rVal;
        case TokenType ::conjunction:
            return lVal && rVal;
        case TokenType ::disjunction:
            return lVal || rVal;
        case TokenType ::implication:
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

PremiseWrapper* BackwardChaining::find_rule_with_symbol(std::vector<PremiseWrapper*>& rules, std::string searchSym){
    //Look through rules searching for the one that contains the symbol we are querying for
    // return that rule
    for(auto* rule : rules){
        if(rule->rhs_ == searchSym){
            auto ruleCopy = rule;
            if(rules.size() > 1) {
                for (auto it = rules.begin(); it != rules.end(); it++) {
                    if ((*it) == rule) {
                        rules.erase(it);
                    }
                }
            }
            return rule;
        }
    }

    std::cerr << "rule does not exist";

}

}
