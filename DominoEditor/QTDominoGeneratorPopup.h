#ifndef QTDOMINOGENERATORPOPUP_H
#define QTDOMINOGENERATORPOPUP_H

#include <QWidget>
#include "ui_QTDominoGeneratorPopup.h"
#include <map>

class QTDominoGeneratorPopup : public QWidget
{
	Q_OBJECT

public:
	QTDominoGeneratorPopup(QWidget *parent = 0);
	~QTDominoGeneratorPopup();

public slots:
	void GenerateGrid();
	void Save();

signals:
	void SavePatternSignal(std::vector<DominoTransform> transforms, int numColumns, int numRows, double xSpacing, double zSpacing);

private:
	Ui::QTDominoGeneratorPopup ui;
};

#endif // QTDOMINOGENERATORPOPUP_H
