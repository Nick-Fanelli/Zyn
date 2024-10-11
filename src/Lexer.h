#pragma once

#include "zynpch.h"

#include "Token.h"

namespace Zyn {

    class Tokenizer;

    struct TokenPattern {

        std::regex Pattern;
        TokenType TokenType;
        std::function<void(Tokenizer&, enum TokenType, const std::smatch&)> Handler;

    };

    class Tokenizer {

    public:
        explicit Tokenizer(const std::string& inProgram);

        void Advance(size_t n);
        void PushBackToken(TokenType tokenType, std::string_view text);

        std::vector<Token> Parse();

    private:

        [[nodiscard]] bool IsAtEOF() const { return m_Pos >= m_InProgram.size(); }

    public:

    private:
        std::vector<TokenPattern> m_TokenPatterns;

        std::string m_InProgram;
        std::vector<Token> m_Tokens;

        size_t m_Pos = 0;
        size_t m_LineNumber = 1;

    };

}