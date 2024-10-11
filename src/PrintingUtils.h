#pragma once

#include "zynpch.h"

#include "AST.h"

namespace Zyn {

    static std::ostream& RepresentProgram(std::ostream& os, const ProgramNode& program);
    static std::ostream& RepresentIdentifier(std::ostream& os, const IdentifierNode& identifier);
    static std::ostream& RepresentIntegerLiteral(std::ostream& os, const IntegerLiteralNode& identifier);
    static std::ostream& RepresentBinaryExpression(std::ostream& os, const BinaryExpressionNode& identifier);

    inline std::ostream& operator<<(std::ostream& os, const Node& node) {

        if (auto* programNode = dynamic_cast<const ProgramNode*>(&node)) {
            return RepresentProgram(os, *programNode);
        }

        if (auto* identifierNode = dynamic_cast<const IdentifierNode*>(&node)) {
            return RepresentIdentifier(os, *identifierNode);
        }

        if (auto* integerLiteralNode = dynamic_cast<const IntegerLiteralNode*>(&node)) {
            return RepresentIntegerLiteral(os, *integerLiteralNode);
        }

        if (auto* binaryExpressionNode = dynamic_cast<const BinaryExpressionNode*>(&node)) {
            return RepresentBinaryExpression(os, *binaryExpressionNode);
        }

        return os << "{ type: Unhandled }";

    }

    static std::ostream& RepresentBinaryExpression(std::ostream& os, const BinaryExpressionNode& identifier) {

        return os << "{ type: BinaryExpression, left: " << identifier.Left << ", operator: " << identifier.Operator
            << ", right: " << identifier.Right << " }";

    }

    static std::ostream& RepresentIntegerLiteral(std::ostream& os, const IntegerLiteralNode& identifier) {

        return os << "{ type: IntegerLiteral, value: " << identifier.Value << " }";

    }

    static std::ostream& RepresentProgram(std::ostream& os, const ProgramNode& program) {

        os << "{ type: Program, body: [";

        for (auto& it : program.Body) {
            os << *it;
            os << ", ";
        }

        return os << "] }";

    }

    static std::ostream& RepresentIdentifier(std::ostream& os, const IdentifierNode& identifier) {

        return os << "{ type: Identifier, symbol: " << identifier.Symbol << " }";

    }

    // inline std::ostream& operator<<(std::ostream& os, const StatementNode& node) {
    //
    //     return os << "{ type: Statement }";
    //
    // }
    //
    // inline std::ostream& operator<<(std::ostream& os, const IdentifierNode& node) {
    //
    //     return os << "{ type: Identifier }";
    //
    // }
    //
    // inline std::ostream& operator<<(std::ostream& os, const ProgramNode& node) {
    //
    //     os << "{ type: ProgramNode, body: [ ";
    //
    //     for (auto& it : node.Body) {
    //         os << *it;
    //     }
    //
    //     return os << " ] }";
    //
    // }

}