#include <QApplication>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
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

	QGridLayout* sliderLayout = new QGridLayout;
	topLayout->addLayout(sliderLayout);

	QLabel* wLabel = new QLabel("W: 0.0", this);
	sliderLayout->addWidget(wLabel, 0, 0);
	wSlider = new QSlider(Qt::Horizontal, this);
	wSlider->setMinimum(-30);
	wSlider->setMaximum(30);
	wSlider->setValue(0);
	sliderLayout->addWidget(wSlider, 0, 1);

	QLabel* hLabel = new QLabel("H: 0.0", this);
	sliderLayout->addWidget(hLabel, 1, 0);
	hSlider = new QSlider(Qt::Horizontal, this);
	hSlider->setMinimum(-30);
	hSlider->setMaximum(30);
	hSlider->setValue(0);
	sliderLayout->addWidget(hSlider, 1, 1);

	QLabel* gLabel = new QLabel("G: 0.0", this);
	sliderLayout->addWidget(gLabel, 2, 0);
	gSlider = new QSlider(Qt::Horizontal, this);
	gSlider->setMinimum(-30);
	gSlider->setMaximum(30);
	gSlider->setValue(0);
	sliderLayout->addWidget(gSlider, 2, 1);

	sampleBtn = new QPushButton("Randomize", this);
	topLayout->addWidget(sampleBtn);

	connect(wSlider, &QSlider::valueChanged, [=](int v) {
		facadeView->setW(v / 10.0);
		wLabel->setText("W: " + QString::number(v / 10.0)); });
	connect(hSlider, &QSlider::valueChanged, [=](int v) {
		facadeView->setH(v / 10.0);
		hLabel->setText("H: " + QString::number(v / 10.0)); });
	connect(gSlider, &QSlider::valueChanged, [=](int v) {
		facadeView->setG(v / 10.0);
		gLabel->setText("G: " + QString::number(v / 10.0)); });
	connect(sampleBtn, &QPushButton::clicked, [=]() {
		std::normal_distribution<double> nd_wh(0.0, 8.0);
		std::normal_distribution<double> nd_g(0.0, 10.0);
		wSlider->setValue(nd_wh(rng));
		wLabel->setText("W: " + QString::number(wSlider->value() / 10.0));
		hSlider->setValue(nd_wh(rng));
		hLabel->setText("H: " + QString::number(hSlider->value() / 10.0));
		gSlider->setValue(nd_g(rng));
		gLabel->setText("G: " + QString::number(gSlider->value() / 10.0));
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
