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
        return "해당 element가 존재하지 않습니다.";
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


// 상위클래스 tree에 의하여 input parameter idx의 유효성을 보장
//childeren 중 idx를 지정해서 반환 
node* node::getChild(int idx){
    return children[idx];
}
//elements 모두 반환 
int* node::getElementsAll(){
    return elements;
}
//children 모두 반환 
node** node::getChildrenAll(){
    return children;
}
//첫번째 element반환 
int node::getFirstElement(){
    return elements[1];
}

//내가 몇번째 children인지 파악 
int node::getParentIdx(){
    int myidx = 0;
    
    while(1){
        if(parent->getChild(myidx)==this) break;
        myidx++;
    }
    return myidx;
}

//현재 노드의 상태 (2, 3, 4) 반환 
int node::getSize(){
    return elements[0];
}

// 자신을 포함한 sibling node의 갯수를 반환
int node::getSiblingNum(){
    return parent->getSize()+1;
}

// 상위클래스 tree에 의하여 sibling이 반드시 존재하는 node에서만 호출됨을 보장
// sibling이 없는 경우인 root만 존재하는 경우 tree클래스가 예외처리
// sibling 중 3,4 node가 우선 순위를 갖고 반환

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

// fusion case에도 child는 맨 앞 index 또는 맨 뒤 index에 추가되는 경우만 존재
// element의 유효성에 관여X, 추가된 child와 관계하는 element는 tree에 의해 추가됨을 보장
// 외부에서 child node가 추가되는 경우에는 delete의 fusion 경우
// insert의node는 addChildFromQueue에서 처리한다. (큐를 사용한 이유) 


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


// 노드 입력범위 초과하면 -1 return
// 추가된 element에 의해 빈 children은 tree 의해 채워진다 
 
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
    //사이즈 증가
    elements[0]++;
    //정상실행시 0 반환
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

// split된 node들을 queue에서 꺼내 input node의 children으로 연결

int node::addChildFromQueue(node* n){
	//큐가 비면 해당X 
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


// 상위클래스 tree에 의해서elements의 사이즈가 5인 node에서만 호출됨을 보장
// split된 node는 node class의 static queue에 저장되어서 addChildFromQueue 함수에서 사용
int node::split(){
    int ele1[3], ele2[2];
    node* ptre1[3], *ptre2[2];
    
    // 첫번째 split에 옮겨담는다. 
    ele1[0] = 2;
    ptre1[0] = children[0];
    for (int i=1; i<3; i++) {
        ele1[i] = elements[i];
        ptre1[i] = children[i];
    }
    
    node* child1 = new node(ele1, ptre1);
    q.push(child1);
    
    // 두번째 split에 옮겨담는다. 
    ele2[0] = 1;
    ele2[1] = elements[4];
    ptre2[0] = children[3];
    ptre2[1] = children[4];
    
    node* child2 = new node(ele2, ptre2);
    q.push(child2);
    
    return elements[3];
}


//delete and change methods



// element가 존재하지않으면 -1 return
// 상위 클래스 tree에 의해서 항상 삭제할 element가 존재하는 node에서만 호출됨을 보장받는다.
 

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


// 같은 element가 존재할 때 생기는 이슈로 인해 idx로 element를 삭제하는 function 추가

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

// 상위클래스 tree에 의해서 대체될 element가 항상 존재하는 leaf node에서만 호출됨을 보장받는다. 

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


// 같은 element가 존재할 때 생기는 이슈로 인해 idx로 element를 변경하는 function 추가

int node::changeByIdx(int originIdx, int src){
    int originEle = elements[originIdx];
    elements[originIdx] = src;
    
    return originEle;
}



//생성자. root node를 생성합니다. 
tree::tree(){
    root = new node();
}

//getters

node* tree::getInsert(int val){
	//root부터 시작. 
    node* searchNode = root;
    //root의 부모는 없음. 
    node* parentSearchNode = NULL;
    //아래로 탐색. 
    while (searchNode != NULL) {
        int i = 1;
        //노드에 담긴 값들의 배열을 전달. 
        int* ptrval = searchNode->getElementsAll();
        //그 배열의 사이즈(ptrval[0]에 사이즈가 저장되어있음)만큼 탐색. 
        for (; i<ptrval[0]+1; i++) {
            if (val > ptrval[i])
				continue;
            else
				break;
        }
        //아래로 내려감. 
        parentSearchNode = searchNode;
        searchNode = searchNode -> getChild(i-1);
    }
    
    return parentSearchNode;
}



// 해당 node의 element의 바로 전 successor node를 반ㅎㅘㄴ. 

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

//insert command를 수행 
int tree::_insert(int val){
	//넣을 위치 선정
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
        
        // 메모리 해제해야 하는 경우가 더 있는가? 
        // - 4노드를 초과하는 경우 = split한 후에 original node를 메모리 해제
        delete [] insertNode;
        
        insertNode = parent;
        parent = insertNode->getParent();
    }
    return 0;
}


// internal node에 삭제할 valment가 존재하는 경우successor leaf와 swap 

int tree::_delete(int val){
    node* n = _search(val);
    if (n==NULL) return -1;
    
    node* successor = getSuccessor(n, val);
    int NodeSize = successor->getSize();
 
    if (n!=successor) {
        int successEle = successor->changeByIdx(NodeSize, val);
        n->changeElement(val, successEle);
        successor->delElementByIdx(NodeSize, 1); // 무조건 leaf node에서만 발생
    } else {
        successor->delElement(val);
    }
    
    if (NodeSize==2 || NodeSize==3 || successor == root) return 0;
    
    // leaf node가 2node일 경우
    q.push(successor);
    
    while (!q.empty()) {
        n = q.front(); q.pop();
        if(n->getSize()!=0) break;
        
        node* sibling = n->getSibling();
        int nodeParentIdx = n->getParentIdx();
        int siblingParentIdx = sibling->getParentIdx();
        
        // transferOffset>0  sibling은 right sibling
        int transferOffset = (siblingParentIdx - nodeParentIdx + 1)/2;
        int parentEleIdx = nodeParentIdx + transferOffset;
        
        if (sibling->getSize()!=1) {
            //transfer 과정
            int EleFromSibling;
            node* ChildFromSibling;
            
            if(transferOffset>0){
            	EleFromSibling = sibling->getElementsAll()[1];
				ChildFromSibling = sibling->getChild(0);
			}
			//맨 왼쪽인경우. 
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
        	
        	
            // fusion 과정. 
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

//search의 경우 간단한 순회. 
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


// while -> level 만큼 실행 
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



