/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AVL.h"
#include <random>
// Name: Katie He, UFID: 5555-1836

using namespace std;

TEST_CASE("Insert Command Testing")
{
    AVLTree tree;
    SECTION("short id")
    {
        REQUIRE(tree.insert("Hello", "12345") == false);
    };
    SECTION("numbers in name")
    {
        REQUIRE(tree.insert("h3LL0", "12345667") == false);
    };
    SECTION("symbols in name")
    {
        REQUIRE(tree.insert("h&&HI", "12345667") == false);
    };
    SECTION("invalid id")
    {
        REQUIRE(tree.insert("Sammy Freeman", "1!!!!667") == false);
    };
    SECTION("duplicate account")
    {
        REQUIRE(tree.insert("Sammy Freeman", "12345678") == true);
        REQUIRE(tree.insert("Sammy", "12345678") == false);
    };
}

TEST_CASE("AVL Insert + Left Rotation"){
		AVLTree tree;
		tree.insert("alice", "12341231");
		tree.insert("bob", "12341232");
		tree.insert("charlie", "12341233");
	    tree.insert("dean", "12341234");
	    tree.insert("eileen", "12341235");

	    SECTION("inorder")
        {
            vector<string> actual = {};
            tree.printInorder(actual);
            vector<string> expected = {"alice", "bob", "charlie", "dean", "eileen"};
            REQUIRE(expected.size() == actual.size());
            REQUIRE(actual == expected);
        };
        SECTION("preorder")
        {
            vector<string> actual = {};
            tree.printPreorder(actual);
            vector<string> expected = {"bob", "alice", "dean", "charlie", "eileen"};
            REQUIRE(expected.size() == actual.size());
            REQUIRE(actual == expected);
        };
        SECTION("postorder")
        {
            vector<string> actual = {};
            tree.printPostorder(actual);
            vector<string> expected = {"alice", "charlie", "eileen", "dean", "bob"};
            REQUIRE(expected.size() == actual.size());
            REQUIRE(actual == expected);
        };
}

TEST_CASE("AVL Insert + Right Rotation"){
    AVLTree tree;
    tree.insert("charlie", "12341233");
    tree.insert("bob", "12341232");
    tree.insert("alice", "12341231");
    vector<string> actual = {};
    tree.printPreorder(actual);
    vector<string> expected = {"bob", "alice", "charlie"};
    REQUIRE(expected.size() == actual.size());
    REQUIRE(actual == expected);
}

TEST_CASE("AVL Insert + Right-Left Rotation"){
    AVLTree tree;
    tree.insert("alice", "12341231");
    tree.insert("charlie", "12341233");
    tree.insert("bob", "12341232");
    vector<string> actual = {};
    tree.printPostorder(actual);
    vector<string> expected = {"alice", "charlie", "bob"};
    REQUIRE(expected.size() == actual.size());
    REQUIRE(actual == expected);
}

TEST_CASE("AVL Insert + Left-Right Rotation"){
    AVLTree tree;
    tree.insert("charlie", "12341233");
    tree.insert("alice", "12341231");
    tree.insert("bob", "12341232");
    vector<string> actual = {};
    tree.printInorder(actual);
    vector<string> expected = {"alice", "bob", "charlie"};
    REQUIRE(expected.size() == actual.size());
    REQUIRE(actual == expected);
}

TEST_CASE("100-Node AVL Tree and 10-Node Removal")
{
    AVLTree tree;
    vector<string> expected = {};
    for(int i = 0; i < 100; ++i)
    {
        string name = "";
        string id = to_string(12341200 + i);
        srand(time(0));
        for(int j = 0; j < 8; ++j)
        {
            char randomChar = (rand() % 26) + 'A';
            name += randomChar;
        }
        tree.insert(name, id);
        expected.push_back(name);
    }
    for(int i = 0; i < 10; ++i)
    {
        int randomIndex = rand() % (100 - i);
        REQUIRE(tree.removeInorder(randomIndex));
        expected.erase(expected.begin() + randomIndex);
    }
    vector<string> actual = {};
    tree.printInorder(actual);
    REQUIRE(expected.size() == actual.size());
    REQUIRE(actual == expected);
}
*/