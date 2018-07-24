#include "main_class.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	srand ( time(NULL) );
	QApplication a(argc, argv);
	main_class w;
	w.show();
	return a.exec();
}
