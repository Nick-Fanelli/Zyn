#pragma once

#include "zynpch.h"

namespace Zyn {

    enum TokenType {

        // Identifiers
        TokenTypeUndefined,
        TokenTypeIdentifier,

        // Keywords
        TokenTypeIntegerKeyword,
        TokenTypeStringKeyword,
        TokenTypeVoidKeyword,

        // Literals
        TokenTypeIntegerLiteral,
        TokenTypeStringLiteral,

        // Operators
        TokenTypeEquals,
        TokenTypeBinaryOperator,

        // Parens
        TokenTypeOpenParen,
        TokenTypeCloseParen,
        TokenTypeOpenCurlyBrace,
        TokenTypeCloseCurlyBrace,

        // Delimeter
        TokenTypeSemiColon,

        // Special
        TokenTypeEOF

    };

    constexpr std::string_view TOKEN_TYPES[] = {

        "UNDEFINED",
        "IDENTIFIER",

        "INTEGER_KEYWORD",
        "STRING_KEYWORD",
        "VOID_KEYWORD",

        "INTEGER_LITERAL",
        "STRING_LITERAL",

        "EQUALS",
        "BINARY_OPERATOR",

        "OPEN_PAREN",
        "CLOSE_PAREN",
        "OPEN_CURLY_BRACE",
        "CLOSE_CURLY_BRACE",

        "SEMI_COLON",

        "EOF"
        
    };

    const std::unordered_map<std::string, TokenType> IDENTIFIER_MAP = {
        { "int", TokenTypeIntegerKeyword },
        { "string", TokenTypeStringKeyword },
        { "void", TokenTypeVoidKeyword }
    };

    class Token {

    public:
        void print() const {
            std::cout << "Token {" << TOKEN_TYPES[m_Type] << ", " << m_Text << ", " << m_StartOffset << ":" << m_EndOffset << ", " << m_LineNumber << "}" << std::endl;
        }

    public:
        TokenType m_Type{TokenTypeUndefined};
        std::string m_Text;

        size_t m_StartOffset{0};
        size_t m_EndOffset{0};
        size_t m_LineNumber{1};
    
    };

    class Tokenizer {

    public:
        std::vector<Token> Parse(const std::string& inProgram);

    private:
        static inline void EndToken(Token& token, std::vector<Token>& tokens);
        static inline bool IsAlpha(const std::string& string);
        static inline bool IsInt(const std::string& string);

    };

}