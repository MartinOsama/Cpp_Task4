#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>


class Logger {
public:
    explicit Logger(const QString& filename);  // Allows specifying the file path upon creation
    ~Logger();
    void log(const QString& message, const QString& level = "INFO");

private:
    QFile file;
};

#endif // LOGGER_H
