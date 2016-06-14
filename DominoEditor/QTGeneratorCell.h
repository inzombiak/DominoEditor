#ifndef QTGENERATORCELL_H
#define QTGENERATORCELL_H

#include <QGraphicsRectItem>

class QTGeneratorCell
{
public:
	QTGeneratorCell(double x, double y, double w, double h);
	~QTGeneratorCell();
	
	void SetFlag(QGraphicsItem::GraphicsItemFlag flag);

	void SetOrigin(QPointF newOrigin);
	const QPointF& GetPosition() const;
	void Move(double dx, double dy);
	void SavePosition();

	void SetRotation(double angle);
	double GetRotation() const;
	void Rotate(double amount);

	void AssignScene(QGraphicsScene* scene);

	bool IsActive() const
	{
		return m_isActive;
	}
	void SetIsActive(bool value)
	{
		m_isActive = value;
		if (m_isActive)
			m_graphicsRect->setBrush(m_activeFill);
		else
			m_graphicsRect->setBrush(m_inactiveFill);
	}

	void SetIsInitial(bool value)
	{
		m_isInitial = value;
		if (m_isInitial)
			m_graphicsRect->setBrush(m_initialFill);
		else
			m_graphicsRect->setBrush(m_inactiveFill);
	}
	bool IsInitial() const
	{
		return m_isInitial;
	}

	void ResetPosition();

private:
	bool m_isActive;
	bool m_isInitial;
	QPointF m_defaultPos;
	static QBrush m_activeFill;
	static QBrush m_initialFill;
	static QBrush m_inactiveFill;
	QGraphicsRectItem* m_graphicsRect;
};

#endif // QTGENERATORCELL_H
