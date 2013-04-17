/*
Implementation of a MultiwayTrie for storing strings
---

*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

template <class t>
void DEBUG(t s)
{
	cout << "DEBUGGING from main :: " << s << " ::" << endl << flush;
}

template <class t1, class t2>
void DEBUG(t1 s0, t2 s1)
{
	cout << "DEBUGGING from main :: " << s0 << " | " << s1 << " ::" << endl << flush;
}


class Trie
{public:
	class Node
	{public:
		int n; bool leaf;
		vector<Node*> children;
		
		Node()
		{
			ClearChildren();
			leaf = false;
		}
		
		void ClearChildren()
		{
			children.clear();
			children.assign(26, NULL);
		}
		
		void PrintChildren()
		{
				DEBUG("PR {");
			for(int i = 0; i < children.size(); ++i)
			{
				if(children.at(i) == NULL)
				{
					DEBUG(i, "NULL");
				}
				else
				{
					DEBUG(i, (char) (children.at(i)->n + 'a'));
				}
			}
				DEBUG("PR }");
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
			
			// Find first char that differs in the strings(cmp,s)
			int i;
			for(i = 0; i < cmp.size(); ++i)
			{
				if(i == s.size())
				{
					break;
				}
				if(cmp.at(i) != s.at(i))
				{
					break;
				}
			}
			
			int p_significand = (i>=cmp.size())?25:i;		
			int f_significand = (i>=s.size())?25:i;
			
			/* Create new Node to represent the current 'loc' */
			Node* P = new Node();
			P->n = loc->n;
			
			/* Create new Node to represent the new value we are inserting */
			Node* F = new Node();
			F->n = val;
			
			/* Overwrite existing loc to branch to both P and F */
			loc->n = i;
			loc->ClearChildren();
			loc->children.at(p_significand) = P;
			loc->children.at(f_significand) = F;
			loc->leaf = false;
			return;
		}
		else
		{
			DEBUG("Here");
			int c = loc->n;
			int lookup;
			if(s.size() <= c  || loc->children.at(s.at(loc->n) - 'a')==NULL)
			// Need to create new node
			{
				Node* N = new Node();
				N->n = val;
				N->leaf = true;
			}
			else
			{
				lookup = s.at(c) - 'a';
				insert(s, loc->children.at(lookup), val);
			}
			
			return;
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
			return;
		}		
	}

	int find(string s, Node* loc)
	{
		if(loc == NULL)
		{
			return 0;
		}
		else if(loc->leaf)
		{
			
			if(data[loc->n] == s) return 1;		
			else { return 0; }
		}
		else
		{
			if(s.size() <= loc->n) { return 0; }
			
			int a = s.at(loc->n) - 'a';
			loc->PrintChildren();
			
			DEBUG("s is ", s);
			DEBUG("loc->n is ", loc->n);
			DEBUG("s[loc->n] is ", s.at(loc->n));
			// if(loc->children.at(a) == NULL) { DEBUG("Was looking for ", s); }
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
	// DEBUG("size",T.head->children.size());
	
	
	// Testing[0]
	DEBUG( "looking for bear", T.find("bear") );
	
	DEBUG( "looking for bell", T.find("bell") );
	
	DEBUG( "looking for be", T.find("be") );
	DEBUG( "looking for bee", T.find("bee") );
	DEBUG( "looking for bumblebee", T.find("bumblebee") );
	
	// Testing[1]
				DEBUG("PR {");
	T.insert("beee");
	DEBUG("Finished inserting beee");
	
	DEBUG( "looking for bear", T.find("bear") );
	
	DEBUG( "looking for bell", T.find("bell") );
	
	DEBUG( "looking for be", T.find("be") );
	DEBUG( "looking for bee", T.find("bee") );
	DEBUG( "looking for bumblebee", T.find("bumblebee") );
	DEBUG( "looking for beee", T.find("beee") );
	
	return 0;
}
