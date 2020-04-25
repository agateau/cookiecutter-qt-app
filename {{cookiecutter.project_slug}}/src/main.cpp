#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLocale>
#include <QTranslator>

#include "Config.h"

static void loadTranslations(QObject* parent) {
    // Search in current path first, to give translators an easy way to test
    // their translations
    QStringList searchDirs = {QDir::currentPath(), ":/translations"};
    auto translator = new QTranslator(parent);
    QLocale locale;
    for (const auto& dir : searchDirs) {
        if (translator->load(locale, QCoreApplication::applicationName(), "_", dir)) {
            QCoreApplication::installTranslator(translator);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(app);
    Q_INIT_RESOURCE(translations);
    app.setOrganizationName(ORGANIZATION_NAME);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);
    app.setWindowIcon(QIcon(":/icons/appicon.svg"));
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    loadTranslations(&app);

    MainWindow window;
    window.show();

    return app.exec();
}
