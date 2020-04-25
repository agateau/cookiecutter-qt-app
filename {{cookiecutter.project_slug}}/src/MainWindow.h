#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
class MainWindow;
}

class SettingsDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupActions();
    void showSettingsDialog();

    std::unique_ptr<Ui::MainWindow> ui;
    SettingsDialog* mSettingsDialog = nullptr;
};

#endif // MAINWINDOW_H
