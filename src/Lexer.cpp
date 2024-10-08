#include "Lexer.h"

using namespace Zyn;

std::vector<Token> Tokenizer::Parse(const std::string& inProgram) {

    std::vector<Token> tokens;

    Token currentToken;
    currentToken.m_LineNumber = 1;

    for(char currCh : inProgram) {

        switch (currCh) {

            case '(':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeOpenParen;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);
                
                break;

            case ')':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeCloseParen;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case '{':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeOpenCurlyBrace;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case '}':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }
                    
                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeCloseCurlyBrace;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case '+':
            case '-':
            case '*':
            case '/':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeBinaryOperator;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case '=':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeEquals;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case ';':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                    break;
                }

                if(currentToken.m_Type != TokenTypeUndefined) {
                    EndToken(currentToken, tokens);
                }

                currentToken.m_Type = TokenTypeSemiColon;
                currentToken.m_Text.append(1, currCh);
                EndToken(currentToken, tokens);

                break;

            case '"':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    EndToken(currentToken, tokens);
                } else if(currentToken.m_Type == TokenTypeUndefined) {
                    currentToken.m_Type = TokenTypeStringLiteral;
                } else {
                    EndToken(currentToken, tokens);
                    currentToken.m_Type = TokenTypeStringLiteral;
                }

                break;

            case '\n':
            case '\r':
                EndToken(currentToken, tokens);

                currentToken.m_LineNumber++;

                break;
            case '\t':
            case ' ':
                if(currentToken.m_Type == TokenTypeStringLiteral) {
                    currentToken.m_Text.append(1, currCh);
                } else {                    
                    EndToken(currentToken, tokens);
                }

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
                if(currentToken.m_Type == TokenTypeUndefined) {
                    currentToken.m_Type = TokenTypeIntegerLiteral;
                }
                
                currentToken.m_Text.append(1, currCh);

                break;

            default: 
                if(currentToken.m_Type == TokenTypeUndefined) {

                    if(std::isalpha(currCh)) {
                        
                        currentToken.m_Type = TokenTypeIdentifier;

                    }

                }

                currentToken.m_Text.append(1, currCh);

                break;

        }

    }

    EndToken(currentToken, tokens);

    return tokens;

}

void Tokenizer::EndToken(Token& token, std::vector<Token>& tokens) {

    if(token.m_Type != TokenTypeUndefined) {

        if(token.m_Type == TokenTypeIdentifier) {
            auto it = IDENTIFIER_MAP.find(token.m_Text);
            if(it != IDENTIFIER_MAP.end()) {
                token.m_Type = it->second;
            }
        }

        tokens.push_back(token);        
    }

    // Reset Token
    token.m_Type = TokenTypeUndefined;
    token.m_Text.erase();

}

bool Tokenizer::IsAlpha(const std::string& string) {

    for(char ch : string) {
        if(!isalpha(ch)) {
            return false;
        }
    }
    
    return true;

}

bool Tokenizer::IsInt(const std::string& string) {

    std::string::const_iterator it = string.begin();
    while(it != string.end() && std::isdigit(*it)) ++it;
    return !string.empty() && it == string.end();

}