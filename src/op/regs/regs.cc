/*!
 * Copyright (c) 2020 by Contributors
 * \file src/op/regs/regs.cc
 * \brief Auto generated. Do not touch.
 */
#include <algorithm>
#include <array>
#include "./regs_utils.h"
#include "./ffi2expr.h"
#include "./ffi2schema.h"
#include "./value2schema.h"
#include "./schema2value.h"
#include "../schema/list_args.h"
#include "../schema/likes.h"
#include "../schema/loss.h"
#include "../schema/nn.h"
#include "../schema/optimizer.h"
#include "../schema/transform.h"
#include "../schema/ufunc.h"

using namespace mnm::ir;
using namespace mnm::value;
using namespace mnm::registry;
using namespace mnm::binding;
using mnm::op::FMNMSchema;
using mnm::executor::interpreter::InvokePrimitive;

// Part 0. Op names
namespace mnm {
namespace op {
namespace regs {
namespace names {
static const char abs[] = "mnm.op.abs";
static const char add[] = "mnm.op.add";
static const char avg_pool2d[] = "mnm.op.avg_pool2d";
static const char avg_pool2d_dx[] = "mnm.op.avg_pool2d_dx";
static const char batch_flatten[] = "mnm.op.batch_flatten";
static const char batch_matmul[] = "mnm.op.batch_matmul";
static const char batch_norm_infer[] = "mnm.op.batch_norm_infer";
static const char batch_norm_train[] = "mnm.op.batch_norm_train";
static const char batch_norm_train_dxwb[] = "mnm.op.batch_norm_train_dxwb";
static const char broadcast_to[] = "mnm.op.broadcast_to";
static const char ceil[] = "mnm.op.ceil";
static const char collapse_sum_like[] = "mnm.op.collapse_sum_like";
static const char conv2d[] = "mnm.op.conv2d";
static const char conv2d_dw[] = "mnm.op.conv2d_dw";
static const char conv2d_dx[] = "mnm.op.conv2d_dx";
static const char copy[] = "mnm.op.copy";
static const char cos[] = "mnm.op.cos";
static const char divide[] = "mnm.op.divide";
static const char equal[] = "mnm.op.equal";
static const char erf[] = "mnm.op.erf";
static const char erf_dx[] = "mnm.op.erf_dx";
static const char expand_dims[] = "mnm.op.expand_dims";
static const char floor[] = "mnm.op.floor";
static const char get_kept_dims[] = "mnm.op.get_kept_dims";
static const char get_reduce_axis[] = "mnm.op.get_reduce_axis";
static const char greater[] = "mnm.op.greater";
static const char greater_equal[] = "mnm.op.greater_equal";
static const char less[] = "mnm.op.less";
static const char less_equal[] = "mnm.op.less_equal";
static const char log[] = "mnm.op.log";
static const char log_softmax[] = "mnm.op.log_softmax";
static const char log_softmax_dx[] = "mnm.op.log_softmax_dx";
static const char logical_not[] = "mnm.op.logical_not";
static const char matmul[] = "mnm.op.matmul";
static const char matmul_nt[] = "mnm.op.matmul_nt";
static const char matmul_tn[] = "mnm.op.matmul_tn";
static const char matmul_tt[] = "mnm.op.matmul_tt";
static const char max_pool2d[] = "mnm.op.max_pool2d";
static const char max_pool2d_dx[] = "mnm.op.max_pool2d_dx";
static const char maximum[] = "mnm.op.maximum";
static const char minimum[] = "mnm.op.minimum";
static const char mod[] = "mnm.op.mod";
static const char multiply[] = "mnm.op.multiply";
static const char negative[] = "mnm.op.negative";
static const char nll_loss[] = "mnm.op.nll_loss";
static const char nll_loss_dpred[] = "mnm.op.nll_loss_dpred";
static const char nll_loss_dtrue[] = "mnm.op.nll_loss_dtrue";
static const char not_equal[] = "mnm.op.not_equal";
static const char relu[] = "mnm.op.relu";
static const char relu_dx[] = "mnm.op.relu_dx";
static const char reshape[] = "mnm.op.reshape";
static const char sequence_mask[] = "mnm.op.sequence_mask";
static const char sgd[] = "mnm.op.sgd";
static const char shape[] = "mnm.op.shape";
static const char sigmoid[] = "mnm.op.sigmoid";
static const char sigmoid_dx[] = "mnm.op.sigmoid_dx";
static const char softmax[] = "mnm.op.softmax";
static const char softmax_dx[] = "mnm.op.softmax_dx";
static const char sqrt[] = "mnm.op.sqrt";
static const char sqrt_dx[] = "mnm.op.sqrt_dx";
static const char subtract[] = "mnm.op.subtract";
static const char sum[] = "mnm.op.sum";
static const char take[] = "mnm.op.take";
static const char tanh[] = "mnm.op.tanh";
static const char tanh_dx[] = "mnm.op.tanh_dx";
static const char transpose[] = "mnm.op.transpose";
static const char transpose_dx[] = "mnm.op.transpose_dx";
}  // namespace names
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 1.1. FFI to schema (for each schema)
namespace mnm {
namespace op {
namespace regs {
namespace ffi2schema {

#define MNM_TAPE(i, norm, name)               \
  try {                                       \
    attrs->name = norm(values[i], tapes + i); \
  } catch (const dmlc::Error& e) {            \
    FillError(e, "{arg}", #name);             \
  }

#define MNM_POD(i, norm, name)     \
  try {                            \
    attrs->name = norm(values[i]); \
  } catch (const dmlc::Error& e) { \
    FillError(e, "{arg}", #name);  \
  }

#define MNM_PRELUDE(obj, n)                                                                \
  const int size = values.size();                                                          \
  CHECK_EQ(size, n) << "TypeError: Mismatched number of arguments for operator \"{op}\": " \
                    << "Expected " << n << ", but get " << size;                           \
  auto attrs = make_object<obj>();

Attrs BatchNorm(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BatchNormArgs, 7);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, running_mean);
  MNM_TAPE(2, ffi2schema::Tensor, running_var);
  MNM_TAPE(3, ffi2schema::Tensor, w);
  MNM_TAPE(4, ffi2schema::Tensor, b);
  MNM_POD(5, ffi2schema::Double, momentum);
  MNM_POD(6, ffi2schema::Double, eps);
  return Attrs(attrs);
}

Attrs BatchNormTrainDxwb(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BatchNormTrainDxwbArgs, 5);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, dy);
  MNM_TAPE(1, ffi2schema::Tensor, x);
  MNM_TAPE(2, ffi2schema::Tensor, w);
  MNM_TAPE(3, ffi2schema::Tensor, b);
  MNM_POD(4, ffi2schema::Double, eps);
  return Attrs(attrs);
}

Attrs Binary(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BinaryArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  return Attrs(attrs);
}

Attrs BinaryDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BinaryDxArgs, 4);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  MNM_TAPE(2, ffi2schema::Tensor, y);
  MNM_TAPE(3, ffi2schema::Tensor, dy);
  return Attrs(attrs);
}

Attrs BinaryUfunc(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BinaryUfuncArgs, 4);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  MNM_TAPE(2, ffi2schema::ArrayLike, out);
  MNM_TAPE(3, ffi2schema::ArrayLike, where);
  return Attrs(attrs);
}

Attrs BroadcastTo(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::BroadcastToArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

Attrs CollapseLike(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::CollapseLikeArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

Attrs Conv(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::ConvArgs, 6);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, w);
  MNM_POD(2, ffi2schema::IntOrTupleInt, stride);
  MNM_POD(3, ffi2schema::IntOrTupleInt, padding);
  MNM_POD(4, ffi2schema::IntOrTupleInt, dilation);
  MNM_POD(5, ffi2schema::Int, groups);
  return Attrs(attrs);
}

Attrs ConvDxw(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::ConvDxwArgs, 8);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x_or_w);
  MNM_TAPE(1, ffi2schema::Tensor, y);
  MNM_TAPE(2, ffi2schema::Tensor, dy);
  MNM_POD(3, ffi2schema::IntOrTupleInt, shape);
  MNM_POD(4, ffi2schema::IntOrTupleInt, stride);
  MNM_POD(5, ffi2schema::IntOrTupleInt, padding);
  MNM_POD(6, ffi2schema::IntOrTupleInt, dilation);
  MNM_POD(7, ffi2schema::Int, groups);
  return Attrs(attrs);
}

