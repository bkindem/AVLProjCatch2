#include <string>
#include <vector>

struct Node{
    std::string name;
    int ufid;
    Node* left;
    Node* right;
    bool print;
    bool l;
    bool r;

    Node(std::string name, int ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr), print(false), l(false), r(false) {}
};

class AVL {
public:
    Node* root;

    // constructor
    AVL();

    //required functions
    std::string insert(std::string name, int ufid);
    std::string remove(int ufid);
    std::vector<Node*> printInorder();
    std::vector<Node*> printPreorder();
    std::vector<Node*> printPostorder();
    std::string printLevelCount();
    std::string removeInorder(int n);
    std::string search(int ufid);
    std::vector<Node*> search(std::string name);

private:
    //assistive function for insert
    Node* locateUfid(int ufid, Node* curr); // used to locate the node above a newly inserted ufid
    int checkHeight(Node* curr); // finds the height of a node
    int checkAVLValue(Node* curr); // finds the AVL value of a node
    std::vector<Node*> backtrace(Node* curr, int ufid); // returns a vector of all the nodes leading to a node, usefull for analyzing rotations
    // rotation help
    void rotateCheck(Node* curr, Node** branch, int avl, int ufid); // checks what rotation is necesesary
    void rightRotation(Node* curr, Node** branch);
    void leftRotation(Node* curr, Node** branch);
    void leftRightRotation(Node* curr, Node** branch);
    void rightLeftRotation(Node* curr, Node** branch);

    //Assistive function for remove
    Node** locateUfidBranch(int ufid, Node* curr); // returns a pointer to the pointer pointing to the desired node
    Node** findSmallestNodeRight(Node* curr); // returns a pointer to the pointer pointing to the smallest node on the right
    void removeRecursive(Node* curr, Node** branch); // a recursive helper function for the remove function, used for multiple removal if necesesary
};
