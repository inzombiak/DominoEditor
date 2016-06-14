#include "dominoeditor.h"
#include "QTForceSettingsWidget.h"
#include "QTBulletObjectSettingsWidget.h"
#include "QTDominoGeneratorPopup.h"
#include "EventManager.h"

#include "glm\gtc\quaternion.hpp"

DominoEditor::DominoEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_forceSettingsWidget = ui.forceSettings;
	m_objectSettingsWidget = ui.objectSettings;
	
	QObject::connect(m_forceSettingsWidget, SIGNAL(ForceValueChangedSignal(double)), this, SLOT(ForceSpinBoxValueChanged(double)));
	QObject::connect(m_objectSettingsWidget, SIGNAL(SettingsChangedSignal(PhysicsSettings)), this, SLOT(BulletObjectSettingsChanged(PhysicsSettings)));
	m_objectSettingsWidget->SettingsChanged();
}

DominoEditor::~DominoEditor()
{

}

void DominoEditor::ShowForceEditor()
{
	ui.stackedWidget->setCurrentIndex(0);
	m_forceSettingsWidget->SetForce(ui.openGLWidget->GetImpulseForce());
	ui.openGLWidget->SetEditingMode(EditingMode::ApplyForce);
}

void DominoEditor::ForceSpinBoxValueChanged(double value)
{
	ui.openGLWidget->SetImpulseForse(value);
}
void DominoEditor::ShowBulletObjectCreator()
{
	ui.stackedWidget->setCurrentIndex(1);
	ui.openGLWidget->SetEditingMode(EditingMode::CreateObject);
}

void DominoEditor::BulletObjectSettingsChanged(PhysicsSettings settings)
{	
	if (settings.shapeType == BulletObjectType::Box)
	{

		auto gameSettings = new PhysicsDefs::BoxCreationData();
		gameSettings->boxDimensions = settings.boxDimensions;
		gameSettings->msPosition = settings.msPosition;
		gameSettings->rotationAngles = settings.rotationAngles;
		gameSettings->mass = settings.mass;
		gameSettings->friction = settings.friction;
		gameSettings->rollingFriction = settings.rollingFriction;

		ui.openGLWidget->SetObjectSettings(gameSettings);
	}
	else
	{
		auto gameSettings = new PhysicsDefs::SphereCreationData();
		gameSettings->sphereRadius = settings.sphereRadius;
		gameSettings->msPosition = settings.msPosition;
		gameSettings->rotationAngles = settings.rotationAngles;
		gameSettings->mass = settings.mass;
		gameSettings->friction = settings.friction;
		gameSettings->rollingFriction = settings.rollingFriction;

		ui.openGLWidget->SetObjectSettings(gameSettings);
	}
	
}

void DominoEditor::ShowDominoPatternEditor()
{
	QTDominoGeneratorPopup* generator = new QTDominoGeneratorPopup();
	QObject::connect(generator, SIGNAL(SavePatternSignal(std::vector<DominoTransform>, int, int, double, double)), this, SLOT(GenerateObjects(std::vector<DominoTransform>, int, int, double, double)));
	generator->show();
}

void DominoEditor::GenerateObjects(std::vector<DominoTransform> transforms, int numColumns, int numRows, double xSpacing, double zSpacing)
{
	std::vector<PhysicsDefs::ICreationData*> result;
	PhysicsDefs::ICreationData* gameSettings = ui.openGLWidget->GetObjectSettings();
	PhysicsDefs::ICreationData* element;

	//for (unsigned int i = 0; i < transforms.size(); ++i)
	//{
	//	element = gameSettings->clone();

	//	gameSettings->msPosition[0] = transforms[i].x / 10;
	//	gameSettings->msPosition[2] = transforms[i].z / 10;
	//				
	//	gameSettings->rotationAngles[0] = 0;
	//	gameSettings->rotationAngles[1] = transforms[i].angle;
	//	gameSettings->rotationAngles[2] = 0;

	//	result.push_back(element);
	//}

	ui.openGLWidget->GenerateObjects(result);
}