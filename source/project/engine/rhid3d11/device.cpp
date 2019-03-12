

#include "device.h"

namespace d3d11
{
	Device g_Device;

	Device * GetDevice()
	{
		return &g_Device;
	}
	bool Device::Init()
	{
		HRESULT hr = S_OK;
		UINT createDeviceFlags = 0;

#ifdef _DEBUG
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		D3D_FEATURE_LEVEL featureLevel;
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, m_pDevice.GetAddressOf(), &featureLevel, m_pImmediateContext.GetAddressOf());

		return hr == S_OK;
	}

	void Device::Destroy()
	{
	}



	ID3D11Device* GetD3dDevice()
	{
		return g_Device.GetDevice();
	}
	
	ID3D11DeviceContext* GetImmediateContext()
	{
		return g_Device.GetImmediateContext();
	}

}