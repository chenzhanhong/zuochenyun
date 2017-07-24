#include "moststd.h"
using namespace std;

struct treeNode
{
	int val;
	treeNode* left;
	treeNode* right;
	treeNode(int v) :val(v), left(NULL), right(NULL){}
};
treeNode* genCompleteBinaryTree(const vector<int>&arr)
{
	if (arr.empty())return NULL;
	vector<treeNode*>nodes(arr.size()+1);
	for (size_t i = 1; i < nodes.size(); ++i)
	{
		nodes[i] = new treeNode(arr[i-1]);
	}
	delete nodes[0]; 
	nodes[0] = NULL;
	for (size_t i = 1; i < nodes.size(); ++i)
	{
		if (2 * i < nodes.size())nodes[i]->left = nodes[2*i];
		if (2 * i + 1 < nodes.size())nodes[i]->right = nodes[2*i+1];
	}
	return nodes[1];
}
void preOrderUnRecur0(treeNode* root)
{
	cout << "preorder:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	visitedNodes.insert(NULL);//这样能防止去访问null的节点
	stack<treeNode*>stk;
	stk.push(root);
	cout << root->val << " ";
	visitedNodes.insert(root);
	while (!stk.empty())
	{
		auto top = stk.top();
		vector<treeNode*>adj = {top->left,top->right};
		auto it = adj.begin();
		for (; it != adj.end(); ++it)
		{
			if (visitedNodes.find(*it) == visitedNodes.end())
			{
				stk.push(*it);
				cout << (*it)->val << " ";
				visitedNodes.insert(*it);
				break;
			}
		}
		if (it == adj.end())
			stk.pop();
	}
}
void preOrderUnRecur(treeNode* root)
{
	cout << "preorder:" << endl;
	if (!root)return;
	stack<treeNode*>stk;
	stk.push(root);
	while (!stk.empty())
	{
		auto top = stk.top();
		stk.pop();
		cout << top->val << " ";
		if (top->right)stk.push(top->right);
		if (top->left)stk.push(top->left);
	}
}
void inOrderUnRecur0(treeNode* root)
{
	cout << "inorder:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	visitedNodes.insert(NULL);//这样能防止去访问null的节点
	stack<treeNode*>stk;
	stk.push(root);
	while (!stk.empty())
	{
		auto top = stk.top();
		if (visitedNodes.find(top->left) != visitedNodes.end())
		{
			cout << top->val << " ";
			visitedNodes.insert(top);
			stk.pop();
			if (top->right)stk.push(top->right);
		}
		else
		{
			if (top->left)stk.push(top->left);
		}
	}
}
void inOrderUnRecur1(treeNode* root)
{
	cout << "inorder:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	//visitedNodes.insert(NULL);//这样能防止去访问null的节点
	stack<treeNode*>stk;
	stk.push(root);
	while (!stk.empty())
	{
		auto top = stk.top();
		if (visitedNodes.find(top->left) != visitedNodes.end()||!top->left)
		{
			if (visitedNodes.find(top->right) == visitedNodes.end()||!top->right)
			{
				cout << top->val << " ";
				visitedNodes.insert(top);
				if (top->right)stk.push(top->right);
				else stk.pop();
			}
			else
			{
				stk.pop();
			}
		}
		else
		{
		    if (top->left)stk.push(top->left);
		}
	}
}
void inOrderUnRecur(treeNode* root)
{
	cout << "inorder:" << endl;
	if (!root)return;
	stack<treeNode*>stk;
	auto cur = root;
	while (!stk.empty()||cur)
	{
		if (cur)
		{
			stk.push(cur);
			cur = cur->left;
		}
		else
		{
			cur = stk.top();
			stk.pop();
			cout << cur->val << " ";
			cur = cur->right;
		}
	}
}

