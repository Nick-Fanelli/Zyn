#include "Parser.h"

using namespace Zyn;

std::unique_ptr<ExpressionNode> Parser::ParsePrimitiveExpression() {

    switch (At().Type) {

        case TokenTypeIdentifier:
            return std::make_unique<IdentifierNode>(Consume().Text);

        case TokenTypeIntegerLiteral:
            return std::make_unique<IntegerLiteralNode>(std::stoi(Consume().Text));

        default: // TODO: Handle error
            std::cout << "ERROR: Unexpected token found during parsing " << At().Text << std::endl;
            exit(-1);

    }

}

std::unique_ptr<ExpressionNode> Parser::ParseAdditiveExpression() {

    std::unique_ptr<ExpressionNode> left = ParsePrimitiveExpression();

    while (At().Type == TokenTypePlusOperator || At().Type == TokenTypeMinusOperator) {

        const std::string_view op = Consume().Text;
        std::unique_ptr<ExpressionNode> right = ParsePrimitiveExpression();

        left = std::make_unique<BinaryExpressionNode>(&left, op.at(0), &right);

    }

    return left;

}

std::unique_ptr<ExpressionNode> Parser::ParseExpression() {

    // Integer Literal and Identifier
    return ParseAdditiveExpression();

}

std::unique_ptr<StatementNode> Parser::ParseStatement() {

    // TODO: Implement all types of statements eg. function statements
    return ParseExpression();

}

std::unique_ptr<ProgramNode> Parser::ProduceAST() {
    std::unique_ptr<ProgramNode> program = std::make_unique<ProgramNode>();

    while (!IsCurrentTokenEOF()) {

        program->Body.push_back(ParseStatement());

    }

    return program;
}