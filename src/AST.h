#pragma once

#include "zynpch.h"

namespace Zyn {

    enum NodeType {

        NodeTypeProgram,
        NodeTypeIntegerLiteral,
        NodeTypeIdentifier,
        NodeTypeBinaryExpr

    };

    struct Statement {
    
        const NodeType m_Type;

    };

    struct Program : public Statement {

        const NodeType m_Type{NodeTypeProgram};

        Statement m_Body[];

    };

    struct Expr : public Statement {};

    struct BinaryExpr : public Expr {

        const NodeType m_Type{NodeTypeBinaryExpr};

        Expr left;
        Expr right;
        std::string op;

    };

    struct Identifier : public Expr {

        const NodeType m_Type{NodeTypeIdentifier};
        
        std::string symbol;

    };

    struct IntegerLiteral : public Expr {

        const NodeType m_Type{NodeTypeIntegerLiteral};

        int number;

    };

}