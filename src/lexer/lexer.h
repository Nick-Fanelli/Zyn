#pragma once

#include "zynpch.h"

namespace Zyn {

    enum TokenType {

        // Identifiers
        TokenTypeUndefined,
        TokenTypeIdentifier,
        TokenTypeIntegerIdentifier,

        // Literals
        TokenTypeIntegerLiteral,

        // Operators
        TokenTypeEquals,
        TokenTypeBinaryOperator,

        // Parens
        TokenTypeOpenParen,
        TokenTypeCloseParen,

        // Delimeter
        TokenTypeSemiColon

    };

    constexpr std::string_view TOKEN_TYPES[] = {

        "UNDEFINED",
        "IDENTIFIER",
        "INTEGER_IDENTIFIER",

        "INTEGER_LITERAL",

        "EQUALS",
        "BINARY_OPERATOR",

        "OPEN_PAREN",
        "CLOSE_PAREN",

        "SEMI_COLON"
        
    };

    const std::unordered_map<std::string, TokenType> IDENTIFIER_MAP = {
        { "int", TokenTypeIntegerIdentifier }
    };

    class Token {

    public:
        void print() const {
            std::cout << "Token {" << TOKEN_TYPES[m_Type] << ", " << m_Text << ", " << m_StartOffset << ":" << m_EndOffset << ", " << m_LineNumber << "}" << std::endl;
        }

    public:
        enum TokenType m_Type{TokenTypeUndefined};
        std::string m_Text;

        size_t m_StartOffset{0};
        size_t m_EndOffset{0};
        size_t m_LineNumber{1};
    
    };

    class Tokenizer {

    public:
        std::vector<Token> Parse(const std::string& inProgram);

    private:
        inline void EndToken(Token& token, std::vector<Token>& tokens);
        inline bool IsAlpha(const std::string& string);
        inline bool IsInt(const std::string& string);

    };

}