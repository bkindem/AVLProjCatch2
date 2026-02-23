/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "AVL.hpp"
#include <bits/stdc++.h>

using namespace std;

// Name: Ben Kindem
// UFID: 54847697





TEST_CASE("Insertion Testing valid takes", "[one]") {
	AVL tester = AVL();
	REQUIRE(tester.insert("Ben", 11111111)=="successful");
	REQUIRE(tester.insert("Ryan", 33333333)=="successful");
}

TEST_CASE("Insertion Testing Invalid Inputs", "[one]") {
	AVL tester = AVL();
	REQUIRE("unsuccessful" == tester.insert("B3N", 11111111)); // letters in name
	REQUIRE("unsuccessful" == tester.insert("Ben!", 22222222)); // symbols in name
	REQUIRE("unsuccessful" == tester.insert("Ben", 123456789)); // more than 8 in ufid
	REQUIRE("unsuccessful" == tester.insert("Ben", -1234567)); // less than 8 in ufid
	tester.insert("Ben", 33333333);
	REQUIRE("unsuccessful" == tester.insert("Ben", 33333333)); // repeat ufid
}

TEST_CASE("Edge Cases", "[one]") {
	AVL tester = AVL();
	REQUIRE(tester.remove(99999999) == "unsuccessful");

	tester.insert("Ben", 99999999);
	REQUIRE(tester.remove(11111111) == "unsuccessful");

	REQUIRE(tester.removeInorder(3) == "unsuccessful");
}
TEST_CASE("Insertion Testing Rotation Cases", "[one]") {
	AVL tester = AVL();
	tester.insert("Ben", 55555555);

	SECTION("Left Rotation") {
		tester.insert("Ryan", 33333333);
		tester.insert("Jonah", 11111111);
		vector<Node*> vec = tester.printPostorder();
		REQUIRE(vec[0]->name == "Jonah");
		REQUIRE(vec[1]->name == "Ben");
		REQUIRE(vec[2]->name == "Ryan");
	}
	SECTION("Right Rotation") {
		tester.insert("Ryan", 77777777);
		tester.insert("Jonah", 99999999);
		vector<Node*> vec = tester.printPostorder();
		REQUIRE(vec[0]->name == "Ben");
		REQUIRE(vec[1]->name == "Jonah");
		REQUIRE(vec[2]->name == "Ryan");
	}
	SECTION("Left Right Rotation") {
		tester.insert("Ryan", 11111111);
		tester.insert("Jonah", 22222222);
		vector<Node*> vec = tester.printPostorder();
		REQUIRE(vec[0]->name == "Ryan");
		REQUIRE(vec[1]->name == "Ben");
		REQUIRE(vec[2]->name == "Jonah");
	}
	SECTION("Right Left Rotation") {
		tester.insert("Ryan", 99999999);
		tester.insert("Jonah", 77777777);
		vector<Node*> vec = tester.printPostorder();
		REQUIRE(vec[0]->name == "Ben");
		REQUIRE(vec[1]->name == "Ryan");
		REQUIRE(vec[2]->name == "Jonah");
	}
}

TEST_CASE("Deletion Cases", "[one]") {
	AVL tester = AVL();
	SECTION("No Children") {
		tester.insert("Ben", 55555555);
		tester.insert("Jonah", 11111111);
		REQUIRE(tester.remove(11111111) == "successful");
		std::vector<Node*> vec = tester.printInorder();
		REQUIRE(vec[0]->name == "Ben");
		REQUIRE(vec.size() == 1);
	}
	SECTION("One Child") {
		tester.insert("Ben", 55555555);
		tester.insert("Jonah", 11111111);
		REQUIRE(tester.remove(55555555) == "successful");
		std::vector<Node*> vec = tester.printInorder();
		REQUIRE(vec[0]->name == "Jonah");
		REQUIRE(vec.size() == 1);
	}
	SECTION("Two Children") {
		tester.insert("Ben", 55555555);
		tester.insert("Jonah", 11111111);
		tester.insert("Ryan", 99999999);
		REQUIRE(tester.remove(55555555) == "successful");
		std::vector<Node*> vec = tester.printPreorder();
		REQUIRE(vec[0]->name == "Ryan");
		REQUIRE(vec[1]->name == "Jonah");
		REQUIRE(vec.size() == 2);
	}

}

int checkHeight(Node* root) {
	if (root == nullptr) return 0;
	int leftHeight = checkHeight(root->left);
	int rightHeight = checkHeight(root->right);
	if (leftHeight >= rightHeight) return 1 + leftHeight;
	return 1 + rightHeight;
}

bool boolHeight(Node* root) {
	if (root == nullptr) return true;
	int difference = checkHeight(root->left) - checkHeight(root->right);
	if (difference < -1 || difference > 1) return false;
	return boolHeight(root->left) && boolHeight(root->right);
}

TEST_CASE("100 points test", "[one]") {
	AVL tester = AVL();
	for (int i = 0; i < 100; i++) {
		tester.insert("test", i+10000000);
	}

	//confirm still in order
	REQUIRE(boolHeight(tester.root) == true);

	// try 10 random deletions (used a random number gen)
	REQUIRE(tester.remove(10000040) == "successful");
	REQUIRE(tester.remove(10000033) == "successful");
	REQUIRE(tester.remove(10000078) == "successful");
	REQUIRE(tester.remove(10000027) == "successful");
	REQUIRE(tester.remove(10000085) == "successful");
	REQUIRE(tester.remove(10000076) == "successful");
	REQUIRE(tester.remove(10000014) == "successful");
	REQUIRE(tester.remove(10000088) == "successful");
	REQUIRE(tester.remove(10000041) == "successful");
	REQUIRE(tester.remove(10000091) == "successful");
	std::vector<Node*>vec = tester.printInorder();
	std::vector<int> result;
	for (int i = 0; i < static_cast<int>(vec.size()); i++) {
		result.push_back(vec[i]->ufid);
	}
	REQUIRE(std::is_sorted(result.begin(), result.end()));


}
*/