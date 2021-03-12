#pragma once
#include "GLObject.h"
#include "GLCameraMover.h"
class GLMeshGenerator;

class GLScene final
{
public:
	GLCamera camera;
	GLCameraMover camera_mover{camera};
	std::vector<std::shared_ptr<GLObject>> objects;

	void init_scene(std::size_t num_objects);

private:
	void add_object(ShaderData& data, const std::shared_ptr<GLMeshGenerator>& mesh_generator, const QVector3D& pos);
	
	std::shared_ptr<GLObject> create_object(ShaderData& data, 
											const std::shared_ptr<GLMeshGenerator>& mesh_generator, 
											const QVector3D& pos) const;
};
