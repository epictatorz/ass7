#include "btree.h"
#include <string>
using namespace std;

tree::tree() {
	root = NULL;
	p = NULL;
	i = -1;
}

bool tree::isPSet() {
	if (p == NULL) { return false; }
	return true;
}

bool tree::isISet() {
	if (i == -1) { return false; }
	return true;
}

int tree::read() {
	return p->page[i].val;
}

void tree::write(int x) {
	p->page[i].val = x;
}

bool tree::isEmpty() {
	if (root == NULL) { return true; }
	return false;
}

bool tree::isFull() {
	try { BTreeNode* q = new BTreeNode; }

	catch (bad_alloc) {
		return true;
	}
	return false;
}

void tree::find(int x, BTreeNode*& q) {
	if (q->leaf == true) {
		for (int j = q->n - 1; j >= 0; j--) {
			if (x == q->page[j].val) {
				p = q;
				i = j;
			}
			if (j == -1) {
				p = NULL;
				i = -1;
			}
		}
	}
	else {
		int j = q->n - 1;
		while (j > 0 && x < q->page[j].val) {
			j--;
		}
		find(x, q->page[j].next);
	}
}

void tree::insertRoot(int x) {
	BTreeNode* root;
	root->root = true;
	root->leaf = true;
	for (int j = 0; j < PAGE_SIZE; j++) {
		root->page[j].val = 0;
		root->page[j].next = NULL;
	}
	root->page[0].val = x;
	root->n = 1;
	p = root;
	i = 0;
}

void tree::insert(int x, BTreeNode*& q) {
	if (q->n == PAGE_SIZE && q->root == true) {
		if (splitRoot()) {
			insert(x, root);
		}
		else {
			p = NULL;
			i = -1;
		}
	}
	else if (q->leaf == true) {
		int j = q->n - 1;
		while (j >= 0 && x < q->page[j].val) {
			q->page[j + 1].val = q->page[j].val;
			j--;
		}
		j++;
		q->page[j].val = x;
		q->n++;
		p = q;
		i = j;
	}
	else {
		int j = q->n - 1;
		while (j > 0 && x < q->page[j].val) {
			j--;
		}
		if (q->page[j].next->n == PAGE_SIZE) {
			if (splitChild(q, j)) {
				insert(x, q);
			}
			else {
				p = NULL;
				i = -1;
			}
		}
		else {
			insert(x, q->page[j].next);
			q->page[j].val = q->page[j].next->page[0].val;
		}
	}
}

bool tree::splitRoot() {
	BTreeNode* q1 = root;
	if (isFull()) { return false; }
	BTreeNode* q2;
	if (isFull()) { return false; }
	root = new BTreeNode;
	for (int j = 0; j < PAGE_SIZE; j++) {
		root->page[j].val = 0;
		root->page[j].next = NULL;
		q2->page[j].val = 0;
		q2->page[j].next = NULL;
	}
	for (int j = 0; j < (PAGE_SIZE / 2); j++) {
		q2->page[j].val = q1->page[(PAGE_SIZE + 1) / (2 + j)].val;
		q2->page[j].next = q1->page[(PAGE_SIZE + 1) / (2 + j)].next;
	}
	q1->root = false;
	q2->root = false;
	if (q2->page[0].next == NULL) {
		q1->leaf = true;
		q2->leaf = true;
	}
	else {
		q1->leaf = false;
		q2->leaf = false;
	}
	q1->n = (PAGE_SIZE + 1) / 2;
	q2->n = PAGE_SIZE / 2;
	root->root = true;
	root->leaf = false;
	root->n = 2;
	root->page[0].val = q1->page[0].val;
	root->page[0].next = q1;
	root->page[1].val = q2->page[0].val;
	root->page[1].next = q2;
	return true;
}

bool tree::splitChild(BTreeNode*& q1, int k) {
	if (isFull()) { return false; }
	BTreeNode* q2;
	for (int j = 0; j < PAGE_SIZE; j++) {
		q2->page[j].val = 0;
		q2->page[j].next = NULL;
	}
	for (int j = 0; j < (PAGE_SIZE / 2); j++) {
		q2->page[j].val = q1->page[k].next->page[(PAGE_SIZE + 1) / (2 + j)].val;
		q2->page[j].next = q1->page[k].next->page[(PAGE_SIZE + 1) / (2 + j)].next;
	}
	q2->root = false;
	if (q2->page[0].next == NULL) {
		q2->leaf = true;
	}
	else {
		q2->root = false;
	}
	q2->n = PAGE_SIZE / 2;
	q1->page[k].next->n = (PAGE_SIZE + 1) / 2;
	int j = q1->n - 1;
	while (j > k) {
		q1->page[j + 1].val = q1->page[j].val;
		q1->page[j + 1].next = q1->page[j].next;
		j--;
	}
	j++;
	q1->page[j].val = q2->page[0].val;
	q1->page[j].next = q2;
	q1->n++;
	return true;
}