#ifndef QTFORCESETTINGSWIDGET_H
#define QTFORCESETTINGSWIDGET_H

#include <QWidget>
#include "ui_ForceSettingsWidget.h"

class QTForceSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	QTForceSettingsWidget(QWidget *parent = 0);
	~QTForceSettingsWidget();
	void SetForce(double value)
	{
		ui.doubleSpinBox->setValue(value);
	}
public slots:
	void ForceValueChanged(double value);
signals:
	void ForceValueChangedSignal(double value);
private:
	Ui::QTForceSettingsWidget ui;
};

#endif // QTFORCESETTINGSWIDGET_H
