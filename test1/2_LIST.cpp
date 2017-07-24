#include "moststd.h"
using namespace std;
//enjoy your talents

//chap1
struct node
{
	int val;
	node* left=NULL;
	node* right=NULL;
	node() = default;
	node(int v) :val(v){}
};
void popStackSetMap(stack<node*>&stk, map<node*, node*>&mp)
{
	node* top = stk.top();
	stk.pop();
	if (stk.empty())mp[top] = NULL;
	else mp[top] = stk.top();
	
}
node* getMaxTree(const vector<int>&arr)
{
	vector<node*>nodes;
	for (auto a : arr)
		nodes.push_back(new node(a));
	map<node*, node*>lbigMp, rbigMp;
	stack<node*>stk1;
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		while (!stk1.empty() && stk1.top()->val < nodes[i]->val)
		{
			popStackSetMap(stk1,lbigMp);
		}
		stk1.push(nodes[i]);
	}
	while (!stk1.empty())
		popStackSetMap(stk1,lbigMp);

	for (int i = nodes.size()-1; i >= 0; --i)
	{
		while (!stk1.empty() && stk1.top()->val < nodes[i]->val)
		{
			popStackSetMap(stk1, rbigMp);
		}
		stk1.push(nodes[i]);
	}
	while (!stk1.empty())
		popStackSetMap(stk1, rbigMp);
	
	node* left, *right, *head=NULL;
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		left = lbigMp[nodes[i]];
		right = rbigMp[nodes[i]];
		if (left == NULL&&right == NULL)
		{
			head = nodes[i];
		}
		else if (left == NULL)
		{
			if (right->left == NULL)right->left = nodes[i];
			else right->right = nodes[i];
		}
		else if (right == NULL)
		{
			if (left->left == NULL)left->left = nodes[i];
			else left->right = nodes[i];
		}
		else
		{
			node* parent = (left->val<right->val?left:right);
			if (parent->left == NULL)parent->left = nodes[i];
			else parent->right = nodes[i];
		}
	}
	return head;
}
//P21
vector<int> getMaxWindow(const vector<int>&arr, int w)
{
	assert(arr.size()>=w);
	deque<int>maxIndexDq;
	vector<int>res;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		while (!maxIndexDq.empty() && arr[i] > arr[maxIndexDq.back()])//not arr[i]>maxIndexDq.back()
		{
			maxIndexDq.pop_back();
		}
		maxIndexDq.push_back(i);
		if (i >= w - 1)
		{
			while (i - maxIndexDq.front() >= w)
			{
				maxIndexDq.pop_front();
			}
			res.push_back(arr[maxIndexDq.front()]);//not res.push_back(maxIndexDq.front())
		}
	}
	return res;
}
int maxRecFromBottom(const vector<int>&heights)
{
	stack<int>stk;
	int maxRecSize = 0;
	for (size_t i = 0; i < heights.size(); ++i)
	{
		while (!stk.empty() && heights[i] <= heights[stk.top()])
		{
			int top = stk.top();
			stk.pop();
			int lindex = (stk.empty() ? 0 : stk.top() + 1);
			int rindex = (heights[i] < heights[top] ? i - 1:i);
			maxRecSize = max(maxRecSize,(rindex-lindex+1)*heights[top]);
		}
		stk.push(i);
	}
	if (stk.empty())return maxRecSize;
	int rindex = heights.size()-1;
	while (!stk.empty())
	{
		int top = stk.top();
		stk.pop();
		int lindex = (stk.empty() ? 0 : stk.top() + 1);
		maxRecSize = max(maxRecSize, (rindex - lindex + 1)*heights[top]);
	}
	return maxRecSize;
}
int maxRecSize(const vector<vector<int>>&mat)
{
	assert(mat.size()>0);
	int n = mat.size();
	int m = mat[0].size();
	vector<int>heights(m,0);
	int maxRecArea = 0;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			if (mat[i][j] == 0)heights[j] = 0;
			else ++heights[j];
		}
		maxRecArea = max(maxRecArea,maxRecFromBottom(heights));
	}
	return maxRecArea;
}

