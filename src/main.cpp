#include "AVL.hpp"
#include <iostream>
#include <string>
#include <cctype>
bool isNumber(std::string str) {
    bool num = true;
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        if (!isdigit(static_cast<unsigned char>(str[i]))) {
            num = false;
            break;
        }
    }
    return num;
}

std::string getItem(std::string str) {
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        if (str[i] == ' ') {
            return str.substr(0, i);
        }
    }
    return str;
}

std::string getRest(std::string str) {
    for (int i = 0; i < static_cast<int>(str.length())-1; i++) {
        if (str[i] == ' '){
            return str.substr(i+1);
        }
    }
    return str;
}

bool stringParsed(std::string str) {
    if (str[0] == '"' && str[str.length() - 1] == '"') return true;
    return false;
}

void insert(AVL &database, std::string data) { // include the check for quotation marks, and remove them
    std::string name = getItem(data);
    if (stringParsed(name)) {
        name = name.substr(1,name.length() - 2);
    }
    else {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    data = getRest(data);
    std::string tempUfid = getItem(data);
    if (isNumber(tempUfid)) {
        int ufid;
        ufid = std::stoi(tempUfid);
        std::cout << database.insert(name, ufid) << std::endl;
    }
    else std::cout << "unsuccessful" << std::endl;
}

void remove(AVL &database, std::string data) {
    std::string tempUfid = getItem(data);
    if (isNumber(tempUfid)) {
        int ufid;
        ufid = std::stoi(tempUfid);
        std::cout << database.remove(ufid) << std::endl;
    }
    else std::cout << "unsuccessful" << std::endl;
}

void search(AVL &database, std::string data) {
    bool num = isNumber(data);
    if (num) {
        std::cout << database.search(std::stoi(data)) << std::endl;
    }
    else {
        std::vector<Node*> result;
        result = database.search(data.substr(1, data.length() - 2));
        if (result.size() == 0) std::cout << "unsuccessful" << std::endl;
        else {
            for (Node* curr : result) {
                std::cout << curr->ufid << std::endl;
            }
        }
    }
}

void printInorder(AVL &database) {
    std::vector<Node*> result;
    result = database.printInorder();
    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        if (i != static_cast<int>(result.size()) - 1) {
            std::cout << result[i]->name << ", ";
        }
        else std::cout << result[i]->name << std::endl;
    }
}

void printPreorder(AVL &database) {
    std::vector<Node*> result;
    result = database.printPreorder();
    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        if (i != static_cast<int>(result.size()) - 1) {
            std::cout << result[i]->name << ", ";
        }
        else std::cout << result[i]->name << std::endl;
    }
}
void printPostorder(AVL &database) {
    std::vector<Node*> result;
    result = database.printPostorder();
    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        if (i != static_cast<int>(result.size()) - 1) {
            std::cout << result[i]->name << ", ";
        }
        else std::cout << result[i]->name << std::endl;
    }
}

void printLevelCount(AVL &database) {
    std::cout << database.printLevelCount() << std::endl;
}

void removeInorder(AVL &database, std::string data) {
    if (isNumber(data)) {
        int num = std::stoi(data);
        std::cout << database.removeInorder(num) << std::endl;
    }
    else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void invalid() {
    std::cout << "unsuccessful" << std::endl;
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    int count;
    if (isNumber(line)) {
        count = std::stoi(line);
    }
    else {
        std::cout << "unsuccessful" << std::endl;
        return 0;
    }

    AVL database = AVL();
    std::string func;
    std::string data;

    for (int i = 0; i < count; i++) {
        std::getline(std::cin, data);
        func = getItem(data);
        if (func == "insert") {
            data = getRest(data);
            insert(database, data);
        }
        else if (func == "remove") {
            data = getRest(data);
            remove(database, data);
        }
        else if (func == "search") {
            data = getRest(data);
            search(database, data);
        }
        else if (func == "printInorder") {
            printInorder(database);
        }

        else if (func == "printPreorder") {
            printPreorder(database);
        }

        else if (func == "printPostorder") {
            printPostorder(database);
        }

        else if (func == "printLevelCount") {
            printLevelCount(database);
        }
        else if (func == "removeInorder") {
            data = getRest(data);
            removeInorder(database, data);
        }
        else invalid();

    }
}