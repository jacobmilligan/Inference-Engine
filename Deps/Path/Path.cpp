//
// Path.cpp
// Project
//
// ----------------------------------------------------------------------------
//
// Created by Jacob Milligan on 8/12/2016.
// Copyright (c) 2016 Jacob Milligan All rights reserved.
//

#include "Path.hpp"


namespace sky {

void Path::assign(const std::string& root)
{
    assign(root.c_str());
}

std::string Path::filename() const
{
    std::string filename = "";
    auto lastslash = root_.rfind(separator_);

	if ( lastslash != std::string::npos )
		return root_.substr(lastslash + 1, root_.size());

    return root_;
}

std::string Path::parent()
{
    return root_.substr(0, root_.find_last_of(separator_));
}


}
