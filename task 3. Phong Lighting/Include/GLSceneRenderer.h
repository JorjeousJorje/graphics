#pragma once

#include <QOpenGLFunctions_3_0>
class GLScene;

class GLSceneRenderer final : protected QOpenGLFunctions_3_0
{
public:
	void init();
	void render(GLScene& scene);
};
