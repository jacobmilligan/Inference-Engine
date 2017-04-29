//
//  PathMac.cpp
//  Skyrocket Framework
//
//  --------------------------------------------------------------
//
//  Created by Jacob Milligan on 13/12/2016.
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//
//  --------------------------------------------------------------
//
// Implements the MacOSX-specific path functions
//

#include "Path.hpp"

#include <mach-o/dyld.h>
#include <sys/param.h>
#include <stdlib.h>

namespace sky {

const char Path::separator_ = '/';

void Path::assign(const char* root)
{
    char resolved[MAXPATHLEN];
    realpath(root, resolved);
    root_ = resolved;

    if ( root_[root_.size()] == separator_ && root_.size() > 1 ) {
        root_.pop_back();
    }
}

std::string Path::bin_path(char** argv)
{
    char buffer[MAXPATHLEN];
    
    auto bufsize = static_cast<uint32_t>(MAXPATHLEN);
    auto result = _NSGetExecutablePath(buffer, &bufsize);
    
    if ( result != 0 ) {
        printf("Path error: Unable to locate binary get_relative");
        return "";
    }

    std::string binpath = realpath(argv[0], buffer);
    auto lastslash = binpath.rfind(separator_);
    
    if ( lastslash != std::string::npos )
        binpath.replace(lastslash, binpath.length(), "");

    return binpath;
}

}
