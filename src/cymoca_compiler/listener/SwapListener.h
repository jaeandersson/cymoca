//
// Created by jgoppert on 6/28/18.
//

#pragma once

#include "../ast/Listener.h"
#include "../../../../../../../usr/include/c++/5/memory"
#include "../../../../../../../usr/include/c++/5/unordered_map"

using namespace std;

namespace cymoca {
namespace ast {

class SwapListener : public Listener {
 public:
  void apply();
  void set(const Node &ctx, unique_ptr<Node> node);
 private:
  unordered_map<const Node *, unique_ptr<Node>> _swap{};
};

} // ast
} // cymoca