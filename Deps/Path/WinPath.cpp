//
//  PathWin.cpp
//  Skyrocket Framework
//
//  --------------------------------------------------------------
//
//  Created by Jacob Milligan on 13/12/2016.
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "Path.hpp"

#include <Windows.h>

namespace sky {

const char Path::separator_ = '\\';

void Path::assign(const char* root)
{
	root_ = root;
}

std::string Path::bin_path(char** argv)
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	
	std::string binpath = buffer;
	auto lastslash = binpath.rfind(separator_);

	if ( lastslash != std::string::npos )
		binpath.replace(lastslash, binpath.length(), "");

	return binpath;
}

}