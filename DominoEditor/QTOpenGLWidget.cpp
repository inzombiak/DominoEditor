#include "QTOpenGLWidget.h"
#include "EventManager.h"
#include "EDCreateObject.h"
#include "EDApplyForce.h"
//#include "ED
#include <QMouseEvent>

QTOpenGLWidget::QTOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_gameStepTimer = 0;
	m_objectSettings = 0;
	m_selectedObjectPhysData = 0;
}

QTOpenGLWidget::~QTOpenGLWidget()
{
	if (m_gameStepTimer)
		delete m_gameStepTimer;

	if (m_objectSettings)
		delete m_objectSettings;

	if (m_selectedObjectPhysData)
		delete m_selectedObjectPhysData;

}

void QTOpenGLWidget::initializeGL()
{
	m_gameEngine.Init();
	m_gameStepTimer = new QTimer(this);
	m_gameEngine.SetScreenSize(width(), height());
	m_gameStepTimer->setInterval(20);
	connect(m_gameStepTimer, SIGNAL(timeout()), this, SLOT(TimerStep()));
	m_gameStepTimer->start();
}
void QTOpenGLWidget::resizeGL(int w, int h)
{

}
void QTOpenGLWidget::paintGL()
{
	m_gameEngine.Draw();
}

void QTOpenGLWidget::TimerStep()
{ 
	m_gameEngine.Step(0.02);
	update();
}

void QTOpenGLWidget::mousePressEvent(QMouseEvent* event)
{

	if (event->button() != Qt::LeftButton)
		return;
	setFocus();
	m_clickX = event->pos().x();
	m_clickY = event->pos().y();

	if (m_altKey)
	{
		if (m_editingMode == EditingMode::CreateObject)
		{
			ObjectCreationData* creationData = new ObjectCreationData();
			//PhysicsDefs::ICreationData*  physData
			creationData->renderCompData = new GameDefs::RenderCompCreationData();
			
			if (m_objectSettings->GetShape() == PhysicsDefs::Box)
			{
				auto boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(m_objectSettings);
				creationData->renderCompData->vertices = CreateBox(glm::vec3(0,0,0), boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);
				creationData->physCompData = new PhysicsDefs::BoxCreationData();
				memcpy(creationData->physCompData,m_objectSettings, sizeof(PhysicsDefs::BoxCreationData));
			}
			else
			{
				auto sphereData = dynamic_cast<PhysicsDefs::SphereCreationData*>(m_objectSettings);
				creationData->physCompData = new PhysicsDefs::SphereCreationData();
				memcpy(creationData->physCompData, m_objectSettings, sizeof(PhysicsDefs::SphereCreationData));
				creationData->renderCompData->vertices = CreateSphere(glm::vec3(0, 0, 0), sphereData->sphereRadius);
			}
				

			creationData->renderCompData->drawType = GL_TRIANGLES;
			creationData->renderCompData->color.push_back(glm::vec3(0.0f, 0.5f, 1.f));

			EDCreateObject* createObjectED = new EDCreateObject(creationData);
			EventManager::GetInstance()->QueueEvent(EventDefs::EventType::CREATE_OBJECT, createObjectED, false);
		}
		else if (m_editingMode == EditingMode::ApplyForce)
		{
			EDApplyForce* applyForceED = new EDApplyForce(m_clickX, m_clickY, m_impulseForce);
			EventManager::GetInstance()->QueueEvent(EventDefs::EventType::APPLY_FORCE, applyForceED, false);
		}
	}
	else if (m_ctrlKey)
	{
		Object* selectedObj = NULL;

//		EDSelectObjectClick* selectClick = new EDSelectObjectClick(m_clickX, m_clickY, selectedObj);
	}
}

void QTOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
		return;

	m_clickX = event->pos().x();
	m_clickY = event->pos().y();
}

void QTOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	Qt::MouseButton mb = event->button();

	if (event->buttons() != Qt::LeftButton)
		return;

	m_xRotate += m_mouseSpeed * 2 * float(m_clickX - event->pos().x());
	m_yRotate += m_mouseSpeed * 2 * float(m_clickY - event->pos().y());
	m_clickX = event->pos().x();
	m_clickY = event->pos().y();
	m_gameEngine.UpdateCameraRotation(m_xRotate, m_yRotate);
}

void QTOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
	GameDefs::GameKey key;
	switch (event->key())
	{
	case Qt::Key_D:
		key = GameDefs::GameKey::D;
		break;
	case Qt::Key_A:
		key = GameDefs::GameKey::A;
		break;
	case Qt::Key_S:
		key = GameDefs::GameKey::S;
		break;
	case Qt::Key_W:
		key = GameDefs::GameKey::W;
		break;
	case Qt::Key_Delete:
		key = GameDefs::GameKey::Delete;
		break;
	case Qt::Key_Alt:
		key = GameDefs::GameKey::Alt;
		m_altKey = true;
		break;
	case Qt::Key_Control:
		key = GameDefs::GameKey::Ctrl;
		m_ctrlKey = true;
		break;
	default:
		return;
	}
	m_gameEngine.SetKey(key, true);
}

void QTOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
	GameDefs::GameKey key;
	switch (event->key())
	{
	case Qt::Key_D:
		key = GameDefs::GameKey::D;
		break;
	case Qt::Key_A:
		key = GameDefs::GameKey::A;
		break;
	case Qt::Key_S:
		key = GameDefs::GameKey::S;
		break;
	case Qt::Key_W:
		key = GameDefs::GameKey::W;
		break;
	case Qt::Key_Delete:
		key = GameDefs::GameKey::Delete;
		break;
	case Qt::Key_Alt:
		key = GameDefs::GameKey::Alt;
		m_altKey = false;
		break;
	case Qt::Key_Control:
		key = GameDefs::GameKey::Ctrl;
		m_ctrlKey = false;
		break;
	default:
		return;
	}
	m_gameEngine.SetKey(key, false);
}

void QTOpenGLWidget::GenerateObjects(std::vector<PhysicsDefs::ICreationData*> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		PhysicsDefs::BoxCreationData*  physData = dynamic_cast<PhysicsDefs::BoxCreationData*>(data[i]);
		if (!physData)
			continue;
		ObjectCreationData* creationData = new ObjectCreationData();
		creationData->physCompData = new PhysicsDefs::BoxCreationData(*physData);

		creationData->renderCompData = new GameDefs::RenderCompCreationData();
		creationData->renderCompData->color.push_back(glm::vec3(0.f, 0.f, 1.f));
		creationData->renderCompData->drawType = GL_TRIANGLES;
		creationData->renderCompData->vertices = CreateBox(glm::vec3(0.f, 0.f, 0.f), physData->boxDimensions[0], physData->boxDimensions[1], physData->boxDimensions[2]);

		EDCreateObject* createObjectED = new EDCreateObject(creationData);

		EventManager::GetInstance()->QueueEvent(EventDefs::EventType::CREATE_OBJECT, createObjectED, false);

		delete data[i];
		data[i] = 0;
	}
	
	data.clear();
}