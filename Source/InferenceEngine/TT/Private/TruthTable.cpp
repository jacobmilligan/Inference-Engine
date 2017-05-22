//
// Created by mac on 29/04/17.
//


#include "InferenceEngine/AST/ResolutionVisitor.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"
#include "InferenceEngine/TT/Model.hpp"

namespace ie {


bool pl_true(const Symbol& alpha, const Model& model)
{
    return model.is_true(alpha.GetSymbolName());
}

bool pl_true(const KnowledgeBase& kb, const Model& model)
{
    return model.is_true(kb.as_sentence());
}

Response TruthTable::ask(const KnowledgeBase& kb, const Symbol& alpha)
{
    auto result = tt_check_all(kb, alpha, kb.symbols(), Model());
    return Response(models_, result);
}

bool TruthTable::tt_check_all(const KnowledgeBase& kb, const Symbol& alpha,
                              std::unordered_map<std::string, bool> symbols,
                              const Model& model)
{
    if ( symbols.empty() ) {
        if ( pl_true(kb, model) ) {
            auto result = pl_true(alpha, model);

            if ( result )
                models_++;

            return result;
        }

        return true; // when KB is false always return true
    } else {
        // P <- First(symbols)
        auto p = Symbol(symbols.begin()->first, symbols.begin()->second);
        // rest <- REST(symbols)
        auto rest = symbols;
        rest.erase(p.GetSymbolName());
        // Model U true
        auto left = model.extend(p.GetSymbolName(), true);
        // Model U false
        auto right = model.extend(p.GetSymbolName(), false);

        return tt_check_all(kb, alpha, rest, left)
            && tt_check_all(kb, alpha, rest, right);
    }
}


}
