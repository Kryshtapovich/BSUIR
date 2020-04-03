#include <iostream>
#include <ctime>

using namespace std;

int main() {

	srand(time(0));
	int n, m;
	cout << "Enter number of rows of the array: ";
	cin >> n;
	cout << "Enter number of columns of the array: ";
	cin >> m;

	int** arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = rand() % 10 - 5;
			cout << arr[i][j] << '\t';
		}
		cout << endl << endl;
	}
	cout << endl << endl;
	int** newarr = new int* [n];

	int* length = new int[n];
	for (int i = 0; i < n; i++)
	{
		int* rep = new int[m / 2];
		for (int k = 0; k < m / 2; k++)
		{
			rep[k] = INT_MAX;
		}

		int len = 0;
		for (int j = 0; j < m; j++)
		{
			for (int z = j + 1; z < m; z++)
			{
				if (arr[i][z] == arr[i][j] && arr[i][z] != INT_MAX) 
				{                                                   
					rep[len++] = arr[i][z];				
					if (len > 1) {
						if (rep[len - 1] == rep[len - 2])
						{
							rep[len - 1] = INT_MAX;	
							len--;
						}
					}
					arr[i][z] = INT_MAX;
				}
			}
		}

		if (len)
		{
			length[i] = len;
			newarr[i] = new int[len];
		}

		for (int k = 0; k < len; k++)
		{
			newarr[i][k] = rep[k];
		}
		delete[]rep;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < length[i]; j++)
		{
			cout << newarr[i][j] << '\t';
		}
		cout << endl << endl;
	}

	for (int i = 0; i < n; i++) {
		delete[] newarr[i];
		delete[] arr[i];
	}
	delete[] newarr;
	delete[] arr;

	return 0;
}
