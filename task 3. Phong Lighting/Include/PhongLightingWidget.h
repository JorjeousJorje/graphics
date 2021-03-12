#pragma once
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColorDialog>
#include <QBasicTimer>
#include <random>
#include <chrono>


#include "FPSCounter.h"
#include "GLScene.h"
#include "GLSceneRenderer.h"



class PhongLightingWidget final : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit PhongLightingWidget(QWidget* parent = nullptr);


	
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* e) override;

public slots:
	void show_color_dialog();
	void set_cubes_color(const QColor& color);
	void catch_fps(const QString&);

signals:
	void send_fps(const QString&);

	
protected:
	void initializeGL() override;
	void paintGL() override;

	void timerEvent(QTimerEvent*) override;
	void update_framerate();
	
private:
	GLScene scene_;
	GLSceneRenderer renderer_;

	
	QColorDialog color_dialog_;
	FPSCounter fps_counter_;


	QBasicTimer timer_;
	std::size_t grid_size_length_{ 20 };
	QVector2D mouse_pos_{};
};
