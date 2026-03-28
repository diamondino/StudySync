#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "ui/ClientState.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
private:
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;

    QWidget* sidebar;
    QPushButton* btnDashboard;
    QPushButton* btnFocus;
    QPushButton* btnGroups;
    QPushButton* btnAiTutor;
    QPushButton* btnLogout;

    QWidget* topbar;
    QLabel* topbarTitle;

    void setupUi();
    void setupSidebar();
    void setupTopbar();
};