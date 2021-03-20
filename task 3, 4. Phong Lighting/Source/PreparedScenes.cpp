#include "PreparedScenes.h"

#include "GLDirectedLight.h"
#include "GLPointLight.h"
#include "GLSpotLight.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"


//void init_grid(GLScene& scene, const size_t grid_size)
//{
//	auto& shader = ShaderCollection::shaders["guro_lighting"];
//	const auto& generator = MeshGeneratorCollection::generators["sphere"];
//	QVector3D pos = {};
//	
//	GLMaterial material;
//	material.shininess = 32.0f;
//	
//	for (std::size_t i = 0; i < grid_size; ++i) {
//
//		for (std::size_t j = 0; j < grid_size; ++j) {
//			pos.setX(static_cast<float>(i) * 2.5f);
//			pos.setY(-5);
//			pos.setZ(static_cast<float>(j) * 2.5f - 10);
//
//			scene.add_object(shader, generator, pos, { 0, 0, 0 }, material);
//		}
//	}
//}

void PreparedScenes::init()
{
	scenes.emplace("default", default_scene());

}

GLScene PreparedScenes::default_scene()
{
	GLScene scene;
	auto& shader = ShaderCollection::shaders["guro_lighting"];
	const auto& generator = MeshGeneratorCollection::generators["sphere"];

	GLMaterial material;
	material.shininess = 32.0f;
	scene.add_object(shader, generator, { -1, 0, -1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { -1, 0, 1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { 1, 0, 1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, {1, 0, -1}, { 0, 0, 0 }, material);
	

	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto light = std::make_shared<GLSpotLight>(QVector3D{ 0, 2, 0 }, QColor{ 255, 255, 255 });
	scene.add_light(light, light_object_shader, light_object_generator);


	return scene;
}