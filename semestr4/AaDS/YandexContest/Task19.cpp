#include <iostream>
using namespace std;

void MergeSort(int* arr, int left, int right, long* count)
{
	if (left < right)
	{
		int center = (left + right) / 2;

		MergeSort(arr, left, center, count);
		MergeSort(arr, center + 1, right, count);

		int i = left, j = center + 1, k = 0;
		int* res = new int[right - left + 1];

		while (i <= center && j <= right)
		{
			if (arr[i] < arr[j])
			{
				res[k++] = arr[i++];
			}
			else
			{
				res[k++] = arr[j++];
				*count += center - i + 1;
			}
		}

		while (i <= center)
		{
			res[k++] = arr[i++];
		}

		while (j <= right)
		{
			res[k++] = arr[j++];
		}

		for (int i = left, k = 0; i <= right; i++, k++)
		{
			arr[i] = res[k];
		}

		delete[] res;
	}
}

int main()
{
	int n;
	long count = 0;
	cin >> n;

	int* numbers = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> numbers[i];
	}

	MergeSort(numbers, 0, n - 1, &count);

	cout << count;
}
