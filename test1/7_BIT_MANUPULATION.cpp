#include "moststd.h"
using namespace std;
//P318
class GetMax
{
private:
    int flip(int a)
	{
		return a ^ 1;
	}
	int sign(int a)
	{
		return flip((a >> 31)^0);
	}
public:
	int getMax1(int a, int b)
	{
		//有可能溢出
		int c = a - b;
		int scA = sign(c);
		int scB = flip(scA);
		return scA*a + scB*b;
	}
	int getMax2(int a, int b)
	{
		int sa = sign(a);
		int sb = sign(b);
		int difSab = sa ^ sb;
		int sameSab = flip(difSab);
		int c = a - b;
		int scA = sign(c);
		int scB = flip(scA);
		return sameSab*(scA*a + scB*b) + difSab*(sa*a+sb*b);
	}
};
//P325
class CountNumOfOne
{
public:
	int count1(int n)
	{
		int res = 0;
		int k = 32;
		while (k != 0)
		{
			res += (n&1);
			n=n >> 1;
			--k;
		}
		return res;
	}
	int count2(int n)
	{
		int res = 0;
		while (n != 0)
		{
			n &= (n-1);
			++res;
		}
		return res;
	}
};
string intToBinaryStrRepr(int a)
{
	//将a转化为其在计算机中的二进制表示（32位的补码形式）
	char b[100];
	_itoa_s(a, b, 2);
	string res(b);
	if (res.size() < 32)
	{
		res = string(32 - res.size(),'0') + res;
	}
	assert(res.size()==32);
	return res;
}
//P327
class PrintOddTimesNum
{
public:
	int printOddTimesNum1(const vector<int>&arr)
	{
		int e0 = 0;
		for (auto a : arr)
		{
			e0 ^= a;
		}
		return e0;
	}
	pair<int,int> printOddTimesNum2(const vector<int>&arr)
	{
		int eO = printOddTimesNum1(arr);
		int rightOne = eO&(~eO+1);
		int eOHasOne = 0;
		for (auto a : arr)
		{
			if ((rightOne&a) != 0)
			{
				eOHasOne ^= a;
			}
		}
		return{eOHasOne,eOHasOne^eO};
	}
};
//P329
class OnceNum
{
private:
	vector<int>getKSysNumFromNum(int value, int k)
	{
		vector<int>res(32,0);
		int index = 0;
		while (value != 0)
		{
			int v = value%k;
			res[index++] = v;
			value /= k;
		}
		return res;
	}
	int getNumFromKSysNum(const vector<int>&eO, int k)
	{
		int res = 0;
		for (int i = 0; i < eO.size(); ++i)
		{
			res += (eO[i]*pow(k,i));
		}
		return res;
	}
	void setExclusiveOr(vector<int>&eO, int value, int k)
	{
		vector<int> curKSysNum = getKSysNumFromNum(value,k);
		for (size_t i = 0; i != eO.size(); ++i)
		{
			eO[i] = (eO[i] + curKSysNum[i]) % k;
		}
	}
public:
	int onceNum(const vector<int>&arr, int k)
	{
		vector<int>eO(32,0);
		for (auto a : arr)
		{
			setExclusiveOr(eO,a,k);
		}
		return getNumFromKSysNum(eO,k);
	}
};

