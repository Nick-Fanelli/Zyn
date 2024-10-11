#include "zynpch.h"

#include "Lexer.h"

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

    // const std::string testString = "int number = (10 * hello);";

    // const std::string programString = FileUtils::ReadFile("res/program.zyn");

    const std::string programString = ReadFile("res/program.zyn");

    Tokenizer tokenizer{programString};
    std::vector<Token> tokens = tokenizer.Parse();

    for(const Token& token : tokens) {

        token.print();

    }

    // Parser parser{tokens};
    // const Program& program = parser.ProduceAST();

    // std::cout << program << std::endl;

    return 0;

}