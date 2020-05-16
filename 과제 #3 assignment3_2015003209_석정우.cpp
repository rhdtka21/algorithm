#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <ctime>
//프로그램 종료 데드라인 
#define DEADLINE 1500
using namespace std;

//최종적으로 3가지 알고리즘의 결과를 저장 
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
	//프로그램 시작시 시간 
	start = time(NULL);
	
	//input 파일 오픈
	ifstream infile;
	
	//정답 출력하기 위한 변수 
	int minanswer;
	
	//mBit Stringdmf 최대 5000개 저장할 수 있는 stringSet 선언
	string stringSet[5001];
	
	//input 파일을 stringSet에 저장한다
	infile.open("input.txt", ios::in);
	int number = 0;
	while (getline(infile, stringSet[number])){
        number++;
    }
    
    //nBit, mBit값 저장
    nBit = number;
	mBit = stringSet[0].length();
	
	//input파일 close 
	infile.close();
	
	cout << "n : " << nBit << endl << "m : " << mBit << endl;
	cout << "DeadLine Time : " << DEADLINE << "초" << endl;
	
	//정답 스트링과 그에 해당하는 d-value 저장하는 pair 
	pair<string, int> anspair;
	
	//stringSet 출력. 초기 개발당시 디버그용 
	//printAllStringSet(stringSet);
	
	//Greedy 알고리즘으로 구한 정답저장. 
	anspair = Greedy(stringSet);
	returnAnswer[0] = anspair.first;
	returnDvalue[0] = anspair.second;

	cout << '.';
	timeoverIdx++;
	
	//Branch and Bound 알고리즘으로 구한 정답저장. 
	anspair = Branch(stringSet);
	returnAnswer[1] = anspair.first;
	returnDvalue[1] = anspair.second;

	cout << '.';
	timeoverIdx++;
	
	//BruteForce 알고리즘으로 구한 정답저장. 
	ofstream file("output.txt", ios::out);
	anspair = BruteForce(stringSet);
	returnAnswer[2] = anspair.first;
	returnDvalue[2] = anspair.second;

	//d-value가 제일 작은 정답 출력 
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
	
	//프로그램 종료시간 측정. 
	time_t end = time(NULL);
	cout << "프로그램 실행시간 : " << end - start << " 초" << endl;
	
	return 0;
}

pair<string, int> Greedy(string * stringSet){
	//모든 n개의 string중에서 특정 m번째 자리수 중에서 0, 1 두가지중에 뭐가 더 많은지 저장 
	int check[2];
	
	//m Bit 각 자리수마다 탐색한다. 
	for(int i = 0; i < mBit; i++){
		//실행도중 시간오버되면 지금까지 구한 답 출력하고 강제 종료. 
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
		
		//더 많은 것을 선택해야 그 때의 해밍 디스턴스를 최소화 할 수 있다. 
		if(check[0] > check[1]){
			ansString.replace(i,0,"0");
		}
		else{
			ansString.replace(i,0,"1");
		}
	}
	
	//정답 return. 
	return make_pair(ansString, HammingDistance(stringSet, ansString));
}

pair<string, int> BruteForce(string * stringSet){
	
	// mBit가 20자리 이상되면 2^20 * nBit이상의 연산과정 -> 프로그램 오류 
	if(mBit > 20){
		return make_pair("NULL", mBit*2);
	}
		
	int minVal = mBit;

	long idx = pow(2,mBit);
	string bruteString;

    for(long j = 0; j < idx; j++){
    	//실행중 타임오버나면 
    	timeover(stringSet, DEADLINE);
    	
    	bruteString.clear();
    	if(idx == (j+1) * 8)
    		cout << "12.5%" << endl;
    	else if(idx == (j+1) * 4)
    		cout << "25%" << endl;
    	else if(idx == (j+1) * 2)
    		cout << "50%" << endl;
       	
       	//bruteString에 j값에 해당하는 이진수를 넣는다. 
    	for (int i = mBit-1; i >= 0; i--){
    		string s = std::to_string((j >> i & 1 ? 1 : 0));
    		bruteString.append(s);	
		}
		//bruteString의 해밍거리를 구해서, 현재 최소값보다 작으면 바꾼다. 
		int temp = HammingDistance(stringSet, bruteString);
		if(minVal > temp){
			minVal = temp;
			ansString = bruteString;
		}
	}
	//정답 반환 
	return make_pair(ansString, HammingDistance(stringSet, ansString));
}


pair<string, int> Branch(string * stringSet){
	//재귀로 구현했으나, 재귀함수 호출 오버플로우가 나서 스택으로 구현함
	stack<pair<string, int>> st;
	
	int temp;
	int minVal = mBit;
    string est, sel0, sel1, sel2, sel3;;
	int idx, revidx;
	
	//초기 예측값은 모두 "0"인 mBit string 
    for(int i=0;i<mBit ;i++)
		est.append("0");
	//BackTracking 방법이므로, 다시 돌아와야 하기에 스택에 넣어줌 
    st.push(make_pair(est,0));
    
	while(!st.empty()){
		//하다가 시간초과 되면 종료 
    	timeover(stringSet, DEADLINE);
    	
    	//stack의 맨위 꺼내기 
    	est = st.top().first;
    	idx = st.top().second;
    	st.pop();
    	
    	//일반적인 재귀함수 호출시 return하는것과 동일
    	if(idx == est.length())	
			continue;
	
		int check[2] = { 0 };
		
		sel0 = est;
		sel1 = est;
		//하나는 0, 하나는 1로 예측 
		sel0[idx] = '0';
		sel1[idx] = '1';
	
		//각각 예측한것의 해밍거리를 계산함 
		check[0] = HammingDistance(stringSet, sel0);
		check[1] = HammingDistance(stringSet, sel1);

		//0을 넣은게 1보다 작으면, 0을 넣은것으로 계속 branch함 
        if (check[0] < check[1]){
			if(minVal > check[0]){
				minVal = check[0];
				ansString = sel0;
			}	
			st.push(make_pair(sel0, idx+1));
		}
		
		//같으면 둘다 branch 
		else if(check[0] == check[1]){
			if(minVal > check[0]){
				minVal = check[0];
				ansString = sel0;
			}
			st.push(make_pair(sel0, idx+1));
			st.push(make_pair(sel1, idx+1));
		}	
		//1이 더 작으면 1을 넣은것으로 branch 
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
