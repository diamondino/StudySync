#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFrame>
#include "DataStructures.h"

class TaskCard : public QFrame {
    Q_OBJECT
public:
    // Added groupName parameter
    TaskCard(const Task& task, const QString& groupName, QWidget* parent = nullptr);
};