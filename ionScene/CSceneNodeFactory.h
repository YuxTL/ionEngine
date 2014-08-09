
#pragma once

#include <ionCore.h>

#include "CSceneNode.h"
#include "CPerspectiveCamera.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * SceneManager);
	
	CSceneNode * AddMeshNode(string const & Mesh, string const & Shader);
	CSceneNode * AddSkySphereNode(string const & TextureLabel);
	CPerspectiveCamera * AddPerspectiveCamera(f32 const AspectRatio);

private:

	CSceneManager * SceneManager;

};