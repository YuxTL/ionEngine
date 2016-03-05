
#pragma once

#if 0

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

		enum EBuffer
		{
			Color = 0,
			Depth = 1,
			Stencil = 2
		};

		class Context
		{
		public:

			static void Init();
			static void Clear(std::vector<EBuffer> Buffers = { EBuffer::Color, EBuffer::Depth });
			static void SetClearColor(color4f const & Color);
			static color4f const & GetClearColor();

			static byte * ReadPixels();
			static vec2i GetViewportSize();

		};
		}
	}
}

#endif
