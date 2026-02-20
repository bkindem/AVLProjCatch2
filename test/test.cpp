#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "AVL.hpp"
#include <random>

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
	REQUIRE("unsuccessful" == tester.insert("Ben", 1234567)); // less than 8 in ufid
	tester.insert("Ben", 33333333);
	REQUIRE("unsuccessful" == tester.insert("Ben", 33333333)); // repeat ufid
}

TEST_CASE("Insertion Testing Rotation Cases", "[one]") {
	AVL tester = AVL();
	tester.insert("Ben", 55555555);

	SECTION("Left Rotation") {
		tester.insert("Ryan", 33333333);
		tester.insert("Jonah", 11111111);
		vector<string> vec = tester.printPostorder();
		REQUIRE(vec[0] == "Jonah");
		REQUIRE(vec[1] == "Ben");
		REQUIRE(vec[2] == "Ryan");
	}
	SECTION("Right Rotation") {
		tester.insert("Ryan", 77777777);
		tester.insert("Jonah", 99999999);
		vector<string> vec = tester.printPostorder();
		REQUIRE(vec[0] == "Ben");
		REQUIRE(vec[1] == "Jonah");
		REQUIRE(vec[2] == "Ryan");
	}
	SECTION("Left Right Rotation") {
		tester.insert("Ryan", 11111111);
		tester.insert("Jonah", 22222222);
		vector<string> vec = tester.printPostorder();
		REQUIRE(vec[0] == "Ryan");
		REQUIRE(vec[1] == "Ben");
		REQUIRE(vec[2] == "Jonah");
	}
	SECTION("Right Left Rotation") {
		tester.insert("Ryan", 99999999);
		tester.insert("Jonah", 77777777);
		vector<string> vec = tester.printPostorder();
		REQUIRE(vec[0] == "Ben");
		REQUIRE(vec[1] == "Ryan");
		REQUIRE(vec[2] == "Jonah");
	}
}


int checkHeight(Node* root) {
	if (root == nullptr) return -1;
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

	// create random var
	std::random_device rando;
	std::mt19937 gen(rando());
	std::uniform_int_distribution<int> dist(10000000,10000099);
	for (int i = 0; i < 10; i++) {
		tester.remove(dist(gen));
	}

	//confirm still in order
	REQUIRE(boolHeight(tester.root) == true);
}
