#pragma once

#include "zynpch.h"

#include "Parser/AST.h"

namespace Zyn {

     template<typename T>
     static std::ostream& operator<<(std::ostream& os, std::vector<T>& vector) {

          os << "[ ";

          for (auto& it : vector) {
               os << it << ", ";
          }

          os << "]";

          return os;

     }

     inline std::ostream& operator<<(std::ostream& os, Node* node) {
          if (auto* rNode = dynamic_cast<ProgramNode*>(node)) {
               return os << "Program{ " << rNode->Body << " }";
          }

          if (auto* rNode = dynamic_cast<BinaryExpressionNode*>(node)) {
               return os << "BinaryExpressionNode{ left: " << rNode->Left << ", op: " << rNode->Operator <<  ", right: " << rNode->Right << " }";
          }

          if (auto* rNode = dynamic_cast<IntegerLiteralNode*>(node)) {
               return os << "IntegerLiteralNode{ value: " << rNode->Value <<  " }";
          }

          return os;
     }

}