
#pragma once

#include <ionCore.h>
#include <ionGraphics.h>
#include <ionWindow.h>
#include <ionScene.h>


namespace ion
{
	
	class CAssetManager : public Singleton<CAssetManager>
	{

	public:

		void Init(CGraphicsAPI * GraphicsAPI);

		SharedPointer<Graphics::IShader> LoadShader(string const & Name);
		CImage * LoadImage(string const & FileName);
		SharedPointer<Graphics::ITexture2D> LoadTexture(string const & FileName, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		SharedPointer<Graphics::ITexture3D> Load3DTexture(const std::vector<std::string> & fileName, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		SharedPointer<Graphics::ITexture2DArray> Load2DTextureArray(const std::vector<std::string> & fileName, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		SharedPointer<Graphics::ITextureCubeMap> LoadCubeMapTexture(
			string const & FileNameLeft,
			string const & FileNameRight,
			string const & FileNameUp,
			string const & FileNameDown,
			string const & FileNameFront,
			string const & FileNameBack,
			Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		Scene::CSimpleMesh * LoadMesh(string const & FileName);
		Scene::CSimpleMesh * LoadMeshMerged(string const & FileName);
		vector<Scene::CSimpleMesh *> LoadMeshes(string const & FileName);

		void AddAssetPath(string const & Path);
		void SetTexturePath(string const & Path);
		void SetShaderPath(string const & Path);
		void SetMeshPath(string const & Path);

		string ParseShaderSource(string const & FileName, string const & RelativeDirectory);

	protected:

		SingletonPointer<CGraphicsAPI> GraphicsAPI;

		vector<string> AssetPaths;
		string TexturePath = "Textures/";
		string ShaderPath = "Shaders/";
		string MeshPath = "Meshes/";

	private:

		friend class Singleton<CAssetManager>;
		CAssetManager()
		{}

	};

}
