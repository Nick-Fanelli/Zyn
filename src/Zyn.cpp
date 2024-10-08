#include "zynpch.h"

#include "lexer/lexer.h"

using namespace Zyn;

int main() {

    const std::string testString = "int number = (10 * hello);";

    Tokenizer tokenizer;

    std::vector<Token> tokens = tokenizer.Parse(testString);

    for(const Token& token : tokens) {

        token.print();

    }

    return 0;

}