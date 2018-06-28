//
// Created by jgoppert on 6/28/18.
//

#include "FunctionCall.h"

namespace cymoca {
namespace ast {

FunctionCall::FunctionCall(const string &name, unique_ptr<Args> args) :
    Expr(typeid(*this)), _name(name), _args(move(args)) {
  _args->setParent(this);
}

void FunctionCall::swapChild(Node *oldChild, unique_ptr<Node> newChild) {
}

vector<Node *> FunctionCall::children() const {
  return {};
}


unique_ptr<Node> FunctionCall::clone() const {
  auto args = static_unique_ptr_cast<Args>(_args->clone());
  return make_unique<FunctionCall>(name(), move(args));
}

} // ast
} // cymoca