//chap2链表
struct listNode
{
	int val;
	listNode* next;
	listNode(int v) :val(v), next(NULL){}
};
listNode* genList(vector<int>&arr)
{
	if (arr.empty())return NULL;
	listNode* cur, *pre, *head;
	head = (listNode*)malloc(sizeof(listNode));
	head->val = arr[0];
	head->next = NULL;
	pre = head;
	for (int i = 1; i < (int)arr.size(); ++i)
	{
		cur = (listNode*)malloc(sizeof(listNode));
		cur->val = arr[i];
		cur->next = NULL;
		pre->next = cur;
		pre = cur;
	}
	return head;
}
void printList(listNode*lstHead)
{
	while (lstHead != NULL)
	{
		cout << lstHead->val << " ";
		lstHead = lstHead->next;
	}
	cout << endl;
}
//P36,37
listNode* removeLastKthNode(listNode* head,int lastKth)
{
	if (!head || lastKth < 1)return head;
	int cnt = lastKth;
	listNode* cur = head,*pre=NULL;
	while (cur)
	{
		--cnt;
		pre = cur;
		cur = cur->next;
	}
	
	if (cnt > 0)return head;
	if (cnt == 0)return head->next;
	cur = head;
	while (cur)
	{
		++cnt;
		if (cnt == 0)break;
		cur = cur->next;
	}
	cur->next = cur->next->next;
	return head;

}
//P41
listNode* reverseList(listNode* node)
{
	listNode* pre = NULL, *cur = node, *next;
	while (cur)//注意不是while(cur->next)!!!!!!!!!!
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}
 
