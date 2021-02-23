import pytest
import torch

import mnm
from mnm.testing import check, randn_torch, run_vm_model, get_device_list, resnet
from mnm.testing.utils import ir_simplify, ir_fusion


@pytest.mark.skipif(not mnm.build.with_cuda(), reason="CUDA is not enabled")
def test_r50_v1_imagenet():
    device = "cuda"
    m_model, t_model = resnet.get_model([3, 4, 6, 3])
    m_model.to(device=device)
    t_model.to(device)
    m_in, t_in = resnet.get_input(batch_size=1, device=device)
    m_loss = m_model(*m_in)
    t_loss = t_model(*t_in)
    m_loss.backward()
    t_loss.backward()
    check(m_loss, t_loss)
    resnet.check_params(m_model, t_model)


@pytest.mark.parametrize("device", get_device_list())
@pytest.mark.parametrize("fuse", [False, True])
def test_vm_forward(device, fuse):
    layers = [3, 4, 6, 3]
    ir_optimizer = ir_fusion if fuse else ir_simplify
    m_model, t_model = resnet.get_model(layers)
    m_model.to(device=device)
    t_model.to(device)
    m_in, t_in = resnet.get_input(batch_size=1, device=device)
    m_loss = run_vm_model(m_model, device, [*m_in], ir_optimizer)[0]
    t_loss = t_model(*t_in)
    check(m_loss, t_loss, atol=1e-3, rtol=1e-3)
    resnet.check_params(m_model, t_model, atol=1e-3, rtol=1e-3)


@pytest.mark.parametrize("device", get_device_list())
@pytest.mark.parametrize("fuse", [False, True])
def test_vm_backward(device, fuse):
    layers = [1, 1, 1, 1]
    ir_optimizer = ir_fusion if fuse else ir_simplify
    m_model, t_model = resnet.get_model(layers)
    m_model.to(device=device)
    t_model.to(device=device)
    m_optimizer = mnm.optim.sgd.with_sgd(learning_rate=0.1, momentum=0.01)(m_model)
    t_optimizer = torch.optim.SGD(t_model.parameters(), lr=0.1, momentum=0.01)
    m_dy, t_dy = randn_torch((), device=device, requires_grad=False)
    m_in, t_in = resnet.get_input(batch_size=1, device=device)
    m_loss = run_vm_model(m_optimizer, device, [m_dy, *m_in], ir_optimizer)[0][0]
    t_optimizer.zero_grad()
    t_loss = t_model(*t_in)
    t_loss.backward(t_dy)
    t_optimizer.step()
    check(m_loss, t_loss, atol=1e-3, rtol=1e-3)
    resnet.check_params(m_model, t_model, atol=1e-2, rtol=1e-2)


if __name__ == "__main__":
    pytest.main([__file__])
