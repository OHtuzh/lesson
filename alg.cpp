#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

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



bool canConstruct(string &target, vector<string> &wordBank)
{
    if (!target.length()) return true;

    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            if (canConstruct(suffix, wordBank))
                return true;
        }
    }

    return false;
}


bool canConstructMemoized(string &target, vector<string> &wordBank, map<string, bool> &memo)
{
    if (target == "") return true;
    else
    {
        try
        { 
            bool res = memo.at(target);
            return res;
        }
        catch(out_of_range& e)
        {  

        }    
    }

    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            if (canConstructMemoized(suffix, wordBank, memo))
            {
                memo[target] = true;
                return true;
            }
        }
    }

    memo[target] = false;
    return false;
}


int countConstruct(string &target, vector<string> &wordBank)
{
    if (target == "") return 1;

    int totalCount = 0;
    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            int numWaysForRest = countConstruct(suffix, wordBank);
            totalCount += numWaysForRest;
        }
    }

    return totalCount;
}


int countConstructMemoized(string &target, vector<string> &wordBank, map<string, int> &memo)
{
    if (target == "") return 1;
    else
    {
        try
        {
            int res = memo.at(target);
            return res;
        }
        catch(out_of_range &e)
        {
            
        }
        
    }

    int totalCount = 0;
    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            int numWaysForRest = countConstructMemoized(suffix, wordBank, memo);
            totalCount += numWaysForRest;
        }
    }

    memo[target] = totalCount;
    return totalCount;
}


vector<vector<string>> allConstruct(string &target, vector<string> &wordBank)
{
    if (target == "") return {{}};

    vector<vector<string>> result;
    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            vector<vector<string>> suffixWays = allConstruct(suffix, wordBank);
            vector<vector<string>> targetWays(suffixWays);
            for (int j = 0; j < targetWays.size(); j++)
                targetWays[j].insert(targetWays[j].begin(), wordBank[i]);
            for (int j = 0; j < targetWays.size(); j++)
                result.push_back(targetWays[j]);
        }
    }

    return result;
} 


vector<vector<string>> allConstructMemoized(string &target, vector<string> &wordBank, map<string, vector<vector<string>>> &memo)
{
    if (target == "") return {{}};
    else
    {
        try
        {
            vector<vector<string>> res = memo.at(target);
            return res;
        }
        catch(out_of_range &e)
        {

        }
    }

    vector<vector<string>> result;
    for (int i = 0; i < wordBank.size(); i++)
    {
        if (target.find(wordBank[i]) == 0)
        {
            string suffix(target);
            for (int j = 0; j < wordBank[i].length(); j++)
                suffix.erase(suffix.begin());
            vector<vector<string>> suffixWays = allConstructMemoized(suffix, wordBank, memo);
            vector<vector<string>> targetWays(suffixWays);
            for (int j = 0; j < targetWays.size(); j++)
                targetWays[j].insert(targetWays[j].begin(), wordBank[i]);
            for (int j = 0; j < targetWays.size(); j++)
                result.push_back(targetWays[j]);
        }
    }

    memo[target] = result; 
    return result;
} 


int gridTravalerTabulation(int m, int n)
{
    int** table = new int*[m + 1];
    for (int i = 0; i <= m; i++)
    {
        table[i] = new int[n+1];
        for (int j = 0; j <= n; j++)
            table[i][j] = 0;
    }
    table[1][1] = 1;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            table[i][j] += table[i-1][j] + table[i][j-1];
    }
    return table[m][n];
}


bool canSumTabulation(int targetSum, int numbers[], int arrsize)
{
    bool* table = new bool[targetSum + 1];
    for (int i = 0; i < targetSum + 1; i++)
        table[i] = false;
    table[0] = true;

    for (int i = 0; i < targetSum + 1; i++)
    {
        if (table[i])
        {
            for (int j = 0; j < arrsize; j++)
            {
                if (i + numbers[j] < targetSum + 1)
                    table[i+numbers[j]] = true;
            }
        }
    }

    return table[targetSum];
}


vector<int> howSumTabulation(int targetSum, int numbers[], int arrsize)
{
    vector<vector<int>> table;
    table.resize(targetSum+1, {-1});
    table[0] = {};

    for (int i = 0; i <= targetSum; i++)
    {
        if (table[i].size() == 1 && table[i][0] == -1)
            continue;
        else
        {
            for (int j = 0; j < arrsize; j++)
            {
                if (i + numbers[j] <= targetSum)
                {
                    table[i + numbers[j]] = {};
                    for (int k = 0; k < table[i].size(); k++)
                        table[i+numbers[j]].push_back(table[i][k]);
                    table[i+numbers[j]].push_back(numbers[j]);
                }
            }
        }
    }

    return table[targetSum];
}


