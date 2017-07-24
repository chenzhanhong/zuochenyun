#include "moststd.h"
using namespace std;


int minPathSum1(const vector<vector<int>>& m)
{
	if (m.empty())
		return 0;
	int h = m.size(), w = m[0].size();
	vector<vector<int>>dp(h+1,vector<int>(w+1,0));
	dp[1][1] = m[0][0];
	for (int c = 2; c <= w; ++c)
	{
		dp[1][c] = dp[1][c - 1] + m[0][c - 1];
	}
	for (int r = 2; r <= h; ++r)
	{
		dp[r][1] = dp[r - 1][1] + m[r-1][0];//不是m[r][0]
	}
	for (int i = 2; i <= h; ++i)
	{
		for (int j = 2; j <= w; ++j)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + m[i-1][j-1];//不是m[i][j]
		}
	}
	return dp[h][w];
}
int minPathSumLessSpace(const vector<vector<int>>& m)
{
	if (m.empty())
		return 0;
	int h = m.size(), w = m[0].size();
	vector<int>dpArr(w);
	dpArr[0] = m[0][0];
	for (int i = 1; i < w; ++i)
		dpArr[i] = m[0][i]+dpArr[i-1];
	for (int i = 1; i < h; ++i)
	{
		dpArr[0] = dpArr[0] + m[i][0];
		for (int j = 1; j < w; ++j)
		{
			dpArr[j] = min(dpArr[j], dpArr[j - 1]) + m[i][j];
		}
	}
	return dpArr[w-1];
}
int minCoins1(const vector<int>&arr, int aim)
{
	int kindsOfCoins = arr.size();
	vector<vector<int>>dp(kindsOfCoins+1,vector<int>(aim+1,INT_MAX));
	for (int i = 1; i <= kindsOfCoins; ++i)
		dp[i][0] = 0;
	for (int i = 1; i <= kindsOfCoins; ++i)
	{
		for (int j = 1; j <= aim; ++j)
		{
			if (arr[i-1]>j)//注意不是arr[i]啊
			{
				dp[i][j] = dp[i-1][j];
			}
			else
			{
				dp[i][j] = min(dp[i - 1][j], dp[i][j - arr[i-1]] == INT_MAX ? INT_MAX : dp[i][j - arr[i-1]]+1);
			}
		}
	}
	return dp[kindsOfCoins][aim] == INT_MAX ? -1:dp[kindsOfCoins][aim];
}
int coins4(const vector<int>&arr, int aim)
{
	if (arr.empty() || aim < 0)
		return 0;
	int kindsOfCoins = arr.size();
	vector<vector<int>>dp(kindsOfCoins + 1, vector<int>(aim + 1, 0));
	for (int i = 1; i <= kindsOfCoins; ++i)
		dp[i][0] = 1;
	for (int i = 1; i <= kindsOfCoins; ++i)
	{
		for (int j = 1; j <= aim; ++j)
		{
			dp[i][j] = dp[i - 1][j] + (j-arr[i-1]<0?0:dp[i][j-arr[i-1]]);//注意不是arr[i]啊！！！！
		}
	}
	return dp[kindsOfCoins][aim];
}

