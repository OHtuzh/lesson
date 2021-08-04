#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define ll long long
#define ull unsigned long long
#define ld long double
#define DEBUG
using namespace std;


int n, a, b;
string s;

void fast()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}


void solution()
{
	return;
}


ll fib(int n)
{
	ll* f = new ll[n + 1];
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i <= n; i++)
		f[i] = f[i - 1] + f[i - 2];
	return f[n];
}


ll gridTraveler(int m, int n, ll** memo)
{
	if (m == 1 && n == 1) return 1;
	else if (m == 0 || n == 0) return 0;
	else if (memo[m][n]) return memo[m][n];
	memo[m][n] =  gridTraveler(m - 1, n, memo) + gridTraveler(m, n - 1, memo);
	return memo[m][n];
}


bool canSum(int targetSum, int numbers[], int arrsize, int memo[])
{
	if (targetSum < 0) return false;
	else if (memo[targetSum] != -1) return memo[targetSum];

	for (int i = 0; i < arrsize; i++)
	{
		int remainder = targetSum - numbers[i];
		if (canSum(remainder, numbers, arrsize, memo))
		{
			memo[targetSum] = 1;
			return true;
		}
	}
	memo[targetSum] = 0;
	return false;
}


bool how_sum(int targetSum, int numbers[], int arr_size, vector<int> & v, int memo[])
{
	if (targetSum < 0) return false;
	else if (memo[targetSum] != -1) return memo[targetSum];

	for (int i = 0; i < arr_size; i++)
	{
		int remainder = targetSum - numbers[i];
		if (how_sum(remainder, numbers, arr_size, v, memo))
		{
			memo[targetSum] = 1;
			v.push_back(numbers[i]);
			return true;
		}
	}
	memo[targetSum] = 0;
	return false;
}


vector<int> best_sum(int targetSum, int numbers[], int arr_size, vector<vector<int>> &memo)
{
	if (targetSum == 0) return {};
	else if (targetSum < 0) return { -1 };
	else if (memo[targetSum].size() != 0) return memo[targetSum];

	vector<int> shortestCombination = { -1 };
	for (int i = 0; i < arr_size; i++)
	{
		int remainder = targetSum - numbers[i];
		vector<int> remainderCombination = best_sum(remainder, numbers, arr_size, memo);
		if (remainderCombination.size() == 1 && remainderCombination[0] == -1)
			continue;
		else
		{
			vector<int> combination(remainderCombination);
			combination.push_back(numbers[i]);
			if (shortestCombination[0] = -1 || shortestCombination.size() > combination.size())
			{
				shortestCombination = {};
				for (int i = 0; i < combination.size(); i++)
					shortestCombination.push_back(combination[i]);
			}
		}
	}

	memo[targetSum] = shortestCombination;
	return shortestCombination;
}



int main()
{
#ifdef DEBUG
	ifstream f_inp("Text.txt");
#define cin f_inp
#endif
	int m, n;
	cin >> m >> n;
	ll** mtrx = new ll*[m+1];
	for (int i = 1; i <= m; i++)
	{
		mtrx[i] = new ll[n + 1];
		for (int j = 0; j <= n; j++)
			mtrx[i][j] = 0;
	}

	cout << gridTraveler(m, n, mtrx) << "\n";*/

	int arr[] = { 7, 14 };
	int target = 300;
	int* m = new int[target+1];
	for (int i = 0; i <= target; i++)
		m[i] = -1;
	m[0] = 1;
	cout << canSum(target, arr, 2, m) << "\n";
	delete[] m;

	int arr[] = {2, 3, 5};  //300 [7, 14]
	int target = 8;         
	int* m = new int[target + 1];
	for (int i = 0; i <= target; i++)
		m[i] = -1;
	m[0] = 1;
	vector<int> ans;

	if (how_sum(target, arr, 3, ans, m))
	{
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i] << " ";
		cout << "\n";
	}  
	else
		cout << "None" << "\n";

	delete[] m;

	int arr[] = {1,2,5,25};  //300 [7, 14]
	int target = 100;         
	vector<vector<int>> m;
	m.resize(target + 1);
	for (int i = 0; i <= target; i++)
		m[i].resize(0);
	vector<int> ans = best_sum(target, arr, 4, m);

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	cout << "\n";


	return 0;
}
