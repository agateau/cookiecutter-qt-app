#include "MainWindow.h"
#include "SettingsDialog.h"
#include "TestUtils.h"

// Qt
#include <QAction>

// Catch2
#include <catch2/catch.hpp>

TEST_CASE("example") {
    SECTION("addition") {
        REQUIRE(2 + 2 == 4);
    }
    SECTION("substraction") {
        REQUIRE(2 - 2 == 0);
    }
}

TEST_CASE("SettingsDialog") {
    // Given a main window
    MainWindow window;
    window.show();

    // When the Settings action is triggered
    QAction* action = window.findChild<QAction*>("actionSettings");
    REQUIRE(action);
    action->trigger();

    // Then the Settings dialog appears
    auto dialog = waitForActiveWindow<SettingsDialog*>();
    REQUIRE(dialog);
}
