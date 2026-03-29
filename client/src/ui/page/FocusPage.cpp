#include "ui/page/FocusPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/widget/GroupCard.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include "LanguageManager.h"

FocusPage::FocusPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QGroupBox* group = new QGroupBox(LanguageManager::tr("focus.timer_title"));
    QVBoxLayout* groupLayout = new QVBoxLayout(group);
    groupLayout->setAlignment(Qt::AlignCenter);

    QComboBox* taskSelect = new QComboBox();
    taskSelect->addItem("Review Cell Division Notes");

    QLabel* timerLabel = new QLabel("25:00");
    QFont timerFont = timerLabel->font();
    timerFont.setPointSize(48);
    timerLabel->setFont(timerFont);
    timerLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(new QPushButton(LanguageManager::tr("focus.start")));
    btnLayout->addWidget(new QPushButton(LanguageManager::tr("focus.pause")));
    btnLayout->addWidget(new QPushButton(LanguageManager::tr("focus.reset")));

    groupLayout->addWidget(taskSelect);
    groupLayout->addWidget(timerLabel);
    groupLayout->addLayout(btnLayout);

    layout->addWidget(group);
}