vector<int> bestSumTabulation(int targetSum, int numbers[], int arrsize)
{
    vector<vector<int>> table;
    table.resize(targetSum+1, {-1});
    table[0] = {};

    for (int i = 0; i <= targetSum; i++)
    {
        if (table[i].size() == 1 && table[i][0] == -1)
            continue;
        else
        {
            for (int j = 0; j < arrsize; j++)
            {
                if (i + numbers[j] <= targetSum)
                {
                    vector<int> combination;
                    for (int k = 0; k < table[i].size(); k++)
                        combination.push_back(table[i][k]);
                    combination.push_back(numbers[j]);
                    if (table[i + numbers[j]].size() == 1 && table[i+numbers[j]][0] == -1)
                        table[i+numbers[j]] = combination;

                    else if (table[i+numbers[j]].size() > combination.size())
                        table[i+numbers[j]] = combination;
                }
            }
        }
    }

    return table[targetSum];
}


bool canConstructTabulation(string target, vector<string> wordBank)
{
    bool* table = new bool[target.length() + 1];
    for (int i = 0; i < target.length() + 1; i++)
        table[i] = false;
    table[0] = true;

    for (int i = 0; i < target.length() + 1; i++)
    {
        if (table[i])
        {
            for (int word = 0; word < wordBank.size(); word++)
            {
                if (target.find(wordBank[word], i) == i)
                {
                    table[i + wordBank[word].length()] = true;
                }
            }
        }
    }

    return table[target.length()];
}


int countConstructTabulation(string target, vector<string> wordBank)
{
    int* table = new int[target.length() + 1];
    for (int i = 0; i <= target.length(); i++)
        table[i] = 0;
    table[0] = 1;
    
    for (int i = 0; i <= target.length(); i++)
    {
        if (table[i])
        {
            for (int word = 0; word < wordBank.size(); word++)
            {
                if (target.find(wordBank[word], i) == i)
                    table[i + wordBank[word].length()] += table[i];
            }
        }
    }

    return table[target.length()];
}


