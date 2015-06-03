#include "window.h"
#include <QtGui>

int main (int argc, char ** argv) {
	QApplication app(argc, argv);

    md::Window *window = new md::Window();
	window->show();

	return app.exec();
}