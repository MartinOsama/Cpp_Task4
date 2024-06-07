#ifndef STUDENTQUERYWIDGET_H
#define STUDENTQUERYWIDGET_H
#include <set>

#include <QtWidgets>

class Logger; // Forward declaration

class StudentQueryWidget : public QWidget {
Q_OBJECT
public:
    StudentQueryWidget();
    ~StudentQueryWidget();


private:
    std::unordered_map<std::string, std::vector<std::string>> studentsBySubject;
    QCheckBox *bioCheckbox;
    QCheckBox *chemCheckbox;
    QCheckBox *physCheckbox;
    QCheckBox *mathCheckbox;  // Include Mathematics checkbox
    QPushButton *queryButton;
    QTextEdit *resultDisplay;
    Logger *logger;

    void setupUI();
    void performQuery();
    void loadStudents(const QString &filename);
};

#endif // STUDENTQUERYWIDGET_H
