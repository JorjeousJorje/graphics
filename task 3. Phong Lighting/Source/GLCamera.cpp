#include "GLCamera.h"

GLCamera::GLCamera()
{
	update_camera_vectors();
}

QMatrix4x4 GLCamera::get_projection_matrix() const
{
	QMatrix4x4 projection;
	projection.perspective(FOV, aspectRatio, 0.1f, 1000.0f);
	return projection;
}

QMatrix4x4 GLCamera::get_view_matrix() const
{
	QMatrix4x4 view;
	view.lookAt(position, position + front, up);
	return view;
}

void GLCamera::update_camera_vectors()
{
	QVector3D forward;

	forward.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
	forward.setY(sin(qDegreesToRadians(pitch)));
	forward.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
	front = forward.normalized();

	right = QVector3D::crossProduct(forward, QVector3D(0, 1, 0)).normalized();
	up = QVector3D::crossProduct(right, front).normalized();
}


void GLCamera::translate(const QVector3D& mult)
{
	position += front * mult.z();
	position += right * mult.x();
	position += up * mult.y();
	update_camera_vectors();
}


void GLCamera::look(const float dx, const float dy)
{
	yaw += dx;
	pitch += dy;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	pitch = std::clamp(pitch, -89.0f, 89.0f);
	update_camera_vectors();
}
