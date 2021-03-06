#include <future>
#include <QStatusBar>
#include "PhongLightingWidget.h"
#include "ShaderCollection.h"


void PhongLightingWidget::show_render_dialog()
{
    render_dialog_.show();
}

void PhongLightingWidget::set_light_color(const QColor& color)
{
    for (auto& [light, light_object] : current_scene_.lights_objects) {
        light->color = color;

        for (auto& vertex : light_object->mesh.vertices) {
            vertex.color.setX(static_cast<float>(color.redF()));
        	vertex.color.setY(static_cast<float>(color.greenF()));
            vertex.color.setZ(static_cast<float>(color.blueF()));
        }

        light_object->renderer->reload();
    }
}

void PhongLightingWidget::set_ambient_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.ambient = color;
        });
}

void PhongLightingWidget::set_diffuse_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.diffuse = color;
        });
}

void PhongLightingWidget::set_specular_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.specular = color;
        });
}



void PhongLightingWidget::set_render_mode(const int state)
{
	auto* obj = sender();

	if(obj->objectName() == "fill_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_fill);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_fill);
        }
	} else if (obj->objectName() == "line_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_line);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_line);
        }
	} else if (obj->objectName() == "front_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_front);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_front);
        }
    } else {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_back);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_back);
        }
    }
}

void PhongLightingWidget::catch_fps(const QString& fps)
{
	emit send_fps(fps);
}


PhongLightingWidget::PhongLightingWidget(QWidget* parent)
	:   QOpenGLWidget{ parent },
		render_dialog_{*this },
		lighting_dialog_{*this}
{
	setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
	connect(&fps_counter_, &FPSCounter::emit_fps, this, &PhongLightingWidget::catch_fps);
    connect(&light_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_light_color);
    connect(&ambient_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_ambient_color);
    connect(&diffuse_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_diffuse_color);
    connect(&specular_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_specular_color);

    light_color_dialog_.setWindowTitle("Light Color");
    ambient_color_dialog_.setWindowTitle("Ambient Color");
    diffuse_color_dialog_.setWindowTitle("Diffuse Color");
    specular_color_dialog_.setWindowTitle("Specular Color");
}


void PhongLightingWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_1) {
        makeCurrent();
        ++scene_count_;
        lighting_dialog_.reset_state();
        const auto current_scene = std::next(prep_scenes_.scenes.begin(), scene_count_);
    	if(current_scene == prep_scenes_.scenes.end()) {
            scene_count_ = 0;
            current_scene_ = prep_scenes_.scenes.begin()->second;
    	} else {
            current_scene_ = current_scene->second;
    	}
    }
    if (event->key() == Qt::Key_2 && !is_guro_) {
        auto& shader_data = ShaderCollection::shaders["guro_lighting"];
        auto shader_program = shader_data.get_shader_program();
    	
        std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
			object->renderer->set_shader(shader_program);
        });

        is_guro_ = true;
    	
    }
    if (event->key() == Qt::Key_3 && is_guro_) {
        auto& shader_data = ShaderCollection::shaders["phong_lighting"];
        auto shader_program = shader_data.get_shader_program();

        std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
            {
                object->renderer->set_shader(shader_program);
            });

        is_guro_ = false;

    }
	else {
        current_scene_.camera_mover.set_key(event->key());
    }
}

void PhongLightingWidget::keyReleaseEvent(QKeyEvent* event)
{
    current_scene_.camera_mover.reset_key(event->key());
}

void PhongLightingWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.5f, 2.f, 1);

    const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
    glViewport(0, 0, width() * retina_scale, height() * retina_scale);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    renderer_.init();
    prep_scenes_.init();
    current_scene_ = prep_scenes_.scenes.begin()->second;

    timer_.start(16, this);
}

void PhongLightingWidget::paintGL()
{
    update_framerate();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->transform.rotate(100.f / 85.f, { 1, 1, 0});
        });
	
    renderer_.render(current_scene_);
}

void PhongLightingWidget::timerEvent(QTimerEvent*)
{
    current_scene_.camera_mover.set_camera_speed(fps_counter_.delta_time());
    current_scene_.camera_mover.move();
	update();
}

void PhongLightingWidget::update_framerate()
{
	fps_counter_.calculate_fps();
}
