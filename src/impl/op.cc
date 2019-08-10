#include <dmlc/registry.h>

#include <mnm/ir.h>
#include <mnm/op.h>
#include <mnm/registry.h>
#include <mnm/value.h>

#include "../requests.h"

namespace dmlc {
DMLC_REGISTRY_ENABLE(::mnm::op::OpBackend);
DMLC_REGISTRY_ENABLE(::mnm::op::OpDispatch);
}  // namespace dmlc

namespace mnm {
namespace op {

using executor::Executor;
using requests::Requests;
using ir::Array;
using ir::Attrs;
using value::Value;

// Implementation: OpBackend

OpBackend& OpBackend::set_device(DevType device) {
  CHECK(this->device == DevType::kUnknown()) << "Cannot set backend's device twice";
  this->device = device;
  TDeviceRegistry::EntryPtr& ptr = DeviceRegistry()->Get(device);
  {
    std::unique_lock<std::mutex> lock = DeviceRegistry()->GrabLock();
    ptr->push_back(this);
  }
  return *this;
}

OpBackend::TDeviceRegistry* OpBackend::DeviceRegistry() {
  static OpBackend::TDeviceRegistry* registry = new OpBackend::TDeviceRegistry();
  return registry;
}

OpBackend* OpBackend::Get(const std::string& name) {
  return &Registry()->__REGISTER_OR_GET__(name);
}

OpBackend::TRegistry* OpBackend::Registry() {
  return TRegistry::Get();
}

// Implementation: OpDispatch

OpDispatch::TDispatchList* OpDispatch::Get(const std::string& op_name, DevType device_type) {
  OpDispatch& op_dispatch = Registry()->__REGISTER_OR_GET__(op_name);
  std::shared_ptr<TDispatchList>& list = op_dispatch.dispatch.Get(device_type);
  return list.get();
}

OpDispatch::TRegistry* OpDispatch::Registry() {
  return TRegistry::Get();
}

OpDispatch& OpDispatch::add_dispatch(DevType device_type,              //
                                     const std::string& backend_name,  //
                                     const FMakeOpEnv& op_env_maker) {
  OpBackend* backend = OpBackend::Get(backend_name);
  auto& list = dispatch.Get(device_type);
  {
    std::unique_lock<std::mutex> lock = dispatch.GrabLock();
    for (const auto& e : *list) {
      if (e.first == backend) {
        LOG(FATAL) << "InternalError: operator " << name
                   << " already has an implementation on backend " << backend_name;
      }
    }
    list->push_back(std::make_pair(backend, op_env_maker));
  }
  return *this;
}

// Implementation: OpEnv

class OpEnv::Impl {
 public:
  friend class OpEnv;

  Impl() : requests(new Requests()) {
  }

  ~Impl() = default;

  void RequestMemory(void** dest, Context ctx, int64_t nbytes) {
    if (executor == nullptr) {
      requests->memory.push_back({dest, ctx, nbytes});
    } else {
      // TODO(@junrushao1994): eagerly call from executor
    }
  }

  void RequestWorkspace(void** dest, Context ctx, int64_t nbytes) {
    if (executor == nullptr) {
      requests->workspace.push_back({dest, ctx, nbytes});
    } else {
      // TODO(@junrushao1994): eagerly call from executor
    }
  }

  void RequestStream(void** dest, Context ctx) {
    if (executor == nullptr) {
      requests->stream.push_back({dest, ctx});
    } else {
      // TODO(@junrushao1994): eagerly call from executor
    }
  }

  void RequestDistributed(void** dest) {
    if (executor == nullptr) {
      requests->dist.push_back({dest});
    } else {
      // TODO(@junrushao1994): eagerly call from executor
    }
  }

  Requests* SetExecutor(Executor* exec) {
    CHECK(this->executor == nullptr);
    this->executor = exec;
    return requests.release();
  }

 public:
  Executor* executor = nullptr;
  std::unique_ptr<Requests> requests;
};

OpEnv::OpEnv() : impl(new OpEnv::Impl()) {
}

OpEnv::~OpEnv() = default;

void OpEnv::RequestMemory(void** dest, Context ctx, int64_t nbytes) {
  impl->RequestMemory(dest, ctx, nbytes);
}

void OpEnv::RequestWorkspace(void** dest, Context ctx, int64_t nbytes) {
  impl->RequestWorkspace(dest, ctx, nbytes);
}

void OpEnv::RequestStream(void** dest, Context ctx) {
  impl->RequestStream(dest, ctx);
}

void OpEnv::RequestDistributed(void** dest) {
  impl->RequestDistributed(dest);
}

void* OpEnv::SetExecutor(Executor* executor) {
  return impl->SetExecutor(executor);
}

Value MakeOutput(std::string op_name, Array<Value> args, Attrs attrs) {
  static const auto f_op_make_output = Op::GetAttr<FOpMakeOutput>("FOpMakeOutput");
  const auto& f = f_op_make_output[Op::Get(op_name)];
  return f(args, attrs);
}

MNM_REGISTER_GLOBAL("mnm.op.MakeOutput").set_body_typed(MakeOutput);

}  // namespace op
}  // namespace mnm
