#include "moststd.h"
using namespace std;
template<class T>
void printMatrix(const vector<vector<T>>&m)
{
	for (auto mm : m)
	{
		for (auto mmm : mm)
			cout << mmm << " ";
		cout << endl;
	}
}
//P331
class SpiralOrderPrint
{
private:
	void printEdge(const vector<vector<int>>&m,int tr,int tc,int dr,int dc)
	{
		if (tr == dr)
		{
			for (int i = tc; i <= dc; ++i)
				printf("%d ",m[tr][i]);
		}
		else if (tc == dc)
		{
			for (int i = tr; i <= dr; ++i)
				printf("%d ",m[i][tc]);
		}
		else
		{
			int tcc = tc;
			while (tcc < dc)
			{
				printf("%d ",m[tr][tcc++]);
			}
			int trr = tr;
			while (trr < dr)
			{
				printf("%d ",m[trr++][dc]);
			}
			int dcc = dc;
			while (dcc > tc)
			{
				printf("%d ",m[dr][dcc--]);
			}
			int drr = dr;
			while (drr > tr)
			{
				printf("%d ",m[drr--][tc]);
			}
		}
	}
public:
	void spiralOrderPrint(const vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty())
			return;
		int tc = 0, tr = 0;
		int dc = m[0].size()-1, dr = m.size()-1;
		while (tc <= dc&&tr <= dr)
			printEdge(m,tr++,tc++,dr--,dc--);
		printf("\n");
	}
};
//P333
class RotateClockWise90
{
	void changeCoord(int& r, int&c, int n)
	{
		int nr, nc;
		nr = c;
		nc = (n-1)-r;
		r = nr;
		c = nc;
	}
	void rotateEdge(vector<vector<int>>&m, int tr, int tc, int dr, int dc)
	{
		//空间复杂度O（1）
		if (tr == dr&&tc == dc)
			return;
		for (int i = tc; i < dc; ++i)
		{
			int curc = i, curr = tr;
			int curVal = m[curr][curc];
			for (int t = 0; t < 4; ++t)
			{
				changeCoord(curr,curc,m.size());
				swap(curVal,m[curr][curc]);
			}
		}
	}

public:
	void rotate(vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty())
			return;
		assert(m.size()==m[0].size());
		int tc = 0, tr = 0, dc = m.size() - 1, dr = m.size() - 1;
		while (dc >= tc&&dr >= tr)
		{
			rotateEdge(m,tr++,tc++,dr--,dc--);
		}
	}
};
//P335
class PrintMatrixZigZag
{
	void printLevel(const vector<vector<int>>&m, int tr, int tc, int dr, int dc, bool direction)
	{
		if (direction)
		{
			//从左下打印到右上（↗）
			while (dr >= tr&&dc <= tc)
			{
				printf("%d ", m[dr--][dc++]);
			}
		}
		else
		{
			//↙
			while (tr <= dr&&tc >= dc)
			{
				printf("%d ",m[tr++][tc--]);
			}
		}
	}
public:
	void printMatrixZigZag(const vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty())
			return;
		int tr = 0, tc = 0, dr = 0, dc = 0;
		bool direction = true;
		while (tr <= dr&&tc >= dc)
		{
			printLevel(m,tr,tc,dr,dc,direction);
			direction = !direction;
			if (tc < m[0].size() - 1)
			{
				tc++;
			}
			else{
				tr++;
			}
			if (dr < m.size() - 1)
			{
				dr++;
			}
			else{
				dc++;
			}
		}
	}
};
//P336
class GetMinKNumsByMaxHeap
{
private:
	int PARENT(int i){ return (i + 1) / 2 - 1; }
	int LEFT(int i){ return  (i + 1) * 2 - 1; }
	int RIGHT(int i){ return (i + 1) * 2; }
	void maxHeapify(vector<int>&heap, int i, int indexOfLastNode)
	{
		int indexOfFirstLeafNode = PARENT(indexOfLastNode)+1;
		int indexOfLargestNode = i;
		while (i < indexOfFirstLeafNode)
		{
			int left = LEFT(i);
			int right = RIGHT(i);
			if (left <= indexOfLastNode&&heap[left] > heap[indexOfLargestNode])
				indexOfLargestNode = left;
			if (right <= indexOfLastNode&&heap[right] > heap[indexOfLargestNode])
				indexOfLargestNode = right;
			if (i == indexOfLargestNode)
				break;
			swap(heap[i],heap[indexOfLargestNode]);
			i = indexOfLargestNode;
		}
	}
	void buildMaxHeap(vector<int>&heap)
	{
		if (heap.empty())
			return;
		int indexOfFirstNonLeaf = PARENT(heap.size()-1);
		for (int i = indexOfFirstNonLeaf; i >= 0; --i)
		{
			maxHeapify(heap,i,heap.size()-1);
		}
	}
public:
	vector<int> getMinKNumsByHeap(const vector<int>&arr, int k)
	{
		assert(arr.size()>=k);
		vector<int>res(arr.begin(),arr.begin()+k);
		buildMaxHeap(res);
		for (int i = k; i < arr.size(); ++i)
		{
			if (arr[i] < res[0])
			{
				res[0] = arr[i];
				maxHeapify(res,0,k-1);
			}
		}
		return res;
	}
};
//P343
class PrintKMajor
{
public:
	void printHalfMajor(const vector<int>&arr)
	{
		if (arr.empty())
		{
			cout << "No such number\n";
			return;
		}
		int cand = 0;
		int times = 0;
		for (int i = 0; i != arr.size(); ++i)
		{
			if (times == 0)
			{
				cand = arr[i];
				times = 1;
			}
			else if (cand == arr[i])
			{
				++times;
			}
			else
			{
				--times;
			}
		}
		times = 0;
		for (int i = 0; i != arr.size(); ++i)
		{
			if (cand == arr[i])
				++times;
		}
		if (times > (arr.size() / 2))
			cout << "The number is:" << cand << endl;
		else
			cout << "No such number\n";
	}
	void printKMajor(const vector<int>&arr, int k)
	{
		if (arr.empty())
		{
			cout << "No such number\n";
			return;
		}
		unordered_map<int, int>mp;
		for (int i = 0; i != arr.size(); ++i)
		{
			if (mp.find(arr[i]) != mp.end())
			{
				++mp[arr[i]];
			}
			else
			{
				if (mp.size() < k - 1)
				{
					mp[arr[i]] = 1;
				}
				else
				{
					for (auto iter = mp.begin(); iter != mp.end();)
					{
						if (iter->second == 1)
						{
							mp.erase(iter++);
						}
						else
						{
							--(iter->second);
							++iter;
						}
					}
				}
			}
		}
		vector<int>res;
		for (auto iter = mp.begin(); iter != mp.end(); ++iter)
		{
			int cand = iter->first;
			int times = 0;
			for (int i = 0; i != arr.size(); ++i)
			{
				if (arr[i] == cand)
					++times;
			}
			if (times > arr.size() / k)
				res.push_back(cand);
		}
		if (res.empty())
			cout << "No such number\n";
		else
		{
			cout << "The numbers are:";
			for (auto r : res)
				cout << r << " ";
			cout << endl;
		}
	}
};
//p349
class IsContains
{
public: 
	bool isContains(const vector<vector<int>>&m, int k)
	{
		if (m.empty() || m[0].empty())
			return false;
		int rmax = m.size()-1, cmax = m[0].size()-1;
		int r = 0, c = cmax;
		while (r <= rmax&&c >= 0)
		{
			if (m[r][c] == k)
				return true;
			if (m[r][c] > k)
			{
				--c;
			}
			else
			{
				++r;
			}
		}
		return false;
	}
};
//p349
class GetLIL
{
public:
	int getLIL2(const vector<int>&arr)
	{
		if (arr.empty())
			return 0;
		unordered_set<int>st;
		int len = 0;
		for (int i = 0; i < arr.size(); ++i)
		{
			int curMin = INT_MAX, curMax = INT_MIN;
			for (int j = i; j < arr.size(); ++j)
			{
				if (st.find(arr[j]) != st.end())
					break;
				st.insert(arr[j]);
				curMin = min(curMin, arr[j]);
				curMax = max(curMax, arr[j]);
				if (curMax - curMin == j - i)
				{
					len = max(len,j-i+1);
				}
			}
			st.clear();
		}
		return len;
	}
};
class Sort1
{
public:
	void sort1(vector<int>&arr)
	{
		for (int i = 0; i != arr.size(); ++i)
		{
			int cur = arr[i], tmp;
			while (arr[i] != i + 1)
			{
				tmp = arr[cur-1];
				arr[cur - 1] = cur;
				cur = tmp;
			}
		}
	}
};
class ArrarMaxSum
{
public:
	int maxSum(const vector<int>&arr)
	{
		if (arr.empty())
			return 0;
		int maxs = INT_MIN;
		int cur = 0;
		for (int i = 0; i != arr.size(); ++i)
		{
			cur = cur + arr[i];
			maxs = max(maxs,cur);
			if (cur < 0)
				cur = 0;
		}
		return maxs;
	}
};
//P369
class MatrixMaxSum
{
public:
	int maxSum(const vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty())
			return 0;
		vector<int>arr(m[0].size());
		int res = INT_MIN;
		for (int i = 0; i != m.size(); ++i)
		{
			fill(arr.begin(),arr.end(),0);
			for (int r = i; r != m.size(); ++r)
			{
				for (int c = 0; c != m[0].size(); ++c)
				{
					arr[c] += m[r][c];
				}
				res = max(res,ArrarMaxSum().maxSum(arr));
			}
		}
		return res;
	}
};
//P371
class GetLessIndex
{
public:
	int getLessIndex(const vector<int>&arr)
	{
		if (arr.empty())
			return -1;
		if (arr.size() == 1)
			return arr[0];
		if (arr[arr.size() - 1] < arr[arr.size() - 2])
			return arr[arr.size() - 1];
		if (arr[0] < arr[1])
			return arr[0];
		int left = 0, right = arr.size() - 1;
		while (left < right)
		{
			int mid = (left + right) / 2;
			if (arr[mid] < arr[mid + 1] && arr[mid] < arr[mid - 1])
				return mid;
			else if (arr[mid] > arr[mid + 1])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		return left;
	}
};
//P373
template<class T>
class MaxProduct
{
public:
	T maxProduct(const vector<T>&arr)
	{
		if (arr.empty())
			return -1;
		T min = arr[0], max = arr[0];
		T res = max;
		for (int i = 1; i < arr.size(); ++i)
		{
			T premin = min, premax = max;
			auto p = minmax({min*arr[i],max*arr[i],arr[i]});
			min = p.first;
			max = p.second;
			res = std::max(res,max);
		}
		return res;
	}
};
class PrintTopK
{
private:
	struct heapNode
	{
		int val;
		int arrNum;
		int index;
		heapNode(int v, int a, int i) :val(v), arrNum(a), index(i){}
	};
	int PARENT(int i){ return (i + 1) / 2 - 1; }
	int LEFT(int i){ return  (i + 1) * 2 - 1; }
	int RIGHT(int i){ return (i + 1) * 2; }
	void maxHeapify(vector<heapNode>&heap, int i, int indexOfLastNode)
	{
		int indexOfFirstLeafNode = PARENT(indexOfLastNode) + 1;
		int indexOfLargestNode = i;
		while (i < indexOfFirstLeafNode)
		{
			int left = LEFT(i);
			int right = RIGHT(i);
			if (left <= indexOfLastNode&&heap[left].val > heap[indexOfLargestNode].val)
				indexOfLargestNode = left;
			if (right <= indexOfLastNode&&heap[right].val > heap[indexOfLargestNode].val)
				indexOfLargestNode = right;
			if (i == indexOfLargestNode)
				break;
			swap(heap[i], heap[indexOfLargestNode]);
			i = indexOfLargestNode;
		}
	}
	void buildMaxHeap(vector<heapNode>&heap)
	{
		if (heap.empty())
			return;
		int indexOfFirstNonLeaf = PARENT(heap.size() - 1);
		for (int i = indexOfFirstNonLeaf; i >= 0; --i)
		{
			maxHeapify(heap, i, heap.size() - 1);
		}
	}
public:
	void printTopK(const vector<vector<int>>&m, int k)
	{
		if (m.empty() || m[0].empty())
			return;
		int n = m.size();
		vector<heapNode>heap;
		for (int i = 0; i < n; ++i)
		{
			heap.push_back(heapNode(m[i].back(),i,m[i].size()-1));
		}
		buildMaxHeap(heap);
		int heapSize = heap.size();
		for (int i = 0; i < k&&heapSize>0; ++i)
		{
			auto top = heap[0];
			cout << top.val << " ";
			if (top.index > 0)
			{
				heap[0] = heapNode(m[top.arrNum][top.index-1],top.arrNum,top.index-1);
				maxHeapify(heap,0,heapSize-1);
			}
			else
			{
				swap(heap[0],heap[heapSize-1]);
				--heapSize;
				maxHeapify(heap,0,heapSize-1);
			}
		}
		cout << endl;
	}
};
//P377
class GetMaxMatrixWithBorderOfAllOnes
{
private:
	void setBorderMap(const vector<vector<int>>&m, vector<vector<int>>&down, vector<vector<int>>&right)
	{
		down = vector<vector<int>>(m.size(),vector<int>(m[0].size(),0));
		right = down;
		int height = m.size(), width = m[0].size();
		if (m[height - 1][width - 1] == 1)
		{
			down[height - 1][width - 1] = 1;
			right[height - 1][width - 1] = 1;
		}
		for (int i = width-2; i>=0; --i)
		{
			if (m[height - 1][i] == 1)
			{
				down[height - 1][i] = 1;
				right[height - 1][i] = right[height - 1][i + 1] + 1;
			}
		}
		for (int i = height - 2; i >= 0; --i)
		{
			if (m[i][width - 1] == 1)
			{
				down[i][width - 1] = down[i + 1][width - 1] + 1;
				right[i][width - 1] = 1;
			}
		}
		for (int r = height - 2; r >= 0; --r)
		{
			for (int c = width - 2; c >= 0; --c)
			{
				if (m[r][c] == 1)
				{
					down[r][c] = down[r+1][c] + 1;
					right[r][c] = right[r][c + 1] + 1;
				}
			}
		}
	}
	bool hasSizeOfBorder(int r, int c, int a,const vector<vector<int>>&down, const vector<vector<int>>&right)
	{
		return (down[r][c]>=a&&right[r][c]>=a&&down[r][c+a-1]>=a&&right[r+a-1][c]>=a);
	}
public:
	int getMaxSize(const vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty())
			return 0;
		int height = m.size(), width = m[0].size();
		vector<vector<int>>down, right;
		setBorderMap(m,down,right);
		int res = 0;
		for (int r = 0; r <= height - 1; ++r)
		{
			for (int c = 0; c <= width - 1; ++c)
			{
				int ma = min(height-r,width-c);
				for (int sz = 1; sz <= ma; ++sz)
				{
					if (hasSizeOfBorder(r, c, sz, down, right))
						res = max(res,sz);
				}
			}
		}
		return res;
	}
};
//p381
vector<int>product2(const vector<int>&arr)
{
	if (arr.empty())
		return vector<int>();
	vector<int>res(arr.size());
	res[0] = arr[0];
	for (int i = 1; i <= arr.size() - 1; ++i)
	{
		res[i] = arr[i] * res[i-1];
	}
	int tmp = 1;
	for (int i = arr.size() - 1; i >= 1; --i)
	{
		res[i] = res[i - 1] * tmp;
		tmp *= arr[i];
	}
	res[0] = arr[0];
	return res;
}
class ArrayPartition
{
public:
	void leftUnique(vector<int>&arr)
	{
		if (arr.size() <= 1)
			return;
		int u = 0;
		for (int j = 1; j <= arr.size() - 1; ++j)
		{
			if (arr[j] > arr[u])
			{
				swap(arr[++u],arr[j]);
			}
		}
	}
	void sort0(vector<int>&arr)
	{
		if (arr.size() <= 1)
			return;
		int i0 = -1;
		for (int j = 0; j <= arr.size() - 1; ++j)
		{
			if (arr[j] == 0)
				swap(arr[++i0],arr[j]);
		}
		int i1 = i0;
		for (int j = i0+1; j <= arr.size()-1; ++j)
		{
			if (arr[j] == 1)
				swap(arr[++i1],arr[j]);
		}
	}
	void sort(vector<int>&arr)
	{
		if (arr.size() <= 1)
			return;
		int left = -1,right = arr.size();
		//loop invariant:[0,left]==0;[left+1,mid-1]==1,[right,arr.size()-1]==2
		for (int mid = 0; mid <= arr.size() - 1&&mid<right; ++mid)
		{
			if (arr[mid] == 1)
				continue;
			else if (arr[mid] == 0)
				swap(arr[++left], arr[mid]);
			else
				swap(arr[--right],arr[mid--]);
		}
	}
};
//P384
class MinPathValue
{
	struct Point
	{
		int r;
		int c;
		Point(int rv, int cv) :r(rv), c(cv){}
	};
public:
	int minPathValue(const vector<vector<int>>&m)
	{
		if (m.empty() || m[0].empty()||m.back().back()==0)
			return 0;
		vector<vector<int>>mp = vector<vector<int>>(m.size(),vector<int>(m[0].size(),0));
		queue<Point>q;
		if (m[0][0] == 1)
		{
			q.push(Point(0,0));
			mp[0][0] = 1;
		}
		int dr[4] = {0,-1,0,1};
		int dc[4] = {-1,0,1,0};
		while (!q.empty())
		{
			auto f = q.front();
			q.pop();
			for (int i = 0; i < 4; ++i)
			{
				int r = f.r + dr[i];
				int c = f.c + dc[i];
				if (r >= 0 && r <= m.size() - 1 && c >= 0 && c <= m[0].size() - 1&&mp[r][c]==0&&m[r][c]==1)
				{
					mp[r][c] = mp[f.r][f.c] + 1;
					q.push(Point(r,c));
				}
				if (r == m.size() - 1 && c == m[0].size() - 1)
					return mp[r][c];
			}
		}
		return 0;
	}
};
//P388
class MaxGap
{
	int getBucketIndex(long num, long min, long max, long len)
	{
		return (num - min)*len / (max - min);
	}
public:
	int maxGap(const vector<int>&nums)
	{
		if (nums.size() <= 1)
			return 0;
		auto p = minmax_element(nums.begin(),nums.end());
		int min = *(p.first), max = *(p.second);
		if (max == min)
			return 0;
		int len = nums.size();
		vector<int>mins(len + 1,INT_MAX), maxs(len + 1,INT_MIN);
		vector<bool>hasNum(len+1,false);
		for (auto num : nums)
		{
			int bi = getBucketIndex(num,min,max,len);
			hasNum[bi] = true;
			mins[bi] = std::min(mins[bi],num);
			maxs[bi] = std::max(maxs[bi],num);
		}
		int i = 0;
		int lastMax = 0;
		for (; i <= len; ++i)
		{
			if (hasNum[i])
			{
				lastMax = maxs[i];
				++i;
				break;
			}
		}
		int res = 0;
		for (; i <= len; ++i)
		{
			if (hasNum[i])
			{
				res = std::max(mins[i]-lastMax,res);
				lastMax = maxs[i];
			}
		}
		return res;

	}
};
//p387
int missNum(vector<int>arr)
{
	int l = 0, r = arr.size();
	while (l < r)
	{
		if (arr[l] == l + 1)
			l++;
		else if (arr[l] <= l || arr[l]>r || arr[arr[l] - 1] == arr[l])
			arr[l] = arr[--r];
		else
			swap(arr[l],arr[arr[l]-1]);
	}
	return l + 1;
}
void main()
{
	
	vector<vector<int>>m = {
			{1,0,1,1,1},
			{1,1,1,0,1},
			{1,1,0,0,1},
			{1,1,0,1,1},
			{1,0,1,1,1}
	};
	
	vector<int>arr = {-1,2,3,4};
	int a = missNum(arr);
	
	int itrpt = 0;
}