#include "pch.h"
#include "SortAlgs.h"

SortAlgs::SortAlgs(int size)
{
	m_nSize = size;
	m_pPrimalArr = new int[m_nSize];
	m_pCopyArr = new int[m_nSize];

	InsertRandomData();
}
SortAlgs::~SortAlgs()
{
	delete[] m_pPrimalArr;
	delete[] m_pCopyArr;
}

//===================================================
// sorting methods
//===================================================

void SortAlgs::SelectionSort()
{
	for (int i = 0; i < m_nSize - 1; i++)
	{
		int min_idx = i;
		int min = m_pCopyArr[i];
		for (int j = i + 1; j < m_nSize; j++)
			if (m_pCopyArr[j] < min) {
				min_idx = j;
				min = m_pCopyArr[j];
			}

		m_pCopyArr[min_idx] = m_pCopyArr[i];
		m_pCopyArr[i] = min;
	}
}

void SortAlgs::InsertionSort()
{
	for (int i = 1; i < m_nSize; i++)
	{
		int key = m_pCopyArr[i];
		int j = i - 1;

		while (j >= 0 && m_pCopyArr[j] > key)
			m_pCopyArr[j + 1] = m_pCopyArr[j--];

		m_pCopyArr[j + 1] = key;
	}
}

void SortAlgs::HalfInsertionSort()
{
	int begin;
	int end;
	int middle;
	int value;

	for (int i = 1; i < m_nSize; i++) 
	{
		value = m_pCopyArr[i];
		begin = 0;
		end = i - 1;
		while (begin <= end) {
			middle = (begin + end) / 2;

			if (value < m_pCopyArr[middle])
				end = middle - 1;
			else begin = middle + 1;
		}

		for (int j = i - 1; j >= begin; j--) {
			m_pCopyArr[j + 1] = m_pCopyArr[j];
		}

		m_pCopyArr[begin] = value;
	}
}

void SortAlgs::BubbleSort()
{
	for (int i = 0; i < m_nSize; i++)
		for (int j = m_nSize - 1; j > i; j--)
			if (m_pCopyArr[j - 1] > m_pCopyArr[j]) {
				int temp = m_pCopyArr[j - 1];
				m_pCopyArr[j - 1] = m_pCopyArr[j];
				m_pCopyArr[j] = temp;
			}
}

void SortAlgs::MixedBubbleSort()
{
	int start = 1;
	int end = m_nSize - 1;
	int k = m_nSize - 1;
	do
	{
		for (int j = end; j >= start; j--)
			if (m_pCopyArr[j - 1] > m_pCopyArr[j]) {
				int temp = m_pCopyArr[j - 1];
				m_pCopyArr[j - 1] = m_pCopyArr[j];
				m_pCopyArr[j] = temp;
				k = j;
			}

		start = k + 1;
		for (int j = start; j <= end; j++)
			if (m_pCopyArr[j - 1] > m_pCopyArr[j]) {
				int temp = m_pCopyArr[j - 1];
				m_pCopyArr[j - 1] = m_pCopyArr[j];
				m_pCopyArr[j] = temp;
				k = j;
			}

		end = k - 1;
	} while (start < end);
}

void SortAlgs::HeapSort()
{
	for (int i = m_nSize / 2; i >= 0; i--)
		HeapHelper(i, m_nSize - 1);

	for (int i = m_nSize - 1; i >= 1; i--) {
		int temp = m_pCopyArr[0];
		m_pCopyArr[0] = m_pCopyArr[i];
		m_pCopyArr[i] = temp;
		HeapHelper(0, i - 1);
	}
}

void SortAlgs::QuickSort(int left, int right)
{
	int i = left;
	int j = right;
	int val = m_pCopyArr[(left + right) / 2];

	while (i < j)
	{
		while (m_pCopyArr[i] < val) i++;
		while (m_pCopyArr[j] > val) j--;

		if (i <= j)
		{
			int temp = m_pCopyArr[i];
			m_pCopyArr[i++] = m_pCopyArr[j];
			m_pCopyArr[j--] = temp;
		}
	}
	if (left < j) QuickSort(left, j);
	if (right > i) QuickSort(i, right);
}

//===================================================
// helper methods
//===================================================

void SortAlgs::InsertRandomData()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < m_nSize; i++)
		m_pCopyArr[i] = m_pPrimalArr[i] = rand() % m_nSize;
}

void SortAlgs::ResetArrData()
{
	memcpy(m_pCopyArr, m_pPrimalArr, sizeof(int) * m_nSize);
}

void SortAlgs::HeapHelper(int root, int bottom)
{
	if (root == bottom) return;
	int left = root;
	int right = root * 2 + 1;
	int temp = m_pCopyArr[root];

	while (right <= bottom)
	{
		if (right < bottom)
			if (m_pCopyArr[right + 1] > m_pCopyArr[right])
				right++;

		if (temp > m_pCopyArr[right]) break;

		m_pCopyArr[left] = m_pCopyArr[right];
		left = right;
		right = left * 2 + 1;
	}
	m_pCopyArr[left] = temp;
}



