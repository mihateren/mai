#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* left;   
    Node* right;    

    Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
};

Node* buildExpressionTreeAD(int a, int d) {
    Node* root = new Node("*");
    root->left = new Node(to_string(a));
    root->right = new Node(to_string(d));
    return root;
}

Node* buildExpressionTreeBC(int b, int c) {
    Node* root = new Node("*");
    root->left = new Node(to_string(b));
    root->right = new Node(to_string(c));
    return root;
}

Node* buildExpressionTreeBD(int b, int d) {
    Node* root = new Node("*");
    root->left = new Node(to_string(b));
    root->right = new Node(to_string(d));
    return root;
}

Node* buildExpressionTree(int a, int b, int c, int d) {
    Node* ad = buildExpressionTreeAD(a, d);

    Node* bc = buildExpressionTreeBC(b, c);

    Node* bd = buildExpressionTreeBD(b, d);

    Node* adPlusBc = new Node("+");
    adPlusBc->left = ad;
    adPlusBc->right = bc;

    Node* root = new Node("/");
    root->left = adPlusBc;
    root->right = bd;

    return root;
}

void printExpressionTree(const Node* node, int level = 0) {
    if (node == nullptr) return;

    printExpressionTree(node->right, level + 1);
    for (int i = 0; i < level; ++i) {
        cout << "   ";
    }
    cout << node->value << endl;
    printExpressionTree(node->left, level + 1);
}

void deleteExpressionTree(Node* node) {
    if (node == nullptr) return;

    deleteExpressionTree(node->left);
    deleteExpressionTree(node->right);
    delete node;
}

bool splitExpression(const string& expression, string& part1, string& part2) {
    size_t plusPos = expression.find('+');
    if (plusPos == string::npos) return false;
    part1 = expression.substr(0, plusPos);
    part2 = expression.substr(plusPos + 1);
    return true;
}

bool extractValues(const string& part1, const string& part2, int& a, int& b, int& c, int& d) {
    istringstream iss1(part1), iss2(part2);
    char div1, div2;
    iss1 >> a >> div1 >> b;
    iss2 >> c >> div2 >> d;
    return div1 == '/' && div2 == '/';
}

int main() {
    string expression;
    cout << "Enter expr in format a/b+c/d: ";
    getline(cin, expression);

    string part1, part2;
    if (!splitExpression(expression, part1, part2)) {
        cerr << "Error: incorrect input format." << endl;
        return 1;
    }

    int a, b, c, d;
    if (!extractValues(part1, part2, a, b, c, d)) {
        cerr << "Error: incorrect input format." << endl;
        return 1;
    }

    if (b == 0 || d == 0) {
        cerr << "Error: division by zero is not allowed." << endl;
        return 1;
    }

    Node* root = buildExpressionTree(a, b, c, d);

    cout << "Expr tree for (ad+bc)/(bd):" << endl;
    printExpressionTree(root);

    deleteExpressionTree(root);

    return 0;
}