#ifndef QTBULLETOBJECTSETTINGSWIDGET_H
#define QTBULLETOBJECTSETTINGSWIDGET_H
#include <array>

#include <QWidget>
#include "ui_QTBulletObjectSettingsWidget.h"

enum BulletObjectType
{
	Box,
	Sphere
};

struct PhysicsSettings
{
	std::string objectName;
	BulletObjectType shapeType;
	double sphereRadius;
	std::array<double, 3> boxDimensions;
	std::array<double, 3> rotationAngles;
	std::array<double, 3> msPosition;
	double mass;
	double friction;
	double rollingFriction;
};

class QTBulletObjectSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	QTBulletObjectSettingsWidget(QWidget *parent = 0);
	~QTBulletObjectSettingsWidget();
	
	PhysicsSettings GetSettings();

public slots:
	void SettingsChanged();
signals:
	void SettingsChangedSignal(PhysicsSettings settings);
private:
	Ui::QTBulletObjectSettingsWidget ui;
};

#endif // QTBULLETOBJECTSETTINGSWIDGET_H
