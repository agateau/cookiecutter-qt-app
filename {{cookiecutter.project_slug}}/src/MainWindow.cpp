#include "MainWindow.h"

#include "BuildConfig.h"
#include "SettingsDialog.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(APP_HUMAN_NAME);
    setupActions();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupActions() {
    ui->actionSettings->setShortcut(QKeySequence::Preferences);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettingsDialog);

    ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(ui->actionQuit, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::showSettingsDialog() {
    if (!mSettingsDialog) {
        mSettingsDialog = new SettingsDialog(this);
    }
    mSettingsDialog->show();
}
