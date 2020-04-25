#include "MainWindow.h"

#include "Config.h"
#include "SettingsDialog.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    setWindowTitle(APP_HUMAN_NAME);
    ui->setupUi(this);
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
