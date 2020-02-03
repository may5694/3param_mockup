#include <QApplication>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QFormLayout>
#include "app.hpp"
#include <iostream>

App::App(QWidget* parent) : QWidget(parent) {
	// Initialize random number generator
	std::random_device rd;
	rng = std::mt19937(rd());

	init();
}

void App::keyReleaseEvent(QKeyEvent* e) {
	switch (e->key()) {
	case Qt::Key_Escape:
		QApplication::quit();
		break;
	default:
		QWidget::keyReleaseEvent(e);
		break;
	}
}

void App::init() {
	setWindowTitle("3-Param Mockup");

	QVBoxLayout* topLayout = new QVBoxLayout;
	setLayout(topLayout);

	facadeView = new FacadeView(this);
	topLayout->addWidget(facadeView);

	QFormLayout* sliderLayout = new QFormLayout;
	topLayout->addLayout(sliderLayout);

	wSlider = new QSlider(Qt::Horizontal, this);
	wSlider->setMinimum(-30);
	wSlider->setMaximum(30);
	wSlider->setValue(0);
	sliderLayout->addRow("W:", wSlider);

	hSlider = new QSlider(Qt::Horizontal, this);
	hSlider->setMinimum(-30);
	hSlider->setMaximum(30);
	hSlider->setValue(0);
	sliderLayout->addRow("H:", hSlider);

	gSlider = new QSlider(Qt::Horizontal, this);
	gSlider->setMinimum(-30);
	gSlider->setMaximum(30);
	gSlider->setValue(0);
	sliderLayout->addRow("G:", gSlider);

	sampleBtn = new QPushButton("Randomize", this);
	topLayout->addWidget(sampleBtn);

	connect(wSlider, &QSlider::valueChanged, [=](int v) { facadeView->setW(v / 10.0); });
	connect(hSlider, &QSlider::valueChanged, [=](int v) { facadeView->setH(v / 10.0); });
	connect(gSlider, &QSlider::valueChanged, [=](int v) { facadeView->setG(v / 10.0); });
	connect(sampleBtn, &QPushButton::clicked, [=]() {
		std::normal_distribution<double> nd_wh(0.0, 8.0);
		std::normal_distribution<double> nd_g(0.0, 10.0);
		wSlider->setValue(nd_wh(rng));
		hSlider->setValue(nd_wh(rng));
		gSlider->setValue(nd_g(rng));
	});
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	// Create the application and show the window
	App a;
	a.show();

	// Run the event loop
	return app.exec();
}
