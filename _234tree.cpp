#include "_234tree.h"

queue<node*> node::q;


//constructor
node::node(){}

node::node(int ele){
    elements[1] = ele;
    elements[0]++;
}

node::node(int* eles, node** cd){
    elements[0] = eles[0];
    if(cd[0]!=NULL){
        children[0] = cd[0];
        children[0]->parent = this;
    }
    for(int i=1; i<=elements[0]; i++) {
        elements[i] = eles[i];
        if(cd[i]){
            children[i] = cd[i];
            children[i]->parent = this;
        }
    }
}

//getters

string node::getStringAllElements(){
    if (elements[0]==0) {
        return "�ش� element�� �������� �ʽ��ϴ�.";
    }
    string e = "(";
    int i=1;
    for(; i<elements[0]; i++) {
        e += to_string(elements[i]) + " ";
    }
    e += to_string(elements[i]) + ")";
    return e;
}

node* node::getParent(){
    return parent;
}


// ����Ŭ���� tree�� ���Ͽ� input parameter idx�� ��ȿ���� ����
//childeren �� idx�� �����ؼ� ��ȯ 
node* node::getChild(int idx){
    return children[idx];
}
//elements ��� ��ȯ 
int* node::getElementsAll(){
    return elements;
}
//children ��� ��ȯ 
node** node::getChildrenAll(){
    return children;
}
//ù��° element��ȯ 
int node::getFirstElement(){
    return elements[1];
}

//���� ���° children���� �ľ� 
int node::getParentIdx(){
    int myidx = 0;
    
    while(1){
        if(parent->getChild(myidx)==this) break;
        myidx++;
    }
    return myidx;
}

//���� ����� ���� (2, 3, 4) ��ȯ 
int node::getSize(){
    return elements[0];
}

// �ڽ��� ������ sibling node�� ������ ��ȯ
int node::getSiblingNum(){
    return parent->getSize()+1;
}

// ����Ŭ���� tree�� ���Ͽ� sibling�� �ݵ�� �����ϴ� node������ ȣ����� ����
// sibling�� ���� ����� root�� �����ϴ� ��� treeŬ������ ����ó��
// sibling �� 3,4 node�� �켱 ������ ���� ��ȯ

node* node::getSibling(){
    int myidx = getParentIdx();
    
    if(myidx==0)
		return parent->getChild(myidx+1);
    
    if (myidx==parent->getSize())
	    return parent->getChild(myidx-1);
    
    int siblingOffset;
	if(parent->getChild(myidx+1)->getSize() > parent->getChild(myidx-1)->getSize()){
		siblingOffset = 1;
	}
	else{
		siblingOffset = -1;
	} 
    return parent->getChild(myidx+siblingOffset);
}

//setters and add methods

void node::setParent(node* n){
    parent = n;
}

// fusion case���� child�� �� �� index �Ǵ� �� �� index�� �߰��Ǵ� ��츸 ����
// element�� ��ȿ���� ����X, �߰��� child�� �����ϴ� element�� tree�� ���� �߰����� ����
// �ܺο��� child node�� �߰��Ǵ� ��쿡�� delete�� fusion ���
// insert��node�� addChildFromQueue���� ó���Ѵ�. (ť�� ����� ����) 


node* node::addChild(int idx, node* child){
    int i = elements[0];
    for (; i>=idx; i--) {
        children[i+1] = children[i];
        children[i] = NULL;
        
    }
    
    children[idx] = child;
    if(child!=NULL) children[idx]->parent = this;
    return 0;
}


// ��� �Է¹��� �ʰ��ϸ� -1 return
// �߰��� element�� ���� �� children�� tree ���� ä������ 
 
int node::addElement(int ele){

    if(elements[0]==4) return -1;
    
    int i = elements[0];
    for (; i>0; i--) {
        if (elements[i] >= ele) {
            elements[i+1] = elements[i];
            if(children[i] != NULL) {
                children[i+1] = children[i];
                children[i] = NULL;
            }
            continue;
        }
        else
			break;
    }
    
    elements[i+1] = ele;
    //������ ����
    elements[0]++;
    //�������� 0 ��ȯ
    return 0;
}

int node::addElementByIdx(int ele, int idx){
    int i = elements[0];
    for (; i>idx; i--) {
        if (elements[i] >= ele) {
            elements[i+1] = elements[i];
        
            children[i+1] = children[i];
            children[i] = NULL;
            continue;
        }
        else break;
    }
    
    elements[i+1] = ele;
    elements[0]++;
    return 0;
}

// split�� node���� queue���� ���� input node�� children���� ����

