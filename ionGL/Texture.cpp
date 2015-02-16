
#include "Texture.h"
#include "Utilities.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		////////////
		// Params //
		////////////

		void Texture::ApplyParams()
		{
			static u32 const FilterMatrix[3][2] = 
			{
				{GL_NEAREST, GL_LINEAR},
				{GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST},
				{GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR},
			};

			static u32 const FilterLookup[2] = 
			{
				GL_NEAREST, GL_LINEAR
			};

			static u32 const WrapLookup[3] = 
			{
				GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
			};

			int MipMapMode;
			if (MipMaps)
				MipMapMode = 1 + (int) MipMapFilter;
			else
				MipMapMode = 0;

			int PreviouslyBoundTexture;
			CheckedGLCall(glGetIntegerv(GetGLTextureBindingEnum(), & PreviouslyBoundTexture));
			CheckedGLCall(glBindTexture(GetGLBindTextureTarget(), GetHandle()));
			CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MIN_FILTER, FilterMatrix[MipMapMode][(int) MinFilter]));
			CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MAG_FILTER, FilterLookup[(int) MagFilter]));

			CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_S, WrapLookup[(int) WrapMode]));
			CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_T, WrapLookup[(int) WrapMode]));
			CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_R, WrapLookup[(int) WrapMode]));

			f32 LargestAnisotropy;
			CheckedGLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, & LargestAnisotropy));
			if (Anisotropy < 0.f)
				Anisotropy = LargestAnisotropy;
			CheckedGLCall(glTexParameterf(GetGLBindTextureTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, Clamp(Anisotropy, 0.f, LargestAnisotropy)));
			CheckedGLCall(glBindTexture(GetGLBindTextureTarget(), PreviouslyBoundTexture));
		}
			
		Texture * Texture::SetMinFilter(EFilter const MinFilter)
		{
			this->MinFilter = MinFilter;
			ApplyParams();
			return this;
		}

		Texture * Texture::SetMagFilter(EFilter const MagFilter)
		{
			this->MagFilter = MagFilter;
			ApplyParams();
			return this;
		}

		Texture * Texture::SetMipMapFilter(EFilter const MipMapFilter)
		{
			this->MipMapFilter = MipMapFilter;
			ApplyParams();
			return this;
		}

		Texture * Texture::SetWrapMode(EWrapMode const WrapMode)
		{
			this->WrapMode = WrapMode;
			ApplyParams();
			return this;
		}

		Texture * Texture::SetAnisotropy(f32 const Anisotropy)
		{
			this->Anisotropy = Anisotropy;
			ApplyParams();
			return this;
		}

		Texture::EFilter Texture::GetMinFilter()
		{
			return MinFilter;
		}

		Texture::EFilter Texture::GetMagFilter()
		{
			return MagFilter;
		}

		Texture::EFilter Texture::GetMipMapFilter()
		{
			return MipMapFilter;
		}

		Texture::EWrapMode Texture::GetWrapMode()
		{
			return WrapMode;
		}

		f32 Texture::GetAnisotropy()
		{
			return Anisotropy;
		}


		/////////////
		// Texture //
		/////////////

		Texture::~Texture()
		{
			CheckedGLCall(glDeleteTextures(1, & Handle));
			Handle = 0;
		}

		Texture::Texture()
		{
			CheckedGLCall(glGenTextures(1, & Handle));
		}

		Texture::Texture(u32 const Handle)
		{
			this->Handle = Handle;
		}

		u32 Texture::GetHandle() const
		{
			return Handle;
		}


		////////////
		// Lookup //
		////////////
		
		u32 const Texture::InternalFormatMatrix[4][10] = 
		{
			{GL_R8, GL_R16, GL_R8UI, GL_R32UI, GL_R32UI, GL_R8I, GL_R16I, GL_R32I, GL_R16F, GL_R32F},
			{GL_RG8, GL_RG16, GL_RG8UI, GL_RG32UI, GL_RG32UI, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG16F, GL_RG32F},
			{GL_RGB8, GL_RGB16, GL_RGB8UI, GL_RGB32UI, GL_RGB32UI, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB16F, GL_RGB32F},
			{GL_RGBA8, GL_RGBA16, GL_RGBA8UI, GL_RGBA32UI, GL_RGBA32UI, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA16F, GL_RGBA32F}
		};

		u32 const Texture::FormatMatrix[4] = 
		{
			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA
		};

		u32 const Texture::DepthComponentMatrix[6] = 
		{
			GL_DEPTH_COMPONENT16,
			GL_DEPTH_COMPONENT24,
			GL_DEPTH_COMPONENT32,
			GL_DEPTH24_STENCIL8,
			GL_DEPTH32F_STENCIL8,
			GL_STENCIL_INDEX8
		};

		string const Texture::InternalFormatStringMatrix[4][10] = 
		{
			{"GL_R8", "GL_R16", "GL_R8UI", "GL_R32UI", "GL_R32UI", "GL_R8I", "GL_R16I", "GL_R32I", "GL_R16F", "GL_R32F"},
			{"GL_RG8", "GL_RG16", "GL_RG8UI", "GL_RG32UI", "GL_RG32UI", "GL_RG8I", "GL_RG16I", "GL_RG32I", "GL_RG16F", "GL_RG32F"},
			{"GL_RGB8", "GL_RGB16", "GL_RGB8UI", "GL_RGB32UI", "GL_RGB32UI", "GL_RGB8I", "GL_RGB16I", "GL_RGB32I", "GL_RGB16F", "GL_RGB32F"},
			{"GL_RGBA8", "GL_RGBA16", "GL_RGBA8UI", "GL_RGBA32UI", "GL_RGBA32UI", "GL_RGBA8I", "GL_RGBA16I", "GL_RGBA32I", "GL_RGBA16F", "GL_RGBA32F"}
		};

		string const Texture::FormatStringMatrix[4] = 
		{
			"GL_RED",
			"GL_RG",
			"GL_RGB",
			"GL_RGBA"
		};


		///////////////
		// Texture2D //
		///////////////
		
		Texture2D::Texture2D(vec2u const & Size, bool const MipMaps, EFormatComponents const Components, EInternalFormatType const Type)
		{
			this->Size = Size;
			this->MipMaps = MipMaps;

			int Levels = 1;

			if (MipMaps)
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y)));

			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
			glTexStorage2D(GL_TEXTURE_2D, Levels, InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y);
			if (OpenGLError())
			{
				cerr << "Error occured during glTexStorage2D: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		Texture2D::Texture2D(vec2u const & Size, EDepthComponents const Components)
		{
			this->Size = Size;
			this->MipMaps = false;

			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
			glTexStorage2D(GL_TEXTURE_2D, 1, DepthComponentMatrix[(int) Components], Size.X, Size.Y);
			if (OpenGLError())
			{
				cerr << "Error occured during glTexStorage2D: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		void Texture2D::Image(void const * const Data, EFormatComponents const Components, EFormatType const Type)
		{
			SubImage(Data, vec2u(0, 0), Size, Components, Type);
		}

		void Texture2D::SubImage(void const * const Data, vec2u const & Offset, vec2u const & Size, EFormatComponents const Components, EFormatType const Type)
		{
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
			CheckExistingErrors(Texture2D::SubImage);
			glTexSubImage2D(GL_TEXTURE_2D, 0, Offset.X, Offset.Y, Size.X, Size.Y, FormatMatrix[(int) Components], Util::TypeMatrix[(int) Type], Data);
			if (OpenGLError())
			{
				cerr << "Error occured during glTexSubImage2D: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
				cerr << "Offset is " << Offset << endl;
				cerr << "Size is " << Size << endl;
				cerr << "Format is " << FormatStringMatrix[(int) Components] << endl;
				cerr << "Type is " << Util::TypeStringMatrix[(int) Type] << endl;
				cerr << endl;
			}
			else
			{
				if (MipMaps)
					CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D));
				ApplyParams();
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		u32 Texture2D::GetGLBindTextureTarget() const
		{
			return GL_TEXTURE_2D;
		}

		u32 Texture2D::GetGLTextureBindingEnum() const
		{
			return GL_TEXTURE_BINDING_2D;
		}


		///////////////
		// Texture3D //
		///////////////

		Texture3D::Texture3D(u32 const Handle)
			: Texture(Handle)
		{}
		
		Texture3D::Texture3D(vec3u const & Size, bool const MipMaps, EFormatComponents const Components, EInternalFormatType const Type)
		{
			this->Size = Size;
			this->MipMaps = MipMaps;

			int Levels = 1;

			if (MipMaps)
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y)));

			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Handle));
			glTexStorage3D(GL_TEXTURE_3D, Levels, InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y, Size.Z);
			if (OpenGLError())
			{
				cerr << "Error occured during glTexStorage2D: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));
		}

		void Texture3D::Image(void const * const Data, EFormatComponents const Components, EFormatType const Type)
		{
			SubImage(Data, vec2u(0, 0), Size, Components, Type);
		}

		void Texture3D::SubImage(void const * const Data, vec3u const & Offset, vec3u const & Size, EFormatComponents const Components, EFormatType const Type)
		{
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Handle));
			CheckExistingErrors(Texture2D::SubImage);
			glTexSubImage3D(GL_TEXTURE_3D, 0, Offset.X, Offset.Y, Offset.Z, Size.X, Size.Y, Size.Z, FormatMatrix[(int) Components], Util::TypeMatrix[(int) Type], Data);
			if (OpenGLError())
			{
				cerr << "Error occured during glTexSubImage3D: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
				cerr << "Offset is " << Offset << endl;
				cerr << "Size is " << Size << endl;
				cerr << "Format is " << FormatStringMatrix[(int) Components] << endl;
				cerr << "Type is " << Util::TypeStringMatrix[(int) Type] << endl;
				cerr << endl;
			}
			else
			{
				if (MipMaps)
					CheckedGLCall(glGenerateMipmap(GL_TEXTURE_3D));
				ApplyParams();
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));
		}

		u32 Texture3D::GetGLBindTextureTarget() const
		{
			return GL_TEXTURE_3D;
		}

		u32 Texture3D::GetGLTextureBindingEnum() const
		{
			return GL_TEXTURE_BINDING_3D;
		}
	}
}
