#include "moststd.h"
using namespace std;
//P245
string removeKZeros(string str, int k)
{
	if (str.empty() || k < 1)
		return str;
	int start = -1, cnt = 0;
	vector<char>vc(str.begin(),str.end());
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] == '0')
		{
			start = (start==-1?i:start);
			++cnt;
		}
		else
		{
			if (cnt == k)
			{
				for (size_t j = start; j < start + k; ++j)
				{
					vc[j] = 0;
				}
			}
			start = -1;
			cnt = 0;
		}
	}
	if (cnt == k)
	{
		for (size_t j = start; j < start + k; ++j)
		{
			vc[j] = 0;
		}
	}
	string res = "";
	for (size_t i = 0; i < vc.size(); ++i)
	{
		if (vc[i] != 0)
		{
			res += vc[i];
		}
	}
	return res;
}
//P248
class StringToInterger
{
private:
	bool isValid(const string&str)
	{
		if (str.empty())
			return false;
		char firstChar = str[0];
		if (firstChar != '-' && (firstChar<'0' || firstChar>'9'))
			return false;
		if (firstChar == '-'&&str.length() == 1)
			return false;
		if (firstChar == '-'&&str[1] == '0')
			return false;
		if (firstChar == '0'&&str.length() != 1)
			return false;
		for (size_t i = 1; i < str.length(); ++i)
		{
			if (str[i]<'0' || str[i]>'9')
				return false;
		}
		return true;
	}
public:
	int convert(const string&str)
	{
		if (!isValid(str))
			return 0;

		int minq = INT_MIN / 10;
		int minr = INT_MIN % 10;
		bool posi = (str[0]!='-');
		int res = 0, cur = 0;
		for (int i = (posi ? 0 : 1); i < str.length(); ++i)
		{
			cur = '0' - str[i];
			if (res < minq)
				return 0;
			if (res == minq&&cur < minr)
				return 0;
			res = 10 * res + cur;
		}

		if (posi&&res == INT_MIN)
			return 0;

		return posi ? -res : res;
	}
};
//P251
class StringReplace
{
public:
	string replace(string str, string from, string to)
	{
		if (str.empty() || from.empty())
			return str;
		vector<char>vc(str.begin(),str.end());
		int match = 0;
		int flen = from.length();
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] == from[match])
			{
				++match;
				if (match == flen)
				{
					int k = i;
					while (match > 0)
					{
						vc[k--] = 0;
						--match;
					}
					
				}
			}
			else
			{
				match = 0;
			}
		}
		string res = "";
		int start = -1;
		for (size_t i = 0; i < vc.size(); ++i)
		{
			if (vc[i] == 0)
			{
				start = (start==-1?i:start);
			}
			else
			{
				if (start != -1)
				{
					res += to;
				}
				start = -1;
				res += vc[i];
			}
		}
		if (start != -1)
		{
			res += to;
		}
		return res;
	}
};
string getCountString(const string&str)
{
	if (str.empty())
		return string();
	string res = "";
	res += str[0];
	int num = 1;
	for (int i = 1; i < str.length(); ++i)
	{
		if (str[i] == str[i - 1])
		{
			++num;
		}
		else
		{
			res = res + "_" + to_string(num) +"_"+ str[i];
			num = 1;
		}
	}
	res = res + "_" + to_string(num);
	return res;
}
char getCharAt(string cstr, int index)
{
	if (cstr.empty())
		return 0;

	bool stage = true;
	char cur = 0;
	int num = 0;
	int sum = 0;
	for (int i = 0; i < cstr.length(); ++i)
	{
		if (cstr[i] == '_')
		{
			stage = !stage;
		}
		else if (stage)
		{
			sum += num;
			if (sum > index)
				return cur;
			num = 0;
			cur = cstr[i];
		}
		else
		{
			num = num * 10 + (cstr[i]-'0');
		}
	}
	return sum + num > index ? cur:0;
}
void rotateWord(vector<char>&chas)
{
	if (chas.empty())
		return;

	reverse(chas.begin(),chas.end());
	int start = -1;
	for (int i = 0; i < chas.size(); ++i)
	{
		if (chas[i] != ' ')
		{
			start = (start==-1?i:start);
		}
		else
		{
			reverse(chas.begin()+start,chas.begin()+i);
			start = -1;
		}
	}
	if (start != -1)
	{
		reverse(chas.begin()+start,chas.end());
	}
}
class MinDistRecord
{
private:
	unordered_map<string, unordered_map<string, int>>record_;
	void updateRecord(const string&curStr,const unordered_map<string,int>lastIndexMp,int index)
	{
		if (record_.find(curStr) == record_.end())
		{
			record_[curStr] = unordered_map<string, int>();
		}
		unordered_map<string, int>&mp = record_[curStr];
		for (auto iter = lastIndexMp.begin(); iter != lastIndexMp.end(); ++iter)
		{
			if (iter->first != curStr)
			{
				if (mp.find(iter->first) == mp.end())
				{
					mp[iter->first] = index - iter->second;
				}
				else
				{
					mp[iter->first] = min(mp[iter->first],index-iter->second);
				}
			}
		}
	}
public:
	MinDistRecord(const vector<string>&strs)
	{
		unordered_map<string, int>lastIndexMp;
		for (int i = 0; i < strs.size(); ++i)
		{
			string curStr = strs[i];
			updateRecord(curStr,lastIndexMp,i);
			lastIndexMp[curStr] = i;
		}
	}
	int minDistance(const string&str1, const string&str2)
	{
		if (str1.empty() || str2.empty())
			return -1;
		if (str1 == str2)
			return 0;
		if (record_.find(str1) != record_.end() && record_[str1].find(str2) != record_[str1].end())
			return record_[str1][str2];
		return -1;
	}
};
class GetPalindrome
{
private:
	vector<vector<int>>getDp(const vector<char>&str)
	{
		//!str.empty()
		int n = str.size();
		vector<vector<int>>dp(n,vector<int>(n,0));
		for (int i = 1; i < n; ++i)
		{
			if (str[i] != str[i - 1])
				dp[i - 1][i] = 1;
			for (int j = i - 2; j >= 0; --j)
			{
				if (str[i] == str[j])
					dp[j][i] = dp[j + 1][i - 1];
				else
					dp[j][i] = min(dp[j+1][i],dp[j][i-1]) + 1;
			}
		}
		return dp;
	}
public:
	string getPalindrome1(const string&str)
	{
		if (str.empty())
			return string();

		vector<char>chas(str.begin(),str.end());
		vector<vector<int>>dp = getDp(chas);
		if (dp[0][str.size() - 1] == 0)
			return str;
		vector<char>res(dp[0][str.size() - 1]+str.size());
		int i = 0, j = res.size() - 1;
		int left = 0, right = str.size() - 1;
		while (i <= j)
		{
			if (str[left] == str[right])
			{
				res[i++] = str[left++];
				res[j--] = str[right--];
			}
			else
			{
				if (dp[left + 1][right] > dp[left][right - 1])
				{
					res[i++] = str[right];
					res[j--] = str[right];
					--right;
				}
				else
				{
					res[i++] = str[left];
					res[j--] = str[left];
					++left;
				}
			}
		}
		string resStr = "";
		for (auto c : res)
			resStr += c;
		return resStr;
	}

};
int maxLength(const string&str)
{
	if (str.empty())
		return 0;
	vector<int>dp(str.size(),0);
	int maxLen = 0;
	for (int i = 1; i < str.size(); ++i)
	{
		if (str[i] == ')')
		{
			int pre = i - dp[i - 1] - 1;
			if (pre >= 0)
			{
				if (str[pre] == '(')
				{
					dp[i] = dp[i - 1] + 2;
					if (pre - 1 >= 0)
					{
						dp[i] += dp[pre - 1];
					}
					maxLen = max(maxLen,dp[i]);
				}
			}
		}
	}
	return maxLen;
}
//P276
class StringCaculator
{
private:
	int cal(const vector<int>&nums, const vector<char>&ops)
	{
		assert(nums.size()==ops.size()+1);
		stack<int>stkNums;
		stack<char>stkOps;
		stkNums.push(nums[0]);
		for (int i = 1; i < nums.size(); ++i)
		{
			stkNums.push(nums[i]);
			if (ops[i-1] == '+' || ops[i-1] == '-')
				stkOps.push(ops[i-1]);
			else
			{
				int second = stkNums.top();
				stkNums.pop();
				int first = stkNums.top();
				stkNums.pop();
				if (ops[i-1] == '*')
					stkNums.push(first*second);
				else
					stkNums.push(first/second);
			}
		}
		while (!stkOps.empty())
		{
			char op = stkOps.top();
			stkOps.pop();
			int second = stkNums.top();
			stkNums.pop();
			int first = stkNums.top();
			stkNums.pop();
			if (op == '+')
				stkNums.push(first+second);
			else
				stkNums.push(first-second);
		}
		assert(stkNums.size()==1);
		return stkNums.top();
	}
	pair<int, int>value(const string&str, int start)
	{
		vector<int>nums;
		vector<char>ops;
		int num = 0;
		for (int i = start; i < str.size(); ++i)
		{
			if (isdigit(str[i]))
			{
				num = num * 10 + str[i] - '0';
			}
			else if (str[i] == '(')
			{
				auto p = value(str,i+1);
				num = p.first;
				i = p.second-1;
			}
			else if (str[i] == ')')
			{
				nums.push_back(num);
				return{cal(nums,ops),i+1};
			}
			else
			{
				nums.push_back(num);
				num = 0;
				ops.push_back(str[i]);
			}
		}
		nums.push_back(num);
		return{cal(nums,ops),str.size()+1};
	}
public:
	int getValue(const string&exp)
	{
		return value(exp,0).first;
	}
};
//P284
int maxUnique(const string&str)
{
	if (str.empty())
		return 0;
	vector<int>mp(128,-1);
	int pre = -1;
	int len = 0, maxLen = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (mp[str[i]] == -1||mp[str[i]]<=pre)
		{
			++len;
		}
		else{
			pre = mp[str[i]];
			len = i - pre;
		}
		maxLen = max(maxLen, len);
		mp[str[i]] = i;
	}
	return maxLen;
}
//P288
int minLength(const string&str1, const string&str2)
{
	if (str1.empty() || str2.empty())
		return 0;
	unordered_map<char, int>mp;
	for (int i = 0; i < str2.size(); ++i)
	{
		mp[str2[i]]++;
	}
	int left = 0, right = 0;
	int minLen = INT_MAX;
	int match = str2.size();
	while (right <= str1.size())
	{
		if (mp.find(str1[right]) != mp.end())
		{
			if (mp[str1[right]] > 0)
			{
				--match;
			}
			--mp[str1[right]];
			while (match == 0)
			{
				minLen = min(minLen,right-left+1);
				if (mp.find(str1[left]) != mp.end())
				{
					if (mp[str1[left]] == 0)
					{
						match = 1;
					}
					++mp[str1[left]];
				}
				++left;
			}
		}
		++right;
	}
	return minLen == INT_MAX ? 0 : minLen;
}
//P292
class MinCut
{
private:
	vector<vector<bool>> getPalindromeDP(const string&str)
	{
		vector<vector<bool>>p(str.size(), vector<bool>(str.size(), true));
		for (int i = str.length() - 2; i >= 0; --i)
		{
			if (str[i] != str[i + 1])
				p[i][i + 1] = false;
			for (int j = i + 2; j <= str.length() - 1; ++j)
			{
				if (str[i] != str[j] || !p[i + 1][j - 1])
					p[i][j] = false;
			}
		}
		return p;
	}
public:
	int minCut(const string&str)
	{
		if (str.empty())
			return 0;
		vector<int>dp(str.size(), INT_MAX);
		vector<vector<bool>>p = getPalindromeDP(str);
		dp[str.size() - 1] = 0;
		for (int i = str.size() - 2; i >= 0; --i)
		{
			if (p[i][str.size() - 1])
				dp[i] = 0;
			else{
				for (int j = i; j <= str.size() - 2; ++j)
				{
					if (p[i][j])
					{
						dp[i] = min(dp[i], dp[j + 1] + 1);
					}
				}
			}
		}
		return dp[0];
	}
};
//P294
class RegExprMatch
{
	
public:
	bool isMatch(string s, string p)
	{
		vector<vector<bool>>dp(s.size()+1,vector<bool>(p.size()+1,false));
		//dp[0][...],dp[...][0]
		dp[0][0] = true;
		for (int j = 2; j <= p.size(); j += 2)
		{
			if (p[j - 1] == '*')
				dp[0][j] = dp[0][j-2];
		}
		if (!s.empty() && !p.empty())
		{
			if (s[0] == p[0] || p[0] == '.')
				dp[1][1] = true;
		}
		for (int i = 1; i <= s.size(); ++i)
		{
			for (int j = 2; j <= p.size(); ++j)
			{
				if (p[j-1] != '*')
				{
					if (p[j-1] == '.' || p[j-1] == s[i-1])
						dp[i][j] = dp[i-1][j-1];
				}
				else
				{
					if (dp[i][j - 1]||dp[i][j-2])//末尾的'*'相当于0个或1个前面的char，匹配成功的情形
						dp[i][j] = true;
					else
					{
						if (p[j - 1-1] != '.')
						{
							if (p[j - 1-1] == s[i-1])
								dp[i][j] = dp[i-1][j];//星号抵消s的最后一个
						}
						else
						{
							dp[i][j] = dp[i-1][j];//星号抵消s的最后一个
						}
					}
				}
			}
		}
		
		return dp[s.size()][p.size()];
	}
};
//p299
class Trie {
	struct TrieNode
	{
		char data;
		vector<TrieNode*>children;
		bool isEnd;
		TrieNode(char d=0, bool ie=false) :data(d), isEnd(ie){}
		TrieNode* getChildren(char c)
		{
			for (int i = 0; i < children.size(); ++i)
			{
				if (children[i]->data == c)
					return children[i];
			}
			return NULL;
		}
	};
	TrieNode* root;
public:
	/** Initialize your data structure here. */
	Trie() {
		root = new TrieNode();
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		if (search(word))
			return;
		TrieNode* cur = root;
		for (int i = 0; i < word.size(); ++i)
		{
			auto child = cur->getChildren(word[i]);
			if (!child)
			{
				child = new TrieNode(word[i]);
				cur->children.push_back(child);
			}
			cur = child;
		}
		cur->isEnd = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode* cur = root;
		for (int i = 0; i < word.size(); ++i)
		{
			auto child = cur->getChildren(word[i]);
			if (!child)
				return false;
			cur = child;
		}
		return cur->isEnd;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		TrieNode* cur = root;
		for (int i = 0; i < prefix.size(); ++i)
		{
			auto child = cur->getChildren(prefix[i]);
			if (!child)
				return false;
			cur = child;
		}
		return true;
	}
};

