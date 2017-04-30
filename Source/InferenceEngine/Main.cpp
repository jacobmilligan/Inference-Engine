#include "InferenceEngine/Parsing/Parser.hpp"

#include <Path/Path.hpp>

int main(int argc, char** argv)
{
    auto path = sky::Path(sky::Path::bin_path(argv));
    path.append("../Tests/test1.txt");

    ie::Parser parser;
    parser.parse(path.str());

    return 0;
}