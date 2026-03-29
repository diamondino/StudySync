#include "ui/page/AiTutorPage.h"
#include <QTimer>
#include <QVBoxLayout>
#include "LanguageManager.h"

AiTutorPage::AiTutorPage(QWidget* parent) : AbstractChatPage(parent) {
    addMessage(LanguageManager::tr("nav.ai_tutor"), LanguageManager::tr("ai.greeting"), true);
}

void AiTutorPage::onSendMessageRequested(const QString& text) {
    //implement properly later
    addMessage(LanguageManager::tr("user.me"), text, false);
    QTimer::singleShot(1000, this, [this]() {
        addMessage(LanguageManager::tr("nav.ai_tutor"), LanguageManager::tr("ai.response"), true);
    });
}