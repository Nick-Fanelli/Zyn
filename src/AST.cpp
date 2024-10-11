#include "AST.h"

using namespace Zyn;

[[nodiscard]] std::string ProgramNode::Represent() const {

    std::stringstream ss;

    ss << "{ type: Program, body: [";

    for (auto& it : Body) {

        ss << it->Represent();
        ss << ", ";
    }

    ss << "] }";

    return ss.str();

}

[[nodiscard]] std::string BinaryExpressionNode::Represent() const {

    std::stringstream ss;

    ss << "{ type: BinaryExpression, left: " << Left->Represent() << ", operator: " << Operator
            << ", right: " << Right->Represent() << " }";

    return ss.str();

}


[[nodiscard]] std::string IdentifierNode::Represent() const {

    std::stringstream ss;

    ss << "{ type: Identifier, symbol: " << Symbol << " }";

    return ss.str();

}

[[nodiscard]] std::string IntegerLiteralNode::Represent() const {

    std::stringstream ss;

    ss << "{ type: IntegerLiteral, value: " << Value << " }";

    return ss.str();

}
