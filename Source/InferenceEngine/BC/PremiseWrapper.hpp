//
// Created by mac on 24/05/17.
//

#ifndef IENGINE_PREMISEWRAPPER_HPP
#define IENGINE_PREMISEWRAPPER_HPP

#include <InferenceEngine/Core/Symbol.hpp>
#include "BCatomic.hpp"

/// -----------------------------------------------------------
/// Wrapper for entire premise both lhs and rhs ---------------
// ------------------------------------------------------------
namespace ie {
    class PremiseWrapper{
    public:
        PremiseWrapper(std::string rhs, BCatomic lhs) : rhs_(rhs), lhs_(lhs){}
        std::string rhs_;
        BCatomic lhs_;
    };

}

#endif //IENGINE_PREMISEWRAPPER_HPP
