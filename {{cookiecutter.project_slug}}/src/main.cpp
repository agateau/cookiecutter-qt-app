#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLocale>
#include <QTranslator>

#include "BuildConfig.h"
#include "Resources.h"

static void loadTranslations(QObject* parent) {
    // Search in current path first, to give translators an easy way to test
    // their translations
    QStringList searchDirs = {QDir::currentPath(), Resources::findDir("translations")};
    auto translator = new QTranslator(parent);
    QLocale locale;
    for (const auto& dir : searchDirs) {
        if (translator->load(locale, APP_NAME, "_", dir)) {
            QCoreApplication::installTranslator(translator);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(app);
    app.setOrganizationName(ORGANIZATION_NAME);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);
    auto iconName = QString(":/icons/sc-apps-%1.svg").arg(APP_NAME);
    app.setWindowIcon(QIcon(iconName));
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    loadTranslations(&app);

    MainWindow window;
    window.show();

    return app.exec();
}
