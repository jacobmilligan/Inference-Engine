#include <InferenceEngine/Parsing/CLIParser.hpp>
#include <Path/Path.hpp>
#include <InferenceEngine/Core/IEngine.hpp>
#include <InferenceEngine/AST/Private/ASTPrinter.hpp>

int main(int argc, char** argv)
{
    ie::CLIParser cli(sky::Path(argv[0]).filename(),
                      "Infers truths from a horn clause knowledge base");
    cli.add_positional(ie::CLIArgument("method", "The method to use when "
        "inferring the given ASK statement"));
    cli.add_positional(ie::CLIArgument("filename", "The name of the file "
        "(relative to the current working directory) where the knowledge base "
        "file is located"));
    cli.parse(argc, argv);

    auto file = cli.get_positional_result("filename");
    auto method = cli.get_positional_result("method");

    ie::IEngine engine;
    engine.infer(method, sky::Path(file));

    return 0;
}