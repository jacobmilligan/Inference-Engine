//
// Created by mac on 12/05/17.
//

#ifndef IENGINE_BC_HPP
#define IENGINE_BC_HPP

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <unordered_set>

namespace ie {


class BC {
public:
    bool bc_entails(const KnowledgeBase& kb, const Symbol& q);
    std::vector<std::string> path();
private:
    std::vector<std::string> path_;
};


}

#endif //IENGINE_BC_HPP
