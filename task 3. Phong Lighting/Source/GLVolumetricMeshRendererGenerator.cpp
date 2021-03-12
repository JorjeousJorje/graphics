#include "GLVolumetricMeshRendererGenerator.h"


std::shared_ptr<GLMeshRenderer> GLVolumetricMeshRendererGenerator::get_renderer(GLMesh& mesh, GLTransform& transform)
{
	return std::make_shared<GLCubeMeshRenderer>(mesh, transform);
}
