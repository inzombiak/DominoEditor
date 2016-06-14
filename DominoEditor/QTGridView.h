#ifndef QTGRIDVIEW_H
#define QTGRIDVIEW_H

#include <QGraphicsView>
#include <vector>
struct DominoTransform
{
	double x;
	double z;
	double angle;
	bool isMain = false;

};

class QTGeneratorCell;
class QTGridView : public QGraphicsView
{
	Q_OBJECT

public:

	struct GridProperties
	{
		GridProperties() {} ;
		GridProperties(int newColumns, int newRows, double newXSpacing, double newZSpacing,
			double newHeightSpacing, double newCellWidth, double newCellLength, double newCellHeight)
		{
			columns = newColumns;
			rows = newRows;

			xSpacing = newXSpacing;
			zSpacing = newZSpacing;
			heightSpacing = newHeightSpacing;

			cellWidth = newCellWidth;
			cellLength = newCellLength;
			cellHeight = newCellHeight;
		}

		int columns;
		int rows;
		
		double xSpacing;
		double zSpacing;
		double heightSpacing;

		double cellWidth;
		double cellLength;
		double cellHeight;
	};

	QTGridView(QWidget *parent);
	~QTGridView();

	void InitGrid(GridProperties properties);
	std::vector<DominoTransform> SaveGrid();
	const GridProperties& GetProperties() const
	{
		return m_properties;
	}
protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	void CalibrateGrid(int column, int row, double angle, bool isClockwise);
	void Clear();

	int m_clickX, m_clickY;
	int m_prevMouseX, m_prevMouseY;
	double m_xSpacingFinal, m_zSpacingFinal, m_gridSize;
	std::vector<std::vector<QTGeneratorCell*>> m_gridMatrix;
	QPoint m_initialCellIndicies;
	QGraphicsRectItem* m_selectedRect;
	GridProperties m_properties;
	QGraphicsScene* m_scene;
};

#endif // QTGRIDVIEW_H
