#pragma once
#include "GLMesh.h"
#include <memory>


class GLMeshGenerator
{
public:
	GLMeshGenerator() = default;

	virtual GLMesh generate(unsigned mesh_steps) const = 0;
	virtual GLMesh generate() const = 0;

	virtual ~GLMeshGenerator() = default;
};