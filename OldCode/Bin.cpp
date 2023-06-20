#include <vector>
#include <iostream>
#include <vector>

using namespace std;

struct Node //узел
{
  string op;
  Node* left, * right;
};

Node* BuildTree(string s, int& pos) //построение дерева в префиксной форме
{
Node * n = new Node;
n->op = s[pos++];
  if (n->op == "+" || n->op == "-" || n->op == "*" || n->op == "/")
  {
    n->left = BuildTree(s, pos);
    n->right = BuildTree(s, pos);
  }
  else n->right = n->left = NULL;
  return n;
}

/*void PrintTree(Node* p, int lev = 0)
{
  if (p == NULL) return;
  PrintTree(p->left, lev + 1);
  cout << '\n';
  for (int i = 0; i < lev; i++)
    cout << "  ";
  cout << p->op;
  PrintTree(p->right, lev + 1);
}*/

string InfTree(Node* p)
{
  if (p->left != NULL && p->right != NULL)
    return "(" + InfTree(p->left) + p->op + InfTree(p->right) + ")";
  return p->op;
}

void Level(Node* p, int i, int n)
{
  if (i == n)
    cout << p->op;
  else
  {
    Level(p->left, i+1, n);
    Level(p->right, i+1, n);
  }
}

int main()
{
  Node* root; //* droot;
  int pos = 0;
  string str = "-/+23*95-83";
  root = BuildTree(str, pos);
  cout << InfTree(root) << endl;
  Level(root, 0, 1);
}