void preOrderUnRecur_(treeNode* root)
{
	cout << "pre-order:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	stack<treeNode*>stk;
	stk.push(root);
	cout << root->val << " ";
	visitedNodes.insert(root);
	while (!stk.empty())
	{
		auto left = stk.top()->left;
		auto right = stk.top()->right;
		if ((!left || visitedNodes.find(left) != visitedNodes.end()) && (!right || visitedNodes.find(right) != visitedNodes.end()))
		{
			stk.pop();
		}
		else
		{
			if (left&&visitedNodes.find(left) == visitedNodes.end())
			{
				stk.push(left);
				cout << left->val << " ";
				visitedNodes.insert(left);
			}
			else
			{
				stk.push(right);
				cout << right->val << " ";
				visitedNodes.insert(right);
			}
		}
	}
}
void inOrderUnRecur_(treeNode* root)
{
	cout << "inorder:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	stack<treeNode*>stk;
	stk.push(root);
	while (!stk.empty())
	{
		auto left = stk.top()->left;
		auto right = stk.top()->right;
		if ((!left || visitedNodes.find(left) != visitedNodes.end()) && (!right || visitedNodes.find(right) != visitedNodes.end()))
		{
			if (!right)
			{
				cout << stk.top()->val << " ";
				visitedNodes.insert(stk.top());
			}
			stk.pop();
		}
		else
		{
			if (left&&visitedNodes.find(left) == visitedNodes.end())
			{
				stk.push(left);
			}
			else
			{
				cout << stk.top()->val << " ";
				visitedNodes.insert(stk.top());
				stk.push(right);
			}
		}
	}
}
void posOrderUnRecur_(treeNode* root)
{
	cout << "pos-order:" << endl;
	if (!root)return;
	unordered_set<treeNode*>visitedNodes;
	stack<treeNode*>stk;
	stk.push(root);
	while (!stk.empty())
	{
		auto left = stk.top()->left;
		auto right = stk.top()->right;
		if ((!left || visitedNodes.find(left) != visitedNodes.end()) && (!right || visitedNodes.find(right) != visitedNodes.end()))
		{
			cout << stk.top()->val << " ";
			visitedNodes.insert(stk.top());
			stk.pop();
		}
		else
		{
			if (left&&visitedNodes.find(left) == visitedNodes.end())
			{
				stk.push(left);
			}
			else
			{
				stk.push(right);
			}
		}
	}
}
//P93
void posOrderUnRecur1(treeNode* root)
{
	cout << "pos-order:" << endl;
	if (!root)return;
	stack<treeNode*>stk1, stk2;
	stk1.push(root);
	while (!stk1.empty())
	{
		auto top = stk1.top();
		stk1.pop();
		stk2.push(top);
		if (top->left)stk1.push(top->left);
		if (top->right)stk1.push(top->right);
	}
	while (!stk2.empty())
	{
		cout << stk2.top()->val << " ";
		stk2.pop();
	}
}
string getSpace(int num)
{
	string res = "";
	for (int i = 0; i < num; ++i)
	{
		res += " ";
	}
	return res;
}
void printInOrder(treeNode*head, int height, int spaceLen, string to)
{
	if (!head)return;
	printInOrder(head->right, height + 1, spaceLen, "v");
	string val = to+to_string(head->val)+to;
	int lenM = val.length();
	int lenL = (spaceLen-lenM) / 2;
	int lenR = spaceLen - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height*spaceLen) + val << endl;
	printInOrder(head->left,height+1,spaceLen,"^");
}
void printTree(treeNode*root)
{
	cout << "打印二叉树:\n";
	printInOrder(root,0,17,"H");
}
string serialByPre(treeNode*root)
{
	if (!root)return "#!";
	string res = to_string(root->val) + "!";
	res += serialByPre(root->left);
	res += serialByPre(root->right);
	return res;
}
vector<string>split(const string& str, char delim)
{
	vector<string>res;
	size_t start = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == delim)
		{
			res.push_back(str.substr(start,i-start));
			start = i + 1;
		}
	}
	return res;
}
treeNode* reconByPreString0(string preStr)
{
	if (preStr == "#!")return NULL;
	vector<string>items = split(preStr,'!');
	stack<treeNode*>stk;
	treeNode* root = new treeNode(stoi(items[0]));
	stk.push(root);
	stack<int>cntStk;
	cntStk.push(0);
	for (size_t i = 1; i < items.size(); ++i)
	{
		if (items[i] != "#")
		{
			stk.push(new treeNode(stoi(items[i])));
			cntStk.push(0);
		}
		else
		{
			treeNode* child = NULL;
			while (!cntStk.empty())
			{
				int top = cntStk.top();
				if (top == 0)
				{
					stk.top()->left = child;
				}
				if (top == 1)
				{
					stk.top()->right = child;
				}
				cntStk.pop();
				++top;
				cntStk.push(top);
				if (top < 2)
					break;
				else
				{
					cntStk.pop();
					child = stk.top();
					stk.pop();
				}
			}
		}
	}
	return root;
}
treeNode* reconPreOrder(queue<string>&q)
{
	string value = q.front();
	q.pop();
	if (value == "#")return NULL;
	treeNode* head = new treeNode(stoi(value));
	head->left = reconPreOrder(q);
	head->right = reconPreOrder(q);
	return head;
}
treeNode* reconByPreString(string preStr)
{
	if (preStr == "#!")return NULL;
	vector<string>items = split(preStr, '!');
	queue<string>q;
	for (auto item : items)
	{
		q.push(item);
	}
	return reconPreOrder(q);
}
string serialByLevel(treeNode*root)
{
	string res="";
	queue<treeNode*>q;
	q.push(root);
	while (!q.empty())
	{
		treeNode* front = q.front();
		q.pop();
		if (!front)
		{
			res += "#!";
		}
		else
		{
			res += to_string(front->val) + "!";
			q.push(front->left);
			q.push(front->right);
		}
	}
	return res;
}
treeNode* reconByLevelString(const string& levelStr)
{
	if (levelStr == "#!")return NULL;
	vector<string>items = split(levelStr,'!');
	queue<treeNode*>q;
	int cnt = 0;
	treeNode* root = new treeNode(stoi(items[0]));
	q.push(root);
	for (size_t i = 1; i < items.size(); ++i)
	{
		treeNode* cur = (items[i]=="#"?NULL:new treeNode(stoi(items[i])));
		if (cnt == 0)
		{
			q.front()->left = cur;
		}
		if (cnt == 1)
		{
			q.front()->right = cur;
		}
		if (cur)q.push(cur);
		++cnt;
		if (cnt == 2)
		{
			cnt = 0;
			q.pop();
		}
	}
	return root;
}
void morrisIn(treeNode* root)
{
	cout << "morrisIn:";
	treeNode*cur = root, *pre = NULL;
	while (cur)
	{
		pre = cur->left;
		if (pre)
		{
			while (pre->right&&pre->right != cur)
			{
				pre = pre->right;
			}
			if (!pre->right)
			{
				pre->right = cur;
				cur = cur->left;
			}
			else
			{
				pre->right = NULL;
				cout << cur->val << " ";
				cur = cur->right;
			}
		}
		else
		{
			cout << cur->val << " ";
			cur = cur->right;
		}
	}
	cout << endl;
}
void morrisPre(treeNode* root)
{
	cout << "morrisPre:";
	treeNode* cur =root, *pre = NULL;
	while (cur)
	{
		pre = cur->left;
		if (pre)
		{
			while (pre->right&&pre->right != cur)
			{
				pre = pre->right;
			}
			if (!pre->right)
			{
				pre->right = cur;
				cout << cur->val << " ";
				cur = cur->left;
			}
			else
			{
				pre->right = NULL;
				cur = cur->right;
			}
		}
		else
		{
			cout << cur->val << " ";
			cur = cur->right;
		}
	}
	cout << endl;
}
treeNode* reverseEdge(treeNode* from)
{
	treeNode* pre = NULL, *cur = from, *next;
	while (cur)
	{
		next = cur->right;
		cur->right = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}
void printEdge(treeNode*head)
{
	treeNode* tail = reverseEdge(head);
	treeNode* cur = tail;
	while (cur)
	{
		cout << cur->val << " ";
		cur = cur->right;
	}
	head = reverseEdge(tail);
}
void morrisPos(treeNode* root)
{
	cout << "morrisPos:";
	treeNode* temp = new treeNode(0);
	temp->left = root;
	treeNode* cur = temp, *pre = NULL;
	while (cur)
	{
		pre = cur->left;
		if (pre)
		{
			while (pre->right&&pre->right != cur)
			{
				pre = pre->right;
			}
			if (!pre->right)
			{
				pre->right = cur;
				cur = cur->left;
			}
			else
			{
				pre->right = NULL;
				printEdge(cur->left);
				cur = cur->right;
			}
		}
		else
		{
			cur = cur->right;
		}
	}
	cout << endl;
}
void preOrder(treeNode*head, int level, int sum, int preSum, int&maxLen, unordered_map<int, int>&sumMap)
{
	if (!head)return;
	int curSum = preSum + head->val;
	bool flag = false;
	if (sumMap.find(curSum) == sumMap.end())
	{
		sumMap[curSum] = level;
		flag = true;
	}
	if (sumMap.find(curSum - sum) != sumMap.end())
	{
		maxLen = max(level - sumMap[curSum - sum], maxLen);
	}
	preOrder(head->left, level + 1, sum, curSum, maxLen, sumMap);
	preOrder(head->right, level + 1, sum, curSum, maxLen, sumMap);
	if (flag)
		sumMap.erase(curSum);
}
int getMaxLength(treeNode*head, int sum)
{
	unordered_map<int, int>sumMap;
	sumMap[0] = 0;
	int maxLen = 0;
	preOrder(head,1,sum,0,maxLen,sumMap);
	return maxLen;
}
treeNode* posOrder(treeNode*head, vector<int>&record)
{
	if (!head)
	{
		record[0] = 0;
		record[1] = INT_MAX;
		record[2] = INT_MIN;
		return NULL;
	}
	int val = head->val;
	auto lbst=posOrder(head->left,record);
	int lsz = record[0];
	int lmin = record[1];
	int lmax = record[2];
	auto rbst = posOrder(head->right,record);
	int rsz = record[0];
	int rmin = record[1];
	int rmax = record[2];
	record[1] = min(min(lmin,rmin),val);
	record[2] = max(max(lmax,rmax),val);
	if (lbst == head->left&&rbst == head->right&&val > lmax&&val < rmin)
	{
		record[0] = lsz + rsz + 1;
		return head;
	}
	record[0] = max(lsz,rsz);
	return lsz > rsz ? lbst : rbst;
}
vector<vector<int>> zigzagLevelOrder(treeNode* root) {
	vector<vector<int>>res;
	if (!root)return res;
	bool right2left = true;
	vector<treeNode*>pre = {root};
	vector<int>p = {root->val};
	res.push_back(p);
	
	while (true)
	{
		vector<treeNode*>cur;
		vector<int>c;
		if (right2left)
		{
			for (auto ri = pre.rbegin(); ri != pre.rend(); ++ri)
			{
				if ((*ri)->right)
				{
					cur.push_back((*ri)->right);
					c.push_back((*ri)->right->val);
				}
				if ((*ri)->left)
				{
					cur.push_back((*ri)->left);
					c.push_back((*ri)->left->val);
				}
				
			}
		}
		else
		{
			for (auto it = pre.rbegin(); it != pre.rend(); ++it)
			{
				if ((*it)->left)
				{
					cur.push_back((*it)->left);
					c.push_back((*it)->left->val);
				}
				if ((*it)->right)
				{
					cur.push_back((*it)->right);
					c.push_back((*it)->right->val);
				}
			}
		}
		if (cur.empty())break;
		pre = cur;
		res.push_back(c);
		right2left = !right2left;
	}
	return res;
}
vector<treeNode*>getTwoErrNodes(treeNode*root)
{
	vector<treeNode*>res(2,NULL);
	if (!root)return res;
	stack<treeNode*>stk;
	treeNode* cur = root;
	treeNode* pre=NULL;
	while (!stk.empty() || cur)
	{
		if (cur)
		{
			stk.push(cur);
			cur = cur->left;
		}
		else
		{
			auto top = stk.top();
			stk.pop();
			if (pre&&top->val < pre->val)
			{
				res[0] = (res[0]?res[0]:pre);
				res[1] = top;
			}
			pre = top;
			cur = cur->right;
		}
	}
	return res;
}
bool check1(treeNode* t1, treeNode*t2)
{
	//判断t1树是否包含t2树全部的拓扑结构,且包含的起点是从t1开始的
	if (!t2)return true;
	if (!t1 || t1->val != t2->val)return false;
	return check1(t1->left, t2->left) && check1(t1->right,t2->right);
}
bool check2(treeNode* t1, treeNode* t2)
{
	//判断t1树是否包含与t2树拓扑结构完全相同的子树，且包含的起点是从t1开始的
	if (!t1 && !t2)return true;
	if (!t1 || !t2)return false;
	if (t1->val != t2->val)return false;
	return check2(t1->left, t2->left) && check2(t1->right, t2->right);
}
bool contain1(treeNode* t1, treeNode*t2)
{
	if (!t1)return check1(t1,t2);
	return check1(t1, t2) || contain1(t1->left, t2) || contain1(t1->right,t2);
}
bool contain2(treeNode* t1, treeNode*t2)
{
	if (!t1)return check2(t1,t2);
	return check2(t1, t2) || contain2(t1->left, t2) || contain2(t1->right, t2);
}
pair<bool, int> isBalancedAux(treeNode*head)
{
	if (!head)return{true,0};
	auto pl = isBalancedAux(head->left);
	if (!pl.first)return{ false, -1 };
	auto pr = isBalancedAux(head->right);
	if (!pr.first)return{ false, -1 };
	if (abs(pl.second - pr.second) > 1)return{false,-1};
	return{true,max(pl.second,pr.second)+1};
}
bool isBalanced(treeNode* head)
{
	return isBalancedAux(head).first;
}
bool isPostArray(const vector<int>& arr)
{
	if (arr.size() == 0 || arr.size() == 1)return true;
	int mid = arr.back();
	vector<int>v1, v2;
	bool isLarger = false;
	for (size_t i = 0; i <= arr.size() - 2; ++i)
	{
		if (!isLarger)
		{
			if (arr[i] > mid)
			{
				isLarger = true;
				v2.push_back(arr[i]);
			}
			else
			{
				v1.push_back(arr[i]);
			}
		}
		else
		{
			if (arr[i] < mid)
				return false;
			v2.push_back(arr[i]);
		}
	}
	return isPostArray(v1) && isPostArray(v2);
}
bool isBST(treeNode* head)
{
	if (!head)return true;
	bool res = true;
	treeNode* cur = head;
	int preVal = head->val;
	while (cur)
	{
		auto pre = cur->left;
		if (pre)
		{
			while(pre->right&&pre->right!=cur)
			{
				pre = pre->right;
			}
			if (!pre->right)
			{
				pre->right = cur;
				cur = cur->left;
			}
			else
			{
				int curVal = cur->val;
				if (curVal != preVal&&curVal < preVal)
					res = false;
				preVal = curVal;
				pre->right = NULL;
				cur = cur->right;
			}
		}
		else
		{
			int curVal = cur->val;
			if (curVal != preVal&&curVal < preVal)
				res = false;
			preVal = curVal;
			cur = cur->right;
		}
	}
	return res;
}
bool isCBT(treeNode*head)
{
	if (!head)return true;
	queue<treeNode*>q;
	q.push(head);
	bool needTobeLeaf = false;
	while (!q.empty())
	{
		auto front = q.front();
		q.pop();
		auto left = front->left;
		auto right = front->right;
		if (!left&&right)return false;
		if (needTobeLeaf && (left || right))return false;
		if (!left || !right)needTobeLeaf = true;
		if (left)q.push(left);
		if (right)q.push(right);
	}
	return true;
}
struct ptreeNode
{
	int val;
	ptreeNode* left;
	ptreeNode* right;
	ptreeNode* parent;
	ptreeNode(int v) :val(v), left(NULL), right(NULL),parent(NULL){}
};
ptreeNode* getLeftMost(ptreeNode* node)
{
	auto pre = node;
	auto cur = node->left;
	while (cur)
	{
		pre = cur;
		cur = cur->left;
	}
	return pre;
}
ptreeNode* getNextNode(ptreeNode*node)
{
	if (!node)return NULL;
	if (node->right)
		return getLeftMost(node->right);
	auto cur = node;
	while (cur)
	{
		auto parent = cur->parent;
		if (!parent)
			return NULL;
		if (parent->left == cur)
			return parent;
		cur = parent;
	}
	return NULL;
}
treeNode* lowestAncestor(treeNode* head, treeNode* o1, treeNode*o2)
{
	if (head == NULL || head == o1 || head == o2)
		return head;
	auto l = lowestAncestor(head->left,o1,o2);
	auto r = lowestAncestor(head->right,o1,o2);
	if (!l&&r)
		return r;
	if (l&&!r)
		return l;
	return head;
}
class Record1
{
private:
	unordered_map<treeNode*, treeNode*>parents;
	treeNode* head;
	void setParents(treeNode* h,treeNode* parent)
	{
		parents[h] = parent;
		if (h->left)
			setParents(h->left,h);
		if (h->right)
			setParents(h->right,h);
	}
public:
	Record1(treeNode* h)
	{
		head = h;
		setParents(h,NULL);
	}
	treeNode* query(treeNode* o1, treeNode*o2)
	{
		unordered_set<treeNode*>ancestorsOfO1;
		treeNode* ancestor = o1;
		while (ancestor)
		{
			ancestorsOfO1.insert(ancestor);
			ancestor = parents[ancestor];
		}
		treeNode* ancestor2 = o2;
		while (ancestor2)
		{
			if (ancestorsOfO1.find(ancestor2) != ancestorsOfO1.end())
				return ancestor2;
			ancestor2 = parents[ancestor2];
		}
		return NULL;
	}
};
treeNode* getNodeVal(treeNode*head, int val)
{
	if (!head)return NULL;
	if (head->val == val)return head;
	auto l = getNodeVal(head->left,val);
	if (l)return l;
	auto r = getNodeVal(head->right, val);
	if (r)return r;
	return NULL;
}
class DisjointSets
{
private:
	unordered_map<treeNode*, treeNode*>fatherMap;
	unordered_map<treeNode*, int>rankMap;
	void preMakeSets(treeNode*head)
	{
		if (!head)return;
		fatherMap[head] = head;
		rankMap[head] = 0;
		preMakeSets(head->left);
		preMakeSets(head->right);
	}
public:
	
	void makeSets(treeNode*head)
	{
		fatherMap.clear();
		rankMap.clear();
		preMakeSets(head);
	}
	treeNode* findFather(treeNode* node)
	{
		auto father = fatherMap[node];
		if (father != node)
		{
			father = findFather(father);
		}
		fatherMap[node] = father;
		return father;
	}
	void unionSets(treeNode* a, treeNode* b)
	{
		if (!a || !b)
			return;
		auto aFather = fatherMap[a];
		auto bFather = fatherMap[b];
		if (aFather != bFather)
		{
			int aFrank = rankMap[aFather];
			int bFrank = rankMap[bFather];
			if (bFrank > aFrank)
			{
				fatherMap[aFather] = bFather;
			}
			else if (bFrank < aFrank)
			{
				fatherMap[bFather] = aFather;
			}
			else
			{
				fatherMap[bFather] = aFather;
				rankMap[aFather] = aFrank + 1;
			}
		}
	}
};
pair<int, int>maxDistanceAux(treeNode*head)
{
	//返回pair.first是以head为头的子树中相聚最远两点的距离，pair.second是该子树中距离head最远的点到head的距离
	if (!head)
		return{0,0};
	auto pl = maxDistanceAux(head->left);
	auto pr = maxDistanceAux(head->right);
	int crossDist = pl.second + 1 + pr.second;
	pair<int, int>res;
	res.first = max(max(pl.first,pr.first),crossDist);
	res.second = max(pl.second, pr.second) + 1;
	return res;
}
int maxDistance(treeNode*head)
{
	return maxDistanceAux(head).first;
}
treeNode* preInToTreeAux(const vector<int>& preArr, int pi, int pj, 
	const vector<int>& inArr, int ni, int nj,unordered_map<int,int>& valIndexMpIn)
{
	if (pi > pj || ni > nj)
		return NULL;
	int headVal = preArr[pi];//不是preArr[0]啊！！！！
	treeNode* head = new treeNode(headVal);
	int indexMid = valIndexMpIn[headVal];
	int lpi, lpj, rpi, rpj, lni, lnj, rni, rnj;
	int ll = indexMid - ni;
	int rl = nj - indexMid;
	lpi = pi + 1;
	lpj = pi + ll;
	rpi = lpj + 1;
	rpj = pj;
	lni = ni;
	lnj = indexMid - 1;
	rni = indexMid + 1;
	rnj = nj;
	head->left = preInToTreeAux(preArr, lpi, lpj, inArr, lni, lnj, valIndexMpIn);
	head->right = preInToTreeAux(preArr,rpi,rpj,inArr,rni,rnj,valIndexMpIn);
	return head;
}
treeNode* preInToTree(const vector<int>& preArr, const vector<int>& inArr)
{
	assert(preArr.size()==inArr.size());
	unordered_map<int, int>valIndexMpIn;
	for (size_t i = 0; i < inArr.size(); ++i)
	{
		valIndexMpIn[inArr[i]] = i;
	}
	return preInToTreeAux(preArr,0,preArr.size()-1,inArr,0,inArr.size()-1,valIndexMpIn);
}
void getPosAux(const vector<int>&preArr, int ai,int aj,const vector<int>&inArr,
	int bi, int bj, vector<int>&resPosArr, int ci, int cj, unordered_map<int, int>&valIndexMpIn)
{
	if (ai>aj || bi > bj || ci > cj)
		return;
	resPosArr[cj] = preArr[ai];
	int indexMid = valIndexMpIn[preArr[ai]];
	int ll = indexMid - bi;
	int lai = ai + 1;
	int laj = lai + ll - 1;
	int rai = laj + 1;
	int raj = aj;
	int lbi = bi;
	int lbj = indexMid - 1;
	int rbi = indexMid + 1;
	int rbj = bj;
	int lci = ci;
	int lcj = lci + ll - 1;
	int rci = lcj + 1;
	int rcj = cj - 1;
	getPosAux(preArr,lai,laj,inArr,lbi,lbj,resPosArr,lci,lcj,valIndexMpIn);
	getPosAux(preArr, rai, raj, inArr, rbi, rbj, resPosArr, rci, rcj, valIndexMpIn);
}
vector<int>getPos(const vector<int>&preArr, const vector<int>&inArr)
{
	assert(preArr.size()==inArr.size());
	vector<int>resPosArr(inArr.size());
	unordered_map<int, int>valIndexMpIn;
	for (size_t i = 0; i < inArr.size(); ++i)
	{
		valIndexMpIn[inArr[i]] = i;
	}
	if (inArr.size() == 0)
		return resPosArr;
	getPosAux(preArr,0,preArr.size()-1,inArr,0,inArr.size()-1,resPosArr,0,resPosArr.size()-1,valIndexMpIn);
	return resPosArr;
}
treeNode* cloneTree(treeNode* head)
{
	if (!head)return NULL;
	treeNode* res = new treeNode(head->val);
	res->left = cloneTree(head->left);
	res->right = cloneTree(head->right);
	return res;
}
list<treeNode*>genTreeAux(int start, int end)
{
	list<treeNode*>res;
	if (start > end)
	{
		res.push_back(NULL);
		return res;
	}
	for (int i = start; i <= end; ++i)
	{
		auto leftTrees = genTreeAux(start,i-1);
		auto rightTrees = genTreeAux(i + 1, end); 
		for (auto leftTree : leftTrees)
		{
			for (auto rightTree : rightTrees)
			{
				treeNode* head = new treeNode(i);
				head->left = cloneTree(leftTree);
				head->right = cloneTree(rightTree);
				res.push_back(head);
			}
		}
	}
	return res;
}

list<treeNode*>generateTrees(int n)
{
	return genTreeAux(1,n);
}
int getLeftHeight(treeNode* node)
{
	int h = 0;
	auto cur = node;
	while (cur)
	{
		++h;
		cur = cur->left;
	}
	return h;
}
int nodeNum1(treeNode* head)
{
	if (!head)
		return 0;
	int lh = getLeftHeight(head->left);
	int rh = getLeftHeight(head->right);
	if (rh == lh)
	{
		return (int)(pow(2, lh) + nodeNum1(head->right));
	}
	else
	{
		//rh==lh-1
		return (int)(pow(2, rh) + nodeNum1(head->left));
	}
}
/*
void main()
{
	vector<int>arr = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	auto root = genCompleteBinaryTree(arr);
	
	auto head = reconByLevelString("1!2!3!4!5!6!7!#!#!#!#!#!#!8!#!#!#!");
	//auto head2 = reconByLevelString("2!4!5!#!8!#!#!#!#!");
	//auto head3 = reconByLevelString("2!4!5!#!8!9!#!#!#!#!#!");
	//printTree(head);
	//Record1 r(head);
	//cout << "ancestor:" << r.query(getNodeVal(head,5),getNodeVal(head,2))->val<<endl;
	cout << nodeNum1(root) << endl;
	int itrpt = 0;
}
*/