#include "StudentQueryWidget.h"
#include <algorithm>
#include "Logger.h"
#include <QFile>
#include <QTextStream>
StudentQueryWidget::StudentQueryWidget() {
    setupUI();
    // Specify the path to the log file
    logger = new Logger("C:\\Users\\Admin\\CLionProjects\\untitled2\\logger.txt");
    loadStudents("C:\\Users\\Admin\\CLionProjects\\untitled2\\students.txt");
    connect(queryButton, &QPushButton::clicked, this, &StudentQueryWidget::performQuery);
}
StudentQueryWidget::~StudentQueryWidget() {
    delete logger;
}

void StudentQueryWidget::setupUI() {
    bioCheckbox = new QCheckBox("Biology");
    chemCheckbox = new QCheckBox("Chemistry");
    physCheckbox = new QCheckBox("Physics");
    mathCheckbox = new QCheckBox("Mathematics");  // Ensure this is included
    queryButton = new QPushButton("Query");
    resultDisplay = new QTextEdit();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(bioCheckbox);
    layout->addWidget(chemCheckbox);
    layout->addWidget(physCheckbox);
    layout->addWidget(mathCheckbox);
    layout->addWidget(queryButton);
    layout->addWidget(resultDisplay);
}


void StudentQueryWidget::performQuery() {
    resultDisplay->clear();
    logger->log("Query started");

    // Mapping checkbox states to subject sets
    std::map<QString, std::set<std::string>> subjects {
            {"Biology", std::set<std::string>(studentsBySubject["Biology"].begin(), studentsBySubject["Biology"].end())},
            {"Chemistry", std::set<std::string>(studentsBySubject["Chemistry"].begin(), studentsBySubject["Chemistry"].end())},
            {"Physics", std::set<std::string>(studentsBySubject["Physics"].begin(), studentsBySubject["Physics"].end())},
            {"Mathematics", std::set<std::string>(studentsBySubject["Mathematics"].begin(), studentsBySubject["Mathematics"].end())}
    };

    std::vector<QString> selectedSubjects;
    if (bioCheckbox->isChecked()) selectedSubjects.push_back("Biology");
    if (chemCheckbox->isChecked()) selectedSubjects.push_back("Chemistry");
    if (physCheckbox->isChecked()) selectedSubjects.push_back("Physics");
    if (mathCheckbox->isChecked()) selectedSubjects.push_back("Mathematics");

    // Check the number of selected subjects
    size_t numSelected = selectedSubjects.size();
    if (numSelected == 0) {
        resultDisplay->setText("Please select at least one specialty.");
        logger->log("No subjects selected.");
        return;
    }

    // Find the intersection of selected subjects
    std::set<std::string> intersection = subjects[selectedSubjects[0]]; // Start with the first selected subject
    for (size_t i = 1; i < numSelected; i++) {
        std::set<std::string> temp;
        std::set_intersection(intersection.begin(), intersection.end(),
                              subjects[selectedSubjects[i]].begin(), subjects[selectedSubjects[i]].end(),
                              std::inserter(temp, temp.begin()));
        intersection = temp;
    }

    // Display results
    if (intersection.empty()) {
        resultDisplay->setText("No students found that match all selected specialties.");
    } else {
        for (const auto& name : intersection) {
            resultDisplay->append(QString::fromStdString(name));
        }
    }

    logger->log("Query performed with results count: " + QString::number(intersection.size()));
}




void StudentQueryWidget::loadStudents(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        logger->log("Failed to open file: " + filename, "ERROR");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() != 2) {
            logger->log("Invalid line format: " + line, "ERROR");
            continue;
        }
        QString surname = parts[0];
        QString subject = parts[1];

        studentsBySubject[subject.toStdString()].push_back(surname.toStdString());
        logger->log("Loaded student: " + surname + " for subject: " + subject); // Confirm each load
    }
    file.close();
    logger->log("Students loaded successfully from " + filename);
}