#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class t>
void DEBUG(t s)
{
	cout << "DEBUGGING from main :: " << s << " ::" << endl;
}

template <class t1, class t2>
void DEBUG(t1 s0, t2 s1)
{
	cout << "DEBUGGING from main :: " << s0 << " | " << s1 << " ::" << endl;
}


class Trie
{public:
	class Node
	{public:
		int n; bool leaf;
		vector<Node*> children;
		
		Node()
		{
			children.assign(25, NULL);
			leaf = false;
		}
		
	};
	
	Node* head;
	vector<string> data;
	
	Trie()
	{
		head = new Node();
	}

	void insert(string s, Node* loc, int val)
	{
		if(loc->leaf)
		{
			string cmp = data.at(loc->n);
			DEBUG("cmp",cmp);
			DEBUG("s",s);
			return;
		}
		else
		{
			int c = loc->n;
			insert(s, loc->children.at(c), val);
		}
	}
	
	void insert(string s)
	{
		int n = data.size();
		data.push_back(s);
		
		if(n == 0)
		{
			head->n = n;
			head->leaf = true;
		}
		else
		{
			insert(s, head, n);
		}		
	}

	int find(string s, Node* loc)
	{
		if(loc->leaf)
		{
			if(data[loc->n] == s) return 1;		
			else return 0;
		}
		else if(loc == NULL)
		{
			return 0;
		}
		else
		{
			int a = s.at(loc->n);
			return find(s, loc->children.at(a));
		}	
	}
	
	int find(string s)
	{
		return find(s, head);
	}
};

int main()
{
	Trie T;
	T.insert("bear");
	T.insert("bell");	
	DEBUG( T.find("bear") );
	return 0;
}
