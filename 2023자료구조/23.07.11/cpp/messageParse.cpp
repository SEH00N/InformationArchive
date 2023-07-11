#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>

std::vector<std::string> Split(std::string serve, char prefix) {
    std::vector<std::string> container;
    std::stringstream ss(serve);
    std::string temp;

    while (std::getline(ss, temp, prefix))
        container.push_back(temp);

    return container;
}

class Log {
private:
    std::string* id;
    std::string command;

public:
    Log(std::string* id, std::string command) : id{ id }, command{ command } {}

public:
    std::string ToString() { return *(this->id) + command; }
};

std::vector<std::string> solution(std::vector<std::string> record) {
    std::vector<std::string> answer;
	std::vector<Log> logVector;
    std::unordered_map<std::string, std::string> userTable;

    for (auto iter = record.begin(); iter != record.end(); ++iter)
    {
        std::vector<std::string>commands = Split(*iter, ' ');

        if (commands[0] == "Enter") {
            userTable[commands[1]] = commands[2];
            logVector.push_back({ &userTable[commands[1]], "´ÔÀÌ µé¾î¿Ô½À´Ï´Ù." });
        }
        else if (commands[0] == "Leave")
            logVector.push_back({ &userTable[commands[1]], "´ÔÀÌ ³ª°¬½À´Ï´Ù." });
        else if (commands[0] == "Change")
            userTable[commands[1]] = commands[2];
    }

    for (auto iter = logVector.begin(); iter != logVector.end(); ++iter)
        answer.push_back(iter->ToString());

    return answer;
}

int main()
{
    std::vector<std::string> answer = solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" });
    for (auto iter = answer.begin(); iter != answer.end(); ++iter)
        std::cout << (*iter) << std::endl;

    return 0;
}