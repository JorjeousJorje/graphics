#include "PreparedScenes.h"


#include "AssimpMeshLoader.h"
#include "GLDirectedLight.h"
#include "GLPointLight.h"
#include "GLSpotLight.h"
#include "GLTextureLoader.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"


void PreparedScenes::init()
{

	scenes.push_back(default_scene_sphere(ShaderCollection::shaders["phong_wo_normal_mapping"]));
	scenes.push_back(default_scene_sphere(ShaderCollection::shaders["guro_wo_normal_mapping"]));
	
	scenes.push_back(default_scene_cube(ShaderCollection::shaders["phong_wo_normal_mapping"]));
	scenes.push_back(default_scene_cube(ShaderCollection::shaders["guro_wo_normal_mapping"]));

	scenes.push_back(default_scene_sphere(ShaderCollection::shaders["phong_normal_mapping"]));
	scenes.push_back(mesh_earth(ShaderCollection::shaders["phong_normal_mapping"]));


	scenes.push_back(mesh_house(ShaderCollection::shaders["phong_normal_mapping"]));
}


GLScene PreparedScenes::default_scene_sphere(ShaderData& data)
{
	GLScene scene;
	const auto& generator = MeshGeneratorCollection::generators["sphere"];


	GLMaterial material;
	GLTextureLoader::load_texture(material, "Textures\\Earth_Albedo.jpg", "Textures\\Earth_NormalMap.jpg");
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };
	
	const auto distance = 1.5f;
	scene.add_object(data, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);


	for(auto& object : scene.objects) {
		object->transform.rotate(270.f, { 1, 0 ,0 });
	}
	

	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;
	
	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);


	return scene;
}

GLScene PreparedScenes::default_scene_cube(ShaderData& data)
{
	GLScene scene;
	const auto& generator = MeshGeneratorCollection::generators["cube"];


	GLMaterial material;
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 1.5f;
	scene.add_object(data, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);


	for (auto& object : scene.objects) {
		object->transform.rotate(270.f, { 1, 0 ,0 });
	}


	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);


	return scene;
}

GLScene PreparedScenes::mesh_earth(ShaderData& data)
{
	GLScene scene;
	const auto& generator = MeshGeneratorCollection::generators["sphere"];

	auto models = MeshLoader().loadModel("Assets\\Models\\earth.obj");
	auto& [mesh, material] = models.front();
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 5.5f;
	scene.add_object(data, mesh, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(data, mesh, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, mesh, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(data, mesh, { distance, 0, -distance }, { 0, 0, 0 }, material);

	for (auto& object : scene.objects) {
		object->transform.rotate(90.f, { 1, 0 ,0 });
	}

	
	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);

	return scene;
}

GLScene PreparedScenes::mesh_cube(ShaderData& data)
{
	GLScene scene;

	auto& shader = ShaderCollection::shaders["phong_wo_normal_mapping"];

	auto models = MeshLoader().loadModel("Assets\\My Models\\MeshCube.obj");
	auto& [mesh, material] = models.front();
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 3.5f;
	scene.add_object(shader, mesh, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, -distance }, { 0, 0, 0 }, material);

	for (auto& object : scene.objects) {
		object->transform.rotate(90.f, { 1, 0 ,0 });
	}


	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);

	return scene;
}

GLScene PreparedScenes::mesh_sphere(ShaderData& data)
{
	GLScene scene;

	auto& shader = ShaderCollection::shaders["phong_wo_normal_mapping"];

	auto models = MeshLoader().loadModel("Assets\\My Models\\MeshSphere.obj");
	auto& [mesh, material] = models.front();
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 3.5f;
	scene.add_object(shader, mesh, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, -distance }, { 0, 0, 0 }, material);

	for (auto& object : scene.objects) {
		object->transform.rotate(90.f, { 1, 0 ,0 });
	}


	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);

	return scene;
}

GLScene PreparedScenes::mesh_house(ShaderData& data)
{
	GLScene scene;

	auto& shader = ShaderCollection::shaders["phong_wo_normal_mapping"];

	auto models = MeshLoader().loadModel("Assets\\My Models\\SpiderMan.obj");
	auto& [mesh, material] = models.front();
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 3.5f;
	scene.add_object(shader, mesh, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, mesh, { distance, 0, -distance }, { 0, 0, 0 }, material);

	for (auto& object : scene.objects) {
		object->transform.rotate(90.f, { 1, 2 ,0 });
	}

	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.2f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);

	return scene;
}

GLScene PreparedScenes::mystery_cube(ShaderData& data)
{
	GLScene scene;
	// texture
	auto& shader = ShaderCollection::shaders["phong_normal_mapping"];
	const auto& generator = MeshGeneratorCollection::generators["cube"];


	GLMaterial material;
	GLTextureLoader::load_texture(material, "Textures\\Wow2.jpg", "Textures\\Wow2_normal.png");
	material.shininess = 32.0f;
	material.diffuse = { 255, 255, 255 };
	material.ambient = { 255, 255, 255 };

	const auto distance = 1.5f;
	scene.add_object(shader, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);


	auto& light_object_shader = ShaderCollection::shaders["light_source"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

	const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
	light_sphere_gen->radius_ = 0.3f;

	const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
	scene.add_light(light, light_object_shader, light_sphere_gen);


	return scene;
}
