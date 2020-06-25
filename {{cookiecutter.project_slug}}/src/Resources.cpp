#include "Resources.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGlobalStatic>

#include "BuildConfig.h"

class ResourcesInfo {
public:
    ResourcesInfo() {
        if (tryPath(QCoreApplication::applicationDirPath() + '/' + BIN_TO_DATA_DIR)) {
            return;
        }
        // Try the absolute install path, useful when running the app from the
        // build directory
        if (tryPath(QString(INSTALL_PREFIX) + '/' + DATA_INSTALL_DIR)) {
            return;
        }
        qWarning() << "Can't find data dir, has the app been installed?";
    }

    QString findDir(const QString& name) const {
        return mDataDir.filePath(name);
    }

private:
    bool tryPath(const QString& path) {
        mDataDir = QDir(path);
        return mDataDir.exists();
    }

    QDir mDataDir;
};

Q_GLOBAL_STATIC(ResourcesInfo, info)

namespace Resources {

QString findDir(const QString& name) {
    return info()->findDir(name);
}

} // namespace Resources
