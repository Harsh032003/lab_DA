#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Node structure for the AST
struct ASTNode
{
    string data;
    vector<ASTNode *> children;

    ASTNode(string val) : data(val) {}
};

// Function to perform pre-order traversal
void preOrderTraversal(ASTNode *node)
{
    if (node == nullptr)
        return;
    cout << node->data << endl;
    for (ASTNode *child : node->children)
    {
        preOrderTraversal(child);
    }
}

// Function to construct an AST for a given block of code
ASTNode *constructAST(const string &codeBlock)
{
    ASTNode *root = new ASTNode("Block");

    // Parse the codeBlock to identify assignments, loops, and conditions
    if (codeBlock.find("=") != string::npos && codeBlock.find("for") == string::npos)
    {
        root->children.push_back(new ASTNode("Assignment: " + codeBlock));
    }
    if (codeBlock.find("for") != string::npos)
    {
        root->children.push_back(new ASTNode("Loop: " + codeBlock));
    }

    return root;
}

int main()
{
    ifstream file("factorial.cpp");
    string line;
    vector<ASTNode *> asts;

    while (getline(file, line))
    {
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); // remove whitespace
        if (!line.empty())
        {
            asts.push_back(constructAST(line));
        }
    }

    // Display each AST in pre-order traversal
    for (ASTNode *ast : asts)
    {
        preOrderTraversal(ast);
    }

    // Clean up dynamically allocated memory
    for (ASTNode *ast : asts)
    {
        delete ast;
    }

    return 0;
}
