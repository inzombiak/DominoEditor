#define _USE_MATH_DEFINES

#include "QTGridView.h"
#include "QTGeneratorCell.h"

#include <cmath>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <glm\glm.hpp>
#include <glm\gtx\vector_angle.hpp>


QTGridView::QTGridView(QWidget *parent)
	: QGraphicsView(parent)
{
	m_scene = new QGraphicsScene(this);
	setScene(m_scene);
}

QTGridView::~QTGridView()
{
	Clear();
}

void QTGridView::Clear()
{
	m_scene->clear();
	for (unsigned int i = 0; i < m_properties.columns; ++i)
	{
		for (unsigned int j = 0; j < m_properties.rows; ++j)
		{
			delete m_gridMatrix[i][j];
		}
	}
	m_gridMatrix.clear();
}

void QTGridView::InitGrid(QTGridView::GridProperties properties)
{
	m_scene->clear();
	m_gridMatrix.clear();
	m_properties = properties;

	double x, y;
	double w = m_properties.cellWidth = m_properties.cellWidth * 10;
	double h = m_properties.cellLength = m_properties.cellLength * 10;// +m_properties.heightSpacing * m_properties.cellHeight * 20;
	double gridSize = std::max(m_properties.cellWidth, m_properties.cellLength);
	double gridWidth = gridSize*m_properties.columns;
	double gridHeight = gridSize*m_properties.rows;
	m_gridSize = gridSize;
	m_scene->setSceneRect(0, 0, gridWidth, gridHeight);

	m_properties.cellHeight *= 10;
	m_xSpacingFinal = w + m_properties.xSpacing * m_properties.cellWidth;
	m_zSpacingFinal = h + m_properties.zSpacing * m_properties.cellLength;
	QTGeneratorCell* cell;

	double gridStartX = -gridSize / 2 + w / 2, gridStartY = -gridSize / 2 + h / 2;

	for (unsigned int i = 0; i <= m_properties.columns; ++i)
	{
		m_scene->addLine(gridStartX + i * gridSize, gridStartY, gridStartX + i * gridSize, gridHeight,QPen(Qt::black, 2));
	}

	for (unsigned int j = 0; j <= m_properties.rows; ++j)
	{
		m_scene->addLine(gridStartX, gridStartY + j*gridSize, gridWidth, gridStartY + j*gridSize, QPen(Qt::black, 2));
	}
	for (unsigned int i = 0; i < m_properties.columns; ++i)
	{
		std::vector<QTGeneratorCell*> row;

		for (unsigned int j = 0; j < m_properties.rows; ++j)
		{
			x = i * gridSize;
			y = j * gridSize;

			cell = new QTGeneratorCell(x, y, w, h);
			//cell->SetFlag(QGraphicsItem::ItemIsSelectable);
			cell->SetOrigin(QPointF(x + w / 2, y + h / 2));
			
			cell->AssignScene(m_scene);

			row.push_back(cell);
		}
		m_gridMatrix.push_back(row);
	}
}

std::vector<DominoTransform> QTGridView::SaveGrid()
{
	std::vector<DominoTransform> result;

	DominoTransform trans;
	QPointF pos;
	for (unsigned int i = 0; i < m_properties.columns; ++i)
	{
		for (unsigned int j = 0; j < m_properties.rows; ++j)
		{
			if (!m_gridMatrix[i][j]->IsActive())
				continue;

			if (m_gridMatrix[i][j]->IsInitial())
				trans.isMain = true;

			pos = m_gridMatrix[i][j]->GetPosition();
			QPointF scenePos = mapFromScene(pos);

			trans.x = pos.x();
			trans.z = pos.y();
			trans.angle = m_gridMatrix[i][j]->GetRotation();

			result.push_back(trans);
		}
	}

	return result;
}

void QTGridView::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_selectedRect || event->buttons() != Qt::LeftButton)
		return;

	int mouseX = event->pos().x();
	int mouseY = event->pos().y();
	int posX = pos().x();
	int posY = pos().y();

	double angle = m_selectedRect->rotation();

	glm::vec2 u(m_prevMouseX - m_clickX, m_prevMouseY - m_clickY);
	glm::vec2 v(mouseX - m_clickX, mouseY - m_clickY);
	double rotation = (glm::orientedAngle(glm::normalize(u), glm::normalize(v))) * 180 / 3.14;
	angle += rotation;
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;
	
	m_selectedRect->setRotation(angle);

	m_prevMouseX = mouseX;
	m_prevMouseY = mouseY;
	
	double sceneWidth = m_scene->width();
	double sceneHeight = m_scene->height();

	auto selectedPos = m_selectedRect->transformOriginPoint();

	printf("Rotation:%lf \n", rotation);

	int column = selectedPos.x() / m_gridSize;
	int row = selectedPos.y() /  m_gridSize;
	angle += 90;

	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;

	//CalibrateGrid(column, row, angle, rotation > 0);
}

