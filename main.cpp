#include <iostream>
#include <cstdlib>
#include <fstream>
#include "_234tree.h"

string inputProcess(tree* treeMain, string input){
    char val = input[0];
    input.erase(0, 1);
 
	switch(val){
	case 'f':
		exit(0);
		break;
    case 'i':
        treeMain->_insert(stoi(input));
        return treeMain->_show();
        break;
    case 'd':
        treeMain->_delete(stoi(input));
        return treeMain->_show();
        break;
    case 's':
    	if(treeMain->_search(stoi(input))==NULL)
    		return "찾을수 없습니다.\n";
    	else
    		return "존재합니다.\n";
        break;
    default:
        return "유효하지 않은 명령입니다.\n"; 
        break;
	}
}

int mainPrint(){
	int i;
	
	cout << "--------------------------" <<endl;
	cout << "Algorithm Assignment #2 " <<endl;
	cout << "융합전자공학부 2015003209 " <<endl;
	cout << "석정우" <<endl;
	cout << "--------------------------" <<endl;
	cout << "모드를 선택하세요.\n1) batch mode\n2) interactive mode" <<endl;
	 
	cin >> i;
	return i;
}


int main(int argc, char *argv[]){
	int sel;
    tree* treeMain = new tree;
    string inputString;
    char * filename;
 
    if(argc>1)		//batch mode로 입력받을때. 
		filename = argv[1];
	else			//그냥 실행할때. 
		filename = (char*)("batch.txt");
	
    ifstream in(filename);
    ofstream out("output.txt");
    
    sel = mainPrint();

	switch(sel){
		case 1:{
			string temp;
			
			if (in.is_open()) {
				do{
					in >> inputString;
					out << inputString <<endl;
					cout << inputString <<endl;
					
					temp = inputProcess(treeMain, inputString);
					cout << temp << endl;
			        out << temp <<endl;
				}while(!in.eof());
			} 
			else {
			
				cout << "파일을 찾을 수 없습니다!" << endl;
			}
			break;
		}
			
			
		case 2:{
			while(true){
				string temp;
		        cout << "명령을 입력하세요. (i:input, d:delete, s:search, f:finish) " << endl;
		        cin >> inputString;
		        cout << inputString <<endl;
		        out << inputString <<endl;
		        
		        temp = inputProcess(treeMain, inputString);
		        
		        cout << temp << endl;
		        out << temp <<endl;
		    }
			break;
		}
	}
	
	out.close();
    return 0;

}


