#ifndef _CABBAGE_SCENE_CSHADERLOADER_H_INCLUDED_
#define _CABBAGE_SCENE_CSHADERLOADER_H_INCLUDED_

#include "CShader.h"

class CShaderLoader
{

	static std::map<std::pair<std::string, std::string>, CShader *> LoadedShaders;

public:

	static std::string const parseShaderSource(std::string const & fileName, std::vector<std::pair<std::string, std::string> > SymbolTable = std::vector<std::pair<std::string, std::string> >());

	static CShader * const loadShader(std::string const & name);
	static CShader * const loadShader(std::string const & vertName, std::string const & fragName);

	static std::string ShaderDirectory;
	static bool LogOpened;
	static std::ofstream LogFile;

};


#endif
