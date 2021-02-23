#include "CubeWindow.h"
#include <QMouseEvent>
#include <QScreen>


CubeWindow::CubeWindow(ShaderParser& parser) : shader_parser_{ parser }
{
	cube_geometry_.InitGeometry();
	inner_edges_geometry_.InitGeometry();
	outer_edges_geometry_.InitGeometry();
}

void CubeWindow::setRotation()
{
	angular_speed_ *= 0.99;

	if (angular_speed_ < 0.01) {
		angular_speed_ = 0.0;
	}
	else {
		rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) * rotation_;
	}
}

void CubeWindow::initShaders()
{
	auto [vertex_code, fragment_code] = shader_parser_.parse();
	program_.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_code);
	program_.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_code);
	
}

void CubeWindow::mousePressEvent(QMouseEvent* e)
{
	mouse_press_position_ = QVector2D(e->screenPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent* e)
{
	QVector2D diff = QVector2D(e->screenPos()) - mouse_press_position_;
	QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized(); 

	qreal acc = diff.length() / 100.0f; 

	rotation_axis_ = (rotation_axis_ * angular_speed_ + n * acc).normalized();
	angular_speed_ += acc;
}

void CubeWindow::initializeGL()
{
	initializeOpenGLFunctions();
	initShaders();

	const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
	glViewport(0, 0, width() * retina_scale, height() * retina_scale);

	glClearColor(0.1f, 0.3f, 0.3f, 1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void CubeWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_.bind();
	
	const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
	const auto near_plane = 0.1f, far_plane = 100.0f, fov = 45.0f;

	
	QMatrix4x4 matrix;
	setRotation();
	matrix.perspective(fov, ratio, near_plane, far_plane);
	matrix.translate(0.0, 0.0, -3.0);
	matrix.rotate(rotation_);

	const auto matrix_location = program_.uniformLocation("matrix");
	Q_ASSERT(matrix_location != -1);

	program_.setUniformValue(matrix_location, matrix);

	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

	painter_.setUniformColor(color_);

	cube_geometry_.DrawGeometry(&program_);
	inner_edges_geometry_.DrawGeometry(&program_);
	outer_edges_geometry_.DrawGeometry(&program_);
	
	program_.release();

	update();
}

void CubeWindow::get_color(const QColor& color)
{
	color_ = color;
}
