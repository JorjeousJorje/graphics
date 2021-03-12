#include "GLScene.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"

void GLScene::init_scene(const std::size_t num_objects)
{
	for (std::size_t i = 0; i < num_objects; ++i) {

		for (std::size_t j = 0; j < num_objects; ++j) {
			add_object(ShaderCollection::shaders["cube_morphing"],
				MeshGeneratorCollection::generators["cube"],
				{ static_cast<float>(i) * 2.0f - 13, -11,static_cast<float>(j) * 2.0f - 70 });
		}
	}
}

std::shared_ptr<GLObject> GLScene::create_object(ShaderData& data, const std::shared_ptr<GLMeshGenerator>& mesh_generator, const QVector3D& pos) const
{
	auto object = std::make_shared<GLObject>();
	object->mesh = mesh_generator->generate(initial_grid_step);
	object->transform.translate(pos);
	object->renderer = data.renderer_generator->get_renderer(object->mesh, object->transform);
	object->init_renderer(data.get_shader_program());
	
	return object;
}

void GLScene::add_object(ShaderData& data, const std::shared_ptr<GLMeshGenerator>& mesh_generator, const QVector3D& pos)
{
	objects.push_back(create_object(data, mesh_generator, pos));
}
