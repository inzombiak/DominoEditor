#define CRTDBG_MAP_ALLOC

#include "dominoeditor.h"
#include <QtWidgets/QApplication>

#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DominoEditor w;
	w.show();

	
	auto test =  a.exec();
	_CrtDumpMemoryLeaks();
	return test;
}
