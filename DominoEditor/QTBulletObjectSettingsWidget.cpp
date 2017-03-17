#include "QTBulletObjectSettingsWidget.h"
#include "tinyxml2.h"

using namespace tinyxml2;

QTBulletObjectSettingsWidget::QTBulletObjectSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//SettingsChanged(); 
}

QTBulletObjectSettingsWidget::~QTBulletObjectSettingsWidget()
{

}

PhysicsSettings QTBulletObjectSettingsWidget::GetSettings()
{
	PhysicsSettings settings;

	std::string shapeType = ui.shapeType->currentText().toStdString();

	if (shapeType.compare("Box") == 0)
	{
		settings.shapeType = Box;
		settings.boxDimensions[0] = ui.width->value();
		settings.boxDimensions[1] = ui.height->value();
		settings.boxDimensions[2] = ui.length->value();
	}
	else
	{
		settings.shapeType = Sphere;
		settings.sphereRadius = ui.radius->value();
	}

	settings.rotationAngles[0] = ui.rotationX->value();
	settings.rotationAngles[1] = ui.rotationY->value();
	settings.rotationAngles[2] = ui.rotationZ->value();


	settings.msPosition[0] = ui.positionX->value();
	settings.msPosition[1] = ui.positionY->value();
	settings.msPosition[2] = ui.positionZ->value();

	settings.mass = ui.mass->value();
	settings.friction = ui.friction->value();
	settings.rollingFriction = ui.rollingFriction->value();

	return settings;
}

void QTBulletObjectSettingsWidget::SettingsChanged()
{
	
	SettingsChangedSignal(GetSettings());
}