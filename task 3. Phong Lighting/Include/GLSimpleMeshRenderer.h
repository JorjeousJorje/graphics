#pragma once
#include "GLMeshRenderer.h"

class GLSimpleMeshRenderer : public GLMeshRenderer
{

public:
	GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transform)
		: GLMeshRenderer{ mesh, transform }
	{
	}
	
	void render(const GLCamera& camera) override {}

private:

};
