#include "GLCubeMeshRenderer.h"

void GLCubeMeshRenderer::render(const GLCamera& camera)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	shader_program_->bind();
	shader_program_->setUniformValue("wireframe", false);
	upload_camera_details(camera);
	
	vao_.bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_.indices.size()), GL_UNSIGNED_INT, nullptr);
	vao_.release();
}