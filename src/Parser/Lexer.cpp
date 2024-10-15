#include "Lexer.h"

#include "AST.h"

using namespace Zyn;

void Tokenizer::EndToken(Token& token) {

    if (token.Type != TokenTypeWhitespace && token.Type != TokenTypeComment) {

        if (token.Type == TokenTypeIdentifier) {
            if (KeywordMap.contains(token.Text)) {
                token.Type = KeywordMap.at(token.Text);
            }
        }

        m_Tokens.push_back(token);
    }

    token.Type = TokenTypeWhitespace;
    token.Text.erase();

}


void Tokenizer::SingleTokenHandler(Token& currentToken, const TokenType tokenType, const char character) {

    if (currentToken.Type == TokenTypeComment)
        return;

    if (currentToken.Type == TokenTypeStringLiteral) {
        currentToken.Text.push_back(character);
        return;
    }

    if (currentToken.Type != TokenTypeWhitespace) {
        EndToken(currentToken);
    }

    currentToken.Type = tokenType;
    currentToken.Text.push_back(character);

    EndToken(currentToken);

}

void Tokenizer::NumericalTokenHandler(Token& currentToken, const TokenType tokenType, const char character) {

    if (currentToken.Type == TokenTypeComment)
        return;

    if (currentToken.Type == TokenTypeStringLiteral) {
        currentToken.Text.push_back(character);
        return;
    }

    if (currentToken.Type == tokenType) {
        currentToken.Text.push_back(character);
        return;
    }

    if (currentToken.Type != TokenTypeWhitespace) {
        EndToken(currentToken);
    }

    currentToken.Type = tokenType;
    currentToken.Text.push_back(character);

}

void Tokenizer::StringTokenHandler(Token& currentToken) {

    if (currentToken.Type == TokenTypeComment)
        return;

    if (currentToken.Type == TokenTypeStringLiteral) {
        EndToken(currentToken);
        return;
    }

    if (currentToken.Type != TokenTypeWhitespace) {
        EndToken(currentToken);
    }

    currentToken.Type = TokenTypeStringLiteral;

}

Tokenizer::Tokenizer(const std::string& inProgram) : m_InProgram(inProgram) {}

std::vector<Token> Tokenizer::Parse() {

    ZYN_PROFILE_FUNCTION()

    Token currenToken{TokenTypeWhitespace, "", 0, 0, 1};

    while (m_Pos < m_InProgram.size()) {

        char c = At();

        ZYN_PROFILE_SCOPE("Tokenizer::Parse::ForLoop");

        switch (c) {

            case '"':
                StringTokenHandler(currenToken);
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                NumericalTokenHandler(currenToken, TokenTypeIntegerLiteral, c);

                break;

            case '{':
                SingleTokenHandler(currenToken, TokenTypeOpenCurlyBrace, c);
                break;
            case '}':
                SingleTokenHandler(currenToken, TokenTypeCloseCurlyBrace, c);
                break;
            case '(':
                SingleTokenHandler(currenToken, TokenTypeOpenParen, c);
                break;
            case ')':
                SingleTokenHandler(currenToken, TokenTypeCloseParen, c);
                break;
            case '[':
                SingleTokenHandler(currenToken, TokenTypeOpenSquareBracket, c);
                break;
            case ']':
                SingleTokenHandler(currenToken, TokenTypeCloseSquareBracket, c);
                break;

            case '?':
                SingleTokenHandler(currenToken, TokenTypeQuestionMark, c);
                break;
            case '.':
                SingleTokenHandler(currenToken, TokenTypeDot, c);
            break;

            case '+':
                SingleTokenHandler(currenToken, TokenTypePlusOperator, c);
                break;
            case '-':
                SingleTokenHandler(currenToken, TokenTypeMinusOperator, c);
                break;
            case '*':
                SingleTokenHandler(currenToken, TokenTypeMultiplyOperator, c);
                break;
            case '/':
                if (currenToken.Type == TokenTypeComment) {
                    break;
                }

                if (PeekChar().has_value()) {
                    if (PeekChar().value() == '/') { // Start Comment
                        currenToken.Type = TokenTypeComment;
                        break;
                    }
                }

                SingleTokenHandler(currenToken, TokenTypeDivideOperator, c);
                break;
            case '=':
                SingleTokenHandler(currenToken, TokenTypeEquals, c);
                break;

            case ':':
                SingleTokenHandler(currenToken, TokenTypeColon, c);
                break;
            case ';':
                SingleTokenHandler(currenToken, TokenTypeSemiColon, c);
                break;
            case ',':
                SingleTokenHandler(currenToken, TokenTypeComma, c);
                break;

            case ' ':
            case '\t':
                if (currenToken.Type == TokenTypeComment)
                    break;

                if (currenToken.Type == TokenTypeStringLiteral) {
                    currenToken.Text.push_back(c);
                } else {
                    EndToken(currenToken);
                }

                break;

            case '\n':
            case '\r':
                EndToken(currenToken);
                break;

            default:
                if (currenToken.Type == TokenTypeWhitespace) {
                    currenToken.Type = TokenTypeIdentifier;
                }

                if (isalpha(c)) {
                    currenToken.Text.push_back(c);
                } else {
                    Log::FormatError("Invalid Symbol found during lexical anaylis: %c", c);
                    exit(-1);
                }

                break;

        }

        m_Pos++;

    }

    EndToken(currenToken);

    m_Tokens.push_back({ TokenTypeEOF, "EOF" });

    return m_Tokens;

}

void Tokenizer::PushBackToken(TokenType tokenType, std::string_view text) {
    m_Tokens.push_back({ tokenType, std::move(std::string(text)) });
}

char Tokenizer::At() const { return m_InProgram.at(m_Pos); }
std::optional<char> Tokenizer::PeekChar() const { return (m_Pos + 1 < m_InProgram.size()) ? std::make_optional(m_InProgram.at(m_Pos + 1)) : std::nullopt; }