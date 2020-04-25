#include "SettingsDialog.h"

#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog() {
}
