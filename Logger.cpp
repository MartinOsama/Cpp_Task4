#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>  // For qCritical

Logger::Logger(const QString& filename) {
    file.setFileName(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qCritical() << "Failed to open log file: " << filename;
    }
}

Logger::~Logger() {
    if (file.isOpen()) {
        file.close();
    }
}

void Logger::log(const QString& message, const QString& level) {
    if (!file.isOpen()) {
        return;
    }
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " [" << level << "] " << message << "\n";
}
