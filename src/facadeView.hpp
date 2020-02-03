#ifndef FACADEVIEW_HPP
#define FACADEVIEW_HPP

#include <QWidget>

class FacadeView : public QWidget {
	Q_OBJECT
public:
	FacadeView(QWidget* parent = NULL);

	QSize minimumSizeHint() const { return QSize(sz, sz); }
	QSize sizeHint() const { return QSize(sz * 2, sz * 2); }

public slots:
	void setW(double w) { this->w = w; update(); }
	void setH(double h) { this->h = h; update(); }
	void setG(double g) { this->g = g; update(); }

protected:
	const int sz = 128;		// Pixel dimensions of canvas
	const int rows = 6;		// Rows and cols of windows
	const int cols = 6;

	double w, h, g;			// Layout parameters

	void paintEvent(QPaintEvent* e);
};

#endif
