#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	ShaderParser parser{ "Resources/vshader.glsl", "Resources/fshader.glsl" };

	MainWindow window{parser };
	window.setFixedSize(1200, 600);
	window.show();
	
	return app.exec();
}
