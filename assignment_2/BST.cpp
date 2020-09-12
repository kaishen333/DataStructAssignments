#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"

using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

int BST::height(BTNode *n) {
	if (!n) return -1; // if n is null, return -1
	int left = height(n->left);  // keeps track of nodes on left
	int right = height(n->right); // keeps track of nodes on right
	if (left > right) return 1 + left; // compares left and right
	else return 1 + right;
}

bool BST::deepestNodes() {
	if (root) {
		if (!root->right && !root->left) // handle special case
			root->item.print(cout); 
		else
			deepestNodes2(root);
		return true;
	}
	return false;
}

void BST::deepestNodes2(BTNode* n) {
	if (!n->right && !n->left)  // if left and right of node are empty
		n->item.print(cout); // print root
	else if (!n->left || !n->right) { // if left or right of node is not empty
		if (n->left) deepestNodes2(n->left);
		else deepestNodes2(n->right);
	}
	else {
		int l = height(n->left); //height of left node
		int r = height(n->right); //height of right node
		if (l > r) deepestNodes2(n->left);  //if left is deeper
		else if (l < r) deepestNodes2(n->right); //if right is deeper
		else { // if both depth are equal
			deepestNodes2(n->left);
			deepestNodes2(n->right);
		}
	}
}

bool BST::display(int order, int source) {\
	ofstream text("student-info.txt");  //opens fresh text file
	if (order == 1) ascending(source);
	else descending(source);
	text.close();
	return true;
}

void BST::ascending(int source) {
	if (root == NULL) return;// handle special case
	if (source == 1) inOrderPrint2(root);
	else	inOrderPrint2_file(root);// do normal process
	cout << endl;
}

void BST::inOrderPrint2_file(BTNode *cur) {
	ofstream text;
	text.open("student-info.txt", ios::app); //opens text file and appends
	if (cur == NULL) return; //handel special case
	inOrderPrint2_file(cur->left);
	cur->item.print(text);
	text.close(); // close file
	inOrderPrint2_file(cur->right);
}

void BST::descending(int source) {
	if (root == NULL) return;// handle special case
	if (source == 1) reversePrint2(root);
	else	reversePrint2_file(root);// do normal process
	cout << endl;
}

void BST::reversePrint2(BTNode *cur) {
	if (cur == NULL) return; // handle special case
	reversePrint2(cur->right);
	cur->item.print(cout);
	reversePrint2(cur->left);
}

void BST::reversePrint2_file(BTNode *cur) {
	ofstream text;
	text.open("student-info.txt", ios::app);
	if (cur == NULL) return; // handle special case
	reversePrint2_file(cur->right);
	cur->item.print(text);
	text.close(); // close file
	reversePrint2_file(cur->left);
}

bool BST::CloneSubtree(BST t1, type item) {
	BTNode*n;
	BTNode*y = t1.root;
	if (y == NULL)return false; // handle special case
	if (t1.search(y, item, n) == true) { // if node that user input is found
		insertclone(n); // let the node be root
		return true;
	}
	else {
		cout << "Number entered does not exist!" << endl;
		return false;
	}
}

bool BST::search(BTNode* cur, type item,BTNode*& n) {
	if (cur == NULL) return false; // handle special case
	else if (cur->item.id == item.id) { //node matching with user input
		n = cur;
		return true;
	}
	// traverse BST 
	else if (cur->item.id < item.id)  search(cur->right, item,n);
	else  search(cur->left, item,n);
}

void BST::insertclone(BTNode* cur) {
	insertclone2(cur);// do normal process
	cout << endl;
	return;
}

void BST::insertclone2(BTNode *cur) {
	if (cur == NULL) return; // handle special case
	insert(cur->item); // do normal process
	insertclone2(cur->left);
	insertclone2(cur->right);
}

bool BST::printAncestor(type item) {
	BTNode*cur = root;
	if (!search2(cur, item)) {
		cout << "Node doesnt exist!" << endl;
		return false;
	}
	if (root == NULL) return false; // handle special case
	if (item.id == cur->item.id) { //checks if node that user input exists
		cout << "There is no ancestor for this item";
		return true;
	}
	cout << "\n----------------Ancestors----------------\n";

	while (cur->item.id != item.id) { // loop to print while searcing for node
		cur->item.print(cout);
		if (cur->item.id < item.id) cur = cur->right;
		else  cur = cur->left;
	}
	return true;
}

bool BST::search2(BTNode* cur, type item) {
	if (cur == NULL) return false; // handle special case
	else if (cur->item.id == item.id) { //node matching with user input
		return true;
	}
	// traverse BST 
	else if (cur->item.id < item.id)  search2(cur->right, item);
	else  search2(cur->left, item);
}

bool BST::printPath() {
	if (root == NULL) return false; // handle special case
	leafFinder(root);
	return true;
}

void BST::leafFinder(BTNode* cur) {
	if (cur == NULL) return ; // handle special case
	if (cur->left == NULL && cur->right == NULL) { // if leaf is found
		printPath2(cur->item.id); // do normal process
		return;
	}
	// traverse BST
	leafFinder(cur->left);
	leafFinder(cur->right);
}

void BST::printPath2(int leaf) {
	BTNode*cur = root;
	do {
		cout << cur->item.id << " "; //print item
		if (cur->item.id < leaf) cur = cur->right;
		else  cur = cur->left;
	} while (cur->item.id != leaf); // while leaf is not reached,continue to loop
	cout << cur->item.id << " ";
	cout << endl;
}