//zuochenyun P228
class numOfExpectedRes
{
public:
	bool isValid(string str)
	{
		if (str.size() % 2 == 0)
			return false;
		for (size_t i = 0; i < str.size(); i += 2)
		{
			if (str[i] != '0'&&str[i] != '1')
				return false;
		}
		for (size_t i = 1; i < str.size(); i += 2)
		{
			if (str[i] != '|'&&str[i] != '&'&&str[i]!='^')
				return false;
		}
		return true;
	}
	int num2(string str, bool desired)
	{
		if (str.empty() || !isValid(str))
			return 0;
		vector<vector<int>>t(str.length(),vector<int>(str.length(),0));
		vector<vector<int>>f(str.length(), vector<int>(str.length(), 0));
		for (int i = 0; i < str.length(); i += 2)
		{
			if (str[i] == '0')
				f[i][i] = 1;
			else
				t[i][i] = 1;
		}
		for (int len = 3; len <= str.length(); len += 2)
		{
			for (int i = 0; i + len - 1 < str.length(); i += 2)
			{
				int j = i + len - 1;
				for (int ii = i + 1; ii <= j - 1; ii += 2)
				{
					char sep = str[ii];
					if (sep == '|')
					{
						t[i][j]+= (t[i][ii - 1] * t[ii + 1][j] + t[i][ii - 1] * f[ii + 1][j] + f[i][ii - 1] * t[ii+1][j]);//不是=而是+=!!
						f[i][j] += (f[i][ii - 1] * f[ii + 1][j]);
					}
					else if (sep == '&')
					{
						t[i][j] += (t[i][ii - 1] * t[ii+1][j]);
						f[i][j] += (f[i][ii - 1] * f[ii + 1][j] + t[i][ii - 1] * f[ii + 1][j] + f[i][ii - 1] * t[ii + 1][j]);
					}
					else
					{
						t[i][j] += (t[i][ii - 1] * f[ii + 1][j] + f[i][ii - 1] * t[ii+1][j]);
						f[i][j] += (t[i][ii - 1] * t[ii + 1][j] + f[i][ii - 1] * f[ii + 1][j]);
					}
				}

			}
		}
		return (desired?t[0][str.length()-1]:f[0][str.length()-1]);
	}
};
//zuochenyun P223
int minHP1(const vector<vector<int>>m)
{
	if (m.empty() || m[0].empty())
		return 1;
	int h = m.size(), w = m[0].size();
	vector<vector<int>>dp(h, vector<int>(w));
	dp[h - 1][w - 1] = max(1 - m[h - 1][w - 1], 1);
	for (int i = w - 2; i >= 0; --i)
	{
		dp[h - 1][i] = max(dp[h - 1][i + 1] - m[h - 1][i], 1);
	}
	for (int i = h - 2; i >= 0; --i)
	{
		dp[i][w - 1] = max(dp[i + 1][w - 1] - m[i][w - 1], 1);
	}
	for (int i = h - 2; i >= 0; --i)
	{
		for (int j = w - 2; j >= 0; --j)
		{
			int right = max(dp[i][j + 1] - m[i][j], 1);
			int down = max(dp[i + 1][j] - m[i][j], 1);
			dp[i][j] = min(right, down);
		}
	}
	return dp[0][0];
}
//P220
bool isCross1(string str1,string str2,string aim)
{
	if (aim.length() != str1.length() + str2.length())
		return false;
	if (str1.empty())
	{
		return str2 == aim;
	}
	if (str2.empty())
	{
		return str1 == aim;
	}
	int a = str1.length(), b = str2.length();
	vector<vector<bool>>dp(a+1,vector<bool>(b+1,false));
	dp[0][0] = true;
	for (int i = 1; i <= a; ++i)
	{
		if (str1[i - 1] != aim[i - 1])
			break;
		dp[i][0] = true;
	}
	for (int i = 1; i <= b; ++i)
	{
		if (str2[i - 1] != aim[i - 1])
			break;
		dp[0][i] = true;
	}
	for (int i = 1; i <= a; ++i)
	{
		for (int j = 1; j <= b; ++j)
		{
			if ((dp[i - 1][j] && str1[i - 1] == aim[i+j - 1]) || (dp[i][j - 1] && str2[j - 1] == aim[i+j - 1]))
				dp[i][j] = true;
		}
	}
	return dp[a][b];
}
bool isCross2(string str1, string str2, string aim)
{
	if (aim.length() != str1.length() + str2.length())
		return false;
	if (str1.empty())
	{
		return str2 == aim;
	}
	if (str2.empty())
	{
		return str1 == aim;
	}
	int a = str1.length(), b = str2.length();
	vector<bool>dp(b+1,false);
	dp[0] = true;
	for (int i = 1; i <= b; ++i)
	{
		if (str2[i - 1] != aim[i - 1])
			break;
		dp[i] = true;
	}
	for (int i = 1; i <= a; ++i)
	{
		if (dp[0] && str1[i - 1] == aim[i - 1])
			dp[0] = true;
		else
			dp[0] = false;
		for (int j = 1; j <= b; ++j)
		{
			if ((dp[j] && str1[i - 1] == aim[i + j - 1]) || (dp[j - 1] && str2[j - 1] == aim[i + j - 1]))
				dp[j] = true;
			else
				dp[j] = false;
		}
	}
	return dp[b];
}
//P202最长递增子序列
vector<int>generateLIS(const vector<int>&arr, const vector<int>&dp)
{//还原决策路径
	vector<int>res;
	if (arr.empty() || dp.empty())
		return res;
	int maxIndex = static_cast<int>(max_element(dp.begin(),dp.end())-dp.begin());
	res.push_back(arr[maxIndex]);
	int cur = arr[maxIndex];
	for (int i = maxIndex - 1; i >= 0; --i)
	{
		if (cur > arr[i])
		{
			cur = arr[i];
			res.push_back(cur);
		}
	}
	reverse(res.begin(),res.end());
	return res;
}
vector<int>getDp1(const vector<int>&arr)
{
	vector<int>dp(arr.size(),1);
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (arr[i]>arr[j])
			{
				if (dp[j] + 1 > dp[i])
				{
					dp[i] = dp[j] + 1;
				}
			}
		}
	}
	return dp;
}
vector<int>lis1(const vector<int>&arr)
{
	if (arr.empty())
		return vector<int>();
	vector<int>dp = getDp1(arr);
	return generateLIS(arr,dp);
}
class longestCommonSequence
{
	//P210
public:
	vector<vector<int>>getDp(const string&str1, const string&str2)
	{
		//str1,str2 not empty here
		int a = str1.size(), b = str2.size();
		vector<vector<int>>dp(a,vector<int>(b,0));
		bool f1 = false, f2 = false;
		for (int i = 0; i < str2.length(); ++i)
		{
			if (str1[0] == str2[i])
			{
				f1 = true;
				break;
			}
		}
		if (f1)
			dp[0] = vector<int>(b,1);
		for (int i = 0; i < str1.length(); ++i)
		{
			if (str2[0] == str1[i])
			{
				f2 = true;
				break;
			}
		}
		if (f2)
		{
			for (int i = 0; i < a; ++i)
			{
				dp[i][0] = 1;
			}
		}
		for (int i = 1; i < a; ++i)
		{
			for (int j = 1; j < b; ++j)
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if (str1[i] == str2[j])
					dp[i][j] = max(dp[i-1][j-1]+1,dp[i][j]);
			}
		}
		return dp;
	}
	string lcse(const string& str1, const string&str2)
	{
		if (str1.empty() || str2.empty())
			return string();
		auto dp = getDp(str1, str2);
		int a = dp.size();
		int b = dp[0].size();
		int len = dp[a - 1][b - 1];
		string res = "";
		vector<char>vc(len);
		int i = a - 1, j = b - 1;
		while (len > 0)
		{
			char direction;
			if (i - 1 >= 0 && dp[i - 1][j] == dp[i][j])
			{
				direction = 't';
			}
			else if (j-1>=0&&dp[i][j-1]==dp[i][j])
			{
				direction = 'l';
			}
			else
			{
				direction = 'd';
			}
			if (direction == 'd')
			{
				vc[--len] = str1[i];
				i--;
				j--;
			}
			else if (direction == 't')
			{
				i--;
			}
			else
			{
				j--;
			}
		}
		for (auto c : vc)
			res += c;
		return res;
	}
};
class lcst
{
	//P213
private:
	vector<vector<int>>getDp(const string&str1, const string&str2)
	{
		int a = str1.size(), b = str2.size();
		vector<vector<int>>dp(a, vector<int>(b, 0));
		for (int i = 0; i < a; ++i)
		{
			if (str1[i] == str2[0])
			{
				dp[i][0] = 1;
			}
		}
		for (int i = 0; i < b; ++i)
		{
			if (str1[0] == str2[i])
			{
				dp[0][i] = 1;
			}
		}
		for (int i = 1; i < a; ++i)
		{
			for (int j = 1; j < b; ++j)
			{
				if (str1[i] == str2[j])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
			}
		}
		return dp;
	}
public:
	string lcst1(const string&str1, const string&str2)
	{
		if (str1.empty() || str2.empty())
			return string();
		auto dp = getDp(str1,str2);
		int maxLen = INT_MIN;
		int maxIndex = 0;
		for (int i = 0; i < dp.size(); ++i)
		{
			for (int j = 0; j < dp[0].size(); ++j)
			{
				if (dp[i][j] > maxLen)
				{
					maxLen = dp[i][j];
					maxIndex = i;
				}
			}
		}
		string res = "";
		if (maxLen > 0)
		{
			res = str1.substr(maxIndex-maxLen+1,maxLen);
		}
		return res;
	}
	string lcst2(const string&str1, const string&str2)
	{
		if (str1.empty() || str2.empty())
			return string();
		int row = 0;
		int col = str2.length() - 1;
		int maxLen = 0, end = 0;
		while (row < str1.length())
		{
			int i = row, j = col, len = 0;
			while (i < str1.length() && j < str2.length())
			{
				len = (str1[i]!=str2[j]?0:len+1);
				if (len > maxLen)
				{
					end = i;
					maxLen = len;
				}
				++i;
				++j;
			}
			if (col > 0)
				--col;
			else
				++row;
		}
		return str1.substr(end-maxLen+1,maxLen);
	}
};
//P235  leetcode 45. Jump Game II
class Solution_jump2 {
public:
	int jump(vector<int>& nums) {
		int cur = 0, next = 0, jumpStep = 0;
		if (nums.empty())return 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (cur < i)
			{
				++jumpStep;
				cur = next;
			}
			next = max(next,i+nums[i]);
		}
		return jumpStep;
	}
};
//leetcode 55. Jump Game
class Solution_canJump {
public:
	bool canJump_timeLimitExceed(vector<int>& nums) {
		vector<bool>dp(nums.size());
		dp[nums.size() - 1] =true;
		int sz = nums.size();
		for (int i = sz - 2; i >= 0; --i)
		{
			if (nums[i] == 0)
				dp[i] = false;
			else
			{
				if (nums[i] + i >= sz - 1)
				{
					dp[i] = true;
				}
				else
				{
					bool flag = false;
					for (int k = 1; k <= nums[i]; ++k)
					{
						if (dp[i + k] == true)
						{
							flag = true;
							break;
						}
					}
					dp[i] = flag;
				}
			}
		}
		return dp[0];
	}

