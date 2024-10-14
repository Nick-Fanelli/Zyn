#pragma once

#include "zynpch.h"

#include "Token.h"

namespace Zyn {

    class Tokenizer;

    class Tokenizer {

    public:
        explicit Tokenizer(const std::string& inProgram);

        void PushBackToken(TokenType tokenType, std::string_view text);

        std::vector<Token> Parse();

    private:

        [[nodiscard]] char At() const;
        [[nodiscard]] std::optional<char> PeekChar() const;

        void SingleTokenHandler(Token& currentToken, TokenType tokenType, char character);
        void NumericalTokenHandler(Token& currentToken, TokenType tokenType, char character);
        void StringTokenHandler(Token& currentToken);

        void EndToken(Token& currenToken);

    public:

    private:
        std::string m_InProgram;
        std::vector<Token> m_Tokens;

        size_t m_Pos = 0;

    };

}