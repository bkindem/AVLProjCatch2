#include <string>
#include <vector>

struct Node{
    std::string name;
    int ufid;
    int height;
    Node* left;
    Node* right;

    Node(std::string name, int ufid) : name(name), ufid(ufid), height(0), left(nullptr), right(nullptr) {}
};

class AVL {
public:
    Node* root;

    //required functions
    std::string insert(std::string name, int ufid);


    std::string remove(int ufid);
    std::vector<std::string> printInorder();
    std::vector<std::string> printPreorder();
    std::vector<std::string> printPostorder();
    std::string printLevelCount();
    std::string removeInorder(int n);

private:
    //assistive function
    Node* locateUfid(int ufid, Node* curr);
    int checkHeight(Node* curr);
    int checkAVLValue(Node* curr);
    std::vector<Node*> backtrace(Node* curr, int ufid);
    // rotation help
    void rotateCheck(Node* curr, Node** branch, int avl, int ufid);
    void rightRotation(Node* curr, Node** branch);
    void leftRotation(Node* curr, Node** branch);
    void leftRightRotation(Node* curr, Node** branch);
    void rightLeftRotation(Node* curr, Node** branch);

};
