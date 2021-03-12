#pragma once
#include <map>
#include "ShaderData.h"
#include "GLMeshRendererGenerator.h"
#include "GLVolumetricMeshRendererGenerator.h"


class ShaderCollection final
{
public:
	
	inline static std::map<std::string, ShaderData> shaders =
	{
		{{"cube_morphing"}, {"Shaders\\vcube_morph.glsl", "Shaders\\fcube_morph.glsl", std::make_shared<GLVolumetricMeshRendererGenerator>()}}
	};
};
