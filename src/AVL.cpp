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

int AVL::checkHeight(Node* curr) {
    if (root == nullptr) return 1;
    int leftHeight = checkHeight(root->left);
    int rightHeight = checkHeight(root->right);
    if (leftHeight >= rightHeight) return 1 + leftHeight;
    return 1 + rightHeight;
}
/*
std::vector<Node*> AVL::adjustAVL(int ufid, Node* curr) {
    if (ufid == curr->ufid) {
        std::vector<Node*> final;
        return final;
    }

    curr->AVLValue = checkHeight(curr->left) - checkHeight(curr->right);
    if (ufid > curr->ufid) {
        std::vector<Node*> final =  adjustAVL(ufid, curr->right);
        final.push_back(curr);
        return final;
    }
    std::vector<Node*> final = adjustAVL(ufid, curr->left);
    final.push_back(curr);
    return final;
}

void AVL::checkRotate(std::vector<Node*>) {
    if (curr == nullptr) return;

}
*/

std::vector<Node*> AVL::backtraceNode(int ufid, Node* curr) {
    if (curr == nullptr) throw std::runtime_error("invalid curr node");
    if (curr->ufid == ufid) {
        std::vector<Node*> final;
        return final;
    }
    if (ufid < curr->ufid) {
        std::vector<Node*> final = backtraceNode(ufid, curr->left);
        final.push_back(curr);
        return final;
    }
    std::vector<Node*> final = backtraceNode(ufid, curr->right);
    final.push_back(curr);
    return final;
}

std::string AVL::insert(std::string name, int ufid) {
    // checks undefined answers
    if (ufid > 99999999 || ufid < 10000000) return "unsuccessful";
    bool alpha = true;
    for (int i = 0; i < static_cast<int>(name.size()); i++) {
        unsigned char a = name[i];
        if (!std::isalpha(a)) alpha = false;
    }
    if (!alpha) return "unsuccessful";

    // finding the spot to insert
    std::vector<Node*> BCNode;
    if (root == nullptr) {
        root = new Node(name, ufid);
        return "successful";
    }
    Node* parent = locateUfid(ufid, root);
    if (ufid > parent->ufid) {
        parent->right = new Node(name, ufid);
        BCNode = backtraceNode(ufid, root);
        for (Node* curr : BCNode) {

        }
        return "successful";
    }
    if (ufid < parent->ufid) {
        parent->left = new Node(name, ufid);
        BCNode = backtraceNode(ufid, root);
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
