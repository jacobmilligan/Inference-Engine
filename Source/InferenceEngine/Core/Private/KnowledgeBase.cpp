//
//  KnowledgeBase.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - xIntroduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          12/05/2017
//

#include "InferenceEngine/Core/KnowledgeBase.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"
#include "InferenceEngine/FC/ForwardChaining.hpp"
#include "InferenceEngine/BC/BackwardChaining.hpp"

#include <algorithm>
#include <map>

namespace ie {


void KnowledgeBase::tell(const std::vector<ASTNode::Child>& ast)
{
    for ( auto& s : ast ) {
        s->accept(finder_);
    }

    std::string c = "";
    for ( auto& r : finder_.rules() ) {
        r->accept(stringifier_);
        c = stringifier_.current_string();
        auto found = rules_.find(c) != rules_.end();
        if ( !found ) {
            rules_[c] = r;
        }
        stringifier_.clear();
    }

    for ( auto& f : finder_.facts() ) {
        if ( facts_.find(f->get_value()) == facts_.end() ) {
            facts_[f->get_value()] = f;
        }
    }

    for ( auto& s : finder_.symbols() ) {
        if ( symbols_.find(s) == symbols_.end() ) {
            symbols_[s] = false;
        }
    }
}

std::string join(const std::vector<std::string>& strings, const std::string& delimiter)
{
    std::string result = "";
    for ( int i = 0; i < strings.size() - 1; ++i ) {
        result += strings[i];
        result += delimiter;
    }
    result += strings.back();

    return result;
}

void KnowledgeBase::ask(const InferenceMethod method, const Symbol& q)
{
    switch (method) {
        case InferenceMethod::TT:
        {
            TruthTable tt;
            auto response = tt.ask(*this, q);

            if ( response.result ) {
                std::cout << "YES: " << response.models_inferred << std::endl;
            } else {
                std::cout << "NO";
            }
        } break;
        case InferenceMethod::FC:
        {
            FC fc;
            auto response = fc.fc_entails(*this, q);
            if ( response.value ) {
                std::cout << "YES: " << join(response.path, ", ");
            } else {
                std::cout << "NO";
            }
            std::cout << std::endl;
        } break;
        case InferenceMethod::BC:
        {
            BackwardChaining bc;
            std::vector<const ComplexSentence*> rules;
            for ( auto& r : rules_ ) {
                rules.push_back(r.second);
            }
            std::map<std::string, bool> facts;
            for ( auto& f : facts_ ) {
                facts.emplace(f.first, true);
            }
            auto response = bc.bc_entails(rules, q.name(), facts);
            if ( response ) {
                std::cout << "YES: " << join(bc.path(), ", ");
            } else {
                std::cout << "NO";
            }
            std::cout << std::endl;
        } break;
        default:
            std::cout << "IEngine: Invalid ASK statement" << std::endl;
    }
}

const std::unordered_map<std::string, const Sentence*>
KnowledgeBase::as_sentence() const
{
    std::unordered_map<std::string, const Sentence*> result;
    for ( auto& r : rules_ ) {
        auto as_sentence = dynamic_cast<const Sentence*>(r.second);
        result.emplace(r.first, as_sentence);
    }
    for ( auto& f : facts_ ) {
        auto as_sentence = dynamic_cast<const Sentence*>(f.second);
        result.emplace(f.first, as_sentence);
    }
    return result;
}


}