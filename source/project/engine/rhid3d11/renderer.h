#pragma once
#include <engine/renderer.h>

namespace d3d11
{
	class Renderer :public graphics::IRenderer
	{
		virtual bool Init(void *) override;
		virtual void Destroy() override;

		virtual void Resize(void*, uint32_t width, uint32_t height) override;
		//‰÷»æ
		virtual void Render(const graphics::RenderData* data) override;
	};
}