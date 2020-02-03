#include "facadeView.hpp"
#include <QPainter>

FacadeView::FacadeView(QWidget* parent) : QWidget(parent),
	w(0.0),
	h(0.0),
	g(0.0) {}

void FacadeView::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	double scale = std::min(width() / (double)sz, height() / (double)sz);
	painter.translate(width() / 2.0, height() / 2.0);
	painter.scale(scale, scale);
	painter.translate(-sz / 2.0, -sz / 2.0);

	// Draw background
	painter.fillRect(0, 0, sz, sz, QColor(255, 255, 255));

	// Go to normalized facade coords
	painter.scale((double)sz, (double)sz);

	double ww = (w + 3) / 6;
	double wh = (h + 3) / 6;

	// Draw windows
	for (int r = 0; r < rows; r++) {
		painter.save();
		painter.translate(0.0, (double)r / rows);
		painter.scale(1.0, 1.0 / rows);

		for (int c = 0; c < cols; c++) {
			// Get column x offset based on grouping
			double cm2 = (c % 2) * 2 - 1;
			double cm3 = 1 - (c % 3);
			double cx;
			if (g < 0.0)
				cx = cm2 * g * (1.0 - ww) / 6.0;
			else
				cx = cm3 * g * (1.0 - ww) / 3.0;

			painter.save();
			painter.translate((double)c / cols, 0.0);
			painter.scale(1.0 / cols, 1.0);
			painter.translate(cx, 0.0);

			painter.translate(0.5, 0.5);
			QRectF fillRect(-ww / 2.0, -wh / 2.0, ww, wh);
			painter.fillRect(fillRect, QColor(0, 0, 0, 255));

			painter.restore();
		}

		painter.restore();
	}
}
