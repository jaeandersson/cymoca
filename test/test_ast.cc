#include <gtest/gtest.h>
#include <iostream>

#include "cymoca/ast/ast.h"
#include "cymoca/ast/listener/lisp.h"
#include "test_config.h"

using namespace cymoca::ast;

// save typing
#define M(NAME) std::make_unique<NAME>
namespace elem = element;
namespace eq = equation;
namespace expr = expression;
namespace cond = condition;
namespace mdl = model;

struct AddOne : listener::Base {
  void enter(expr::Number &ctx) override { ctx.setValue(ctx.getValue() + 1); }
};

TEST(Ast, If) {
  auto c = M(mdl::Class)(
      M(mdl::ElementDict)(
          M(elem::Component)("x", "Real", elem::Prefix::CONSTANT),
          M(elem::Component)("y", "Real", elem::Prefix::CONSTANT)),
      M(eq::List)(M(eq::If)(
          M(eq::Block)(
              M(cond::LessThan)(M(expr::Reference)("x"), M(expr::Number)(3)),
              M(eq::List)(M(eq::Simple)(
                  M(expr::Add)(M(expr::Number)(1), M(expr::Number)(2)),
                  M(expr::Reference)("x")))),
          M(eq::Block)(M(cond::And)(M(cond::LessThan)(M(expr::Reference)("x"),
                                                      M(expr::Number)(3)),
                                    M(cond::Boolean)(true)),
                       M(eq::List)(M(eq::Simple)(
                           M(expr::Add)(M(expr::Number)(1), M(expr::Number)(2)),
                           M(expr::Reference)("x")))))));

  auto c2 = c->cloneAs<mdl::Class>();
  listener::Lisp printer;
  Walker walker;
  walker.walk(*c, printer);
  std::cout << printer.get() << std::endl;

  AddOne add_one;
  walker.walk(*c, add_one);
  walker.walk(*c, printer);
  std::cout << printer.get() << std::endl;

  walker.walk(*c2, printer);
  std::cout << printer.get() << std::endl;
}