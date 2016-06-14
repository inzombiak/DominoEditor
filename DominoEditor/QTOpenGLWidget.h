#ifndef QTOPENGLWIDGET_H
#define QTOPENGLWIDGET_H
#include "Game.h"
#include "PhysicsDefs.h"
#include <QOpenGLWidget>
#include <QTimer>
#include <map>

enum EditingMode
{
	CreateObject,
	ApplyForce
};


class QTOpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	QTOpenGLWidget(QWidget *parent = 0);
	~QTOpenGLWidget();

	void SetImpulseForse(float force)
	{
		m_impulseForce  = force;

	}
	const float GetImpulseForce() const
	{
		return m_impulseForce;
	}
	
	void SetEditingMode(EditingMode mode)
	{
		m_editingMode = mode;
	}

	void SetObjectSettings(PhysicsDefs::ICreationData* settings)
	{
		m_objectSettings = settings;
	}
	PhysicsDefs::ICreationData* GetObjectSettings()
	{
		return m_objectSettings;
	}

	void GenerateObjects(std::vector<PhysicsDefs::ICreationData*> data);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

public slots:
	void TimerStep();

private:
	void RetrivedPhysicsData(IEventData*);

	float m_yRotate = 0.f;
	float m_xRotate = 3.14f;
	float m_mouseSpeed = 0.005f;
	int m_clickX, m_clickY;
	float m_impulseForce;
	Game m_gameEngine;
	PhysicsDefs::ICreationData*  m_selectedObjectPhysData;
	QTimer* m_gameStepTimer;
	PhysicsDefs::ICreationData*  m_objectSettings;
	EditingMode m_editingMode;
	bool m_altKey = false, m_ctrlKey = false;
};

#endif // QTOPENGLWIDGET_H
