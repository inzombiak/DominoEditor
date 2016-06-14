#include "QTForceSettingsWidget.h"

QTForceSettingsWidget::QTForceSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	if (parent = 0)
		return;

}

QTForceSettingsWidget::~QTForceSettingsWidget()
{
	printf("Force Settings Deleted");
}

void QTForceSettingsWidget::ForceValueChanged(double value)
{
	ForceValueChangedSignal(value);
}