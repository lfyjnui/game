
#include "device.h"
#include "renderwnd.h"
#include <d3d11.h>
#include <windows.h>
#include <DirectXMath.h>

template<typename T>
void SafeRelease(T*& p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

namespace d3d11
{
	RenderWindow g_RenderWindow;
	RenderWindow * GetRenderWnd()
	{
		return &g_RenderWindow;
	}
	bool RenderWindow::Create(void * hWnd)
	{
		m_hWnd = hWnd;
		HRESULT hr = S_OK;
		RECT rc;
		GetClientRect((HWND)m_hWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;


		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 2;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = (HWND)hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		ID3D11Device* pD3dDevice = GetD3dDevice();

		IDXGIFactory1* dxgiFactory = nullptr;
		{
			IDXGIDevice* dxgiDevice = nullptr;
			hr = pD3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
			if (SUCCEEDED(hr))
			{
				IDXGIAdapter* adapter = nullptr;
				hr = dxgiDevice->GetAdapter(&adapter);
				if (SUCCEEDED(hr))
				{
					hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
					adapter->Release();
				}
				dxgiDevice->Release();
			}
		}
		if (FAILED(hr))
			return false;

		hr = dxgiFactory->CreateSwapChain(GetD3dDevice(), &sd, m_pSwapChain.GetAddressOf());

		dxgiFactory->MakeWindowAssociation((HWND)m_hWnd, DXGI_MWA_NO_ALT_ENTER);

		SafeRelease(dxgiFactory);

		m_vp.Width = (FLOAT)width;
		m_vp.Height = (FLOAT)height;
		m_vp.MinDepth = 0.0f;
		m_vp.MaxDepth = 1.0f;
		m_vp.TopLeftX = 0;
		m_vp.TopLeftY = 0;

		Build();
		return true;
	}

	void RenderWindow::Build()
	{
		HRESULT hr = S_OK;

		ID3D11Device* pD3dDevice = GetD3dDevice();
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		if (FAILED(hr))
			return;

		hr = pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_pRenderTargetView.GetAddressOf());
		if (FAILED(hr))
			return;

		D3D11_TEXTURE2D_DESC backbuffer_desc;
		pBackBuffer->GetDesc(&backbuffer_desc);
		SafeRelease(pBackBuffer);

		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = backbuffer_desc.Width;
		descDepth.Height = backbuffer_desc.Height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = pD3dDevice->CreateTexture2D(&descDepth, nullptr, m_pDepthStencilTex.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return;
		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		m_pDepthStencilView = nullptr;
		hr = pD3dDevice->CreateDepthStencilView(m_pDepthStencilTex.Get(), &descDSV, m_pDepthStencilView.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return;

	}
	void RenderWindow::Resize(uint32_t width, uint32_t height)
	{
		m_pRenderTargetView.Reset();
		m_pDepthStencilView.Reset();
		m_pDepthStencilTex.Reset();

		HRESULT hr = m_pSwapChain->ResizeBuffers(1,
			width,
			height,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			0);

		Build();

		m_vp.Width = (FLOAT)width;
		m_vp.Height = (FLOAT)height;
		m_vp.MinDepth = 0.0f;
		m_vp.MaxDepth = 1.0f;
		m_vp.TopLeftX = 0;
		m_vp.TopLeftY = 0;
	}

	bool RenderWindow::Begin()
	{

		ID3D11DeviceContext* pImmediateContext = GetImmediateContext();

		pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
		pImmediateContext->RSSetViewports(1, &m_vp);

		DirectX::XMVECTORF32 color = { 0.45f, 0.55f, 0.60f, 1.00f };
		pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
		pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
		return true;
	}

	bool RenderWindow::End(bool bVsync)
	{
		HRESULT hr = m_pSwapChain->Present(bVsync ? 1 : 0, 0);

		return SUCCEEDED(hr);
	}


}