void QTGridView::mousePressEvent(QMouseEvent* event)
{
	if(event->button() != Qt::LeftButton)
		return;

	m_prevMouseY = m_clickX = event->pos().x();
	m_prevMouseX = m_clickY = event->pos().y();
	
	QPointF scenePos = mapToScene(event->pos());

	m_selectedRect =(QGraphicsRectItem*) m_scene->itemAt(scenePos, transform());
	if (!m_selectedRect)
	{
		m_selectedRect = 0;
		return;
	}

	auto selectedPos = m_selectedRect->transformOriginPoint();
	int column = selectedPos.x() / m_gridSize;
	int row = selectedPos.y() / m_gridSize;
	
	QTGeneratorCell* selectedCell = m_gridMatrix[column][row];
	if (!selectedCell->IsActive())
	{
		selectedCell->SetIsActive(true);
	}
	else
	{
		if (!selectedCell->IsInitial())
		{
			selectedCell->SetIsInitial(true);
			if (m_initialCellIndicies.x() != -1)
			{
				m_gridMatrix[m_initialCellIndicies.x()][m_initialCellIndicies.y()]->SetIsInitial(false);
				m_gridMatrix[m_initialCellIndicies.x()][m_initialCellIndicies.y()]->SetIsActive(true);
			}

			m_initialCellIndicies.setX(column);
			m_initialCellIndicies.setY(row);
		}
		else
		{
			m_selectedRect = 0;
			selectedCell->SetIsActive(false);
			selectedCell->SetIsInitial(false);
			m_initialCellIndicies.setX(-1);
			m_initialCellIndicies.setY(-1);
		}
		
	}
}

void QTGridView::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_selectedRect)
		m_selectedRect = 0;

	for (unsigned int i = 0; i < m_properties.columns; ++i)
	{
		for (unsigned int j = 0; j < m_properties.rows; ++j)
		{
			m_gridMatrix[i][j]->SavePosition();
		}
	}
}

void QTGridView::CalibrateGrid(int column, int row, double angle, bool isClockwise)
{

	double angleRad = angle * M_PI / 180;

	double angleSin = sin(angleRad);
	double angleCos = cos(angleRad);

	int rowIncrement, columnIncrement;

	if (angleSin < 0)
		rowIncrement = -1;
	else
		rowIncrement = std::ceil(angleSin);

	if (angleCos < 0)
		columnIncrement = -1;
	else
		columnIncrement = std::ceil(angleCos);

	double xHeightIncrement = m_properties.heightSpacing * m_properties.cellHeight * angleCos;
	double zHeightIncrement = m_properties.heightSpacing * m_properties.cellHeight * angleCos;

	QPointF rectPos;

	//printf("A:%lf, RI:%i, CI:%i , XI:%lf, ZI:%lf \n", angle, rowIncrement, columnIncrement, xHeightIncrement, zHeightIncrement);

	if (!isClockwise)
		xHeightIncrement *= -1;
	/*for (int i = column; i < m_properties.columns && i >= 0 && columnIncrement != 0; i += columnIncrement)
	{
		for (int j = row; j < m_properties.rows && j >= 0 && rowIncrement != 0; j += rowIncrement)
		{
			if (i == column && j == row)
				continue;
			rectPos = m_gridMatrix[i][j]->scenePos();
			m_gridMatrix[i][j]->setPos(rectPos.rx() + xHeightIncrement, rectPos.ry() + zHeightIncrement);
		}
	}*/

	for (int i = 0; i < m_properties.columns; i++)
	{
		//for (int j = 0; j < m_properties.rows; j++)
		//{
			m_gridMatrix[i][0]->ResetPosition();
			if (i == column)//&& j == row)
				continue;
			//printf("Column:%i, Row:%i, PosX:%lf, PosY:%lf ICW?:%d \n", i, j, rectPos.x(), rectPos.y(), isClockwise);

			m_gridMatrix[i][0]->Move(xHeightIncrement, 0);
		//}
	}
}