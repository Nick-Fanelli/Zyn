#include "Lexer.h"

using namespace Zyn;

static void DefaultHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    ZYN_PROFILE_FUNCTION()

    tokenizer.Advance(match.str().size());
    tokenizer.PushBackToken(tokenType, match.str());

}

static void SkipHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    ZYN_PROFILE_FUNCTION()

    tokenizer.Advance(match.str().size());

}

static void IdentifierHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    ZYN_PROFILE_FUNCTION()

    tokenizer.Advance(match.str().size());

    if (const auto it = KeywordMap.find(match.str()); it != KeywordMap.end()) {
        tokenType = it->second;
    }

    tokenizer.PushBackToken(tokenType, match.str());

}

Tokenizer::Tokenizer(const std::string& inProgram) : m_InProgram(inProgram) {

    ZYN_PROFILE_FUNCTION();

    m_TokenPatterns = {

        { std::regex(R"(\s+)"), TokenTypeWhitespace, SkipHandler }, // Whitespace
        { std::regex(R"(//.*)"), TokenTypeWhitespace, SkipHandler }, // Single-Line Comment
        { std::regex(R"(/\*(.|\n)*\*/)"), TokenTypeWhitespace, SkipHandler }, // Multi-Line Comment

        { std::regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"), TokenTypeIdentifier, IdentifierHandler },

        { std::regex(R"(".*")"), TokenTypeStringLiteral, DefaultHandler },
        { std::regex(R"([0-9]+(\.[0-9]+)?f)"), TokenTypeFloatLiteral, DefaultHandler },
        { std::regex(R"([0-9]+\.[0-9]+)"), TokenTypeDoubleLiteral, DefaultHandler },
        { std::regex(R"([0-9]+)"), TokenTypeIntegerLiteral, DefaultHandler },

        // Parens, Braces, Brackets
        { std::regex(R"(\()"), TokenTypeOpenParen, DefaultHandler },
        { std::regex(R"(\))"), TokenTypeCloseParen, DefaultHandler },
        { std::regex(R"(\{)"), TokenTypeOpenCurlyBrace, DefaultHandler },
        { std::regex(R"(\})"), TokenTypeCloseCurlyBrace, DefaultHandler },
        { std::regex(R"(\[)"), TokenTypeOpenSquareBracket, DefaultHandler },
        { std::regex(R"(\])"), TokenTypeCloseSquareBracket, DefaultHandler },

        // Multi Numerical Manipulation Operators
        { std::regex(R"(\+=)"), TokenTypePlusEqualsOperator, DefaultHandler },
        { std::regex(R"(\-=)"), TokenTypeMinusEqualsOperator, DefaultHandler },
        { std::regex(R"(\/=)"), TokenTypeDivideEqualsOperator, DefaultHandler },
        { std::regex(R"(\*=)"), TokenTypeMultiplyEqualsOperator, DefaultHandler },

        // Single Binary Operators
        { std::regex(R"(\+)"), TokenTypePlusOperator, DefaultHandler },
        { std::regex(R"(\-)"), TokenTypeMinusOperator, DefaultHandler },
        { std::regex(R"(\/)"), TokenTypeDivideOperator, DefaultHandler },
        { std::regex(R"(\*)"), TokenTypeMultiplyOperator, DefaultHandler },

        // Comparison
        { std::regex(R"(\|\|)"), TokenTypeOrOperator, DefaultHandler },
        { std::regex(R"(&&)"), TokenTypeAndOperator, DefaultHandler },
        { std::regex(R"(==)"), TokenTypeEqEq, DefaultHandler },
        { std::regex(R"(>)"), TokenTypeGreaterThan, DefaultHandler },
        { std::regex(R"(<)"), TokenTypeLessThan, DefaultHandler },

        // Assignment
        { std::regex(R"(!=)"), TokenTypeNotEquals, DefaultHandler },
        { std::regex(R"(=)"), TokenTypeEquals, DefaultHandler },

        { std::regex(R"(!)"), TokenTypeExclamation, DefaultHandler },
        { std::regex(R"(\?)"), TokenTypeQuestionMark, DefaultHandler },

        // Delimiter
        { std::regex(R"(;)"), TokenTypeSemiColon, DefaultHandler },
        { std::regex(R"(:)"), TokenTypeColon, DefaultHandler },
        { std::regex(R"(\.)"), TokenTypeDot, DefaultHandler },
        { std::regex(R"(,)"), TokenTypeComma, DefaultHandler },

    };

}

std::vector<Token> Tokenizer::Parse() {

    ZYN_PROFILE_FUNCTION()

    while(!IsAtEOF()) {

        ZYN_PROFILE_SCOPE("Tokenizer::Parse:While(!IsAtEOF())");

        bool matched = false;

        for (auto& [pattern, tokenType, handler] : m_TokenPatterns) {

            ZYN_PROFILE_SCOPE("Tokenizer::Parse:While(!IsAtEOF()):ForLoop")

            std::smatch match;

            std::string::const_iterator begin = m_InProgram.cbegin() + m_Pos;

            if (std::regex_search(begin, m_InProgram.cend(), match, pattern)) {
                if (match.position() == 0) {

                    handler(*this, tokenType, match);

                    matched = true;
                    break;
                }
            }

        }

        if (!matched) {
            std::cout << "Unrecognized symbol " << m_InProgram.substr(m_Pos, 1) << std::endl;
            break;
        }

    }

    m_Tokens.push_back({ TokenTypeEOF, "EOF" });

    return m_Tokens;

}

void Tokenizer::Advance(const size_t n) {
    m_Pos += n;
}

void Tokenizer::PushBackToken(TokenType tokenType, std::string_view text) {
    m_Tokens.push_back({ tokenType, std::move(std::string(text)) });
}