Attrs ExpandDims(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::ExpandDimsArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::Int, axis);
  MNM_POD(2, ffi2schema::Int, num_newaxis);
  return Attrs(attrs);
}

Attrs LocalResponseNorm(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::LocalResponseNormArgs, 5);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::Int, size);
  MNM_POD(2, ffi2schema::Double, alpha);
  MNM_POD(3, ffi2schema::Double, beta);
  MNM_POD(4, ffi2schema::Double, k);
  return Attrs(attrs);
}

Attrs Loss(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::LossArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, y_true);
  MNM_TAPE(1, ffi2schema::Tensor, y_pred);
  return Attrs(attrs);
}

Attrs Pool(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::PoolArgs, 7);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, kernel);
  MNM_POD(2, ffi2schema::IntOrTupleInt, stride);
  MNM_POD(3, ffi2schema::IntOrTupleInt, padding);
  MNM_POD(4, ffi2schema::IntOrTupleInt, dilation);
  MNM_POD(5, ffi2schema::Bool, ceil_mode);
  MNM_POD(6, ffi2schema::Bool, include_pad);
  return Attrs(attrs);
}

Attrs PoolDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::PoolDxArgs, 9);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, y);
  MNM_TAPE(2, ffi2schema::Tensor, dy);
  MNM_POD(3, ffi2schema::IntOrTupleInt, kernel);
  MNM_POD(4, ffi2schema::IntOrTupleInt, stride);
  MNM_POD(5, ffi2schema::IntOrTupleInt, padding);
  MNM_POD(6, ffi2schema::IntOrTupleInt, dilation);
  MNM_POD(7, ffi2schema::Bool, ceil_mode);
  MNM_POD(8, ffi2schema::Bool, include_pad);
  return Attrs(attrs);
}

Attrs Reshape(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::ReshapeArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

Attrs SequenceMask(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::SequenceMaskArgs, 4);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, sequence_length);
  MNM_POD(2, ffi2schema::Double, mask_value);
  MNM_POD(3, ffi2schema::Int, axis);
  return Attrs(attrs);
}

Attrs Sgd(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::SgdArgs, 5);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, dx);
  MNM_TAPE(2, ffi2schema::Tensor, v);
  MNM_POD(3, ffi2schema::Double, learning_rate);
  MNM_POD(4, ffi2schema::Double, mu);
  return Attrs(attrs);
}

Attrs Softmax(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::SoftmaxArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::Int, axis);
  return Attrs(attrs);
}

Attrs SoftmaxDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::SoftmaxDxArgs, 4);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, y);
  MNM_TAPE(2, ffi2schema::Tensor, dy);
  MNM_POD(3, ffi2schema::Int, axis);
  return Attrs(attrs);
}

Attrs Sum(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::SumArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, axis);
  MNM_POD(2, ffi2schema::IntOrTupleInt, keep);
  return Attrs(attrs);
}

Attrs Take(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TakeArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, indices);
  MNM_TAPE(2, ffi2schema::ArrayLike, axis);
  return Attrs(attrs);
}

Attrs Ternary(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TernaryArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  MNM_TAPE(2, ffi2schema::ArrayLike, x3);
  return Attrs(attrs);
}

Attrs TernaryDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TernaryDxArgs, 5);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  MNM_TAPE(2, ffi2schema::ArrayLike, x3);
  MNM_TAPE(3, ffi2schema::Tensor, y);
  MNM_TAPE(4, ffi2schema::Tensor, dy);
  return Attrs(attrs);
}

Attrs TernaryUfunc(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TernaryUfuncArgs, 5);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x1);
  MNM_TAPE(1, ffi2schema::ArrayLike, x2);
  MNM_TAPE(2, ffi2schema::ArrayLike, x3);
  MNM_TAPE(3, ffi2schema::ArrayLike, out);
  MNM_TAPE(4, ffi2schema::ArrayLike, where);
  return Attrs(attrs);
}

Attrs Transpose(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TransposeArgs, 2);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_POD(1, ffi2schema::IntOrTupleInt, axes);
  return Attrs(attrs);
}

Attrs TransposeDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::TransposeDxArgs, 4);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::Tensor, x);
  MNM_TAPE(1, ffi2schema::Tensor, y);
  MNM_TAPE(2, ffi2schema::Tensor, dy);
  MNM_POD(3, ffi2schema::IntOrTupleInt, axes);
  return Attrs(attrs);
}

Attrs Unary(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::UnaryArgs, 1);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x);
  return Attrs(attrs);
}

Attrs UnaryDx(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::UnaryDxArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x);
  MNM_TAPE(1, ffi2schema::Tensor, y);
  MNM_TAPE(2, ffi2schema::Tensor, dy);
  return Attrs(attrs);
}

Attrs UnaryUfunc(const TVMArgs& values, GradTape* tapes) {
  MNM_PRELUDE(schema::UnaryUfuncArgs, 3);  // NOLINT(whitespace/line_length)
  MNM_TAPE(0, ffi2schema::ArrayLike, x);
  MNM_TAPE(1, ffi2schema::ArrayLike, out);
  MNM_TAPE(2, ffi2schema::ArrayLike, where);
  return Attrs(attrs);
}

