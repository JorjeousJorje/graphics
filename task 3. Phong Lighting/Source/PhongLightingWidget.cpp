#include "PhongLightingWidget.h"
#include <QStatusBar>


void PhongLightingWidget::show_color_dialog()
{
	color_dialog_.show();
}

void PhongLightingWidget::set_cubes_color(const QColor& color)
{
    std::for_each(scene_.objects.begin(), scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            std::for_each(object->mesh.vertices.begin(), object->mesh.vertices.end(), [&](GLVertex& vertex)
                {
                    vertex.color = { static_cast<float>(color.redF()),
                                     static_cast<float>(color.greenF()),
                                     static_cast<float>(color.blueF()) };
                });
            object->renderer->reload();
        });
}

void PhongLightingWidget::catch_fps(const QString& fps)
{
	emit send_fps(fps);
}


PhongLightingWidget::PhongLightingWidget(QWidget* parent)
	: QOpenGLWidget{ parent }
{
	setFocusPolicy(Qt::StrongFocus);
	connect(&fps_counter_, &FPSCounter::emit_fps, this, &PhongLightingWidget::catch_fps);
    connect(&color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_cubes_color);
}


void PhongLightingWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_1) {
        makeCurrent();
    	scene_.objects.clear();
        ++grid_size_length_;
        scene_.init_scene(grid_size_length_);
    }
    if (event->key() == Qt::Key_2) {
        makeCurrent();
        scene_.objects.clear();
        --grid_size_length_;
        scene_.init_scene(grid_size_length_);
    } else {
        scene_.camera_mover.move(event->key());
    }
}

void PhongLightingWidget::mousePressEvent(QMouseEvent* e)
{
    mouse_pos_ = QVector2D(e->localPos());
}

void PhongLightingWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.3f, 0.3f, 1);

    const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
    glViewport(0, 0, width() * retina_scale, height() * retina_scale);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    renderer_.init();
    scene_.init_scene(grid_size_length_);

    timer_.start(16, this);
}

void PhongLightingWidget::paintGL()
{
    update_framerate();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    std::for_each(scene_.objects.begin(), scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->transform.rotate(100.0f / 60.0f, { 0, 1, 0 });
        });
	
    renderer_.render(scene_);
}

void PhongLightingWidget::timerEvent(QTimerEvent*)
{
	update();
}

void PhongLightingWidget::update_framerate()
{
	fps_counter_.calculate_fps();
}
