#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item

		int height(BTNode *);   //compares the tree height of both left and right from given node
		bool deepestNodes();  //print the depeest node in the tree
		void deepestNodes2(BTNode *); // recursive function for deepestNOdes()

		bool display(int, int); // calls print functions below based on types
		void ascending(int); // calls function that prints in ascending order
		void inOrderPrint2_file(BTNode *); // print in ascending order to file
		void descending(int); // calls function that prints in desecnding order
		void reversePrint2(BTNode*); // print in ascending order to screen
		void reversePrint2_file(BTNode *); // print in ascending order to file

		bool CloneSubtree(BST, type);
		bool search(BTNode* ,type, BTNode*&); // search for node in tree from input
		void insertclone(BTNode*); // insert clone into new BST
		void insertclone2(BTNode*); // recursive function for insetclone

		bool printAncestor(type); // prints the ancestors of the node which user input
		bool search2(BTNode*, type); //checks if node that user input exists

		bool printPath();
		void leafFinder(BTNode*); // finds leaves in the BST
		void printPath2(int); // prints nodes while finding leaf from leafFinder
		
};

#endif