vector<vector<string>> allConstructTabulation(string target, vector<string> wordBank)
{
    vector<vector<vector<string>>> table;
    table.resize(target.length() + 1, {});
    table[0] = {{}};

    for (int i = 0; i <= target.length(); i++)
    {
        for (int word = 0; word < wordBank.size(); word++)
        {
            if (target.find(wordBank[word], i) == i)
            {
                vector<vector<string>> newCombination(table[i]);
                for (int k = 0; k < newCombination.size(); k++)
                {
                    newCombination[k].push_back(wordBank[word]);
                    table[i + wordBank[word].length()].push_back(newCombination[k]);
                }
            }
        }
    }

    return table[target.length()];
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

	// string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // canConstruct(s1, k1) ? cout << "YES" << "\n" : cout << "NO" << "\n";
    
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // canConstruct(s2, k2) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // canConstruct(s3, k3) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // canConstruct(s4, k4) ? cout << "YES" << "\n" : cout << "NO" << "\n";


    // map<string, bool> m1;
    // string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // canConstructMemoized(s1, k1, m1) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // map<string,bool> m2;
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // canConstructMemoized(s2, k2, m2) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // map<string, bool> m3;
    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // canConstructMemoized(s3, k3, m3) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // map<string, bool> m4;
    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // canConstructMemoized(s4, k4, m4) ? cout << "YES" << "\n" : cout << "NO" << "\n";
    

    // string s0 = "purple";
    // vector<string> k0 = {"purp", "p", "ur", "le", "purpl"};
    // cout << countConstruct(s0, k0) << "\n";

    // string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // cout << countConstruct(s1, k1) << "\n";
    
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // cout << countConstruct(s2, k2) << "\n";

    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // cout << countConstruct(s3, k3) << "\n";

    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // cout << countConstruct(s4, k4) << "\n";


    // map<string, int> m1;
    // string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // cout << countConstructMemoized(s1, k1, m1) << "\n";

    // map<string,int> m2;
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // cout << countConstructMemoized(s2, k2, m2) << "\n";

    // map<string, int> m3;
    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // cout << countConstructMemoized(s3, k3, m3) << "\n";

    // map<string, int> m4;
    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // cout << countConstructMemoized(s4, k4, m4) << "\n";


    // map<string, vector<vector<string>>> m1;
    // string s1 = "purple";
    // vector<string> k1 = {"purp", "p", "ur", "le", "purpl"};
    // vector<vector<string>> res1 = allConstructMemoized(s1, k1, m1);
    // for (int i = 0; i < res1.size(); i++)
    // {
    //     for (int j = 0; j < res1[i].size(); j++)
    //         cout << res1[i][j] << " ";
    //     cout << "\n";
    // }
    // cout << "\n";
    
    // map<string, vector<vector<string>>> m2;
    // string s2 = "abcdef";
    // vector<string> k2 = {"ab", "abc", "cd", "def", "abcd", "ef", "c"};
    // vector<vector<string>> res2 = allConstructMemoized(s2, k2, m2);
    // for (int i = 0; i < res2.size(); i++)
    // {
    //     for (int j = 0; j < res2[i].size(); j++)
    //         cout << res2[i][j] << " ";
    //     cout << "\n";
    // }
    // cout << "\n";

    // map<string, vector<vector<string>>> m3;
    // string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz";
    // vector<string> k3 = {"a", "aa", "aaa", "aaaa", "aaaaaaa"};
    // vector<vector<string>> res3 = allConstructMemoized(s3, k3, m3);
    // for (int i = 0; i < res3.size(); i++)
    // {
    //     for (int j = 0; j < res3[i].size(); j++)
    //         cout << res3[i][j] << " ";
    //     cout << "\n";
    // }
    // cout << "\n";


    // cout << gridTravalerTabulation(3, 2) << "\n";
    // cout << gridTravalerTabulation(3, 3) << "\n";
    // cout << gridTravalerTabulation(18, 18) << "\n";


    // int arr1[] = {5, 3, 4, 7};
    // cout << canSumTabulation(7, arr1, 4) << "\n";

    // int arr2[] = {2, 4};
    // cout << canSumTabulation(7, arr2, 2) << "\n";

    // int arr3[] = {7, 14};
    // cout << canSumTabulation(300, arr3, 2) << "\n";


    // int arr1[] = {5, 3, 4, 7};
    // vector<int> res1 = howSumTabulation(7, arr1, 4);
    // for (int i = 0; i < res1.size(); i++)
    //     cout << res1[i] << " ";
    // cout << "\n";

    // int arr2[] = {2, 4};
    // vector<int> res2 = howSumTabulation(7, arr2, 2);
    // for (int i = 0; i < res2.size(); i++)
    //     cout << res2[i] << " ";
    // cout << "\n";

    // int arr3[] = {7, 14};
    // vector<int> res3 = howSumTabulation(300, arr3, 2);
    // for (int i = 0; i < res3.size(); i++)
    //     cout << res3[i] << " ";
    // cout << "\n";
 

    // int arr1[] = {5, 3, 4, 7};
    // vector<int> res1 = bestSumTabulation(7, arr1, 4);
    // for (int i = 0; i < res1.size(); i++)
    //     cout << res1[i] << " ";
    // cout << "\n";

    // int arr2[] = {2, 4};
    // vector<int> res2 = bestSumTabulation(7, arr2, 2);
    // for (int i = 0; i < res2.size(); i++)
    //     cout << res2[i] << " ";
    // cout << "\n";

    // int arr3[] = {7, 14};
    // vector<int> res3 = bestSumTabulation(300, arr3, 2);
    // for (int i = 0; i < res3.size(); i++)
    //     cout << res3[i] << " ";
    // cout << "\n";


    // string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // canConstructTabulation(s1, k1) ? cout << "YES" << "\n" : cout << "NO" << "\n";
    
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // canConstructTabulation(s2, k2) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // canConstructTabulation(s3, k3) ? cout << "YES" << "\n" : cout << "NO" << "\n";

    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // canConstructTabulation(s4, k4) ? cout << "YES" << "\n" : cout << "NO" << "\n";


    // string s0 = "purple";
    // vector<string> k0 = {"purp", "p", "ur", "le", "purpl"};
    // cout << countConstructTabulation(s0, k0) << "\n";

    // string s1 = "abcdef";
    // vector<string> k1 = {"ab", "abc", "cd", "def", "abcd"};
    // cout << countConstructTabulation(s1, k1) << "\n";
    
    // string s2 = "skateboard";
    // vector<string> k2 = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    // cout << countConstructTabulation(s2, k2) << "\n";

    // string s3 = "enterapotentpot";
    // vector<string> k3 = {"a", "p", "ent", "enter", "ot", "o", "t"};
    // cout << countConstructTabulation(s3, k3) << "\n";

    // string s4 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    // vector<string> k4 = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    // cout << countConstructTabulation(s4, k4) << "\n";


    string s1 = "purple";
    vector<string> k1 = {"purp", "p", "ur", "le", "purpl"};
    vector<vector<string>> res1 = allConstructTabulation(s1, k1);
    for (int i = 0; i < res1.size(); i++)
    {
        for (int j = 0; j < res1[i].size(); j++)
            cout << res1[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
    

    string s2 = "abcdef";
    vector<string> k2 = {"ab", "abc", "cd", "def", "abcd", "ef", "c"};
    vector<vector<string>> res2 = allConstructTabulation(s2, k2);
    for (int i = 0; i < res2.size(); i++)
    {
        for (int j = 0; j < res2[i].size(); j++)
            cout << res2[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    
    string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaz";
    vector<string> k3 = {"a", "aa", "aaa", "aaaa", "aaaaaaa"};
    vector<vector<string>> res3 = allConstructTabulation(s3, k3);
    for (int i = 0; i < res3.size(); i++)
    {
        for (int j = 0; j < res3[i].size(); j++)
            cout << res3[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

	return 0;
}


