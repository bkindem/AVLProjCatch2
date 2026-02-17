#include "AVL.hpp"
#include <stdexcept>
#include <cctype>

Node* AVL::locateUfid(int ufid, Node* curr) {
    if (curr == nullptr) throw std::runtime_error("invalid curr node");
    if (ufid > curr->ufid) {
        if (curr->right == nullptr) return curr;
        return locateUfid(ufid, curr->right);
    }
    if (ufid < curr->ufid) {
        if (curr->left == nullptr) return curr;
        return locateUfid(ufid, curr->left);
    }
    return curr;
}

bool AVL::checkRotate(Node* curr) {

}

std::string AVL::insert(std::string name, int ufid) {
    if (ufid > 99999999 || ufid < 10000000) return "unsuccessful";
    bool alpha = true;
    for (int i = 0; i < static_cast<int>(name.size()); i++) {
        unsigned char a = name[i];
        if (!std::isalpha(a)) alpha = false;
    }
    if (!alpha) return "unsuccessful";

    if (root == nullptr) {
        root = new Node(name, ufid);
        return "successful";
    }
    Node* parent = locateUfid(ufid, root);
    if (ufid > parent->ufid) {
        parent->right = new Node(name, ufid);
        return "successful";
    }
    if (ufid < parent->ufid) {
        parent->left = new Node(name, ufid);
        return "successful";
    }
    return "unsuccessful";

}

std::string AVL::remove(int ufid) {
    return "tbd";
}

std::vector<std::string> AVL::printInorder() {
    std::vector<std::string> temp;
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    return temp;
}

std::vector<std::string> AVL::printPreorder() {
    std::vector<std::string> temp;
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    return temp;
}

std::vector<std::string> AVL::printPostorder() {
    std::vector<std::string> temp;
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    temp.emplace_back("tbd");
    return temp;
}

std::string AVL::printLevelCount() {
    return "tbd";
}

std::string AVL::removeInorder(int n) {
    return "tbd";
}
