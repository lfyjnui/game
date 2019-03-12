#pragma once
#include <stdint.h>
#include "renderdata.h"

namespace graphics
{
	class IRenderer
	{
	public:
		//��ʼ��ʱ��Ҫ���ھ��,
		virtual bool Init(void *) = 0;
		//��Ϸ����ʱ����Destroy
		virtual void Destroy() = 0;
		//���ڴ�С�ı�ʱ���ĺ��û���
		virtual void Resize(void*, uint32_t width, uint32_t height) = 0;
		//��Ⱦ
		virtual void Render(const RenderData* data) = 0;
	};

}
graphics::IRenderer* GetIRenderer();