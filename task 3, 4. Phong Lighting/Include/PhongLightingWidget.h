#pragma once
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColorDialog>
#include <QBasicTimer>
#include <random>

#include "RenderDialog.h"
#include "FPSCounter.h"
#include "PreparedScenes.h"
#include "GLSceneRenderer.h"
#include "LightingDialog.h"


class PhongLightingWidget final : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit PhongLightingWidget(QWidget* parent = nullptr);
	
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

public slots:
	void show_render_dialog();
	
	void show_shininess_dialog()
	{
		lighting_dialog_.show();
	}
	void show_light_color_dialog()
	{
		light_color_dialog_.show();
	}
	void show_ambient_color_dialog()
	{
		ambient_color_dialog_.show();
	}
	void show_diffuse_color_dialog()
	{
		diffuse_color_dialog_.show();
	}
	void show_specular_color_dialog()
	{
		specular_color_dialog_.show();
	}
	
	void set_render_mode(int state);
	void catch_fps(const QString&);


	void set_light_color(const QColor& color);
	void set_ambient_color(const QColor& color);
	void set_diffuse_color(const QColor& color);
	void set_specular_color(const QColor& color);


	void set_shininess(const int shininess)
	{
		std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
			{
				object->material.shininess = static_cast<float>(shininess);
			});
	}

signals:
	void send_fps(const QString&);

	
protected:
	void initializeGL() override;
	void paintGL() override;

	void timerEvent(QTimerEvent*) override;
	void update_framerate();
	
public:
	PreparedScenes prep_scenes_;
	int scene_count_{ 0 };
	bool is_guro_{ true };
	
	GLScene current_scene_;
	GLSceneRenderer renderer_;

	RenderDialog render_dialog_;
	LightingDialog lighting_dialog_;
	QColorDialog light_color_dialog_;
	
	QColorDialog ambient_color_dialog_;
	QColorDialog diffuse_color_dialog_;
	QColorDialog specular_color_dialog_;
	FPSCounter fps_counter_;

	QBasicTimer timer_;
};
