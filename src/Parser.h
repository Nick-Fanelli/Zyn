#pragma once

#include "zynpch.h"

#include "Lexer.h"
#include "AST.h"

namespace Zyn {

    class Parser {

    public:
        explicit Parser(const std::vector<Token>& tokens) : m_Tokens(tokens) {}

        std::unique_ptr<ProgramNode> ProduceAST();

    private:
        [[nodiscard]] bool IsCurrentTokenEOF() const { return m_Tokens[m_Pos].Type == TokenTypeEOF; }
        [[nodiscard]] const Token& At() const { return m_Tokens[m_Pos]; }

        [[nodiscard]] const Token& Consume() { return m_Tokens[m_Pos++]; }

        std::unique_ptr<ExpressionNode> ParsePrimitiveExpression();
        std::unique_ptr<ExpressionNode> ParseAdditiveExpression();
        std::unique_ptr<ExpressionNode> ParseExpression();
        std::unique_ptr<StatementNode> ParseStatement();

    public:

    private:
        const std::vector<Token>& m_Tokens;
        size_t m_Pos = 0;

    };

}