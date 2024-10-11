#include "Lexer.h"

using namespace Zyn;


static void SkipHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    tokenizer.Advance(match.str().size());

}

static void DefaultHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    tokenizer.Advance(match.str().size());
    tokenizer.PushBackToken(tokenType, match.str());

}

static void IntegerHandler(Tokenizer& tokenizer, TokenType tokenType, const std::smatch& match) {

    tokenizer.Advance(match.str().size());

}

Tokenizer::Tokenizer(const std::string& inProgram) : m_InProgram(inProgram) {

    m_TokenPatterns = {

        { std::regex(R"(\s+)"), TokenTypeWhitespace, SkipHandler },
        { std::regex(R"([0-9]+)"), TokenTypeIntegerLiteral, DefaultHandler },

        // Parens, Braces, Brackets
        { std::regex(R"(\()"), TokenTypeOpenParen, DefaultHandler },
        { std::regex(R"(\))"), TokenTypeCloseParen, DefaultHandler },

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

        // Assignment
        { std::regex(R"(!=)"), TokenTypeNotEquals, DefaultHandler },
        { std::regex(R"(=)"), TokenTypeEquals, DefaultHandler },


    };

}

std::vector<Token> Tokenizer::Parse() {

    bool matched;

    while(!IsAtEOF()) {

        matched = false;

        for (auto& [pattern, tokenType, handler] : m_TokenPatterns) {

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

    return m_Tokens;

}

void Tokenizer::Advance(const size_t n) {
    m_Pos += n;
}

void Tokenizer::PushBackToken(TokenType tokenType, std::string_view text) {
    m_Tokens.push_back({ tokenType, std::move(std::string(text)) });
}
