#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>

#define MAXSIZE 100000
#define SIZE 10000
using namespace std;
using namespace chrono;

string ver, dates, times;
int HEAPSIZE = SIZE;
int ARRSIZE = SIZE;

//Menu Display
int menu() {
	int x;
	cout << "수행할 작업을 선택하세요." << endl;
	cout << "1) 랜덤 추출한 YouTube 동영상 조회수 정렬" << endl;
	cout << "2) 2019 ~ 1981년 까지 원-달러 환율" << endl;
	cout << "3) 인터넷 게임 리그오브레전드 평균 플레이 시간 정렬" << endl;
	cout << "4) 0부터 N까지 랜덤 숫자 정렬" << endl;
	cout << "5) 0부터 N까지 정렬된 숫자 정렬" << endl;
	cout << "6) 0부터 N까지 역순으로 정렬된 숫자 정렬" << endl;
	cout << "-1) 종료" << endl;

	cin >> x;
	return x;
}
//Write arr in "input.txt" 
void ReRoll_Random();
void ReRoll_Sorted();
void ReRoll_InverseSorted();
//Read arr in "input.txt"
void GetData(int* arr, const char* filename);

//Show Sorting Result
void ShowResult(int* arr, int len, string method, const char* resultname);

//Calculate running time
void ShowTime(nanoseconds sec, string method);

//argument 숫자별로 테스트 실행함수 
void StartTest_2(void (*SortingAlgorithm)(int*, int), string method, const char* filename, const char* resultname);
void StartTest_3(void (*SortingAlgorithm)(int*, int, int), string method, const char* filename, const char* resultname);
void StartTest_1(void (*SortingAlgorithm)(int*), string method, const char* filename, const char* resultname);

//Swap
void Swapping(int* data1, int* data2);

// Sorting Algorithms
void BubbleSort(int* arr, int len);

void SelectionSort(int* arr, int len);

void InsertionSort(int* arr, int len);

void MergeTwoArr(int* arr, int left, int mid, int right);
void MergeSort(int* arr, int left, int right);

int Partition(int* arr, int left, int right);
void QuickSort(int* arr, int left, int right);

void Heapify(int i);
void BuildMaxHeap(int* arr);
void HeapSort(int* arr);

void SequentialQuickSort(int* arr, int n);

void SequentialMergeSort(int arr[], int len);

