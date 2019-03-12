#include "renderer.h"
#include "device.h"
#include "renderwnd.h"

namespace d3d11
{
	Renderer g_Renderer;
	bool Renderer::Init(void *hwnd)
	{
		GetDevice()->Init();
		GetRenderWnd()->Create(hwnd);
		return false;
	}

	void Renderer::Destroy()
	{
	}

	void Renderer::Resize(void *, uint32_t width, uint32_t height)
	{
		GetRenderWnd()->Resize(width, height);
	}

	void Renderer::Render(const graphics::RenderData * data)
	{
		GetRenderWnd()->Begin();
		GetRenderWnd()->End(true);

	}

}

graphics::IRenderer* GetIRenderer()
{
	return &d3d11::g_Renderer;
}
