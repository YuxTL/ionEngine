
#include "CGraphicsAPI.h"


namespace ion
{

	void CGraphicsAPI::Init(IGraphicsImplementation * Implementation)
	{
		this->Implementation = Implementation;
	}

	void CGraphicsAPI::PreWindowCreationSetup()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->PreWindowCreationSetup();
		}
	}

	void CGraphicsAPI::PostWindowCreationSetup()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->PostWindowCreationSetup();
		}
	}

	SharedPointer<Graphics::IVertexStage> CGraphicsAPI::CreateVertexStageFromFile(string const & FileName)
	{
		SharedPointer<Graphics::IVertexStage> VertexShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Vertex shader file does not appear to exist: %s", FileName);
		}
		else
		{
			VertexShader = CreateVertexStageFromSource(File::ReadAsString(FileName));

			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader from file '%s'", FileName);
			}
		}
		return VertexShader;
	}

	SharedPointer<Graphics::IGeometryStage> CGraphicsAPI::CreateGeometryStageFromFile(string const & FileName)
	{
		SharedPointer<Graphics::IGeometryStage> GeometryShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Geometry shader file does not appear to exist: %s", FileName);
		}
		else
		{
			GeometryShader = CreateGeometryStageFromSource(File::ReadAsString(FileName));

			if (! GeometryShader)
			{
				Log::Error("Failed to compile geometry shader from file '%s'", FileName);
			}
		}
		return GeometryShader;
	}

	SharedPointer<Graphics::IPixelStage> CGraphicsAPI::CreatePixelStageFromFile(string const & FileName)
	{
		SharedPointer<Graphics::IPixelStage> PixelShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Pixel shader file does not appear to exist: %s", FileName);
		}
		else
		{
			PixelShader = CreatePixelStageFromSource(File::ReadAsString(FileName));

			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader from file '%s'", FileName);
			}
		}
		return PixelShader;
	}

	SharedPointer<Graphics::IVertexStage> CGraphicsAPI::CreateVertexStageFromSource(string const & Source)
	{
		SharedPointer<Graphics::IVertexStage> VertexShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			VertexShader = Implementation->CreateVertexShaderFromSource(Source);
		}

		return VertexShader;
	}

	SharedPointer<Graphics::IGeometryStage> CGraphicsAPI::CreateGeometryStageFromSource(string const & Source)
	{
		SharedPointer<Graphics::IGeometryStage> GeometryShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			GeometryShader = Implementation->CreateGeometryShaderFromSource(Source);
		}

		return GeometryShader;
	}

	SharedPointer<Graphics::IPixelStage> CGraphicsAPI::CreatePixelStageFromSource(string const & Source)
	{
		SharedPointer<Graphics::IPixelStage> PixelShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			PixelShader = Implementation->CreatePixelShaderFromSource(Source);
		}

		return PixelShader;
	}

	SharedPointer<Graphics::IShader> CGraphicsAPI::CreateShaderProgram()
	{
		SharedPointer<Graphics::IShader> ShaderProgram;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			ShaderProgram = Implementation->CreateShaderProgram();
		}

		return ShaderProgram;
	}

	SharedPointer<Graphics::IVertexBuffer> CGraphicsAPI::CreateVertexBuffer()
	{
		SharedPointer<Graphics::IVertexBuffer> VertexBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			VertexBuffer = Implementation->CreateVertexBuffer();
		}

		return VertexBuffer;
	}

	SharedPointer<Graphics::IIndexBuffer> CGraphicsAPI::CreateIndexBuffer()
	{
		SharedPointer<Graphics::IIndexBuffer> IndexBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			IndexBuffer = Implementation->CreateIndexBuffer();
		}

		return IndexBuffer;
	}

	SharedPointer<Graphics::IDepthBuffer> CGraphicsAPI::CreateDepthBuffer(vec2i const & Size)
	{
		SharedPointer<Graphics::IDepthBuffer> DepthBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			DepthBuffer = Implementation->CreateDepthBuffer(Size);
		}

		return DepthBuffer;
	}

	Graphics::IDrawContext * CGraphicsAPI::CreateDrawContext()
	{
		Graphics::IDrawContext * DrawContext = nullptr;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			DrawContext = Implementation->CreateDrawContext();
		}

		return DrawContext;
	}

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture2D> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture2D(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(CImage * Image, Graphics::ITexture::EMipMaps MipMaps)
	{
		if (! Image)
		{
			Log::Error("Attempting to create texture from image that does not exist.");
			return nullptr;
		}

		Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;
		switch (Image->GetChannels())
		{
		case 2:
			Format = Graphics::ITexture::EFormatComponents::RG;
			break;
		case 3:
			Format = Graphics::ITexture::EFormatComponents::RGB;
			break;
		case 4:
			Format = Graphics::ITexture::EFormatComponents::RGBA;
			break;
		}
		SharedPointer<Graphics::ITexture2D> Texture = CreateTexture2D(
			Image->GetSize(),
			MipMaps,
			Format,
			Graphics::ITexture::EInternalFormatType::Fix8);
		Texture->Upload(
			Image->GetData(),
			Image->GetSize(),
			Format,
			Graphics::EScalarType::UnsignedInt8);
		return Texture;
	}

	SharedPointer<Graphics::ITexture3D> CGraphicsAPI::CreateTexture3D(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture3D> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture3D(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITexture2DArray> CGraphicsAPI::CreateTexture2DArray(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture2DArray> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture2DArray(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITextureCubeMap> CGraphicsAPI::CreateTextureCubeMap(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITextureCubeMap> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTextureCubeMap(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITextureCubeMap> CGraphicsAPI::CreateTextureCubeMap(vector<CImage*> const & Images, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (Images.size() != 6)
		{
			Log::Error("Attempting to create cube map texture from not 6 images.");
			return nullptr;
		}

		Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;
		switch (Images[0]->GetChannels())
		{
		case 2:
			Format = Graphics::ITexture::EFormatComponents::RG;
			break;
		case 3:
			Format = Graphics::ITexture::EFormatComponents::RGB;
			break;
		case 4:
			Format = Graphics::ITexture::EFormatComponents::RGBA;
			break;
		}

		SharedPointer<Graphics::ITextureCubeMap> Texture = CreateTextureCubeMap(
			Images[0]->GetSize(),
			MipMaps,
			Format,
			Graphics::ITexture::EInternalFormatType::Fix8);

		for (int i = 0; i < 6; ++ i)
		{
			if (Images[0]->GetChannels() != Images[i]->GetChannels())
			{
				Log::Error("Attempting to create cube map texture from images with mismatched channel count.");
				return nullptr;
			}

			if (Images[0]->GetSize() != Images[i]->GetSize())
			{
				Log::Error("Attempting to create cube map texture from images with mismatched size.");
				return nullptr;
			}

			Texture->Upload(
				(Graphics::ITextureCubeMap::EFace) i,
				Images[i]->GetData(),
				Images[i]->GetSize(),
				Format,
				Graphics::EScalarType::UnsignedInt8);
		}

		return Texture;
	}

	SharedPointer<Graphics::IGraphicsContext> CGraphicsAPI::GetWindowContext(CWindow * Window)
	{
		SharedPointer<Graphics::IGraphicsContext> GraphicsContext;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			GraphicsContext = Implementation->GetWindowContext(Window);
		}

		return GraphicsContext;
	}

}
