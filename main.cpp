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
    		return "ã���� �����ϴ�.\n";
    	else
    		return "�����մϴ�.\n";
        break;
    default:
        return "��ȿ���� ���� ����Դϴ�.\n"; 
        break;
	}
}

int mainPrint(){
	int i;
	
	cout << "--------------------------" <<endl;
	cout << "Algorithm Assignment #2 " <<endl;
	cout << "�������ڰ��к� 2015003209 " <<endl;
	cout << "������" <<endl;
	cout << "--------------------------" <<endl;
	cout << "��带 �����ϼ���.\n1) batch mode\n2) interactive mode" <<endl;
	 
	cin >> i;
	return i;
}


int main(int argc, char *argv[]){
	int sel;
    tree* treeMain = new tree;
    string inputString;
    char * filename;
 
    if(argc>1)		//batch mode�� �Է¹�����. 
		filename = argv[1];
	else			//�׳� �����Ҷ�. 
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
			
				cout << "������ ã�� �� �����ϴ�!" << endl;
			}
			break;
		}
			
			
		case 2:{
			while(true){
				string temp;
		        cout << "����� �Է��ϼ���. (i:input, d:delete, s:search, f:finish) " << endl;
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