#undef MNM_PRELUDE
#undef MNM_POD
#undef MNM_TAPE
}  // namespace ffi2schema
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 1.2. Imperative API, uses "Part 1.1. FFI to schema"
namespace mnm {
namespace op {
namespace regs {
namespace imperative {

#define MNM_PRELUDE(op, n_args, func, obj)                                                     \
  const auto* opack = OpPack<names::op, n_args>::Get();                                        \
  const auto* vpack = VarPack::Get();                                                          \
  std::array<GradTape, n_args> prev_tapes;                                                     \
  std::vector<Expr> grads(opack->grads.begin(), opack->grads.end());                           \
  Attrs _schema;                                                                               \
  try {                                                                                        \
    _schema = func(args, prev_tapes.data());                                                   \
  } catch (const dmlc::Error &e) {                                                             \
    FillError(e, "{op}", names::op);                                                           \
  }                                                                                            \
  Value value = InvokePrimitive(CallValues::make(opack->opv, _schema));                        \
  int n_tapes = grads.size();                                                                  \
  bool full_grads = RemoveNoGrad(prev_tapes.data(), grads.data(), &n_tapes);                   \
  /* case 1: no grad required */                                                               \
  if (n_tapes == 0) {                                                                          \
    *ret = DeTuple(value);                                                                     \
    return;                                                                                    \
  }                                                                                            \
  Expr body = TupleNode::make({grads.begin(), grads.begin() + n_tapes});                       \
  std::vector<const ExprNode*> used_vars;                                                      \
  if (full_grads) {                                                                            \
    /* case 2: full grad required, use pre-computed results */                                 \
    used_vars = opack->grad_used_vars;                                                         \
  } else {                                                                                     \
    /* case 3: partial grad required, have to collect vars */                                  \
    CollectVars(body, &used_vars);                                                             \
  }                                                                                            \
  const auto *schema = _schema.as<obj>();                                                      \
  Map<Var, Value> env;

#define MNM_SET_ENV(var, value)                                                        \
  {                                                                                    \
    const auto &_v = (var);                                                            \
    if (std::binary_search(used_vars.begin(), used_vars.end(), _v.operator->())) {     \
        env.Set(_v, value);                                                            \
    }                                                                                  \
  }

#define MNM_RET()                                                                      \
  DeStruct(std::move(value),                                                           \
           ClosureValue::make(/*env=*/std::move(env),                                  \
                              /*func=*/FunctionNode::make({vpack->dy}, body, {}, {})), \
           {prev_tapes.begin(), prev_tapes.begin() + n_tapes});

MNM_REGISTER_GLOBAL("mnm.op.imp.abs")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(abs, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.add")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(add, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.avg_pool2d")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(avg_pool2d, 7, ffi2schema::Pool, schema::PoolArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->kernel));
  MNM_SET_ENV(vpack->x[2], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[5], schema2value::Bool(schema->ceil_mode));
  MNM_SET_ENV(vpack->x[6], schema2value::Bool(schema->include_pad));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.avg_pool2d_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(avg_pool2d_dx, 9, ffi2schema::PoolDx, schema::PoolDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->kernel));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[5], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[6], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[7], schema2value::Bool(schema->ceil_mode));
  MNM_SET_ENV(vpack->x[8], schema2value::Bool(schema->include_pad));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.batch_flatten")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(batch_flatten, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.batch_matmul")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(batch_matmul, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.batch_norm_infer")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(batch_norm_infer, 7, ffi2schema::BatchNorm, schema::BatchNormArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->running_mean));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->running_var));
  MNM_SET_ENV(vpack->x[3], schema2value::Tensor(schema->w));
  MNM_SET_ENV(vpack->x[4], schema2value::Tensor(schema->b));
  MNM_SET_ENV(vpack->x[5], schema2value::Double(schema->momentum));
  MNM_SET_ENV(vpack->x[6], schema2value::Double(schema->eps));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.batch_norm_train")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(batch_norm_train, 7, ffi2schema::BatchNorm, schema::BatchNormArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->running_mean));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->running_var));
  MNM_SET_ENV(vpack->x[3], schema2value::Tensor(schema->w));
  MNM_SET_ENV(vpack->x[4], schema2value::Tensor(schema->b));
  MNM_SET_ENV(vpack->x[5], schema2value::Double(schema->momentum));
  MNM_SET_ENV(vpack->x[6], schema2value::Double(schema->eps));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.batch_norm_train_dxwb")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(batch_norm_train_dxwb, 5, ffi2schema::BatchNormTrainDxwb, schema::BatchNormTrainDxwbArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->w));
  MNM_SET_ENV(vpack->x[3], schema2value::Tensor(schema->b));
  MNM_SET_ENV(vpack->x[4], schema2value::Double(schema->eps));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.broadcast_to")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(broadcast_to, 2, ffi2schema::BroadcastTo, schema::BroadcastToArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->shape));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.ceil")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(ceil, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.collapse_sum_like")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(collapse_sum_like, 2, ffi2schema::CollapseLike, schema::CollapseLikeArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->shape));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.conv2d")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(conv2d, 6, ffi2schema::Conv, schema::ConvArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->w));
  MNM_SET_ENV(vpack->x[2], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[5], schema2value::Int(schema->groups));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.conv2d_dw")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(conv2d_dw, 8, ffi2schema::ConvDxw, schema::ConvDxwArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x_or_w));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->shape));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[5], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[6], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[7], schema2value::Int(schema->groups));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.conv2d_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(conv2d_dx, 8, ffi2schema::ConvDxw, schema::ConvDxwArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x_or_w));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->shape));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[5], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[6], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[7], schema2value::Int(schema->groups));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.copy")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(copy, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.cos")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(cos, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.divide")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(divide, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.equal")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(equal, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.erf")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(erf, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.erf_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(erf_dx, 3, ffi2schema::UnaryDx, schema::UnaryDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.expand_dims")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(expand_dims, 3, ffi2schema::ExpandDims, schema::ExpandDimsArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->x[2], schema2value::Int(schema->num_newaxis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.floor")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(floor, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.get_kept_dims")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(get_kept_dims, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.get_reduce_axis")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(get_reduce_axis, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.greater")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(greater, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.greater_equal")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(greater_equal, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.less")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(less, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.less_equal")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(less_equal, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.log")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(log, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.log_softmax")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(log_softmax, 2, ffi2schema::Softmax, schema::SoftmaxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.log_softmax_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(log_softmax_dx, 4, ffi2schema::SoftmaxDx, schema::SoftmaxDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.logical_not")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(logical_not, 3, ffi2schema::UnaryUfunc, schema::UnaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.matmul")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(matmul, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.matmul_nt")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(matmul_nt, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.matmul_tn")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(matmul_tn, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.matmul_tt")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(matmul_tt, 2, ffi2schema::Binary, schema::BinaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.max_pool2d")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(max_pool2d, 7, ffi2schema::Pool, schema::PoolArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->kernel));
  MNM_SET_ENV(vpack->x[2], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[5], schema2value::Bool(schema->ceil_mode));
  MNM_SET_ENV(vpack->x[6], schema2value::Bool(schema->include_pad));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.max_pool2d_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(max_pool2d_dx, 9, ffi2schema::PoolDx, schema::PoolDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->kernel));
  MNM_SET_ENV(vpack->x[4], schema2value::IntOrTupleInt(schema->stride));
  MNM_SET_ENV(vpack->x[5], schema2value::IntOrTupleInt(schema->padding));
  MNM_SET_ENV(vpack->x[6], schema2value::IntOrTupleInt(schema->dilation));
  MNM_SET_ENV(vpack->x[7], schema2value::Bool(schema->ceil_mode));
  MNM_SET_ENV(vpack->x[8], schema2value::Bool(schema->include_pad));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.maximum")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(maximum, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.minimum")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(minimum, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.mod")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(mod, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.multiply")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(multiply, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.negative")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(negative, 3, ffi2schema::UnaryUfunc, schema::UnaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.nll_loss")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(nll_loss, 2, ffi2schema::Loss, schema::LossArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->y_true));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y_pred));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.nll_loss_dpred")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(nll_loss_dpred, 2, ffi2schema::Loss, schema::LossArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->y_true));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y_pred));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.nll_loss_dtrue")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(nll_loss_dtrue, 2, ffi2schema::Loss, schema::LossArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->y_true));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y_pred));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.not_equal")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(not_equal, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.relu")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(relu, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.relu_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(relu_dx, 3, ffi2schema::UnaryDx, schema::UnaryDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.reshape")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(reshape, 2, ffi2schema::Reshape, schema::ReshapeArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->shape));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sequence_mask")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sequence_mask, 4, ffi2schema::SequenceMask, schema::SequenceMaskArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->sequence_length));
  MNM_SET_ENV(vpack->x[2], schema2value::Double(schema->mask_value));
  MNM_SET_ENV(vpack->x[3], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sgd")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sgd, 5, ffi2schema::Sgd, schema::SgdArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->dx));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->v));
  MNM_SET_ENV(vpack->x[3], schema2value::Double(schema->learning_rate));
  MNM_SET_ENV(vpack->x[4], schema2value::Double(schema->mu));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.shape")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(shape, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sigmoid")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sigmoid, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sigmoid_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sigmoid_dx, 3, ffi2schema::UnaryDx, schema::UnaryDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.softmax")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(softmax, 2, ffi2schema::Softmax, schema::SoftmaxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.softmax_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(softmax_dx, 4, ffi2schema::SoftmaxDx, schema::SoftmaxDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::Int(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sqrt")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sqrt, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sqrt_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sqrt_dx, 3, ffi2schema::UnaryDx, schema::UnaryDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.subtract")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(subtract, 4, ffi2schema::BinaryUfunc, schema::BinaryUfuncArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x1));
  MNM_SET_ENV(vpack->x[1], schema2value::ArrayLike(schema->x2));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->out));
  MNM_SET_ENV(vpack->x[3], schema2value::ArrayLike(schema->where));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.sum")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(sum, 3, ffi2schema::Sum, schema::SumArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->axis));
  MNM_SET_ENV(vpack->x[2], schema2value::IntOrTupleInt(schema->keep));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.take")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(take, 3, ffi2schema::Take, schema::TakeArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->indices));
  MNM_SET_ENV(vpack->x[2], schema2value::ArrayLike(schema->axis));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.tanh")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(tanh, 1, ffi2schema::Unary, schema::UnaryArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.tanh_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(tanh_dx, 3, ffi2schema::UnaryDx, schema::UnaryDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::ArrayLike(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.transpose")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(transpose, 2, ffi2schema::Transpose, schema::TransposeArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::IntOrTupleInt(schema->axes));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