int node::addChildFromQueue(node* n){
	//ť�� ��� �ش�X 
    if (q.empty()) return -1;

    int idxNull = 0;

    while(1){
        if (n->children[idxNull] == NULL) break;
        else idxNull++;
    }
    if(idxNull==0){
        n->children[idxNull] = q.front(); q.pop();
        n->children[idxNull]->setParent(n);
        n->children[idxNull+1] = q.front(); q.pop();
        n->children[idxNull+1]->setParent(n);

    } else {
        n->children[idxNull-1] = q.front(); q.pop();
        n->children[idxNull-1]->setParent(n);
        n->children[idxNull] = q.front(); q.pop();
        n->children[idxNull]->setParent(n);

    }
    return 0;
}


// ����Ŭ���� tree�� ���ؼ�elements�� ����� 5�� node������ ȣ����� ����
// split�� node�� node class�� static queue�� ����Ǿ addChildFromQueue �Լ����� ���
int node::split(){
    int ele1[3], ele2[2];
    node* ptre1[3], *ptre2[2];
    
    // ù��° split�� �Űܴ�´�. 
    ele1[0] = 2;
    ptre1[0] = children[0];
    for (int i=1; i<3; i++) {
        ele1[i] = elements[i];
        ptre1[i] = children[i];
    }
    
    node* child1 = new node(ele1, ptre1);
    q.push(child1);
    
    // �ι�° split�� �Űܴ�´�. 
    ele2[0] = 1;
    ele2[1] = elements[4];
    ptre2[0] = children[3];
    ptre2[1] = children[4];
    
    node* child2 = new node(ele2, ptre2);
    q.push(child2);
    
    return elements[3];
}


//delete and change methods



// element�� �������������� -1 return
// ���� Ŭ���� tree�� ���ؼ� �׻� ������ element�� �����ϴ� node������ ȣ����� ����޴´�.
 

int node::delElement(int ele){
    int size = elements[0];
    
    if(size==0) return -1;
    int i=1;
    for (; i<size; i++) {
        if (elements[i]<ele)
		   continue;
        
        elements[i] = elements[i+1];
    
        children[i] = children[i+1];
        children[i+1] = NULL;
        
    }
    elements[0]--;
    
    return 0;
}


// ���� element�� ������ �� ����� �̽��� ���� idx�� element�� �����ϴ� function �߰�

int node::delElementByIdx(int idx, int direc){
    int size = elements[0];
    int dltedEle = elements[idx];
    
    for (int i=idx; i<size+1; i++) {
        elements[i] = elements[i+1];
        if (direc==2) {
            children[i] = children[i+1];
            children[i+1] = NULL;
        } else {
            if (i==size && direc==0)
			   break;
            children[i-1] = children[i];
            children[i] = NULL;
        }

    }
    elements[0]--;
    
    return dltedEle;
}

// ����Ŭ���� tree�� ���ؼ� ��ü�� element�� �׻� �����ϴ� leaf node������ ȣ����� ����޴´�. 

int node::changeElement(int ori, int src){
    int size = elements[0];
    for (int i=1; i<size+1; i++) {
        if (elements[i] == ori) {
            elements[i] = src;
            break;
        }
    }
    
    return 0;
}


// ���� element�� ������ �� ����� �̽��� ���� idx�� element�� �����ϴ� function �߰�

int node::changeByIdx(int originIdx, int src){
    int originEle = elements[originIdx];
    elements[originIdx] = src;
    
    return originEle;
}



//������. root node�� �����մϴ�. 
tree::tree(){
    root = new node();
}

//getters

node* tree::getInsert(int val){
	//root���� ����. 
    node* searchNode = root;
    //root�� �θ�� ����. 
    node* parentSearchNode = NULL;
    //�Ʒ��� Ž��. 
    while (searchNode != NULL) {
        int i = 1;
        //��忡 ��� ������ �迭�� ����. 
        int* ptrval = searchNode->getElementsAll();
        //�� �迭�� ������(ptrval[0]�� ����� ����Ǿ�����)��ŭ Ž��. 
        for (; i<ptrval[0]+1; i++) {
            if (val > ptrval[i])
				continue;
            else
				break;
        }
        //�Ʒ��� ������. 
        parentSearchNode = searchNode;
        searchNode = searchNode -> getChild(i-1);
    }
    
    return parentSearchNode;
}



// �ش� node�� element�� �ٷ� �� successor node�� �ݤ��Ȥ�. 

node* tree::getSuccessor(node* n, int val){
    node* parent = n;
    int size = n->getSize();
    for (int i=1; i<size+1; i++) {
        if (n->getElementsAll()[i]==val) {
            n = n->getChild(i-1);
            break;
        }
    }
    while (n!=NULL) {
        parent = n;
        n = n->getChild(n->getSize());
    }
    return parent;
}



//command methods

