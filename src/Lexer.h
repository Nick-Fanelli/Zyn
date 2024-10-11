#pragma once

#include "zynpch.h"

namespace Zyn {

    enum TokenType {

        // Identifiers
        TokenTypeWhitespace,
        TokenTypeIdentifier,

        // Keywords
        TokenTypeIntegerKeyword,
        TokenTypeStringKeyword,
        TokenTypeVoidKeyword,

        // Literals
        TokenTypeIntegerLiteral,
        TokenTypeStringLiteral,

        // Operators
        TokenTypePlusOperator,
        TokenTypeMinusOperator,
        TokenTypeMultiplyOperator,
        TokenTypeDivideOperator,

        // Numerical Manipulators
        TokenTypeEquals,
        TokenTypeNotEquals,
        TokenTypePlusEqualsOperator,
        TokenTypeMinusEqualsOperator,
        TokenTypeMultiplyEqualsOperator,
        TokenTypeDivideEqualsOperator,

        // Comparisons
        TokenTypeAndOperator,
        TokenTypeOrOperator,
        TokenTypeEqEq,

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

    inline const char* TokenTypeToString(TokenType tokenType) {
        switch (tokenType) {
            case TokenTypeWhitespace:           return "WHITESPACE";
            case TokenTypeIdentifier:           return "IDENTIFIER";
            case TokenTypeIntegerKeyword:       return "INTEGER_KEYWORD";
            case TokenTypeStringKeyword:        return "STRING_KEYWORD";
            case TokenTypeVoidKeyword:          return "VOID_KEYWORD";
            case TokenTypeIntegerLiteral:       return "INTEGER_LITERAL";
            case TokenTypeStringLiteral:        return "STRING_LITERAL";
            case TokenTypeEquals:               return "EQUALS";
            case TokenTypePlusOperator:         return "PLUS_OPERATOR";
            case TokenTypeMinusOperator:        return "MINUS_OPERATOR";
            case TokenTypeMultiplyOperator:     return "MUL_OPERATOR";
            case TokenTypeDivideOperator:       return "DIV_OPERATOR";
            case TokenTypeOpenParen:            return "OPEN_PAREN";
            case TokenTypeCloseParen:           return "CLOSE_PAREN";
            case TokenTypeOpenCurlyBrace:       return "OPEN_CURLY_BRACE";
            case TokenTypeCloseCurlyBrace:      return "CLOSE_CURLY_BRACE";
            case TokenTypeSemiColon:            return "SEMI_COLON";
            case TokenTypeEOF:                  return "EOF";
            case TokenTypePlusEqualsOperator:   return "PLUS_EQUALS_OPERATOR";
            case TokenTypeMinusEqualsOperator:  return "MINUS_EQUALS_OPERATOR";
            case TokenTypeMultiplyEqualsOperator: return "MULTIPLE_EQUALS_OPERATOR";
            case TokenTypeDivideEqualsOperator:     return "DIVIDE_EQUALS_OPERATOR";
            case TokenTypeNotEquals:             return "NOT_EQUALS";
            case TokenTypeOrOperator:           return "OR_OPERATOR";
            case TokenTypeAndOperator:          return "AND_OPERATOR";
            case TokenTypeEqEq:          return "EQ_EQ_COMPARISON";

            default:                            return "UNNAMED";
        }
    }

    class Token {

    public:
        void print() const {
            std::cout << "Token {" << TokenTypeToString(m_Type) << ", " << m_Text << ", " << m_StartOffset << ":" << m_EndOffset << ", " << m_LineNumber << "}" << std::endl;
        }

    public:
        TokenType m_Type{TokenTypeWhitespace};
        std::string m_Text;

        size_t m_StartOffset{0};
        size_t m_EndOffset{0};
        size_t m_LineNumber{1};
    
    };

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

        bool IsAtEOF() const { return m_Pos >= m_InProgram.size(); }

    public:

    private:
        std::vector<TokenPattern> m_TokenPatterns;

        std::string m_InProgram;
        std::vector<Token> m_Tokens;

        size_t m_Pos = 0;
        size_t m_LineNumber = 1;

    };

}