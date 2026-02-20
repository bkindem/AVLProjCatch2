#include "AVL.hpp"
#include <stdexcept>

// finds the node above where the new node will lie, in all finds the parent node of the inserted node
Node* AVL::locateUfid(int ufid, Node* curr) {
    if (curr == nullptr) return nullptr;
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

// finds the height of a node used
int AVL::checkHeight(Node* curr) {
    if (curr == nullptr) return -1;
    int leftHeight = checkHeight(curr->left);
    int rightHeight = checkHeight(curr->right);
    if (leftHeight >= rightHeight) return 1 + leftHeight;
    return 1 + rightHeight;
}

// takes in a node and finds the correct avl value corresponding to it
int AVL::checkAVLValue(Node* curr) {
    if (curr == nullptr) throw std::runtime_error("invalid curr node in checkAVLValue");
    int leftHeight = checkHeight(curr->left);
    int rightHeight = checkHeight(curr->right);
    return leftHeight - rightHeight;
}

void AVL::rightRotation(Node* curr, Node** branch) {
    Node* child = curr->left;
    curr->left = child->right;
    child->right = curr;
    *branch = child;
}

void AVL::leftRotation(Node* curr, Node** branch) {
    Node* child = curr->right;
    curr->right = child->left;
    child->left = curr;
    *branch = child;
}

void AVL::leftRightRotation(Node* curr, Node** branch) {
    leftRotation(curr->left, &curr->left);
    rightRotation(curr, branch);
}
void AVL::rightLeftRotation(Node* curr, Node** branch) {
    rightRotation(curr->right, &curr->right);
    return leftRotation(curr, branch);
}


void AVL::rotateCheck(Node* curr, Node** branch, int avl, int ufid) {
    int childAVL;
    if (ufid > curr->ufid) childAVL = checkAVLValue(curr->right);
    else childAVL = checkAVLValue(curr->left);
    if (avl > 0) {
        if (childAVL > 0) rightRotation(curr, branch);
        else leftRightRotation(curr, branch);
    }
    else {
        if (childAVL > 0) rightLeftRotation(curr, branch);
        else leftRotation(curr, branch);
    }
}

std::vector<Node*> AVL::backtrace(Node* curr, int ufid) {
    if (curr == nullptr) throw std::runtime_error("invalid curr node in backtrace function");
    std:: vector<Node*> result;
    if (curr->ufid == ufid) return result; //base case

    if (ufid < curr->ufid) result = backtrace(curr->left, ufid);
    else result = backtrace(curr->right, ufid);
    result.push_back(curr);
    return result;
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

    if (root == nullptr) {
        root = new Node(name, ufid);
        return "successful";
    }



    // locates the position the newly added node should be placed
    Node* parent = locateUfid(ufid, root);
    if (parent-> ufid == ufid) return "unsuccessful";

    if (ufid > parent->ufid) parent->right = new Node(name, ufid);
    else parent->left = new Node(name, ufid);

    std::vector<Node*> BC = backtrace(root, ufid);
    for (int i = 0; i < static_cast<int>(BC.size()); i++) {
        int tempAvlVal = checkAVLValue(BC[i]);
        if (tempAvlVal < -1 || tempAvlVal > 1) {
            Node** branch;
            if (i == static_cast<int>(BC.size() - 1)) branch = &root;
            else {
                if (ufid > BC[i+1]->ufid) branch = &(BC[i+1]->right);
                else branch = &(BC[i+1]->left);
            }
            rotateCheck(BC[i], branch, tempAvlVal, ufid);
            break;
        }
    }
    return "successful";
}

Node** AVL::locateUfidBranch(int ufid, Node* curr) {
    if (ufid == root->ufid) return &root;
    if (ufid > curr->ufid && curr->right != nullptr) {
        if (ufid == curr->right->ufid) return &curr->right;
        return locateUfidBranch(ufid, curr->right);
    }
    if (ufid < curr->ufid && curr->left != nullptr) {
        if (ufid == curr->left->ufid) return &curr->left;
        return locateUfidBranch(ufid, curr->left);
    }
    return nullptr;
}

void AVL::removeRecursive(Node* curr, Node** branch) {
    int children = 0;
    if (curr->right != nullptr && curr->left != nullptr) children = 2;
    else if (curr->right != nullptr || curr->left != nullptr) children = 1;

    if (children = 0) delete curr;
    else if (children = 1) {

    }

}


std::string AVL::remove(int ufid) {
    if (ufid > 99999999 || ufid < 10000000) return "unsuccessful";
    if (root == nullptr) return "unsuccessful";
    Node** branch;
    Node* oldNode;
    if (ufid == root->ufid) {
        branch = &root;
        oldNode= root;
    }
    else {
        branch = locateUfidBranch(ufid, root);
        if (branch == nullptr) return "unsuccessful";
        oldNode = *branch;
    }
    removeRecursive(oldNode, branch);
    return "successful";
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
