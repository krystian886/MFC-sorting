#pragma once
class SortAlgs
{
public:
	
	SortAlgs(int Size);
	~SortAlgs();

public:
	void SelectionSort();
	void InsertionSort();
	void HalfInsertionSort();
	void BubbleSort();
	void MixedBubbleSort();
	void HeapSort();
	void QuickSort(int left, int right);

	void ResetArrData();

private:
	void InsertRandomData();
	void HeapHelper(int root, int bottom);

private:
	int* m_pPrimalArr;
	int* m_pCopyArr;
	int m_nSize;
};

