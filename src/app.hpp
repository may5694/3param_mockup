#ifndef APP_HPP
#define APP_HPP

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <random>
#include "facadeView.hpp"

class App : public QWidget {
	Q_OBJECT
public:
	App(QWidget* parent = NULL);

protected:
	void keyReleaseEvent(QKeyEvent* e);

private:
	FacadeView* facadeView;
	QSlider* wSlider;
	QSlider* hSlider;
	QSlider* gSlider;
	QPushButton* sampleBtn;

	std::mt19937 rng;		// Random number generator

	void init();
};

#endif