	bool canJump(vector<int>& nums)
	{
		int reach = 0;
		int i = 0;
		for (; i < nums.size()&&i<=reach; ++i)
		{
			reach = max(reach,nums[i]+i);
		}
		return i == nums.size();
	}
};
//P236
class longestConsecutiveSequence
{
private:
	int merge(unordered_map<int, int>&mp, int less, int more)
	{
		assert(less+1==more);
		int left = less - mp[less] + 1;
		int right = more + mp[more] - 1;
		int len = right - left + 1;
		mp[left] = len;
		mp[right] = len;
		return len;
	}
public:
	int longestConsecutive(const vector<int>&arr)
	{
		if (arr.empty())
			return 0;
		unordered_map<int, int>mp;
		int curMax = 1;
		for (int i = 0; i < arr.size(); ++i)
		{
			if (mp.find(arr[i]) == mp.end())
			{
				mp[arr[i]] = 1;
				if (mp.find(arr[i] - 1) != mp.end())
				{
					curMax = max(curMax,merge(mp,arr[i]-1,arr[i]));
				}
				if (mp.find(arr[i] + 1) != mp.end())
				{
					curMax = max(curMax,merge(mp,arr[i],arr[i]+1));
				}
			}
		}
		return curMax;
	}
};
//P238 N-Queens
class NQueens
{
private:
	bool isValid(const vector<int>&record, int row, int col)
	{
		assert(row>=0&&row<record.size()&&col>=0&&col<record.size());
		for (int k = 0; k < row; ++k)
		{
			if (record[k] == col || abs(row - k) == abs(col - record[k]))
				return false;
		}
		return true;
	}
	int process1(int row, int n, vector<int>&record)
	{
		if (row == n)
			return 1;
		int res = 0;
		for (int col = 0; col < n; ++col)
		{
			if (isValid(record, row, col))
			{
				record[row] = col;
				res += process1(row+1,n,record);
			}
		}
		return res;
	}
public:
	int num1(int n)
	{
		if (n < 0)
			return 0;
		vector<int>record(n);
		return process1(0,n,record);
	}
};
/*
void main()
{
	vector<int>arr = {1,2,8};
	for (auto a : arr)
	{
		cout << NQueens().num1(a) << endl;
	}
	int itrpt = 0;
}
*/