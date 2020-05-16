#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <ctime>
//���α׷� ���� ������� 
#define DEADLINE 1500
using namespace std;

//���������� 3���� �˰����� ����� ���� 
string returnAnswer[3];
int returnDvalue[3] = {99999, 99999, 99999};

int timeoverIdx = 0;
int nBit;
int mBit;
string ansString;
time_t start;

pair<string, int> Greedy(string * stringSet);
pair<string, int> BruteForce(string * stringSet);
pair<string, int> Branch(string * stringSet);
int HammingDistance(string * stringSet, string ansString);
void saveAnswer(string * stringSet, string ansString);
void printAllStringSet(string * stringSet);

void timeover(string * stringSet, int deadline){
	time_t now = time(NULL);
	ofstream file("output.txt", ios::out);

	if(now - start > deadline){
		returnAnswer[timeoverIdx] = ansString;
		returnDvalue[timeoverIdx] = HammingDistance(stringSet, ansString);
		int minanswer = *min_element(returnDvalue, returnDvalue+3);
		for(int i = 2; i >= 0; i--){
			
			if(returnDvalue[i] == minanswer){
				file << "string t: "<< returnAnswer[i] << endl;
				file << "d-value : "<< returnDvalue[i] << endl;
				break;
			}
			/*
			file << "string t: "<< returnAnswer[i] << endl;
			file << "d-value : "<< returnDvalue[i] << endl;
			*/
		}
		exit(0);
	}

	return;
}


int main(){
	//���α׷� ���۽� �ð� 
	start = time(NULL);
	
	//input ���� ����
	ifstream infile;
	
	//���� ����ϱ� ���� ���� 
	int minanswer;
	
	//mBit Stringdmf �ִ� 5000�� ������ �� �ִ� stringSet ����
	string stringSet[5001];
	
	//input ������ stringSet�� �����Ѵ�
	infile.open("input.txt", ios::in);
	int number = 0;
	while (getline(infile, stringSet[number])){
        number++;
    }
    
    //nBit, mBit�� ����
    nBit = number;
	mBit = stringSet[0].length();
	
	//input���� close 
	infile.close();
	
	cout << "n : " << nBit << endl << "m : " << mBit << endl;
	cout << "DeadLine Time : " << DEADLINE << "��" << endl;
	
	//���� ��Ʈ���� �׿� �ش��ϴ� d-value �����ϴ� pair 
	pair<string, int> anspair;
	
	//stringSet ���. �ʱ� ���ߴ�� ����׿� 
	//printAllStringSet(stringSet);
	
	//Greedy �˰������� ���� ��������. 
	anspair = Greedy(stringSet);
	returnAnswer[0] = anspair.first;
	returnDvalue[0] = anspair.second;

	cout << '.';
	timeoverIdx++;
	
	//Branch and Bound �˰������� ���� ��������. 
	anspair = Branch(stringSet);
	returnAnswer[1] = anspair.first;
	returnDvalue[1] = anspair.second;

	cout << '.';
	timeoverIdx++;
	
	//BruteForce �˰������� ���� ��������. 
	ofstream file("output.txt", ios::out);
	anspair = BruteForce(stringSet);
	returnAnswer[2] = anspair.first;
	returnDvalue[2] = anspair.second;

	//d-value�� ���� ���� ���� ��� 
	minanswer = *min_element(returnDvalue, returnDvalue+3);
	for(int i = 0; i <= timeoverIdx; i++){
		if(returnDvalue[i] == minanswer){
			file << "string t: "<< returnAnswer[i] << endl;
			file << "d-value : "<< returnDvalue[i] << endl;
			break;
		}
		/*
		file << "string t: "<< returnAnswer[i] << endl;
		file << "d-value : "<< returnDvalue[i] << endl;
		*/
	}
	cout << '.';
	
	//���α׷� ����ð� ����. 
	time_t end = time(NULL);
	cout << "���α׷� ����ð� : " << end - start << " ��" << endl;
	
	return 0;
}

pair<string, int> Greedy(string * stringSet){
	//��� n���� string�߿��� Ư�� m��° �ڸ��� �߿��� 0, 1 �ΰ����߿� ���� �� ������ ���� 
	int check[2];
	
	//m Bit �� �ڸ������� Ž���Ѵ�. 
	for(int i = 0; i < mBit; i++){
		//���൵�� �ð������Ǹ� ���ݱ��� ���� �� ����ϰ� ���� ����. 
		timeover(stringSet, DEADLINE);
		
		check[0] = 0; check[1] = 0;
		
		for(int j = 0; j < nBit; j++){ 
			if(stringSet[j][i] == '0'){
				check[0] ++;
			}
			else{
				check[1] ++;
			}
		}
		
		//�� ���� ���� �����ؾ� �� ���� �ع� ���Ͻ��� �ּ�ȭ �� �� �ִ�. 
		if(check[0] > check[1]){
			ansString.replace(i,0,"0");
		}
		else{
			ansString.replace(i,0,"1");
		}
	}
	
	//���� return. 
	return make_pair(ansString, HammingDistance(stringSet, ansString));
}

