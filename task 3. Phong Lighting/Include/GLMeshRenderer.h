#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_0>

#include "GLMesh.h"
#include "GLTransform.h"
#include "ShaderData.h"


class GLCamera;

class GLMeshRenderer : protected QOpenGLFunctions_3_0
{
public:
	GLMeshRenderer(GLMesh& mesh, GLTransform& transform);

	void init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program);
	virtual void render(const GLCamera& camera) = 0;
	
	void render_wireframe(const GLCamera& camera);
	void upload_camera_details(const GLCamera& camera) const;
	void reload();

	virtual ~GLMeshRenderer() = default;

protected:
	std::shared_ptr<QOpenGLShaderProgram> shader_program_ { nullptr };
	
	QOpenGLBuffer vbo_;
	QOpenGLBuffer ibo_;
	QOpenGLVertexArrayObject vao_;
	
	GLMesh& mesh_;
	GLTransform& transform_;
	


	void enable_attributes() const;
	void disable_attributes() const;


private:

	void init_vbo();
	void init_ibo();
	void init_vao();
};
