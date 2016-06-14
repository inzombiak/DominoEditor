#include "QTGeneratorCell.h"

#include <QGraphicsScene>

QTGeneratorCell::QTGeneratorCell(double x, double y, double w, double h)
{
	m_graphicsRect = new QGraphicsRectItem();

	QPen outlinePen(Qt::darkCyan);
	outlinePen.setWidth(2);
	m_graphicsRect->setPen(outlinePen);
	m_graphicsRect->setRect(x, y, w, h);

	SetIsActive(false);
	SetIsInitial(false);
}

QTGeneratorCell::~QTGeneratorCell()
{

}

void QTGeneratorCell::SetFlag(QGraphicsItem::GraphicsItemFlag flag)
{
	m_graphicsRect->setFlag(flag);
}

void QTGeneratorCell::SetOrigin(QPointF newOrigin)
{
	m_graphicsRect->setTransformOriginPoint(newOrigin);
}

const QPointF& QTGeneratorCell::GetPosition() const
{
	return m_graphicsRect->mapToScene(m_graphicsRect->boundingRect().center());
}

void QTGeneratorCell::Move(double dx, double dy)
{
	m_graphicsRect->moveBy(dx, dy);
}

void QTGeneratorCell::SavePosition()
{
	m_defaultPos = m_graphicsRect->pos();
}

void QTGeneratorCell::SetRotation(double angle)
{
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;

	m_graphicsRect->setRotation(angle);
}

void QTGeneratorCell::ResetPosition()
{
	m_graphicsRect->setPos(m_defaultPos);
}
double QTGeneratorCell::GetRotation() const
{
	return m_graphicsRect->rotation();
}

void QTGeneratorCell::Rotate(double amount)
{
	SetRotation(m_graphicsRect->rotation() + amount);
}

void QTGeneratorCell::AssignScene(QGraphicsScene* scene)
{
	scene->addItem(m_graphicsRect);
	
}

QBrush QTGeneratorCell::m_activeFill = QBrush(Qt::blue);
QBrush QTGeneratorCell::m_initialFill = QBrush(Qt::red);
QBrush QTGeneratorCell::m_inactiveFill = QBrush(Qt::NoBrush);