MNM_REGISTER_GLOBAL("mnm.op.imp.transpose_dx")
.set_body([](TVMArgs args, TVMRetValue* ret) {
  MNM_PRELUDE(transpose_dx, 4, ffi2schema::TransposeDx, schema::TransposeDxArgs);  // NOLINT(whitespace/line_length)
  MNM_SET_ENV(vpack->x[0], schema2value::Tensor(schema->x));
  MNM_SET_ENV(vpack->x[1], schema2value::Tensor(schema->y));
  MNM_SET_ENV(vpack->x[2], schema2value::Tensor(schema->dy));
  MNM_SET_ENV(vpack->x[3], schema2value::IntOrTupleInt(schema->axes));
  MNM_SET_ENV(vpack->y, value);
  *ret = MNM_RET();
});

#undef MNM_RET
#undef MNM_SET_ENV
#undef MNM_PRELUDE

}  // namespace imperative
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 2.1. FFI to Array<Expr> (for each schema)
namespace mnm {
namespace op {
namespace regs {
namespace ffi2expr {

#define MNM_PRELUDE(n)                                                                     \
  const int size = values.size();                                                          \
  CHECK_EQ(size, n) << "TypeError: Mismatched number of arguments for operator \"{op}\": " \
                    << "Expected " << n << ", but get " << size;                           \
  std::vector<Expr> result;

#define MNM_ARG(i, norm, name)                \
  try {                                       \
    result.push_back(norm(values[i]));        \
  } catch (const dmlc::Error& e) {            \
    FillError(e, "{arg}", #name);             \
  }

#define MNM_RET() return Array<Expr>(result);

Array<Expr> BatchNorm(const TVMArgs& values) {
  MNM_PRELUDE(7);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, running_mean);
  MNM_ARG(2, ffi2expr::Tensor, running_var);
  MNM_ARG(3, ffi2expr::Tensor, w);
  MNM_ARG(4, ffi2expr::Tensor, b);
  MNM_ARG(5, ffi2expr::Double, momentum);
  MNM_ARG(6, ffi2expr::Double, eps);
  MNM_RET();
}

Array<Expr> BatchNormTrainDxwb(const TVMArgs& values) {
  MNM_PRELUDE(5);
  MNM_ARG(0, ffi2expr::Tensor, dy);
  MNM_ARG(1, ffi2expr::Tensor, x);
  MNM_ARG(2, ffi2expr::Tensor, w);
  MNM_ARG(3, ffi2expr::Tensor, b);
  MNM_ARG(4, ffi2expr::Double, eps);
  MNM_RET();
}

Array<Expr> Binary(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_RET();
}

Array<Expr> BinaryDx(const TVMArgs& values) {
  MNM_PRELUDE(4);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_ARG(2, ffi2expr::Tensor, y);
  MNM_ARG(3, ffi2expr::Tensor, dy);
  MNM_RET();
}

Array<Expr> BinaryUfunc(const TVMArgs& values) {
  MNM_PRELUDE(4);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_ARG(2, ffi2expr::ArrayLike, out);
  MNM_ARG(3, ffi2expr::ArrayLike, where);
  MNM_RET();
}

Array<Expr> BroadcastTo(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, shape);
  MNM_RET();
}

Array<Expr> CollapseLike(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, shape);
  MNM_RET();
}

Array<Expr> Conv(const TVMArgs& values) {
  MNM_PRELUDE(6);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, w);
  MNM_ARG(2, ffi2expr::IntOrTupleInt, stride);
  MNM_ARG(3, ffi2expr::IntOrTupleInt, padding);
  MNM_ARG(4, ffi2expr::IntOrTupleInt, dilation);
  MNM_ARG(5, ffi2expr::Int, groups);
  MNM_RET();
}

Array<Expr> ConvDxw(const TVMArgs& values) {
  MNM_PRELUDE(8);
  MNM_ARG(0, ffi2expr::Tensor, x_or_w);
  MNM_ARG(1, ffi2expr::Tensor, y);
  MNM_ARG(2, ffi2expr::Tensor, dy);
  MNM_ARG(3, ffi2expr::IntOrTupleInt, shape);
  MNM_ARG(4, ffi2expr::IntOrTupleInt, stride);
  MNM_ARG(5, ffi2expr::IntOrTupleInt, padding);
  MNM_ARG(6, ffi2expr::IntOrTupleInt, dilation);
  MNM_ARG(7, ffi2expr::Int, groups);
  MNM_RET();
}

Array<Expr> ExpandDims(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Int, axis);
  MNM_ARG(2, ffi2expr::Int, num_newaxis);
  MNM_RET();
}

Array<Expr> LocalResponseNorm(const TVMArgs& values) {
  MNM_PRELUDE(5);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Int, size);
  MNM_ARG(2, ffi2expr::Double, alpha);
  MNM_ARG(3, ffi2expr::Double, beta);
  MNM_ARG(4, ffi2expr::Double, k);
  MNM_RET();
}

Array<Expr> Loss(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, y_true);
  MNM_ARG(1, ffi2expr::Tensor, y_pred);
  MNM_RET();
}

Array<Expr> Pool(const TVMArgs& values) {
  MNM_PRELUDE(7);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, kernel);
  MNM_ARG(2, ffi2expr::IntOrTupleInt, stride);
  MNM_ARG(3, ffi2expr::IntOrTupleInt, padding);
  MNM_ARG(4, ffi2expr::IntOrTupleInt, dilation);
  MNM_ARG(5, ffi2expr::Bool, ceil_mode);
  MNM_ARG(6, ffi2expr::Bool, include_pad);
  MNM_RET();
}

Array<Expr> PoolDx(const TVMArgs& values) {
  MNM_PRELUDE(9);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, y);
  MNM_ARG(2, ffi2expr::Tensor, dy);
  MNM_ARG(3, ffi2expr::IntOrTupleInt, kernel);
  MNM_ARG(4, ffi2expr::IntOrTupleInt, stride);
  MNM_ARG(5, ffi2expr::IntOrTupleInt, padding);
  MNM_ARG(6, ffi2expr::IntOrTupleInt, dilation);
  MNM_ARG(7, ffi2expr::Bool, ceil_mode);
  MNM_ARG(8, ffi2expr::Bool, include_pad);
  MNM_RET();
}

