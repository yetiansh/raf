#pragma once

#include <mnm/base.h>
#include <mnm/ir.h>
#include <mnm/value.h>

namespace mnm {
namespace op {
namespace attrs {

class DropoutAttrs : public ir::AttrsNode<DropoutAttrs> {
 public:
  ir::Float dropout;

  MNM_DECLARE_ATTRS(DropoutAttrs, "mnm.attrs.DropoutAttrs") {
    MNM_ATTR_FIELD(dropout);
  }
};

}  // namespace attrs
}  // namespace op
}  // namespace mnm
