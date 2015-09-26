#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct _node
{
	int no;
	string str;
	_node *child;
	_node *parent;
	_node(char ch)
	{
		no = 1;
		str.push_back(ch);
		child = parent = nullptr;
	}
	void inc() { no++; }
};

string text;
vector<_node*> vt;
priority_queue<_node*, cmp> pq;

int main()
{
	ios::sync_with_stdio(false);
	cin >> text;

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

	cout << pq.size() << '\n';

	while (!pq.empty()) // need to implement the comparison function
	{
		_node *temp = pq.top();
		pq.pop();

		printf("%s %d\n", temp->str.c_str(), temp->no);
	}
}