#pragma once
#include "GLMeshRendererGenerator.h"
#include "GLCubeMeshRenderer.h"



class GLVolumetricMeshRendererGenerator : public GLMeshRendererGenerator
{
public:
	std::shared_ptr<GLMeshRenderer> get_renderer(GLMesh& mesh, GLTransform& transform) override;
};