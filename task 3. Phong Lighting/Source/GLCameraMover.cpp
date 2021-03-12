#include "GLCameraMover.h"




GLCameraMover::GLCameraMover(GLCamera& camera)
	:	camera_{ camera }
{
	
}



void GLCameraMover::move(const int move_key)
{
	const auto& direction = controls_[move_key];
	if(direction == QVector3D{0, 0, 0}) {
		return;
	}
	camera_.translate(direction * camera_speed_);
}
