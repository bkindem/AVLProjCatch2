#include "AVL.hpp"
#include <stdexcept>

// basic constructor
AVL::AVL() : root(nullptr) {}

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
    if (curr == nullptr) return 0;
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
    if (ufid > 99999999 || ufid < 0) return "unsuccessful";
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

    //begins the search for rotations and implements a function to carry out the rotation if one is needed
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

//####################################  DONE WITH INSERT #####################


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

 Node** AVL::findSmallestNodeRight(Node* curr) {
    if (curr->right->left == nullptr) return &curr->right;
    curr = curr->right;
    while (curr->left->left != nullptr) {
        curr = curr->left;
    }
    return &curr->left;
}

void AVL::removeRecursive(Node* curr, Node** branch) {
    int children = 0;
    if (curr->right != nullptr && curr->left != nullptr) children = 2;
    else if (curr->right != nullptr || curr->left != nullptr) children = 1;

    if (children == 0) {
        delete curr;
        *branch = nullptr;
    }
    else if (children == 1) {
        if (curr->left != nullptr) *branch = curr->left;
        else *branch = curr->right;
        curr->left = nullptr;
        curr->right = nullptr;
        delete curr;
    }
    else if (children == 2) {
        Node** nuBranch = findSmallestNodeRight(curr);
        Node* nuNode = *nuBranch;
        int tempUfid = curr->ufid;
        // swap the values
        std::string tempName = curr->name;
        curr->name = nuNode->name;
        curr->ufid = nuNode->ufid;
        nuNode->name = tempName;
        nuNode->ufid = tempUfid;
        removeRecursive(nuNode, nuBranch);
    }

}


std::string AVL::remove(int ufid) {
    if (ufid > 99999999 || ufid < 0) return "unsuccessful";
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

std::vector<Node*> AVL::printInorder() {
    std::vector<Node*> result;
    std::vector<Node*> backTrace;
    if (root == nullptr) return result;
    Node* curr = root;

    while (true) {
        // bypassing the loops if the node doesn't exist
        if (curr->left == nullptr) curr->l = true;
        if (curr->right == nullptr) curr->r = true;

        if (curr->l == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->l = true;
            curr = curr->left;
            continue;
        }
        if (curr->print == false) {
            result.push_back(curr);
            curr->print = true;
        }
        if (curr->r == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->r = true;
            curr = curr->right;
            continue;
        }
        if (!(backTrace.empty()) && backTrace.back() == curr) backTrace.pop_back();
        if (backTrace.empty()) {
            curr->print = false;
            curr->l = false;
            curr->r = false;
            break;
        }
        curr->print = false;
        curr->l = false;
        curr->r = false;
        curr = backTrace.back();
    }
    return result;
}



std::vector<Node*> AVL::printPreorder() {
    std::vector<Node*> result;
    std::vector<Node*> backTrace;
    if (root == nullptr) return result;
    Node* curr = root;

    while (true) {
        if (curr->print == false) {
            result.push_back(curr);
            curr->print = true;
        }
        // bypassing the loops if the node doesn't exist
        if (curr->left == nullptr) curr->l = true;
        if (curr->right == nullptr) curr->r = true;

        if (curr->l == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->l = true;
            curr = curr->left;
            continue;
        }
        if (curr->r == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->r = true;
            curr = curr->right;
            continue;
        }
        if (!(backTrace.empty()) && backTrace.back() == curr) backTrace.pop_back();
        if (backTrace.empty()) {
            curr->print = false;
            curr->l = false;
            curr->r = false;
            break;
        }
        curr->print = false;
        curr->l = false;
        curr->r = false;
        curr = backTrace.back();
    }
    return result;
}

std::vector<Node*> AVL::printPostorder() {
    std::vector<Node*> result;
    std::vector<Node*> backTrace;
    if (root == nullptr) return result;
    Node* curr = root;
    while (true) {
        // bypassing the loops if the node doesn't exist
        if (curr->left == nullptr) curr->l = true;
        if (curr->right == nullptr) curr->r = true;

        if (curr->l == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->l = true;
            curr = curr->left;
            continue;
        }
        if (curr->r == false) {
            if (backTrace.empty() || backTrace.back() != curr) backTrace.push_back(curr);
            curr->r = true;
            curr = curr->right;
            continue;
        }
        if (curr->print == false) {
            result.push_back(curr);
            curr->print = true;
        }
        if (!(backTrace.empty()) && backTrace.back() == curr) backTrace.pop_back();
        if (backTrace.empty()) {
            curr->print = false;
            curr->l = false;
            curr->r = false;
            break;
        }
        curr->print = false;
        curr->l = false;
        curr->r = false;
        curr = backTrace.back();
    }
    return result;

}

std::string AVL::printLevelCount() {
    return std::to_string(checkHeight(root));
}

std::string AVL::removeInorder(int n) {
    std::vector<Node*> result;
    result = printInorder();
    if (n >= static_cast<int>(result.size()) || n < 0) return "unsuccessful";
    int ufid = result[n]->ufid;
    return remove(ufid);
}

std::string AVL::search(int ufid) {
    if (root == nullptr) return "unsuccessful";

    Node* curr = root;
    while (true) {
        if (ufid == curr->ufid) return curr->name;
        if (ufid > curr->ufid ) {
            if (curr->right == nullptr) return "unsuccessful";
            curr = curr->right;
        }
        else {
            if (curr->left == nullptr) return "unsuccessful";
            curr = curr->left;
        }
    }
}

std::vector<Node*> AVL::search(std::string name) {
    std::vector<Node*> preOrder;
    preOrder = printPreorder();
    if (preOrder.empty()) return preOrder;
    std::vector<Node*> result;
    for (Node* curr : preOrder) {
        if (curr->name == name) result.push_back(curr);
    }
    return result;
}
