//
// Path.hpp
// Skyrocket Framework
//
// ----------------------------------------------------------------------------
//
// Created by Jacob Milligan on 17/11/2016.
// Copyright (c) 2016 Jacob Milligan All rights reserved.
//

#pragma once

#include <string>

#include "PlatformConfig.hpp"

namespace sky {

/// @brief Path is an interface for handling path structure and format in a
/// platform-agnostic way. It provides the ability to refer to a path relatively,
/// absoloutly and in the current platforms native format.
class Path {
public:
    /// @brief Assigns a root to the Path using the specified absolute path string
    /// @param root The absolute path root to assign
    Path(const char* root) { assign(root); }
    
    /// @brief Assigns a root to the Path using the specified absolute path string
    /// @param root The absolute path root to assign
    Path(const std::string &root) { assign(root); }
    
    /// @brief A static helper function for retrieving the platform-specific path
    /// to the program
    /// @param argv The command line arguments passed into the programs main()
    /// @return String representation of the path to the programs binary executable
    static std::string bin_path(char** argv);
    
    /// @brief Assigns a new absolute root to the Path
    /// @param root The absolute path to assign as root
    void assign(const char* root);
    
    /// @brief Assigns a new absolute root to the Path using an std::string
    /// @param root The absolute path to assign as root
    void assign(const std::string &root);
    
    /// @brief Gets the filename part of the Path, i.e:
    /// @code{.cpp}
    /// sky::Path p("/Users/Me/Documents/README.md");
    /// printf("Filename part of p is: %s", p.parent());
    /// @endcode
    /// Will output:
    /// @code{.cpp}
    /// Filename part of p is: README.md
    /// @endcode
    /// @return The filename part of the paths currently assigned value
    std::string filename() const;
    
    /// @brief Gets the parent directory part of the path, i.e:
    /// @code{.cpp}
    /// sky::Path p("/Users/Me/Documents/README.md");
    /// printf("Parent directory of p is: %s", p.parent());
    /// @endcode
    /// Will output:
    /// @code{.cpp}
    /// Parent directory of p is: /Users/Me/Documents
    /// @endcode
    /// @return The parent directory of the Path
    std::string parent();
    
    /// @brief Gets a string of the path with a relative path appended to it, i.e:
    /// @code{.cpp}
    /// sky::Path p("/Users/Me/Documents");
    /// printf("Relative path appended to p is: %s", p.relative("Skyrocket_Docs"));
    /// @endcode
    /// @code{.cpp}
    /// Relative path appended to p is: /Users/Me/Documents/Skyrocket_Docs
    /// @endcode
    /// @param path
    /// @return
    inline std::string get_relative(const char* path)
    {
        return root_ + separator_ + path;
    }
    
    /// @brief Appends a new relative path to the end of the current Path
    /// @param path The addition to append
    inline void append(const char* path)
    {
        root_ += separator_;
        root_ += path;
    
        assign(path);
    }
    
    /// @brief Gets the current path as an std::string
    /// @return The Path string
    inline std::string str() const { return root_; }
    
    /// @brief Gets the current path as a const char*
    /// @return The Path string
    inline const char* c_str() const { return root_.c_str(); }

private:
    /// @brief The platform-specific separator character. This will be
    /// '/' for unix-style systems and '\' for windows systems
    static const char separator_;
    
    /// @brief The currently assigned path
    std::string root_;
};

}
