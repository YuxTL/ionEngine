
#include "VertexArray.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		VertexArray::VertexArray(EPrimativeType const PrimativeType)
		{
			BoundIndexBuffer = 0;
			this->PrimativeType = PrimativeType;

			CheckedGLCall(glGenVertexArrays(1, & Handle));
		}

		void VertexArray::SetIndexBuffer(IndexBuffer * ibo)
		{
			if (! ibo)
				return;

			CheckedGLCall(glBindVertexArray(Handle));
			BoundIndexBuffer = ibo;
			BoundIndexBuffer->Bind();
			CheckedGLCall(glBindVertexArray(0));
		}

		void VertexArray::BindAttribute(u32 const index, VertexBuffer * vbo)
		{
			CheckedGLCall(glBindVertexArray(Handle));
			CheckedGLCall(glEnableVertexAttribArray(index));
			vbo->Bind();
			CheckedGLCall(glVertexAttribPointer(index, vbo->Components(), Util::TypeMatrix[(int) vbo->Type()], GL_FALSE, 0, 0));
			vbo->Unbind();
			CheckedGLCall(glBindVertexArray(0));
		}

		void VertexArray::Draw()
		{
			if (! BoundIndexBuffer)
				return;
			
			CheckedGLCall(glBindVertexArray(Handle));
			glDrawElements(
				Util::PrimativeMatrix[(int) PrimativeType],
				BoundIndexBuffer->Elements(),
				Util::TypeMatrix[(int) BoundIndexBuffer->Type()], 0);
			CheckedGLCall(glBindVertexArray(0));
		}

		void VertexArray::Delete()
		{
			delete this;
		}

		VertexArray::~VertexArray()
		{
			CheckedGLCall(glDeleteVertexArrays(1, & Handle));
		}
	}
}
