#include "zynpch.h"

#include "Parser/Parser.h"
#include "Parser/Lexer.h"

using namespace Zyn;

static std::string ReadFile(const char* filepath) {
    std::ifstream fileStream(filepath);
    std::string result;
    std::string line;

    while(std::getline(fileStream, line)) {
        result.append(line).append("\n");
    }

    return result;
}

int main() {

    ZYN_PROFILE_BEGIN_SESSION("ZYN", "zyn-profiling.json");

    Log::Info("Reading file...");

    const std::string programString = ReadFile("/Users/nickfanelli/Dev/Zyn/res/program.zyn");

    Log::Info("File read successfully!");

    Log::Info("Tokenizing String");

    Tokenizer tokenizer{programString};
    std::vector<Token> tokens = tokenizer.Parse();

    Log::Info("Tokenizing Successful!");

    Log::FormatTrace("Num Tokens: %d", tokens.size());

    // for(const Token& token : tokens) {
    //
    //     token.print();
    //
    // }

    Log::Info("Parsing Tokens...");

    Parser parser{tokens};
    std::unique_ptr<ProgramNode> program = parser.ProduceAST();

    Log::Info("Parsing Successful!");

    ZYN_PROFILE_END_SESSION();

    return 0;

}