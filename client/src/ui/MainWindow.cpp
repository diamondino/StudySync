#include "ui/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    this->setWindowTitle("StudySync");
    this->resize(1000, 700);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    setupSidebar();

    QWidget* rightSideContainer = new QWidget(this);
    QVBoxLayout* rightSideLayout = new QVBoxLayout(rightSideContainer);
    rightSideLayout->setContentsMargins(0, 0, 0, 0);

    setupTopbar();

    rightSideLayout->addWidget(topbar);
    rightSideLayout->addStretch();

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(rightSideContainer);
}

void MainWindow::setupSidebar() {
    sidebar = new QWidget(this);
    sidebar->setFixedWidth(200);

    QVBoxLayout* layout = new QVBoxLayout(sidebar);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel* logoLabel = new QLabel("📚StudySync", this);
    QFont logoFont = logoLabel->font();
    logoFont.setBold(true);
    logoFont.setPointSize(23);
    logoLabel->setFont(logoFont);

    layout->addWidget(logoLabel);
    layout->addSpacing(5);

    btnDashboard = new QPushButton("Dashboard", this);
    btnFocus = new QPushButton("Focus Session", this);
    btnGroups = new QPushButton("Study Groups", this);
    btnAiTutor = new QPushButton("AI Tutor", this);

    btnDashboard->setCheckable(true);
    btnFocus->setCheckable(true);
    btnGroups->setCheckable(true);
    btnAiTutor->setCheckable(true);
    btnDashboard->setChecked(true);

    layout->addWidget(btnDashboard);
    layout->addWidget(btnFocus);
    layout->addWidget(btnGroups);
    layout->addWidget(btnAiTutor);
    layout->addStretch();

    btnLogout = new QPushButton("Logout", this);
    layout->addWidget(btnLogout);
}

void MainWindow::setupTopbar() {
    topbar = new QWidget(this);
    topbar->setFixedHeight(50);

    QHBoxLayout* layout = new QHBoxLayout(topbar);
    layout->setContentsMargins(0, 0, 0, 0);

    topbarTitle = new QLabel("Dashboard", this);
    QFont titleFont = topbarTitle->font();
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    topbarTitle->setFont(titleFont);

    layout->addWidget(topbarTitle);
    layout->addStretch();
    layout->addWidget(new QPushButton("Create Task", this));
    layout->addWidget(new QPushButton("Notifications", this));
    layout->addWidget(new QLabel(ClientState::getUser()->getUsername().c_str(), this));
}