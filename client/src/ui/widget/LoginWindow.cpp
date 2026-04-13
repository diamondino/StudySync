#include "ui/widget/LoginWindow.h"

#include "LanguageManager.h"
#include <QMetaObject>

LoginWindow::LoginWindow(std::shared_ptr<ServerAPI> api, QWidget *parent)
    : QDialog(parent), serverApi(api) {
    setupUi();
}

void LoginWindow::setupUi() {
    this->setWindowTitle(LanguageManager::tr("app.auth_title")); 
    this->setFixedSize(350, 250);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);

    QWidget* loginTab = new QWidget(this);
    QFormLayout* loginLayout = new QFormLayout(loginTab);
    
    loginUsernameInput = new QLineEdit(this);
    loginPasswordInput = new QLineEdit(this);
    loginPasswordInput->setEchoMode(QLineEdit::Password);
    loginBtn = new QPushButton(LanguageManager::tr("auth.login_btn"), this);

    loginLayout->addRow(LanguageManager::tr("auth.username"), loginUsernameInput);
    loginLayout->addRow(LanguageManager::tr("auth.password"), loginPasswordInput);
    loginLayout->addWidget(loginBtn);

    QWidget* registerTab = new QWidget(this);
    QFormLayout* regLayout = new QFormLayout(registerTab);
    
    regUsernameInput = new QLineEdit(this);
    regEmailInput = new QLineEdit(this);
    regPasswordInput = new QLineEdit(this);
    regPasswordInput->setEchoMode(QLineEdit::Password);
    regBtn = new QPushButton(LanguageManager::tr("auth.register_btn"), this);

    regLayout->addRow(LanguageManager::tr("auth.username"), regUsernameInput);
    regLayout->addRow(LanguageManager::tr("auth.email"), regEmailInput);
    regLayout->addRow(LanguageManager::tr("auth.password"), regPasswordInput);
    regLayout->addWidget(regBtn);

    tabWidget->addTab(loginTab, LanguageManager::tr("auth.tab_login"));
    tabWidget->addTab(registerTab, LanguageManager::tr("auth.tab_register"));

    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(statusLabel);

    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(regBtn, &QPushButton::clicked, this, &LoginWindow::handleRegistration);
}

void LoginWindow::handleLogin() {
    QString username = loginUsernameInput->text();
    QString password = loginPasswordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        statusLabel->setStyleSheet("color: red;");
        statusLabel->setText("Please enter username and password.");
        return;
    }

    loginBtn->setEnabled(false);
    statusLabel->setStyleSheet("color: black;");
    statusLabel->setText("Logging in...");

    serverApi->login(username.toStdString(), password.toStdString(),
        [this](bool success, const std::string& msg) {
            QMetaObject::invokeMethod(this, [this, success, msg]() {
                loginBtn->setEnabled(true);
                if (success) {
                    this->accept();
                } else {
                    statusLabel->setStyleSheet("color: red;");
                    statusLabel->setText(QString::fromStdString(msg));
                }
            });
        });
}

void LoginWindow::handleRegistration() {
    QString username = regUsernameInput->text();
    QString email = regEmailInput->text();
    QString password = regPasswordInput->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        statusLabel->setStyleSheet("color: red;");
        statusLabel->setText("All fields are required.");
        return;
    }

    regBtn->setEnabled(false);
    statusLabel->setStyleSheet("color: black;");
    statusLabel->setText("Registering...");

    serverApi->createUser(username.toStdString(), email.toStdString(), password.toStdString(),
        [this](bool success) {
            
            QMetaObject::invokeMethod(this, [this, success]() {
                regBtn->setEnabled(true);
                if (success) {
                    statusLabel->setStyleSheet("color: green;");
                    statusLabel->setText("Registration successful! Please log in.");
                    
                    regPasswordInput->clear();
                    loginUsernameInput->setText(regUsernameInput->text());
                    tabWidget->setCurrentIndex(0); 
                } else {
                    statusLabel->setStyleSheet("color: red;");
                    statusLabel->setText("Registration failed. Username may exist.");
                }
            });
        });
}