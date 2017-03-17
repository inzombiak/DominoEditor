#define CRTDBG_MAP_ALLOC
//#include <afx.h>
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
//	afxMemDF |= checkAlwaysMemDF;
	return test;
}
