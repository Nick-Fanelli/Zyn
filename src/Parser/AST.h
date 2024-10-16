#pragma once

#include <utility>

#include "zynpch.h"

namespace Zyn {

    enum NodeType {

        NodeTypeUnknown,
        NodeTypeProgram,
        NodeTypeBinaryExpression,
        NodeTypeIdentifier,
        NodeTypeIntegerLiteral,

    };

    struct Node {

        NodeType Type = NodeTypeUnknown;

        Node() = default;
        virtual ~Node() = default;

        [[nodiscard]] virtual std::string Represent() const = 0;

    };

    struct StatementNode : public Node {};

    struct ProgramNode : public StatementNode {

        NodeType Type = NodeTypeProgram;
        std::vector<std::unique_ptr<StatementNode>> Body;

        [[nodiscard]] std::string Represent() const override;

    };

    struct ExpressionNode : public StatementNode {};

    struct BinaryExpressionNode : public ExpressionNode {

        NodeType Type = NodeTypeBinaryExpression;

        std::unique_ptr<ExpressionNode> Left;
        char Operator{};
        std::unique_ptr<ExpressionNode> Right;

        BinaryExpressionNode() = default;

        BinaryExpressionNode(std::unique_ptr<ExpressionNode> left, char op, std::unique_ptr<ExpressionNode> right)
            : Left(std::move(left)), Operator(op), Right(std::move(right)) {}

        BinaryExpressionNode(std::unique_ptr<ExpressionNode>* left, char op, std::unique_ptr<ExpressionNode>* right)
            : Left(std::move(*left)), Operator(op), Right(std::move(*right)) {}

        [[nodiscard]] std::string Represent() const override;

    };

    struct IdentifierNode : public ExpressionNode {

        NodeType Type = NodeTypeIdentifier;

        std::string Symbol;

        IdentifierNode() = default;
        explicit IdentifierNode(std::string symbol) : Symbol(std::move(symbol)) {}

        [[nodiscard]] std::string Represent() const override;

    };

    struct IntegerLiteralNode: public ExpressionNode {

        NodeType Type = NodeTypeIntegerLiteral;

        int Value{};

        IntegerLiteralNode() = default;
        explicit IntegerLiteralNode(const int value) : Value(value) {}

        [[nodiscard]] std::string Represent() const override;

    };

}