Array<Expr> Reshape(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, shape);
  MNM_RET();
}

Array<Expr> SequenceMask(const TVMArgs& values) {
  MNM_PRELUDE(4);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, sequence_length);
  MNM_ARG(2, ffi2expr::Double, mask_value);
  MNM_ARG(3, ffi2expr::Int, axis);
  MNM_RET();
}

Array<Expr> Sgd(const TVMArgs& values) {
  MNM_PRELUDE(5);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, dx);
  MNM_ARG(2, ffi2expr::Tensor, v);
  MNM_ARG(3, ffi2expr::Double, learning_rate);
  MNM_ARG(4, ffi2expr::Double, mu);
  MNM_RET();
}

Array<Expr> Softmax(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Int, axis);
  MNM_RET();
}

Array<Expr> SoftmaxDx(const TVMArgs& values) {
  MNM_PRELUDE(4);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, y);
  MNM_ARG(2, ffi2expr::Tensor, dy);
  MNM_ARG(3, ffi2expr::Int, axis);
  MNM_RET();
}

Array<Expr> Sum(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, axis);
  MNM_ARG(2, ffi2expr::IntOrTupleInt, keep);
  MNM_RET();
}

Array<Expr> Take(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, indices);
  MNM_ARG(2, ffi2expr::ArrayLike, axis);
  MNM_RET();
}

Array<Expr> Ternary(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_ARG(2, ffi2expr::ArrayLike, x3);
  MNM_RET();
}

Array<Expr> TernaryDx(const TVMArgs& values) {
  MNM_PRELUDE(5);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_ARG(2, ffi2expr::ArrayLike, x3);
  MNM_ARG(3, ffi2expr::Tensor, y);
  MNM_ARG(4, ffi2expr::Tensor, dy);
  MNM_RET();
}

Array<Expr> TernaryUfunc(const TVMArgs& values) {
  MNM_PRELUDE(5);
  MNM_ARG(0, ffi2expr::ArrayLike, x1);
  MNM_ARG(1, ffi2expr::ArrayLike, x2);
  MNM_ARG(2, ffi2expr::ArrayLike, x3);
  MNM_ARG(3, ffi2expr::ArrayLike, out);
  MNM_ARG(4, ffi2expr::ArrayLike, where);
  MNM_RET();
}

Array<Expr> Transpose(const TVMArgs& values) {
  MNM_PRELUDE(2);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::IntOrTupleInt, axes);
  MNM_RET();
}

Array<Expr> TransposeDx(const TVMArgs& values) {
  MNM_PRELUDE(4);
  MNM_ARG(0, ffi2expr::Tensor, x);
  MNM_ARG(1, ffi2expr::Tensor, y);
  MNM_ARG(2, ffi2expr::Tensor, dy);
  MNM_ARG(3, ffi2expr::IntOrTupleInt, axes);
  MNM_RET();
}

Array<Expr> Unary(const TVMArgs& values) {
  MNM_PRELUDE(1);
  MNM_ARG(0, ffi2expr::ArrayLike, x);
  MNM_RET();
}

Array<Expr> UnaryDx(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::ArrayLike, x);
  MNM_ARG(1, ffi2expr::Tensor, y);
  MNM_ARG(2, ffi2expr::Tensor, dy);
  MNM_RET();
}

Array<Expr> UnaryUfunc(const TVMArgs& values) {
  MNM_PRELUDE(3);
  MNM_ARG(0, ffi2expr::ArrayLike, x);
  MNM_ARG(1, ffi2expr::ArrayLike, out);
  MNM_ARG(2, ffi2expr::ArrayLike, where);
  MNM_RET();
}