//insert command�� ���� 
int tree::_insert(int val){
	//���� ��ġ ����
    node* insertNode = getInsert(val);
    node* parent = insertNode->getParent();
    insertNode->addElement(val);
    
    while(insertNode->getSize() == 4){
        int e = insertNode->split();
        if(parent == NULL) {
            parent = new node(e);
            root = parent;
        }
        else parent->addElement(e);
        
        node::addChildFromQueue(parent);
        
        // �޸� �����ؾ� �ϴ� ��찡 �� �ִ°�? 
        // - 4��带 �ʰ��ϴ� ��� = split�� �Ŀ� original node�� �޸� ����
        delete [] insertNode;
        
        insertNode = parent;
        parent = insertNode->getParent();
    }
    return 0;
}


// internal node�� ������ valment�� �����ϴ� ���successor leaf�� swap 

int tree::_delete(int val){
    node* n = _search(val);
    if (n==NULL) return -1;
    
    node* successor = getSuccessor(n, val);
    int NodeSize = successor->getSize();
 
    if (n!=successor) {
        int successEle = successor->changeByIdx(NodeSize, val);
        n->changeElement(val, successEle);
        successor->delElementByIdx(NodeSize, 1); // ������ leaf node������ �߻�
    } else {
        successor->delElement(val);
    }
    
    if (NodeSize==2 || NodeSize==3 || successor == root) return 0;
    
    // leaf node�� 2node�� ���
    q.push(successor);
    
    while (!q.empty()) {
        n = q.front(); q.pop();
        if(n->getSize()!=0) break;
        
        node* sibling = n->getSibling();
        int nodeParentIdx = n->getParentIdx();
        int siblingParentIdx = sibling->getParentIdx();
        
        // transferOffset>0  sibling�� right sibling
        int transferOffset = (siblingParentIdx - nodeParentIdx + 1)/2;
        int parentEleIdx = nodeParentIdx + transferOffset;
        
        if (sibling->getSize()!=1) {
            //transfer ����
            int EleFromSibling;
            node* ChildFromSibling;
            
            if(transferOffset>0){
            	EleFromSibling = sibling->getElementsAll()[1];
				ChildFromSibling = sibling->getChild(0);
			}
			//�� �����ΰ��. 
			else{
				EleFromSibling = sibling->getElementsAll()[sibling->getSize()];
				ChildFromSibling = sibling->getChild(sibling->getSize());
			}
         
            int EleFromParent = n->getParent()->changeByIdx(parentEleIdx, EleFromSibling);
            n->addElement(EleFromParent);
            if (transferOffset>0) {
                n->addChild(1, ChildFromSibling);
            }
			else {
                n->addChild(0, ChildFromSibling);
            }
            if(transferOffset>0){
            	sibling->delElementByIdx(1, transferOffset);
			}
			else{
				sibling->delElementByIdx(sibling->getSize(), transferOffset);
			}
            
        } else {
        	
        	
            // fusion ����. 
            node* leftNode;
            node* rightNode;
            
            if(transferOffset>0){
            	leftNode  = n;
            	rightNode = sibling;
			}
            else{
            	leftNode  = sibling;
            	rightNode = n;
			}
            int transferEleFromParent = leftNode->getParent()->delElementByIdx(parentEleIdx, 2);
            
			leftNode->addElementByIdx(transferEleFromParent, leftNode->getSize());
            leftNode->addChild(leftNode->getSize(), rightNode->getChild(0));
            
            if(rightNode->getSize()==1){
                leftNode->addElement(rightNode->getElementsAll()[1]);
                leftNode->addChild(leftNode->getSize(), rightNode->getChild(1));
            }
            
            delete [] rightNode;
            if(leftNode->getParent()==root && root->getSize()==0){
                delete [] root;
                root = leftNode;
                break;
            }
            q.push(leftNode->getParent());
        }
    }

    return 0;
}

//search�� ��� ������ ��ȸ. 
node* tree::_search(int val){
    node* searchNode = root;
    
    while (searchNode != NULL) {
        int* ptrval = searchNode->getElementsAll();
        
        int i=1;
        for (; i<ptrval[0]+1; i++) {
            if (val > ptrval[i])
				continue;
            else if(val == ptrval[i]) 
                return searchNode;
            else 
				break;
        }
        searchNode = searchNode -> getChild(i-1);
    }
    
    return searchNode;
}


// while -> level ��ŭ ���� 
// floorNum = level node 


string tree::_show(){
    int childFloorNum=0;
    int floorNum = 1;
    string ret = "";
    q.push(root);
    q.push(NULL);
        
    while (!q.empty()) {
        childFloorNum = 0;
        for (int i=0; i<floorNum; i++) {
            node* p = q.front(); q.pop();
            if (p==NULL) {
                ret += " | ";
                p = q.front(); q.pop();
            }
            
            ret += p->getStringAllElements();
            
            if(p->getChild(0) == NULL)
				continue;
            
            int size = p->getSize()+1;
            for (int j=0; j<size; j++) {
                q.push(p->getChild(j));
            }
            q.push(NULL);
            childFloorNum += size;
        }
        q.pop();
        ret += "\n";
        floorNum = childFloorNum;
    }
    return ret;
}



