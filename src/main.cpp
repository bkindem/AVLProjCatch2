#include <string>
#include <vector>

struct Node{
	int ufid;
	std::string name;
	int AVLValue;
	Node* left;
	Node* right;
};

class AVL {
public:
	std::string insert(std::string name, int ufid) {
		return "tbd";
	}
	std::string remove(int ufid) {
		return "tbd";
	}
	std::vector<std::string> printInorder() {
		std::vector<std::string> result;
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		return result;
	}
	std::vector<std::string> printPreorder() {
		std::vector<std::string> result;
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		return result;
	}
	std::vector<std::string> printPostorder() {
		std::vector<std::string> result;
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		result.emplace_back("tbd");
		return result;
	}
	std::string printLevelCount() {
		return "tbd";
	}
	std::string removeInorder(int n) {
		return "tbd";
	}

	AVL();
};