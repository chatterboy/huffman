// Author : Chansik
// Lang : C++11

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// node to construct a huffman tree
struct _node
{
	int no;
	string str;
	_node *lchild;
	_node *rchild;
	_node *parent;
	// just we make a node including 1 character
	_node(char ch)
	{
		no = 1;
		str.push_back(ch);
		lchild = rchild = parent = nullptr;
	}
	// this constructor can use when we merge two nodes
	_node(_node *a, _node *b)
	{
		no += a->no + b->no;
		str = a->str + b->str;
		parent = nullptr;
		lchild = a; rchild = b;
		a->parent = b->parent = this;
	}
	void inc() { no++; }
};

// for priority_queue in STL
// this can order nodes using the number of characters
struct cmp
{
	bool operator () (_node *a, _node *b)
	{
		return a->no > b->no;
	}
};

string text;
vector<_node*> vt;
priority_queue<_node*, vector<_node*>, cmp> pq;
_node *root;
map<char, string> tb;

// pre-order tree traversal to display huffman tree
// 각 노드에서는 서브트리로부터 나타난 문자들과 각 문자들이 나타난
// 수의 합을 보여준다.
void vlr(_node *pnode, int depth)
{
	if (pnode != nullptr)
	{
		for (int i=0; i<5*depth; ++i) putchar(' ');
		printf("%s %d\n", pnode->str.c_str(), pnode->no);
		vlr(pnode->lchild, depth+1);
		vlr(pnode->rchild, depth+1);
	}	
}

// make a huffman table using huffman tree recursively
void mktb(_node *pnode, string& str)
{
	if (pnode->str.size() == 1)
	{
		tb[pnode->str[0]] = str;
		return;
	}

	str.push_back('0');
	mktb(pnode->lchild, str);
	str.pop_back();

	str.push_back('1');
	mktb(pnode->rchild, str);
	str.pop_back();
}

int main()
{
	ios::sync_with_stdio(false);
	getline(cin, text);

	// first, we need to make all nodes including character and its frequency
	for (auto ch : text)
	{
		int i;
		for (i=0; i<vt.size(); ++i)
			if (ch == vt[i]->str[0])
			{
				vt[i]->inc();
				break;
			}
		if (i == vt.size())
		{
			_node *temp = new _node(ch);
			vt.push_back(temp);
		}
	}

	// next, insert them all in priority queue
	for (auto e : vt)
		pq.push(e);

	// second, we merge two nodes until it have just a node
	while (pq.size() > 1)
	{
		_node *a = pq.top(); pq.pop();
		_node *b = pq.top(); pq.pop();

		_node *temp = new _node(a, b);

		pq.push(temp);
	}

	// need to know the root...
	root = pq.top(); pq.pop();

	puts("Huffman tree");
	vlr(root, 0);
	putchar('\n');

	string str;
	mktb(root, str);

	puts("Huffman table");
	for (auto e : tb)
		printf(" %c   %s\n", e.first, e.second.c_str());
	putchar('\n');

	string res = "";
	for (int i=0; i<text.size(); ++i)
		res += tb[text[i]];

	printf("Result: %s\n\n", res.c_str());

	printf("The number of bits of text: %d\n", text.size()*8);
	printf("The number of bits of using huffan code: %d\n", res.size());
}
