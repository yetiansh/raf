/*!
 * Copyright (c) 2020 by Contributors
 * \file merge_compiler_regions.cc
 * \brief After operators have been annotated with the targets that support
 * them, this pass creates regions of the operators for each target. It
 * is guaranteed that the regions will have a topological ordering so that
 * no data dependency issues exist.
 *
 * This pass only introduces annotations to indicate the regions.
 * partition_graph must subsequently be called to lift these regions out
 * as external functions.
 */
#include "mnm/op.h"
#include "mnm/ir.h"
#include "./common.h"
#include "../op/schema/annotation.h"

namespace mnm {
namespace pass {
namespace merge_compiler_regions {

using namespace mnm::ir;
using namespace tvm;
using namespace tvm::relay;
using mnm::op::schema::CompilerArgs;

static const Op& begin_op = CompilerBeginOp();
static const Op& end_op = CompilerEndOp();

class MergeAnnotations : public ExprRewriter {
 public:
  explicit MergeAnnotations() {
  }

  Expr Rewrite_(const FunctionNode* func, const Expr& post) final {
    std::unique_ptr<ExplicitLetList> ell_ = ExplicitLetList::make(func->body);
    const std::unique_ptr<ExplicitLetList> ref_ell_ = ExplicitLetList::make(func->body);

    size_t ell_n = ell_->vars.size();
    CHECK_GT(ell_n, 0U);

    // Multiple ops inside the FunctionNode. Explore the possible of merging.
    if (ell_n > 1) {
      for (size_t i = 1; i < ell_n; ++i) {
        const CallNode* prev_call = ell_->exprs[i - 1].as<CallNode>();
        const CallNode* call = ell_->exprs[i].as<CallNode>();

        // Merge the CallNodes inside two LetNodes if they have the same target.
        if (ref_ell_->exprs[i - 1].as<CallNode>()->attrs.as<CompilerArgs>()->compiler ==
            ref_ell_->exprs[i].as<CallNode>()->attrs.as<CompilerArgs>()->compiler) {
          // Remove the compiler_begin annotations of the previous CallNode.
          Expr prev_expr = RemoveAnnotation(GetRef<Expr>(prev_call), end_op);
          ell_->exprs[i - 1] = prev_expr;
          // Remove the compiler_end annotations of the present CallNode.
          Expr expr = RemoveAnnotation(GetRef<Expr>(call), begin_op);
          ell_->exprs[i] = expr;
        }
      }

      // Get the new function body from the modified ExplicitLetList.
      Expr new_body = ell_->AsExpr();

      return Function(func->params, new_body, func->ret_type, func->type_params, func->attrs);
    } else {
      return post;
    }
  }

 private:
  ExplicitLetList ell_;
};

Expr MergeCompilerRegions(const Expr& expr) {
  MergeAnnotations merge_anno = MergeAnnotations();
  return PostOrderRewrite(expr, &merge_anno);
}

}  // namespace merge_compiler_regions

ir::Expr MergeCompilerRegions(ir::Expr expr) {
  return merge_compiler_regions::MergeCompilerRegions(expr);
}

MNM_REGISTER_GLOBAL("mnm.pass_.MergeCompilerRegions").set_body_typed(MergeCompilerRegions);

}  // namespace pass
}  // namespace mnm
