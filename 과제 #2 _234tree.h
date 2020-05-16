#include <iostream>
#include <queue>
#include <string>

using namespace std;

class node{
public:
	//class variables
    int elements[5] = {0};
    node* parent = NULL;
    node* children[5] = {NULL};
    static queue<node*> q;
    //constructors
    node();
    node(int ele);
    node(int* eles, node** cd);
    //methods
    //getters 
    string getStringAllElements();
    node* getParent();
    node* getChild(int idx);
    int* getElementsAll();
    node** getChildrenAll();
    int getFirstElement();
    int getParentIdx();
    int getSize();
    int getSiblingNum();
    node* getSibling();
    
    //setters and add methods
    void setParent(node* n); 
    
    node* addChild(int idx, node* child);
    int addElement(int ele);
    int addElementByIdx(int ele, int idx);
    static int addChildFromQueue(node* n);
    
    int split();
    
    //delete and change methods
    int delElement(int ele);
    int delElementByIdx(int idx, int direc);
    int changeElement(int ori, int src);
    int changeByIdx(int oriIdx, int src);

};



class tree {
public:
	//class variables
    node* root = NULL;
    queue<node*> q;  
    //constructors
    tree();
    //methods
    //getters
    node* getInsert(int val);
    node* getSuccessor(node* n, int val);  
    
    //command methods
    int _insert(int val);
    int _delete(int val);
    node* _search(int val);
    
	string _show();

};

