#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    QWidget* w = new QWidget;
    QLabel* label = new QLabel("Study planer",w);
    QPushButton* button = new QPushButton("click to exit", w);
    QVBoxLayout* layout = new QVBoxLayout;
    w->setLayout(layout);
    layout->addWidget(label);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [&]() {
        app.exit();
    });

    w->show();
    return app.exec();
}
