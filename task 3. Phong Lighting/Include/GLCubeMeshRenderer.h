#pragma once
#include "GLMeshRenderer.h"

class GLCubeMeshRenderer : public GLMeshRenderer
{

public:
	GLCubeMeshRenderer(GLMesh& mesh, GLTransform& transform)
		: GLMeshRenderer{mesh, transform}
	{
	}
	
	void render(const GLCamera& camera) override;

private:
};
