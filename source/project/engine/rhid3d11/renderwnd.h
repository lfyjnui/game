#pragma once
#include <stdint.h>
#include <d3d11.h>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

namespace d3d11
{
	class RenderWindow
	{
	public:
		bool Create(void* hwnd);
		void Build();
		void Resize(uint32_t width, uint32_t height);

		bool Begin();
		bool End(bool bVsync);
	private:
		void* m_hWnd;
		uint32_t m_nWidth, m_nHeight;

		ComPtr<IDXGISwapChain>         m_pSwapChain;
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
		ComPtr<ID3D11Texture2D>        m_pDepthStencilTex;
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;

		D3D11_VIEWPORT m_vp;
	};

	RenderWindow* GetRenderWnd();
}