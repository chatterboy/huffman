#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct _node
{
	int no;
	string str;
	_node *lchild;
	_node *rchild;
	_node *parent;
	_node(char ch)
	{
		no = 1;
		str.push_back(ch);
		lchild = rchild = parent = nullptr;
	}
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

	for (auto ch : text)
	{
		int i;
		for (i=0; i<vt.size(); ++i)
			if (ch == vt[i]->str[0])
			{
				vt[i]->inc();
				break;
			}
		if (i == vt.size()) // no ch in vector
		{
			_node *temp = new _node(ch);
			vt.push_back(temp);
		}
	}

	for (auto e : vt)
		pq.push(e);

	while (pq.size() > 1)
	{
		_node *a = pq.top(); pq.pop();
		_node *b = pq.top(); pq.pop();

		_node *temp = new _node(a, b);

		pq.push(temp);
	}

	root = pq.top(); pq.pop();

	vlr(root, 0);

	putchar('\n');

	string str;
	mktb(root, str);

	for (auto e : tb)
		printf("%c %s\n", e.first, e.second.c_str());
	putchar('\n');

	string res = "";
	for (int i=0; i<text.size(); ++i)
		res += tb[text[i]];

	puts(res.c_str());
}