pair<listNode*, listNode*> reverseList2(listNode* node)
{
	//返回翻转后的<头，尾>
	listNode* pre = NULL, *cur = node, *next;
	while (cur)//注意不是while(cur->next)!!!!!!!!!!
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return{ pre, node };
}
listNode* reverseListPart2(listNode* node, int from, int to)
{
	int len = 0;
	listNode* fpre=NULL, *tpos=NULL,*t=NULL,*cur = node;
	while (cur)
	{
		++len;
		if (len == from - 1)fpre = cur;
		if (len == to + 1)tpos = cur;
		if (len == to)t = cur;
		cur = cur->next;
	}
	if (from<1 || len<to || from > to)return node;
	if (t)t->next = NULL;
	listNode* f = (fpre?fpre->next:node);
	auto p = reverseList2(f);
	if (fpre)
	{
		//node不在[from,to]内，不用换头
		fpre->next = p.first;
		p.second->next = tpos;
		return node;
	}
	else
	{
		//头结点在[from,to]内，需要换头
		p.second->next = tpos;
		return p.first;
	}
}
//P44
pair<listNode*,listNode*> removeKthEle(listNode* head, listNode*posHead, int k)
{
	//删除从head开始第k个元素，并返回<被删除元素的上一个,被删除元素的下一个>
	//k>=1,且head->next!=head
	
	listNode* cur=NULL, *pre=NULL;
	int cnt = 1;
	cur = posHead;
	while (cnt <= k)
	{
		pre = cur;
		cur = cur->next;
		cnt = cnt + 1;
	}
	pre->next = cur->next;
	return{pre,pre->next};
}
listNode* josephusKill(listNode* head, int m)
{
	if (m < 1 || !head || head->next == head)return head;
	listNode* last = head;
	while (last->next!=head)
	{
		last = last->next;
	}
	auto p = removeKthEle(head,last,m);
	while (p.first != p.second)
	{
		p = removeKthEle(p.second,p.first,m);
	}
	return p.second;
}
listNode* genCircularList(vector<int>&arr)
{
	if (arr.empty())return NULL;
	listNode* cur, *pre, *head;
	head = (listNode*)malloc(sizeof(listNode));
	head->val = arr[0];
	head->next = NULL;
	pre = head;
	for (int i = 1; i < (int)arr.size(); ++i)
	{
		cur = (listNode*)malloc(sizeof(listNode));
		cur->val = arr[i];
		cur->next = NULL;
		pre->next = cur;
		pre = cur;
	}
	pre->next = head;
	return head;
}
listNode* getListMid(listNode*head)
{
	if (!head || !head->next||!head->next->next)return head;
	listNode* slow = head->next, *fast = head->next->next;
	while (fast->next&&fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
listNode* getListMid2(listNode*head)
{
	if (!head || !head->next || !head->next->next)return head;
	listNode* slow = head, *fast = head->next;
	while (fast->next&&fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
//P50
bool isListPalindrome2(listNode* head)
{
	if (!head || !head->next)return true;
	listNode* right = getListMid(head)->next;
	stack<int>stk;
	while (right)
	{
		stk.push(right->val);
		right = right->next;
	}
	listNode* cur = head;
	while (!stk.empty())
	{
		if (cur->val != stk.top())return false;
		stk.pop();
		cur = cur->next;
	}
	return true;
}
bool isListPalindrome3(listNode* head)
{
	//O(1)空间
	if (!head || !head->next)return true;
	listNode* mid = getListMid(head);
	listNode* right = mid->next;
	mid->next = NULL;
	listNode* rightStart = reverseList(right);
	listNode* r = rightStart, *l = head;
	while (r&&l)
	{
		if (r->val != l->val)
		{
			
			mid->next = reverseList(rightStart);//先恢复链表原状
			return false;
		}
		r = r->next;
		l = l->next;
	}
	mid->next = reverseList(rightStart);//先恢复链表原状
	return true;

}
//P55
listNode* listPartition2(listNode* head, int pivot)
{
	listNode* sh = NULL, *st = NULL, *eh = NULL, *et = NULL, *bh = NULL, *bt = NULL;
	while (head)
	{
		listNode* next = head->next;
		head->next = NULL;//一定先把当前节点从链表中拿出来
		if (head->val < pivot)
		{
			if (!sh)
			{
				sh = head;
				st = sh;
			}
			else
			{
				st->next = head;
				st = head;
			}
		}
		else if (head->val == pivot)
		{
			if (!eh)
			{
				eh = head;
				et = eh;
			}
			else
			{
				et->next = head;
				et = head;
			}
		}
		else
		{
			if (!bh)
			{
				bh = head;
				bt = bh;
			}
			else
			{
				bt->next = head;
				bt = head;
			}
		}
		head = next;
	}

	//处理st,et的连接问题
	if (st)
	{
		if (eh)st->next = eh;
		else st->next = bh;
	}
	if (et)
	{
		et->next = bh;
	}

	//根据sh,eh返回
	if (sh)return sh;
	if (eh)return eh;
	return bh;
}
//P60
listNode* addLists1(listNode* head1,listNode*head2)
{
	stack<int>stk1, stk2;
	listNode* cur1 = head1, *cur2 = head2;
	while (cur1)
	{
		stk1.push(cur1->val);
		cur1 = cur1->next;
	}
	while (cur2)
	{
		stk2.push(cur2->val);
		cur2 = cur2->next;
	}
	int carry = 0;
	listNode* res = NULL, *pre = NULL;
	while (!stk1.empty() || !stk2.empty())
	{
		int v1 = 0, v2 = 0;
		if (!stk1.empty())
		{
			v1 = stk1.top();
			stk1.pop();
		}
		if (!stk2.empty())
		{
			v2 = stk2.top();
			stk2.pop();
		}
		int cv = v1 + v2 + carry;
		carry = (cv>=10?1:0);//carry=cv/10;
		int val = (cv>=10?cv-10:cv);//val=cv%10;
		auto cur = new listNode(val);
		cur->next = pre;
		pre = cur;
	}
	if (carry == 1)
	{
		auto cur = new listNode(carry);
		cur->next = pre;
		res = cur;
	}
	else res = pre;
	return res;

}
//P70
listNode* reverseKNodes2(listNode* head,int k)
{
	listNode* res = NULL, *cur = head;
	int cnt = 0;
	listNode* khead = NULL, *prekhead = NULL;
	while (cur)
	{
		++cnt;
		auto next = cur->next;
		if (cnt == 1)khead = cur;
		if (cnt == k)
		{
			cnt = 0;
			cur->next = NULL;
			auto p = reverseList2(khead);
			if (prekhead)
			{
				prekhead->next = p.first;
				prekhead = p.second;
			}
			else
			{
				res = p.first;
				prekhead = p.second;
			}
		}
		cur = next;
	}
	if (cnt != 0)
	{
		if (prekhead)
		{
			prekhead->next = khead;
		}
		else
		{
			res = khead;
		}
	}
	return res;
}
//P72
void removeRep2(listNode* head)
{
	listNode* cur = head;
	while (cur)
	{
		int curVal = cur->val;
		auto next = cur->next;
		auto pre = cur;
		while (next)
		{
			if (next->val != curVal)
			{
				pre = next;
				next = next->next;
			}
			else
			{
				pre->next = next->next;
				next = next->next;
			}
		}
		cur = cur->next;
	}
}
//P80
listNode* getSmallestPreNode(listNode*head)
{
	int min = INT_MAX;
	listNode*res = NULL, *cur = head, *pre = NULL;
	while (cur)
	{
		if (cur->val < min)
		{
			min = cur->val;
			res = pre;
		}
		pre = cur;
		cur = cur->next;
	}
	return res;
}
listNode* listSelectionSort(listNode*head)
{
	listNode* newNode = NULL, *smallest, *newHead = NULL;
	while (head)
	{
		auto preSmallest = getSmallestPreNode(head);
		if (preSmallest)
		{
			smallest = preSmallest->next;
			preSmallest->next = smallest->next;
			
		}
		else
		{
			smallest = head;
			head = head->next;
		}
		//smallest->next = NULL;//把这个点拿下来的时候注意next赋NULL,如果仅仅是删除该点可以不用这句，当我们只是把它从链表中切割下来，还要拿来用呢
		if (newNode)
		{ 
			newNode->next = smallest; 
			newNode = smallest;//注意加上新的点后该位置也要后移！！
		}
		else
		{
			newHead = smallest;
			newNode = newHead;
		}
	}
	return newHead;
}
//P85
listNode* mergeTwoSortedLists(listNode* head1,listNode* head2)
{
	if (!head1 || !head2)
	{
		return head1 ? head1 : head2;
	}
	listNode* newNode = NULL, *newHead = NULL;

	while (head1&&head2)
	{
		if (head1->val < head2->val)
		{
			if (!newHead)
			{
				newHead = head1;
			}
			else
			{
				newNode->next = head1;
			}
			newNode = head1;
			head1 = head1->next;
			//newNode->next = NULL;
			
		}
		else
		{
			if (!newHead)
			{
				newHead = head2;
			}
			else
			{
				newNode->next = head2;
			}
			newNode = head2;
			head2 = head2->next;
			//newNode->next = NULL;
			
		}
	}
	newNode->next = (head1?head1:head2);
	return newHead;
}
void mergeLR(listNode* left, listNode*right)
{
	auto cur = left;
	listNode* pre=cur;
	while (cur)
	{
		auto next = cur->next;
		cur->next = right;
		right = right->next;
		cur->next->next = next;
		pre = cur->next;//不是pre=cur
		cur = next;
	}
	if (right)pre->next = right;
}
void relocate(listNode* head)
{
	if (!head || !head->next || !head->next->next)return;
	auto mid = getListMid2(head);
	auto right = mid->next;
	mid->next = NULL;
	mergeLR(head,right);
}
/*
void main()
{
	vector<int>arr1 = {1,2,3,4,5,6};
	auto head1 = genList(arr1);
	vector<int>arr2 = {1,3,5,7,9};
	auto head2 = genList(arr2);
	
	relocate(head1);
	printList(head1);
	int itrpt = 0;
}
*/