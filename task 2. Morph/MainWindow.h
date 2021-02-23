#pragma once
#include "CubeWindow.h"
#include <QHBoxLayout>

//TODO: make "morph" class that would take any Geometry and morph it 

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(ShaderParser& parser, QWidget* parent = nullptr);

private:
	QColorDialog* color_dialog_{ new QColorDialog };
	CubeWindow* cube_window_;
	QSlider* time_slider_;

	QHBoxLayout* layout_;


	void initColorDialog();
	void initSlidersDialog();
	void initCubeWindow();
	void initLayout();
};