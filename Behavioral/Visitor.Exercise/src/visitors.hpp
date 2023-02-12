#ifndef VISITORS_HPP
#define VISITORS_HPP

#include "ast.hpp"

class ExprEvalVisitor : public AST::AstVisitor
{
    int result_{};

public:
    void visit(AST::AddNode& node)
    {
        ExprEvalVisitor lv, rv;
        node.left().accept(lv);
        node.right().accept(rv);
        result_ = lv.result() + rv.result();
    }

    void visit(AST::MultiplyNode& node)
    {
        ExprEvalVisitor lv, rv;
        node.left().accept(lv);
        node.right().accept(rv);
        result_ = lv.result() * rv.result();
    }

    void visit(AST::IntNode& node)
    {
        result_ = node.value();
    }

    int result() const
    {
        return result_;
    }
};

// TODO
class PrintingVisitor
{
};

#endif // VISITORS_HPP