#include<iostream>
#include<fstream>
#include<string>
#include <bitset>
#include<vector>


using namespace std;
#define lastIndex 3905630
string genomeSequence;

int compareStrings(int i, int j) {

	int val=0;
	int k = -1;
	int maxK = 4000000;
	while(true)
	{
		k++;
		if (k == maxK) break;
		if (genomeSequence[i + k] == genomeSequence[j + k])
			continue;
		else
		{
			if (genomeSequence[i + k] > genomeSequence[j + k]) {
					val = j;
					break;
			}
			else val = i;
			break;
		}
		
	}
	return val;

}

void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];


	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, 
		indexOfSubArrayTwo = 0; 
	int indexOfMergedArray = left; 

	
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		int val = compareStrings(leftArray[indexOfSubArrayOne], rightArray[indexOfSubArrayTwo]);
		array[indexOfMergedArray] = val;
		if (leftArray[indexOfSubArrayOne] == val) {
			indexOfSubArrayOne++;
		}
		else {
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; 
	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}



int main(int argc,char** argv)
{
	string genomeLine;
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	
	//neglect first line (id)
	getline(fin, genomeLine);

	while(true)
	{
		if (fin.eof())
			break;
		else
		{
			getline(fin, genomeLine);
			genomeSequence += genomeLine;
		}

	}
	fin.close();
	genomeSequence += '$';

	int* suffixArrayIndecees = (int*)malloc(4000000 * sizeof(int));
	auto arr_size = 4000000;
	int i = 0;
	while (true) {
		if (i == 4000000)break;
		suffixArrayIndecees[i] = i;
		i++;
		
	}


	mergeSort(suffixArrayIndecees, 0, arr_size - 1);
	
	fout.open(argv[2],ios_base::binary);
	int j = 0;
	while (true)
	{
		if (j > lastIndex) break;
		fout.write((char*)&suffixArrayIndecees[j], sizeof(int) * 2);
		j++;
	}
	fout.close();
	return 0;
}

