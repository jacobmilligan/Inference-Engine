//
//  CoutUtils.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 5/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>
#include <iostream>

class CoutUtils {
public:
    void redirect_cout()
    {
        ss_.clear();
        ss_.str("");
        coutbuf_ = std::cout.rdbuf(ss_.rdbuf());
    }

    std::string get_cout()
    {
        return ss_.str();
    }

    void reset_cout()
    {
        std::cout.rdbuf(coutbuf_);
    }
private:
    std::stringstream ss_;
    std::streambuf* coutbuf_;
};