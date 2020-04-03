#include <iostream>
#include <vector>
using namespace std;

long long n;
long long mod = (long long)1e9 + 7;

vector<vector<long long>> matrix_mul(vector<vector<long long>>& first_matrix, vector<vector<long long>> second_matrix) 
{
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for (long long i = 0; i < first_matrix.size(); i++) 
    {
        for (long long j = 0; j < first_matrix[i].size(); j++) 
        {
            for (long long k = 0; k < n; k++)
            {
                result[i][j] += (first_matrix[i][k] * second_matrix[k][j]) % mod;
                result[i][j] %= mod;
            }
        }
    }
    return result;
}

vector<vector<long long>> binary_pow(vector<vector<long long>>& matrix, long long k, vector<vector<long long>>& ed_matrix)
{
    if (!k)
    {
        return ed_matrix;
    }
    if (k % 2) 
    {
        vector<vector<long long>> second_matrix = binary_pow(matrix, k - 1, ed_matrix);
        return matrix_mul(second_matrix, matrix);
    }
    else 
    {
        std::vector<std::vector<long long>> second_matrix = binary_pow(matrix, k / 2, ed_matrix);
        return matrix_mul(second_matrix, second_matrix);
    }
}

int main()
{
    long long m, u, v, length, a, b;
    cin >> n >> m;
    vector<vector<long long>> ed_matrix(n, vector<long long>(n, 0));
    for (long long i = 0; i < n; i++)
    {
        ed_matrix[i][i] = 1;
    }
    vector<vector<long long>> graph(n, vector<long long>(n, 0));
    cin >> u >> v >> length;
    for (long long k = 0; k < m; k++)
    {
        cin >> a >> b;
        graph[a - 1][b - 1] += 1;
        graph[b - 1][a - 1] += 1;
    }
    vector<vector<long long>> result = binary_pow(graph, length, ed_matrix);
    cout << result[u - 1][v - 1] % mod;
}