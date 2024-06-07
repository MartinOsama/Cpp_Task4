#include <unordered_map>
#include <vector>
#include <string>

struct Student {
    std::string surname;
    std::vector<std::string> subjects;
};

using SubjectMap = std::unordered_map<std::string, std::vector<std::string>>;  // Maps subjects to student surnames