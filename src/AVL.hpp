#include <string>
#include <vector>

struct Node{
    std::string name;
    int ufid;
    int AVLValue;
    Node* left;
    Node* right;

    Node(std::string name, int ufid) : name(name), ufid(ufid), AVLValue(0), left(nullptr), right(nullptr) {}
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
};
