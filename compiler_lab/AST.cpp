#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

// A simple structure to represent a Node in the AST
struct ASTNode
{
    string value;
    vector<ASTNode *> children;

    ASTNode(string val) : value(val) {}
};

// Function to perform pre-order traversal of the AST
void preOrderTraversal(ASTNode *node)
{
    if (node == nullptr)
        return;

    cout << node->value << " ";
    for (auto child : node->children)
    {
        preOrderTraversal(child);
    }
}

// Function to parse and create ASTs for assignments
ASTNode *parseAssignment(const string &line)
{
    // Assuming simple assignments like 'a = b + c;'
    regex assignmentRegex("(\\w+)\\s*=\\s*(.*);");
    smatch match;

    if (regex_search(line, match, assignmentRegex))
    {
        ASTNode *root = new ASTNode("=");
        root->children.push_back(new ASTNode(match[1]));
        root->children.push_back(new ASTNode(match[2]));
        return root;
    }
    return nullptr;
}

// Function to parse and create ASTs for conditions (if-statements)
ASTNode *parseCondition(const string &line)
{
    // Assuming simple if conditions like 'if (a > b) {'
    regex conditionRegex("if\\s*\\((.*)\\)\\s*\\{?");
    smatch match;

    if (regex_search(line, match, conditionRegex))
    {
        ASTNode *root = new ASTNode("if");
        root->children.push_back(new ASTNode(match[1]));
        return root;
    }
    return nullptr;
}

// Function to parse and create ASTs for loops (for loops)
ASTNode *parseLoop(const string &line)
{
    // Assuming simple for loops like 'for (int i = 0; i < n; i++) {'
    regex loopRegex("for\\s*\\((.*);(.*);(.*)\\)\\s*\\{?");
    smatch match;

    if (regex_search(line, match, loopRegex))
    {
        ASTNode *root = new ASTNode("for");
        root->children.push_back(new ASTNode(match[1]));
        root->children.push_back(new ASTNode(match[2]));
        root->children.push_back(new ASTNode(match[3]));
        return root;
    }
    return nullptr;
}

// Main function to read the file, parse, and generate ASTs
void generateASTs(const string &filename)
{
    ifstream file(filename);
    string line;

    vector<ASTNode *> asts;

    while (getline(file, line))
    {
        // Trim whitespace from both ends of the line
        line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");

        ASTNode *ast = nullptr;

        // Check if the line is an assignment
        if (line.find('=') != string::npos && line.find("==") == string::npos)
        {
            ast = parseAssignment(line);
        }

        // Check if the line is a condition
        if (line.find("if") != string::npos)
        {
            ast = parseCondition(line);
        }

        // Check if the line is a loop
        if (line.find("for") != string::npos)
        {
            ast = parseLoop(line);
        }

        if (ast != nullptr)
        {
            asts.push_back(ast);
        }
    }

    // Display each AST in pre-order traversal
    for (auto ast : asts)
    {
        preOrderTraversal(ast);
        cout << endl;
    }

    // Clean up
    for (auto ast : asts)
    {
        delete ast;
    }
}

int main()
{
    string filename = "factorial.cpp"; // Example input file
    generateASTs(filename);
    return 0;
}