pair<string, int> BruteForce(string * stringSet){
	
	// mBit�� 20�ڸ� �̻�Ǹ� 2^20 * nBit�̻��� ������� -> ���α׷� ���� 
	if(mBit > 20){
		return make_pair("NULL", mBit*2);
	}
		
	int minVal = mBit;

	long idx = pow(2,mBit);
	string bruteString;

    for(long j = 0; j < idx; j++){
    	//������ Ÿ�ӿ������� 
    	timeover(stringSet, DEADLINE);
    	
    	bruteString.clear();
    	if(idx == (j+1) * 8)
    		cout << "12.5%" << endl;
    	else if(idx == (j+1) * 4)
    		cout << "25%" << endl;
    	else if(idx == (j+1) * 2)
    		cout << "50%" << endl;
       	
       	//bruteString�� j���� �ش��ϴ� �������� �ִ´�. 
    	for (int i = mBit-1; i >= 0; i--){
    		string s = std::to_string((j >> i & 1 ? 1 : 0));
    		bruteString.append(s);	
		}
		//bruteString�� �عְŸ��� ���ؼ�, ���� �ּҰ����� ������ �ٲ۴�. 
		int temp = HammingDistance(stringSet, bruteString);
		if(minVal > temp){
			minVal = temp;
			ansString = bruteString;
		}
	}
	//���� ��ȯ 
	return make_pair(ansString, HammingDistance(stringSet, ansString));
}


pair<string, int> Branch(string * stringSet){
	//��ͷ� ����������, ����Լ� ȣ�� �����÷ο찡 ���� �������� ������
	stack<pair<string, int>> st;
	
	int temp;
	int minVal = mBit;
    string est, sel0, sel1, sel2, sel3;;
	int idx, revidx;
	
	//�ʱ� �������� ��� "0"�� mBit string 
    for(int i=0;i<mBit ;i++)
		est.append("0");
	//BackTracking ����̹Ƿ�, �ٽ� ���ƿ;� �ϱ⿡ ���ÿ� �־��� 
    st.push(make_pair(est,0));
    
	while(!st.empty()){
		//�ϴٰ� �ð��ʰ� �Ǹ� ���� 
    	timeover(stringSet, DEADLINE);
    	
    	//stack�� ���� ������ 
    	est = st.top().first;
    	idx = st.top().second;
    	st.pop();
    	
    	//�Ϲ����� ����Լ� ȣ��� return�ϴ°Ͱ� ����
    	if(idx == est.length())	
			continue;
	
		int check[2] = { 0 };
		
		sel0 = est;
		sel1 = est;
		//�ϳ��� 0, �ϳ��� 1�� ���� 
		sel0[idx] = '0';
		sel1[idx] = '1';
	
		//���� �����Ѱ��� �عְŸ��� ����� 
		check[0] = HammingDistance(stringSet, sel0);
		check[1] = HammingDistance(stringSet, sel1);

		//0�� ������ 1���� ������, 0�� ���������� ��� branch�� 
        if (check[0] < check[1]){
			if(minVal > check[0]){
				minVal = check[0];
				ansString = sel0;
			}	
			st.push(make_pair(sel0, idx+1));
		}
		
		//������ �Ѵ� branch 
		else if(check[0] == check[1]){
			if(minVal > check[0]){
				minVal = check[0];
				ansString = sel0;
			}
			st.push(make_pair(sel0, idx+1));
			st.push(make_pair(sel1, idx+1));
		}	
		//1�� �� ������ 1�� ���������� branch 
		else{
			if(minVal > check[1]){
				minVal = check[1];
				ansString = sel1;
			}
			st.push(make_pair(sel1, idx+1));
		}	
       
	}
  	   
	return make_pair(ansString, HammingDistance(stringSet, ansString));
}

int HammingDistance(string * stringSet, string ansString){
	int *HammingDistance = new int[nBit] { 0 };
	int maxVal = 0;
	for(int i = 0; i < nBit; i++){
		for(int j = 0; j < mBit; j++){
			if(stringSet[i][j] != ansString[j]){
				HammingDistance[i]++;
			}
		}
	}
	maxVal = *max_element(HammingDistance, HammingDistance+nBit);
	
	return maxVal;
}


void printAllStringSet(string * stringSet){
	for(int i = 0; i < nBit; i++){
		for(int j = 0; j < mBit; j++){
			cout << stringSet[i][j];
		}
		cout << endl;
	}
}
