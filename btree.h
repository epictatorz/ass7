#ifndef btree_h
#define btree_h
const int PAGE_SIZE = 15;

struct Node {
	int val;
	BTreeNode* next;
};

struct BTreeNode{
	BTreeNode* next;
	Node page[PAGE_SIZE];
	int val, n;
	bool leaf, root;
};

class tree {
public:
	tree();
	bool isPSet();
	bool isISet();
	int read();
	void write(int);
	bool isEmpty();
	bool isFull();
	void find(int, BTreeNode*&);
	void insertRoot(int);
	void insert(int, BTreeNode*&);
	bool splitRoot();
	bool splitChild(BTreeNode*&, int);

private:
	int i;
	BTreeNode* root;
	BTreeNode* p;
};

#endif