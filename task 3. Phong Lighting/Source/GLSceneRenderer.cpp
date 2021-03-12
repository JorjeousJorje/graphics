#include "GLSceneRenderer.h"
#include "GLScene.h"

void GLSceneRenderer::init()
{
	initializeOpenGLFunctions();
}

void GLSceneRenderer::render(GLScene& scene)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	
	std::for_each(scene.objects.begin(), scene.objects.end(), [&](std::shared_ptr<GLObject>& object)
		{
			object->renderer->render(scene.camera);
		
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-1, -1);
		
			object->renderer->render_wireframe(scene.camera);
		
			glDisable(GL_POLYGON_OFFSET_LINE);
		});
}
