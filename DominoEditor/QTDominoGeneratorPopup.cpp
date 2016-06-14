
#include "QTDominoGeneratorPopup.h"


QTDominoGeneratorPopup::QTDominoGeneratorPopup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QTDominoGeneratorPopup::~QTDominoGeneratorPopup()
{

}

void QTDominoGeneratorPopup::GenerateGrid()
{
	int numCol = ui.columns->value();
	int numRow = ui.rows->value();

	double xSpacing = ui.xSpacing->value();
	double zSpacing = ui.zSpacing->value();
	double heightSpacing = ui.heightSpacing->value();

	PhysicsSettings dominoSettings = ui.objectSettings->GetSettings();

	double cellWidth = 2*dominoSettings.boxDimensions[0];
	double cellLength = 2*dominoSettings.boxDimensions[2];
	double cellHeight = 2*dominoSettings.boxDimensions[1];

	QTGridView::GridProperties gridProps(numCol, numRow, xSpacing, zSpacing, heightSpacing, cellWidth, cellLength, cellHeight);

	ui.graphicsView->InitGrid(gridProps);
}

void QTDominoGeneratorPopup::Save()
{
	QTGridView::GridProperties gridProps = ui.graphicsView->GetProperties();
	SavePatternSignal(ui.graphicsView->SaveGrid(), gridProps.columns, gridProps.rows, gridProps.xSpacing, gridProps.zSpacing);
	GenerateGrid();
}