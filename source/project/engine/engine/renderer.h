#pragma once
#include <stdint.h>
#include "renderdata.h"

namespace graphics
{
	class IRenderer
	{
	public:
		//初始化时需要窗口句柄,
		virtual bool Init(void *) = 0;
		//游戏清理时调用Destroy
		virtual void Destroy() = 0;
		//窗口大小改变时更改后置缓冲
		virtual void Resize(void*, uint32_t width, uint32_t height) = 0;
		//渲染
		virtual void Render(const RenderData* data) = 0;
	};

}
graphics::IRenderer* GetIRenderer();