int main() {
	while (1) {
		int x;
		x = menu();
		if (x == -1)
			break;

		switch (x) {
		case 1:		// 랜덤추출한 YouTube 동영상 조회수 정렬 
			StartTest_2(BubbleSort, "Bubble", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_2(SelectionSort, "Selection", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_2(InsertionSort, "Insertion", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_3(MergeSort, "Merge", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_3(QuickSort, "Quick", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_1(HeapSort, "Heap", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "youtubeview.txt", "sorted_youtubeview.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "youtubeview.txt", "sorted_youtubeview.txt");
			break;
		case 2: 	// 2019 ~ 1981년 까지 원-달러 환율 정렬 
			StartTest_2(BubbleSort, "Bubble", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_2(SelectionSort, "Selection", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_2(InsertionSort, "Insertion", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_3(MergeSort, "Merge", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_3(QuickSort, "Quick", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_1(HeapSort, "Heap", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "exchangerate.txt", "sorted_exchangerate.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "exchangerate.txt", "sorted_exchangerate.txt");
			break;
		case 3:		// 인터넷 게임 리그오브레전드 평균 플레이 시간 정렬 
			StartTest_2(BubbleSort, "Bubble", "loltime.txt", "sorted_loltime.txt");
			StartTest_2(SelectionSort, "Selection", "loltime.txt", "sorted_loltime.txt");
			StartTest_2(InsertionSort, "Insertion", "loltime.txt", "sorted_loltime.txt");
			StartTest_3(MergeSort, "Merge", "loltime.txt", "sorted_loltime.txt");
			StartTest_3(QuickSort, "Quick", "loltime.txt", "sorted_loltime.txt");
			StartTest_1(HeapSort, "Heap", "loltime.txt", "sorted_loltime.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "loltime.txt", "sorted_loltime.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "loltime.txt", "sorted_loltime.txt");
			break;
		case 4:		//랜덤한 숫자데이터 텍스트파일을 생성
			cout << "100,000 이하의 정수 입력" << endl;
			cin >> ARRSIZE;
			ReRoll_Random();			//input.txt에 랜덤한 배열 생성 
			StartTest_2(BubbleSort, "Bubble", "input.txt", "sorted_random.txt");
			StartTest_2(SelectionSort, "Selection", "input.txt", "sorted_random.txt");
			StartTest_2(InsertionSort, "Insertion", "input.txt", "sorted_random.txt");
			StartTest_3(MergeSort, "Merge", "input.txt", "sorted_random.txt");
			StartTest_3(QuickSort, "Quick", "input.txt", "sorted_random.txt");
			StartTest_1(HeapSort, "Heap", "input.txt", "sorted_random.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "input.txt", "sorted_random.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "input.txt", "sorted_random.txt");
			break;
		case 5: 	//정렬된 숫자데이터 텍스트파일을 생성
			cout << "100,000 이하의 정수 입력" << endl;
			cin >> ARRSIZE;
			ReRoll_Sorted();			//input.txt에 정렬된 배열 생성 
			StartTest_2(BubbleSort, "Bubble", "input.txt", "sorted_sorted.txt");
			StartTest_2(SelectionSort, "Selection", "input.txt", "sorted_sorted.txt");
			StartTest_2(InsertionSort, "Insertion", "input.txt", "sorted_sorted.txt");
			StartTest_3(MergeSort, "Merge", "input.txt", "sorted_sorted.txt");
			StartTest_3(QuickSort, "Quick", "input.txt", "sorted_sorted.txt");
			StartTest_1(HeapSort, "Heap", "input.txt", "sorted_sorted.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "input.txt", "sorted_sorted.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "input.txt", "sorted_sorted.txt");
			break;
		case 6: 	//역순으로 정렬된 숫자데이터 텍스트파일을 생성
			cout << "100,000 이하의 정수 입력" << endl;
			cin >> ARRSIZE;
			ReRoll_InverseSorted();			//input.txt에 역순으로 정렬된 배열 생성 
			StartTest_2(BubbleSort, "Bubble", "input.txt", "sorted_inversesorted.txt");
			StartTest_2(SelectionSort, "Selection", "input.txt", "sorted_inversesorted.txt");
			StartTest_2(InsertionSort, "Insertion", "input.txt", "sorted_inversesorted.txt");
			StartTest_3(MergeSort, "Merge", "input.txt", "sorted_inversesorted.txt");
			StartTest_3(QuickSort, "Quick", "input.txt", "sorted_inversesorted.txt");
			StartTest_1(HeapSort, "Heap", "input.txt", "sorted_inversesorted.txt");
			StartTest_2(SequentialQuickSort, "Sequential Quick", "input.txt", "sorted_inversesorted.txt");
			StartTest_2(SequentialMergeSort, "Sequential Merge", "input.txt", "sorted_inversesorted.txt");
			break;
		}
	}
	return 0;
}


void ReRoll_Random() {
struct tm *datetime;
	time_t timer;
	timer = time(NULL);
    datetime = localtime(&timer);
    
	_unlink("input.txt");
	srand(timer);
	
	fstream file;
	file.open("input.txt", ios::app);
	
	file << ARRSIZE << endl;
	for(int i =1; i<=ARRSIZE; i++){
    	file << rand() % ARRSIZE << endl;
	}

	file << endl << "Random ";
	file << "(" << datetime->tm_year + 1900 << "/";
	file << datetime->tm_mon +1 << "/";
	file << datetime->tm_mday << ") ";
	file << datetime->tm_hour << ":";
	file << datetime->tm_min << ":";
	file << datetime->tm_sec;
	
	file.close();
}

void ReRoll_Sorted() {
	struct tm *datetime;
	time_t timer;
	timer = time(NULL);
    datetime = localtime(&timer);
    
	_unlink("input.txt");
	
	fstream file;
	file.open("input.txt", ios::app);
	
	file << ARRSIZE << endl;
	for(int i =0; i<ARRSIZE; i++){
    	file << i << endl;
	}

	file << endl << "Sorted ";
	file << "(" << datetime->tm_year + 1900 << "/";
	file << datetime->tm_mon +1 << "/";
	file << datetime->tm_mday << ") ";
	file << datetime->tm_hour << ":";
	file << datetime->tm_min << ":";
	file << datetime->tm_sec;
	
	file.close();
}

void ReRoll_InverseSorted() {
	struct tm *datetime;
	time_t timer;
	timer = time(NULL);
    datetime = localtime(&timer);
    
	_unlink("input.txt");
	
	fstream file;
	file.open("input.txt", ios::app);

	file << ARRSIZE << endl;
	for(int i =0; i<ARRSIZE; i++){
    	file << ARRSIZE - i << endl;
	}

	file << endl << "InverseSorted ";
	file << "(" << datetime->tm_year + 1900 << "/";
	file << datetime->tm_mon +1 << "/";
	file << datetime->tm_mday << ") ";
	file << datetime->tm_hour << ":";
	file << datetime->tm_min << ":";
	file << datetime->tm_sec;
	
	file.close();
}

void GetData(int* arr, const char* filename) {
	fstream file;
	file.open(filename, ios::in);
	file >> ARRSIZE;
	HEAPSIZE = ARRSIZE;
	cout << "SIZE : " << ARRSIZE << endl;
	for (int i = 0; i < ARRSIZE; i++) {
		file >> arr[i];
	}
	file >> ver >> dates >> times;
	cout << ver << endl << dates << " " << times << endl;
	file.close();

}

void ShowResult(int* arr, int len, string method, const char* resultname) {
	_unlink(resultname);

	fstream file;
	file.open(resultname, ios::app);

	for (int i = 0; i < len; i++) {
		file << arr[i] << " ";
	}

}

void ShowTime(nanoseconds sec, string method) {
	if (sec.count() <= 10000000)
		cout << method << " Running Time : " << sec.count() << "ns" << endl;
	cout << method << " Running Time : " << sec.count() / 1000000 << "ms" << endl << endl;
}

void StartTest_2(void (*SortingAlgorithm)(int*, int), string method, const char* filename, const char* resultname) {
	int arr[MAXSIZE];
	GetData(arr, filename);

	system_clock::time_point startns = system_clock::now();
	SortingAlgorithm(arr, ARRSIZE);;
	system_clock::time_point endns = system_clock::now();
	nanoseconds nanoSec = duration_cast<nanoseconds>(endns - startns);
	ShowResult(arr, ARRSIZE, method, resultname);
	ShowTime(nanoSec, method);
}

void StartTest_3(void (*SortingAlgorithm)(int*, int, int), string method, const char* filename, const char* resultname) {
	int arr[MAXSIZE];
	GetData(arr, filename);

	system_clock::time_point startns = system_clock::now();
	SortingAlgorithm(arr, 0, ARRSIZE - 1);
	system_clock::time_point endns = system_clock::now();
	nanoseconds nanoSec = endns - startns;
	ShowResult(arr, ARRSIZE, method, resultname);
	ShowTime(nanoSec, method);
}

void StartTest_1(void (*SortingAlgorithm)(int*), string method, const char* filename, const char* resultname) {
	int arr[MAXSIZE];
	GetData(arr, filename);

	system_clock::time_point startns = system_clock::now();
	SortingAlgorithm(arr);
	system_clock::time_point endns = system_clock::now();
	nanoseconds nanoSec = endns - startns;
	ShowResult(arr, ARRSIZE, method, resultname);
	ShowTime(nanoSec, method);
}

void Swapping(int* data1, int* data2) {
	int temp;
	temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

void BubbleSort(int* arr, int len) {
	int i = len - 1;
	int j;

	while (i > 0) {
		for (j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1])
				Swapping(&arr[j], &arr[j + 1]);
		}
		i--;
	}
}

void SelectionSort(int* arr, int len) {
	int i, j;
	int minidx;
	for (i = 0; i < len; i++) {
		minidx = i;
		for (j = i; j < len; j++) {
			if (arr[minidx] > arr[j])
				minidx = j;
		}
		Swapping(&arr[i], &arr[minidx]);
	}
}

void InsertionSort(int* arr, int len) {
	int temp;
	int j;
	for (int i = 1; i < len; i++) {
		temp = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] >= temp)
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = temp;
	}
}

void MergeTwoArr(int arr[], int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* L;
	int* R;
	// 임시 배열 생성
	L = new int[sizeof(int) * n1];
	R = new int[sizeof(int) * n2];
	// 임시 배열에다가 데이터를 복사
	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];
	// 다시 임시 배열들을 합친다
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	// 남아 있는 L의 나머지값을 복사한다
	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}
	// 남아 있는 R의 나머지값을 복사한다
	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}
void MergeSort(int arr[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArr(arr, left, mid, right);
	}
}

int Partition(int arr[], int left, int right) {
	static int cnt = 0;
	int front, rear;
	int pivot = left + rand() % (right - left + 1); 			//피봇 랜덤 선택 
	//int pivot = right;											//피봇 오른쪽 값 선 

	int pivotval = arr[pivot];
	Swapping(&arr[pivot], &arr[right]);							//pivot을 맨 오른쪽에 놓는다. 

	front = left;
	rear = right - 1;
	//printf("pivot = %d\n", pivotval);
	while (front <= rear) {
		while (pivotval >= arr[front] && front <= right - 1)
			front++;
		while (pivotval <= arr[rear] && rear >= left)
			rear--;
		if (front <= rear)
			Swapping(&arr[front], &arr[rear]);
	}
	Swapping(&arr[right], &arr[front]);
	cnt++;
	//printf("\n cnt : %d ", cnt);
	return front;
}
void QuickSort(int arr[], int left, int right) {
	if (left < right) {
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}

void Heapify(int* arr, int i) {

	int cur = 2 * i + 1;

	if (cur > HEAPSIZE - 1)
		return;

	if (arr[cur] < arr[cur + 1])
		cur++;

	if (arr[i] <= arr[cur]) {
		Swapping(&arr[i], &arr[cur]);
		if (cur <= HEAPSIZE / 2)
			Heapify(arr, cur);
	}
}

void BuildMaxHeap(int* arr) {
	for (int i = HEAPSIZE / 2 - 1; i >= 0; i--) {
		Heapify(arr, i);
	}
}

void HeapSort(int* arr) {
	BuildMaxHeap(arr);

	for (int i = SIZE; i > 1; i--) {
		Swapping(&arr[0], &arr[i]);
		HEAPSIZE--;
		Heapify(arr, 0);
	}
}

void SequentialQuickSort(int* arr, int n) {
	int start, end, left, right;
	int pv, t;
	int* pBase;
	int top = -1;

	// 인덱스를 저장할 스택 할당: 최대 스택의 크기 2n+2 <--- 역순정렬시 최대 스택 필요
	pBase = new int[sizeof(int) * (2 * n + 2)];
	if (!pBase) {
		return;
	}

	// 첫번째 요소 push: 먼저 꺼내려는 것을 나중에 push해야 한다.(LIFO 구조)
	pBase[++top] = n - 1;
	pBase[++top] = 0;

	// 스택이 empty 상태면 빠져나온다.
	while (top != -1) {
		// pop
		start = pBase[top--]; // pop
		end = pBase[top--]; // pop

		// 갯수가 2 이상인 경우
		if (end - start + 1 > 1) {

			// 피벗 결정
			pv = arr[end];

			// 좌우측 인덱스 설정 및 비교, 교환
			left = start; right = end - 1;
			while (1) {
				while (arr[left] < pv)
					++left;
				while (right > start && arr[right] > pv)
					--right; 				// 시작 인덱스보다 작거나 같으면 값 조사 필요 없다.
				if (left >= right)
					break;
				t = arr[left];
				arr[left] = arr[right];
				arr[right] = t;
				++left;
				--right;
			}

			// 피벗 자리와 left 자리 교환
			arr[end] = arr[left];
			arr[left] = pv;

			// 좌우측 push: 먼저 꺼내려는 것을 나중에 push해야 한다.(LIFO 구조)
			pBase[++top] = end;   // push(end);
			pBase[++top] = left + 1;  // push(left+1);
			pBase[++top] = left - 1;  // push(left-1);
			pBase[++top] = start;   // push(start);   
		}
	}

	// 스택 해제
	delete[] pBase;
}

void SequentialMergeSort(int * arr, int len){
	int* temp;
	temp = new int[sizeof(int) * (len)];
	int i,j,k,l1,h1,l2,h2;

	//l1은 lower bound.
	for(int size=1; size < len; size=size*2 ){
		l1=0;
		k=0;  //temp array에 접근하기 위한 index
		while( l1+size < len){
			h1=l1+size-1;
			l2=h1+1;
			h2=l2+size-1;
			
			if( h2>=len ) 
				h2=len-1;
			
			//두개를 합치는 과정
			i=l1;
			j=l2;
	
			while(i<=h1 && j<=h2 ){
				if( arr[i] <= arr[j] )
					temp[k++]=arr[i++];
				else
					temp[k++]=arr[j++];
			}
			while(i<=h1)
				temp[k++]=arr[i++];
			while(j<=h2)
				temp[k++]=arr[j++];
			//Merge 성공
			l1=h2+1; 
		}
		//남은것 다시 넣기
		for(i=l1; k<len; i++) 
			temp[k++]=arr[i];

		for(i=0;i<len;i++)
			arr[i]=temp[i];
	}
}


