#pragma once

#include <d3d11.h>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

namespace d3d11
{
	class Device
	{
	public:

		virtual bool Init();
		virtual void Destroy();


		ID3D11Device* GetDevice() { return m_pDevice.Get(); }
		ID3D11DeviceContext* GetImmediateContext() { return m_pImmediateContext.Get(); }

	private:
		ComPtr<ID3D11Device>			m_pDevice;
		ComPtr<ID3D11DeviceContext>		m_pImmediateContext;
	};

	Device* GetDevice();
	ID3D11Device* GetD3dDevice();
	ID3D11DeviceContext* GetImmediateContext();
}