#pragma once

#include "zynpch.h"

namespace Zyn {

    enum TokenType {

        // Identifiers
        TokenTypeWhitespace,
        TokenTypeComment,
        TokenTypeIdentifier,

        // Keywords
        TokenTypeIntegerKeyword,
        TokenTypeStringKeyword,
        TokenTypeVoidKeyword,
        TokenTypeReturnKeyword,
        TokenTypeStructKeyword,

        // Literals
        TokenTypeIntegerLiteral,
        TokenTypeFloatLiteral,
        TokenTypeDoubleLiteral,
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
        TokenTypeGreaterThan,
        TokenTypeLessThan,

        TokenTypeExclamation,
        TokenTypeQuestionMark,

        // Parens
        TokenTypeOpenParen,
        TokenTypeCloseParen,
        TokenTypeOpenCurlyBrace,
        TokenTypeCloseCurlyBrace,
        TokenTypeOpenSquareBracket,
        TokenTypeCloseSquareBracket,

        // Delimiter
        TokenTypeSemiColon,
        TokenTypeColon,
        TokenTypeDot,
        TokenTypeComma,

        // Special
        TokenTypeEOF

    };

    inline const char* TokenTypeToString(const TokenType tokenType) {

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
            case TokenTypeFloatLiteral:        return "FLOAT_LITERAL";
            case TokenTypeDoubleLiteral:       return "DOUBLE_LITERAL";
            case TokenTypeDot:                  return "DOT";
            case TokenTypeColon:                return "COLON";
            case TokenTypeExclamation:                  return "NOT";
            case TokenTypeQuestionMark:       return "QUESTION_MARK";
            case TokenTypeReturnKeyword:       return "RETURN_KEYWORD";
            case TokenTypeComma:                return "COMMA";
            case TokenTypeStructKeyword:        return "STRUCT_KEYWORD";
            case TokenTypeGreaterThan:          return "GREATER_THAN";
            case TokenTypeLessThan:             return "LESS_THAN";
            case TokenTypeOpenSquareBracket: return "OPEN_SQUARE_BRACKET";
            case TokenTypeCloseSquareBracket: return "CLOSE_SQUARE_BRACKET";
            case TokenTypeComment:          return "COMMENT";

            default:                            return "UNNAMED";

        }

    }

    inline std::unordered_map<std::string, TokenType> KeywordMap = {

        { "void", TokenTypeVoidKeyword },
        { "int", TokenTypeIntegerKeyword },
        { "string", TokenTypeStringKeyword },
        { "return", TokenTypeReturnKeyword },
        { "struct", TokenTypeStructKeyword },

    };

    struct Token {

        TokenType Type{TokenTypeWhitespace};
        std::string Text;

        size_t StartOffset{0};
        size_t EndOffset{0};
        size_t LineNumber{1};

        void print() const {
            std::stringstream ss;
            ss << "Token {" << TokenTypeToString(Type) << ", " << Text << ", " << StartOffset << ":" << EndOffset << ", " << LineNumber << "}";
            Log::Info(ss.str());
        }

    };

}