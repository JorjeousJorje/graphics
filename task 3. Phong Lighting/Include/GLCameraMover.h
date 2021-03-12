#pragma once
#include "GLCamera.h"



class GLCameraMover final
{
public:
	explicit GLCameraMover(GLCamera& camera);
	void move(int move_key);

private:
	GLCamera& camera_;

	const float camera_speed_{ 1.5f };
	std::map<int, QVector3D> controls_ = {
			{Qt::Key_W, {0,0,1}	},
			{Qt::Key_S, {0,0,-1}	},
			{Qt::Key_A, {-1,0,0}	},
			{Qt::Key_D, {1,0,0}	},
			{Qt::Key_E, {0,1,0}	},
			{Qt::Key_Q, {0,-1,0}	}
	};
};