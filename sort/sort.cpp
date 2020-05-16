#include<iostream>
#include<vector>
using namespace std;

//swap
void swap(vector<int> &v, int i, int j) {
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/************Bubble Sort**************/
void BubbleSort0(vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j])
				swap(v, i, j);
		}
	}
}
void BubbleSort(vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = v.size() - 1; j > i; --j) {
			if (v[j - 1] > v[j])
				swap(v, j - 1, j);
		}
	}
}
void BubbleSort2(vector<int> &v) {
	bool flag = true;
	for (int i = 0; i < v.size() && flag; ++i) {
		flag = false;
		for (int j = v.size() - 1; j > i; --j) {
			if (v[j - 1] > v[j]) {
				swap(v, j - 1, j);
				flag = true;
			}				
		}
	}
}

/************Selection Sort**************/
void SelectionSort(vector<int> &v) {
	int min;
	for (int i = 0; i < v.size(); ++i) {
		min = i;
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[min] > v[j])
				min = j;
		}
		if (min != i)
			swap(v, i, min);
	}
}

/************Insert Sort**************/
void InsertSort(vector<int> &v) {
	for (int i = 1, j; i < v.size(); ++i) {
		int t = v[i];
		for (j = i; j > 0; --j) {
			if (v[j-1] < t)
				break;
			v[j] = v[j-1];
		}
		v[j] = t;		
	}
}

void InsertSort1(vector<int> &v) {
	for (int i = 1, j; i < v.size(); ++i) {
		int t = v[i];
		for (j = i; j > 0 && v[j - 1] > t; --j) {			
			v[j] = v[j - 1];
		}
		v[j] = t;
	}
}

/************Shell Sort**************/
void ShellSort(vector<int> &v) {
	int gap = v.size();
	do {
		//gap = gap / 3 + 1;
		gap /= 2;
		for (int i = gap, j; i < v.size(); ++i) {
			int t = v[i];
			for (j = i - gap; j >= 0; j -= gap) {
				if (v[j] < t)
					break;
				v[j + gap] = v[j];
			}
			v[j + gap] = t;
		}
	} while (gap > 1);
}

/************Heap Sort**************/
void HeapAdjust(vector<int> &v, int s, int m) {
	int temp = v[s];
	for (int j = 2 * s + 1; j <= m; j = 2 * j + 1) {
		if (j < m && v[j] < v[j + 1])
			j++;
		if (v[j] < temp)
			break;
		v[s] = v[j];
		s = j;
	}
	v[s] = temp;
}
void HeapSort(vector<int> &v) {
	for (int i = v.size() / 2 - 1; i >= 0; --i) {
		HeapAdjust(v, i, v.size() - 1);
	}
	for (int i = v.size() - 1; i > 0; --i) {
		swap(v, 0, i);
		HeapAdjust(v, 0, i - 1);
	}
}


/************Merging Sort**************/
void Merge(const vector<int> &v, vector<int> &v1, int s, int m, int t) {
	int j, k;
	for (j = m + 1, k = s; s <= m && j <= t; ++k) {
		if (v[s] < v[j])
			v1[k] = v[s++];
		else
			v1[k] = v[j++];
	}
	if (s <= m) {
		for (; s <= m; ++s, ++k)
			v1[k] = v[s];
	}
	if (j <= t) {
		for (; j <= t; ++j, ++k)
			v1[k] = v[j];
	}
}
void MSort(const vector<int> &v, vector<int> &v1, int s, int t) {
	int m;
	vector<int> v2(v.size());
	if (s == t) {
		v1[s] = v[s];
	}
	else {
		m = (s + t) / 2;
		MSort(v, v2, s, m);		//递归将v[s...m]归并为有序的v2[s...m]
		MSort(v, v2, m + 1, t);	//递归将v[m+1...t]归并为有序的v2[m+1...t]
		Merge(v2, v1, s, m, t);	//将有序的v2[s...m]和v2[m+1...t]归并为v1中
	}
}
void MergeSort(vector<int> &v) {
	MSort(v, v, 0, v.size() - 1);
}


/************Quick Sort**************/
//交换待排序数组中的顺序，是位于枢轴pivot左边的值都小于该值，使其右边的值都大于该值
int Partition(vector<int> &v, int low, int high) {
	int pivotvalue = v[low];
	while (low < high) {
		while (low < high&&v[high] >= pivotvalue)
			high--;
		swap(v, low, high);
		while (low < high&&v[low] <= pivotvalue)
			low++;
		swap(v, low, high);
	}
	return low;
}
//对子数组进行快速排序
void QSort(vector<int> &v, int low, int high) {
	int pivot;	//枢轴
	if (low < high) {		
		pivot = Partition(v, low, high);	//将v[low...high]一分为二，并计算出枢轴值pivot
		QSort(v, low, pivot - 1);			//对低子数组递归排序
		QSort(v, pivot + 1, high);			//对高子数组递归排序
	}
}

void QuickSort(vector<int> &v) {
	QSort(v, 0, v.size() - 1);
}



int main() {
	vector<int> v1 = { 9,1,4,5,3,7,8};
	vector<int> v2 = { 9,1,4,5,3,7,8 };
	vector<int> v3 = { 9,1,4,5,3,7,8 };
	vector<int> v4 = { 9,1,4,5,3,7,8 };
	vector<int> v5 = { 9,1,4,5,3,7,8 };
	
	for (int i = 0; i < v1.size(); ++i) {
		cout << v1[i] << " ";
	}
	cout << endl;

	BubbleSort0(v1);
	BubbleSort(v2);
	BubbleSort2(v3);
	SelectionSort(v4);
	/*InsertSort(v5);	*/
	InsertSort1(v5);

	for (int i = 0; i < v1.size(); ++i) {
		cout << v1[i] << " ";
	}
	cout << endl;
	
	for (int i = 0; i < v1.size(); ++i) {
		cout << v2[i] << " ";
	}
	cout << endl; 
	
	for (int i = 0; i < v1.size(); ++i) {
		cout << v3[i] << " ";
	}
	cout << endl; 
	
	for (int i = 0; i < v1.size(); ++i) {
		cout << v4[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < v1.size(); ++i) {
		cout << v5[i] << " ";
	}
	cout << endl << endl;

	vector<int> v6 = { 8,11,2,45,23,43,20,15,16 };
	vector<int> v7 = { 8,11,2,45,23,43,20,15,16 };
	vector<int> v8 = { 8,11,2,45,23,43,20,15,16 };
	for (int i = 0; i < v6.size(); ++i) {
		cout << v6[i] << " ";
	}
	cout << endl;

	ShellSort(v6);
	QuickSort(v7);
	MergeSort(v8);
	for (int i = 0; i < v6.size(); ++i) {
		cout << v6[i] << " ";
	}
	cout << endl;
	
	for (int i = 0; i < v7.size(); ++i) {
		cout << v7[i] << " ";
	}
	cout << endl;
	
	for (int i = 0; i < v8.size(); ++i) {
		cout << v8[i] << " ";
	}
	cout << endl;

	return 0;
}