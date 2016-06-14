#ifndef DOMINOEDITOR_H
#define DOMINOEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_dominoeditor.h"

#include "QTBulletObjectSettingsWidget.h"
#include "QTDominoGeneratorPopup.h"

class QTForceSettingsWidget;

class DominoEditor : public QMainWindow
{
	Q_OBJECT

public:
	DominoEditor(QWidget *parent = 0);
	~DominoEditor();
public slots:
	void ShowForceEditor();
	void ForceSpinBoxValueChanged(double value);
	void ShowBulletObjectCreator();
	void BulletObjectSettingsChanged(PhysicsSettings settings);
	void ShowDominoPatternEditor();
	void GenerateObjects(std::vector<DominoTransform> transforms, int numColumns, int numRows, double xSpacing, double zSpacing);

private:
	Ui::DominoEditorClass ui;
	QTForceSettingsWidget* m_forceSettingsWidget;
	QTBulletObjectSettingsWidget* m_objectSettingsWidget;
};

#endif // DOMINOEDITOR_H
