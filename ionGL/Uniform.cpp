
#include "Uniform.h"
#include "Utilities.h"

#include <ionMath.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace GL
	{
		template <>
		void Uniform::Bind<float>(uint const Handle, float const & Value)
		{
			CheckedGLCall(glUniform1f(Handle, Value));
		}

		template <>
		void Uniform::Bind<int>(uint const Handle, int const & Value)
		{
			CheckedGLCall(glUniform1i(Handle, Value));
		}

		template <>
		void Uniform::Bind<glm::mat4>(uint const Handle, glm::mat4 const & Value)
		{
			CheckedGLCall(glUniformMatrix4fv(Handle, 1, GL_FALSE, glm::value_ptr(Value)));
		}

		template <>
		void Uniform::Bind<vec2f>(uint const Handle, vec2f const & Value)
		{
			CheckedGLCall(glUniform2f(Handle, Value[0], Value[1]));
		}

		template <>
		void Uniform::Bind<vec3f>(uint const Handle, vec3f const & Value)
		{
			CheckedGLCall(glUniform3f(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void Uniform::Bind<vec4f>(uint const Handle, vec4f const & Value)
		{
			CheckedGLCall(glUniform4f(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void Uniform::Bind<color3f>(uint const Handle, color3f const & Value)
		{
			CheckedGLCall(glUniform3f(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void Uniform::Bind<color4f>(uint const Handle, color4f const & Value)
		{
			CheckedGLCall(glUniform4f(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void Uniform::Bind<vec2i>(uint const Handle, vec2i const & Value)
		{
			CheckedGLCall(glUniform2i(Handle, Value[0], Value[1]));
		}

		template <>
		void Uniform::Bind<vec3i>(uint const Handle, vec3i const & Value)
		{
			CheckedGLCall(glUniform3i(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void Uniform::Bind<vec4i>(uint const Handle, vec4i const & Value)
		{
			CheckedGLCall(glUniform4i(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void Uniform::Bind<color3i>(uint const Handle, color3i const & Value)
		{
			CheckedGLCall(glUniform3i(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void Uniform::Bind<color4i>(uint const Handle, color4i const & Value)
		{
			CheckedGLCall(glUniform4i(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void Uniform::Bind<vec2u>(uint const Handle, vec2u const & Value)
		{
			CheckedGLCall(glUniform2ui(Handle, Value[0], Value[1]));
		}

		template <>
		void Uniform::Bind<vec3u>(uint const Handle, vec3u const & Value)
		{
			CheckedGLCall(glUniform3ui(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void Uniform::Bind<vec4u>(uint const Handle, vec4u const & Value)
		{
			CheckedGLCall(glUniform4ui(Handle, Value[0], Value[1], Value[2], Value[3]));
		}
	}
}