#undef MNM_RET
#undef MNM_ARG
#undef MNM_PRELUDE

}  // namespace ffi2expr
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 2.2. Symbolic API, uses "Part 2.1. FFI to Array<Expr>"
namespace mnm {
namespace op {
namespace regs {
namespace symbolic {

#define MNM_SYMBOLIC_API(op_name, n_args, schema)                               \
  [](TVMArgs args, TVMRetValue* ret) {                                          \
    auto *pack = regs::OpPack<names::op_name, n_args>::Get();                   \
    try {                                                                       \
        *ret = BindSymbol(CallNode::make(pack->op, ffi2expr::schema(args)));    \
    } catch (const dmlc::Error &e) {                                            \
        FillError(e, "{op}", names::op_name);                                   \
    }                                                                           \
  }

MNM_REGISTER_GLOBAL("mnm.op.sym.abs")
.set_body(MNM_SYMBOLIC_API(abs, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.add")
.set_body(MNM_SYMBOLIC_API(add, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.avg_pool2d")
.set_body(MNM_SYMBOLIC_API(avg_pool2d, 7, Pool));
MNM_REGISTER_GLOBAL("mnm.op.sym.avg_pool2d_dx")
.set_body(MNM_SYMBOLIC_API(avg_pool2d_dx, 9, PoolDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.batch_flatten")
.set_body(MNM_SYMBOLIC_API(batch_flatten, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.batch_matmul")
.set_body(MNM_SYMBOLIC_API(batch_matmul, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.batch_norm_infer")
.set_body(MNM_SYMBOLIC_API(batch_norm_infer, 7, BatchNorm));
MNM_REGISTER_GLOBAL("mnm.op.sym.batch_norm_train")
.set_body(MNM_SYMBOLIC_API(batch_norm_train, 7, BatchNorm));
MNM_REGISTER_GLOBAL("mnm.op.sym.batch_norm_train_dxwb")
.set_body(MNM_SYMBOLIC_API(batch_norm_train_dxwb, 5, BatchNormTrainDxwb));
MNM_REGISTER_GLOBAL("mnm.op.sym.broadcast_to")
.set_body(MNM_SYMBOLIC_API(broadcast_to, 2, BroadcastTo));
MNM_REGISTER_GLOBAL("mnm.op.sym.ceil")
.set_body(MNM_SYMBOLIC_API(ceil, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.collapse_sum_like")
.set_body(MNM_SYMBOLIC_API(collapse_sum_like, 2, CollapseLike));
MNM_REGISTER_GLOBAL("mnm.op.sym.conv2d")
.set_body(MNM_SYMBOLIC_API(conv2d, 6, Conv));
MNM_REGISTER_GLOBAL("mnm.op.sym.conv2d_dw")
.set_body(MNM_SYMBOLIC_API(conv2d_dw, 8, ConvDxw));
MNM_REGISTER_GLOBAL("mnm.op.sym.conv2d_dx")
.set_body(MNM_SYMBOLIC_API(conv2d_dx, 8, ConvDxw));
MNM_REGISTER_GLOBAL("mnm.op.sym.copy")
.set_body(MNM_SYMBOLIC_API(copy, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.cos")
.set_body(MNM_SYMBOLIC_API(cos, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.divide")
.set_body(MNM_SYMBOLIC_API(divide, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.equal")
.set_body(MNM_SYMBOLIC_API(equal, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.erf")
.set_body(MNM_SYMBOLIC_API(erf, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.erf_dx")
.set_body(MNM_SYMBOLIC_API(erf_dx, 3, UnaryDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.expand_dims")
.set_body(MNM_SYMBOLIC_API(expand_dims, 3, ExpandDims));
MNM_REGISTER_GLOBAL("mnm.op.sym.floor")
.set_body(MNM_SYMBOLIC_API(floor, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.get_kept_dims")
.set_body(MNM_SYMBOLIC_API(get_kept_dims, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.get_reduce_axis")
.set_body(MNM_SYMBOLIC_API(get_reduce_axis, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.greater")
.set_body(MNM_SYMBOLIC_API(greater, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.greater_equal")
.set_body(MNM_SYMBOLIC_API(greater_equal, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.less")
.set_body(MNM_SYMBOLIC_API(less, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.less_equal")
.set_body(MNM_SYMBOLIC_API(less_equal, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.log")
.set_body(MNM_SYMBOLIC_API(log, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.log_softmax")
.set_body(MNM_SYMBOLIC_API(log_softmax, 2, Softmax));
MNM_REGISTER_GLOBAL("mnm.op.sym.log_softmax_dx")
.set_body(MNM_SYMBOLIC_API(log_softmax_dx, 4, SoftmaxDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.logical_not")
.set_body(MNM_SYMBOLIC_API(logical_not, 3, UnaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.matmul")
.set_body(MNM_SYMBOLIC_API(matmul, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.matmul_nt")
.set_body(MNM_SYMBOLIC_API(matmul_nt, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.matmul_tn")
.set_body(MNM_SYMBOLIC_API(matmul_tn, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.matmul_tt")
.set_body(MNM_SYMBOLIC_API(matmul_tt, 2, Binary));
MNM_REGISTER_GLOBAL("mnm.op.sym.max_pool2d")
.set_body(MNM_SYMBOLIC_API(max_pool2d, 7, Pool));
MNM_REGISTER_GLOBAL("mnm.op.sym.max_pool2d_dx")
.set_body(MNM_SYMBOLIC_API(max_pool2d_dx, 9, PoolDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.maximum")
.set_body(MNM_SYMBOLIC_API(maximum, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.minimum")
.set_body(MNM_SYMBOLIC_API(minimum, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.mod")
.set_body(MNM_SYMBOLIC_API(mod, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.multiply")
.set_body(MNM_SYMBOLIC_API(multiply, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.negative")
.set_body(MNM_SYMBOLIC_API(negative, 3, UnaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.nll_loss")
.set_body(MNM_SYMBOLIC_API(nll_loss, 2, Loss));
MNM_REGISTER_GLOBAL("mnm.op.sym.nll_loss_dpred")
.set_body(MNM_SYMBOLIC_API(nll_loss_dpred, 2, Loss));
MNM_REGISTER_GLOBAL("mnm.op.sym.nll_loss_dtrue")
.set_body(MNM_SYMBOLIC_API(nll_loss_dtrue, 2, Loss));
MNM_REGISTER_GLOBAL("mnm.op.sym.not_equal")
.set_body(MNM_SYMBOLIC_API(not_equal, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.relu")
.set_body(MNM_SYMBOLIC_API(relu, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.relu_dx")
.set_body(MNM_SYMBOLIC_API(relu_dx, 3, UnaryDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.reshape")
.set_body(MNM_SYMBOLIC_API(reshape, 2, Reshape));
MNM_REGISTER_GLOBAL("mnm.op.sym.sequence_mask")
.set_body(MNM_SYMBOLIC_API(sequence_mask, 4, SequenceMask));
MNM_REGISTER_GLOBAL("mnm.op.sym.sgd")
.set_body(MNM_SYMBOLIC_API(sgd, 5, Sgd));
MNM_REGISTER_GLOBAL("mnm.op.sym.shape")
.set_body(MNM_SYMBOLIC_API(shape, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.sigmoid")
.set_body(MNM_SYMBOLIC_API(sigmoid, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.sigmoid_dx")
.set_body(MNM_SYMBOLIC_API(sigmoid_dx, 3, UnaryDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.softmax")
.set_body(MNM_SYMBOLIC_API(softmax, 2, Softmax));
MNM_REGISTER_GLOBAL("mnm.op.sym.softmax_dx")
.set_body(MNM_SYMBOLIC_API(softmax_dx, 4, SoftmaxDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.sqrt")
.set_body(MNM_SYMBOLIC_API(sqrt, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.sqrt_dx")
.set_body(MNM_SYMBOLIC_API(sqrt_dx, 3, UnaryDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.subtract")
.set_body(MNM_SYMBOLIC_API(subtract, 4, BinaryUfunc));
MNM_REGISTER_GLOBAL("mnm.op.sym.sum")
.set_body(MNM_SYMBOLIC_API(sum, 3, Sum));
MNM_REGISTER_GLOBAL("mnm.op.sym.take")
.set_body(MNM_SYMBOLIC_API(take, 3, Take));
MNM_REGISTER_GLOBAL("mnm.op.sym.tanh")
.set_body(MNM_SYMBOLIC_API(tanh, 1, Unary));
MNM_REGISTER_GLOBAL("mnm.op.sym.tanh_dx")
.set_body(MNM_SYMBOLIC_API(tanh_dx, 3, UnaryDx));
MNM_REGISTER_GLOBAL("mnm.op.sym.transpose")
.set_body(MNM_SYMBOLIC_API(transpose, 2, Transpose));
MNM_REGISTER_GLOBAL("mnm.op.sym.transpose_dx")
.set_body(MNM_SYMBOLIC_API(transpose_dx, 4, TransposeDx));

#undef MNM_SYMBOLIC_API

}  // namespace symbolic
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 3.1. Array<Value> to schema (for each schema)
namespace mnm {
namespace op {
namespace regs {
namespace value2schema {

#define MNM_PRELUDE(lb, ub, schema)                                             \
  const int size = values.size();                                               \
  CHECK(size >= lb) << "TypeError: Too few arguments for operator \"{op}\". "   \
                    << "Expected at least " << lb << ", but get " << size;      \
  CHECK(size <= ub) << "TypeError: Too many arguments for operator \"{op}\". "  \
                    << "Expected at most " << ub << ", but get " << size;       \
  auto attrs = make_object<schema>();

#define MNM_REQUIRED(i, norm, name)       \
  try {                                   \
    attrs->name = norm(values[i]);        \
  } catch (const dmlc::Error& e) {        \
    try {                                 \
      FillError(e, "{arg}", #name);       \
    } catch (const dmlc::Error &ee) {     \
      FillError(ee, "{op}", op_name);     \
    }                                     \
  }

#define MNM_OPTIONAL(i, norm, name)       \
  if (size > i) {                         \
    try {                                 \
      attrs->name = norm(values[i]);      \
    } catch (const dmlc::Error& e) {      \
      try {                               \
        FillError(e, "{arg}", #name);     \
      } catch (const dmlc::Error &ee) {   \
        FillError(ee, "{op}", op_name);   \
      }                                   \
    }                                     \
  }

template <const char* op_name>
Attrs BatchNorm(const Array<Value>& values) {
  MNM_PRELUDE(3, 7, schema::BatchNormArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, running_mean);
  MNM_REQUIRED(2, value2schema::Tensor, running_var);
  MNM_OPTIONAL(3, value2schema::Tensor, w);
  MNM_OPTIONAL(4, value2schema::Tensor, b);
  MNM_OPTIONAL(5, value2schema::Double, momentum);
  MNM_OPTIONAL(6, value2schema::Double, eps);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs BatchNormTrainDxwb(const Array<Value>& values) {
  MNM_PRELUDE(5, 5, schema::BatchNormTrainDxwbArgs);
  MNM_REQUIRED(0, value2schema::Tensor, dy);
  MNM_REQUIRED(1, value2schema::Tensor, x);
  MNM_REQUIRED(2, value2schema::Tensor, w);
  MNM_REQUIRED(3, value2schema::Tensor, b);
  MNM_REQUIRED(4, value2schema::Double, eps);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Binary(const Array<Value>& values) {
  MNM_PRELUDE(2, 2, schema::BinaryArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs BinaryDx(const Array<Value>& values) {
  MNM_PRELUDE(4, 4, schema::BinaryDxArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  MNM_REQUIRED(2, value2schema::Tensor, y);
  MNM_REQUIRED(3, value2schema::Tensor, dy);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs BinaryUfunc(const Array<Value>& values) {
  MNM_PRELUDE(2, 4, schema::BinaryUfuncArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  MNM_OPTIONAL(2, value2schema::ArrayLike, out);
  MNM_OPTIONAL(3, value2schema::ArrayLike, where);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs BroadcastTo(const Array<Value>& values) {
  MNM_PRELUDE(2, 2, schema::BroadcastToArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs CollapseLike(const Array<Value>& values) {
  MNM_PRELUDE(2, 2, schema::CollapseLikeArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Conv(const Array<Value>& values) {
  MNM_PRELUDE(2, 6, schema::ConvArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, w);
  MNM_OPTIONAL(2, value2schema::IntOrTupleInt, stride);
  MNM_OPTIONAL(3, value2schema::IntOrTupleInt, padding);
  MNM_OPTIONAL(4, value2schema::IntOrTupleInt, dilation);
  MNM_OPTIONAL(5, value2schema::Int, groups);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs ConvDxw(const Array<Value>& values) {
  MNM_PRELUDE(8, 8, schema::ConvDxwArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x_or_w);
  MNM_REQUIRED(1, value2schema::Tensor, y);
  MNM_REQUIRED(2, value2schema::Tensor, dy);
  MNM_REQUIRED(3, value2schema::IntOrTupleInt, shape);
  MNM_REQUIRED(4, value2schema::IntOrTupleInt, stride);
  MNM_REQUIRED(5, value2schema::IntOrTupleInt, padding);
  MNM_REQUIRED(6, value2schema::IntOrTupleInt, dilation);
  MNM_REQUIRED(7, value2schema::Int, groups);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs ExpandDims(const Array<Value>& values) {
  MNM_PRELUDE(2, 3, schema::ExpandDimsArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Int, axis);
  MNM_OPTIONAL(2, value2schema::Int, num_newaxis);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs LocalResponseNorm(const Array<Value>& values) {
  MNM_PRELUDE(2, 5, schema::LocalResponseNormArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Int, size);
  MNM_OPTIONAL(2, value2schema::Double, alpha);
  MNM_OPTIONAL(3, value2schema::Double, beta);
  MNM_OPTIONAL(4, value2schema::Double, k);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Loss(const Array<Value>& values) {
  MNM_PRELUDE(2, 2, schema::LossArgs);
  MNM_REQUIRED(0, value2schema::Tensor, y_true);
  MNM_REQUIRED(1, value2schema::Tensor, y_pred);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Pool(const Array<Value>& values) {
  MNM_PRELUDE(3, 7, schema::PoolArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::IntOrTupleInt, kernel);
  MNM_REQUIRED(2, value2schema::IntOrTupleInt, stride);
  MNM_OPTIONAL(3, value2schema::IntOrTupleInt, padding);
  MNM_OPTIONAL(4, value2schema::IntOrTupleInt, dilation);
  MNM_OPTIONAL(5, value2schema::Bool, ceil_mode);
  MNM_OPTIONAL(6, value2schema::Bool, include_pad);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs PoolDx(const Array<Value>& values) {
  MNM_PRELUDE(9, 9, schema::PoolDxArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, y);
  MNM_REQUIRED(2, value2schema::Tensor, dy);
  MNM_REQUIRED(3, value2schema::IntOrTupleInt, kernel);
  MNM_REQUIRED(4, value2schema::IntOrTupleInt, stride);
  MNM_REQUIRED(5, value2schema::IntOrTupleInt, padding);
  MNM_REQUIRED(6, value2schema::IntOrTupleInt, dilation);
  MNM_REQUIRED(7, value2schema::Bool, ceil_mode);
  MNM_REQUIRED(8, value2schema::Bool, include_pad);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Reshape(const Array<Value>& values) {
  MNM_PRELUDE(2, 2, schema::ReshapeArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::IntOrTupleInt, shape);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs SequenceMask(const Array<Value>& values) {
  MNM_PRELUDE(2, 4, schema::SequenceMaskArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, sequence_length);
  MNM_OPTIONAL(2, value2schema::Double, mask_value);
  MNM_OPTIONAL(3, value2schema::Int, axis);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Sgd(const Array<Value>& values) {
  MNM_PRELUDE(5, 5, schema::SgdArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, dx);
  MNM_REQUIRED(2, value2schema::Tensor, v);
  MNM_REQUIRED(3, value2schema::Double, learning_rate);
  MNM_REQUIRED(4, value2schema::Double, mu);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Softmax(const Array<Value>& values) {
  MNM_PRELUDE(1, 2, schema::SoftmaxArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_OPTIONAL(1, value2schema::Int, axis);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs SoftmaxDx(const Array<Value>& values) {
  MNM_PRELUDE(3, 4, schema::SoftmaxDxArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, y);
  MNM_REQUIRED(2, value2schema::Tensor, dy);
  MNM_OPTIONAL(3, value2schema::Int, axis);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Sum(const Array<Value>& values) {
  MNM_PRELUDE(3, 3, schema::SumArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::IntOrTupleInt, axis);
  MNM_REQUIRED(2, value2schema::IntOrTupleInt, keep);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Take(const Array<Value>& values) {
  MNM_PRELUDE(2, 3, schema::TakeArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, indices);
  MNM_OPTIONAL(2, value2schema::ArrayLike, axis);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Ternary(const Array<Value>& values) {
  MNM_PRELUDE(3, 3, schema::TernaryArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  MNM_REQUIRED(2, value2schema::ArrayLike, x3);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs TernaryDx(const Array<Value>& values) {
  MNM_PRELUDE(5, 5, schema::TernaryDxArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  MNM_REQUIRED(2, value2schema::ArrayLike, x3);
  MNM_REQUIRED(3, value2schema::Tensor, y);
  MNM_REQUIRED(4, value2schema::Tensor, dy);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs TernaryUfunc(const Array<Value>& values) {
  MNM_PRELUDE(3, 5, schema::TernaryUfuncArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x1);
  MNM_REQUIRED(1, value2schema::ArrayLike, x2);
  MNM_REQUIRED(2, value2schema::ArrayLike, x3);
  MNM_OPTIONAL(3, value2schema::ArrayLike, out);
  MNM_OPTIONAL(4, value2schema::ArrayLike, where);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Transpose(const Array<Value>& values) {
  MNM_PRELUDE(1, 2, schema::TransposeArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_OPTIONAL(1, value2schema::IntOrTupleInt, axes);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs TransposeDx(const Array<Value>& values) {
  MNM_PRELUDE(3, 4, schema::TransposeDxArgs);
  MNM_REQUIRED(0, value2schema::Tensor, x);
  MNM_REQUIRED(1, value2schema::Tensor, y);
  MNM_REQUIRED(2, value2schema::Tensor, dy);
  MNM_OPTIONAL(3, value2schema::IntOrTupleInt, axes);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs Unary(const Array<Value>& values) {
  MNM_PRELUDE(1, 1, schema::UnaryArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs UnaryDx(const Array<Value>& values) {
  MNM_PRELUDE(3, 3, schema::UnaryDxArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x);
  MNM_REQUIRED(1, value2schema::Tensor, y);
  MNM_REQUIRED(2, value2schema::Tensor, dy);
  return Attrs(attrs);
}

template <const char* op_name>
Attrs UnaryUfunc(const Array<Value>& values) {
  MNM_PRELUDE(1, 3, schema::UnaryUfuncArgs);
  MNM_REQUIRED(0, value2schema::ArrayLike, x);
  MNM_OPTIONAL(1, value2schema::ArrayLike, out);
  MNM_OPTIONAL(2, value2schema::ArrayLike, where);
  return Attrs(attrs);
}

#undef MNM_OPTIONAL
#undef MNM_REQUIRED
#undef MNM_PRELUDE

}  // namespace value2schema
}  // namespace regs
}  // namespace op
}  // namespace mnm

// Part 3.2. FMNMSchema API, uses "Part 3.1. Array<Value> to schema"
namespace mnm {
namespace op {
namespace regs {
namespace f_mnm_schema {

#define MNM_BIND_SCHEMA(op_str, op_name, schema) \
  MNM_OP_REGISTER(op_str).set_attr<FMNMSchema>("FMNMSchema", schema<op_name>);

MNM_BIND_SCHEMA("mnm.op.abs", names::abs, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.add", names::add, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.avg_pool2d", names::avg_pool2d, value2schema::Pool);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.avg_pool2d_dx", names::avg_pool2d_dx, value2schema::PoolDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.batch_flatten", names::batch_flatten, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.batch_matmul", names::batch_matmul, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.batch_norm_infer", names::batch_norm_infer, value2schema::BatchNorm);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.batch_norm_train", names::batch_norm_train, value2schema::BatchNorm);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.batch_norm_train_dxwb", names::batch_norm_train_dxwb, value2schema::BatchNormTrainDxwb);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.broadcast_to", names::broadcast_to, value2schema::BroadcastTo);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.ceil", names::ceil, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.collapse_sum_like", names::collapse_sum_like, value2schema::CollapseLike);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.conv2d", names::conv2d, value2schema::Conv);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.conv2d_dw", names::conv2d_dw, value2schema::ConvDxw);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.conv2d_dx", names::conv2d_dx, value2schema::ConvDxw);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.copy", names::copy, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.cos", names::cos, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.divide", names::divide, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.equal", names::equal, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.erf", names::erf, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.erf_dx", names::erf_dx, value2schema::UnaryDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.expand_dims", names::expand_dims, value2schema::ExpandDims);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.floor", names::floor, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.get_kept_dims", names::get_kept_dims, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.get_reduce_axis", names::get_reduce_axis, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.greater", names::greater, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.greater_equal", names::greater_equal, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.less", names::less, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.less_equal", names::less_equal, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.log", names::log, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.log_softmax", names::log_softmax, value2schema::Softmax);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.log_softmax_dx", names::log_softmax_dx, value2schema::SoftmaxDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.logical_not", names::logical_not, value2schema::UnaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.matmul", names::matmul, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.matmul_nt", names::matmul_nt, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.matmul_tn", names::matmul_tn, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.matmul_tt", names::matmul_tt, value2schema::Binary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.max_pool2d", names::max_pool2d, value2schema::Pool);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.max_pool2d_dx", names::max_pool2d_dx, value2schema::PoolDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.maximum", names::maximum, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.minimum", names::minimum, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.mod", names::mod, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.multiply", names::multiply, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.negative", names::negative, value2schema::UnaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.nll_loss", names::nll_loss, value2schema::Loss);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.nll_loss_dpred", names::nll_loss_dpred, value2schema::Loss);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.nll_loss_dtrue", names::nll_loss_dtrue, value2schema::Loss);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.not_equal", names::not_equal, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.relu", names::relu, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.relu_dx", names::relu_dx, value2schema::UnaryDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.reshape", names::reshape, value2schema::Reshape);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sequence_mask", names::sequence_mask, value2schema::SequenceMask);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sgd", names::sgd, value2schema::Sgd);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.shape", names::shape, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sigmoid", names::sigmoid, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sigmoid_dx", names::sigmoid_dx, value2schema::UnaryDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.softmax", names::softmax, value2schema::Softmax);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.softmax_dx", names::softmax_dx, value2schema::SoftmaxDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sqrt", names::sqrt, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sqrt_dx", names::sqrt_dx, value2schema::UnaryDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.subtract", names::subtract, value2schema::BinaryUfunc);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.sum", names::sum, value2schema::Sum);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.take", names::take, value2schema::Take);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.tanh", names::tanh, value2schema::Unary);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.tanh_dx", names::tanh_dx, value2schema::UnaryDx);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.transpose", names::transpose, value2schema::Transpose);  // NOLINT(whitespace/line_length)
MNM_BIND_SCHEMA("mnm.op.transpose_dx", names::transpose_dx, value2schema::TransposeDx);  // NOLINT(whitespace/line_length)

#undef MNM_BIND_SCHEMA

}  // namespace f_mnm_schema
}  // namespace regs
}  // namespace op
}  // namespace mnm

// The last part: registering schemas
namespace mnm {
namespace op {
namespace schema {
namespace {
MNM_REGISTER_OBJECT_REFLECT(ListArgs);
MNM_REGISTER_OBJECT_REFLECT(BatchNormArgs);
MNM_REGISTER_OBJECT_REFLECT(BatchNormTrainDxwbArgs);
MNM_REGISTER_OBJECT_REFLECT(BinaryArgs);
MNM_REGISTER_OBJECT_REFLECT(BinaryDxArgs);
MNM_REGISTER_OBJECT_REFLECT(BinaryUfuncArgs);
MNM_REGISTER_OBJECT_REFLECT(BroadcastToArgs);
MNM_REGISTER_OBJECT_REFLECT(CollapseLikeArgs);
MNM_REGISTER_OBJECT_REFLECT(ConvArgs);
MNM_REGISTER_OBJECT_REFLECT(ConvDxwArgs);
MNM_REGISTER_OBJECT_REFLECT(ExpandDimsArgs);
MNM_REGISTER_OBJECT_REFLECT(LocalResponseNormArgs);
MNM_REGISTER_OBJECT_REFLECT(LossArgs);
MNM_REGISTER_OBJECT_REFLECT(PoolArgs);
MNM_REGISTER_OBJECT_REFLECT(PoolDxArgs);
MNM_REGISTER_OBJECT_REFLECT(ReshapeArgs);
MNM_REGISTER_OBJECT_REFLECT(SequenceMaskArgs);
MNM_REGISTER_OBJECT_REFLECT(SgdArgs);
MNM_REGISTER_OBJECT_REFLECT(SoftmaxArgs);
MNM_REGISTER_OBJECT_REFLECT(SoftmaxDxArgs);
MNM_REGISTER_OBJECT_REFLECT(SumArgs);
MNM_REGISTER_OBJECT_REFLECT(TakeArgs);
MNM_REGISTER_OBJECT_REFLECT(TernaryArgs);
MNM_REGISTER_OBJECT_REFLECT(TernaryDxArgs);
MNM_REGISTER_OBJECT_REFLECT(TernaryUfuncArgs);
MNM_REGISTER_OBJECT_REFLECT(TransposeArgs);
MNM_REGISTER_OBJECT_REFLECT(TransposeDxArgs);
MNM_REGISTER_OBJECT_REFLECT(UnaryArgs);
MNM_REGISTER_OBJECT_REFLECT(UnaryDxArgs);
MNM_REGISTER_OBJECT_REFLECT(UnaryUfuncArgs);
}  // namespace
}  // namespace schema
}  // namespace op
}  // namespace mnm
