
#include <iostream>
using namespace std;

class SortedLinkedList
{
	class Node
	{ // privateなので，SortedLinkedListのメンバ関数以外からはアクセスできない
	public:
		int data;	// ノードの値
		Node *next; // 次のノードへのポインタ
		Node(int num = 0, Node *p = NULL)
		{
			data = num;
			next = p;
		}
		~Node() { cout << data << " is released" << endl; }
	};
	Node *head;
	void push(int x) { head = new Node(x, head); }
	void pop()
	{
		Node *node = head;
		head = head->next;
		delete node;
	}

public:
	SortedLinkedList() { head = NULL; } // 空リストの生成
	SortedLinkedList(int *, int *);		// int配列の内容でリストを初期化
	~SortedLinkedList() { clear(); }
	bool empty() const { return head == NULL; } // リストが空ならTrueを返す
	void clear()
	{
		while (head)
			pop();
	};					   // リストから全データを削除
	void printALL() const; // リストの全データを表示
	void insert(int n);	   // リストにデータnを追加
	void remove(int n);	   // リストからデータnを削除
	int size() const;	   // リストのデータ数を表示
};

// int配列の内容でリストを初期化
SortedLinkedList::SortedLinkedList(int *begin, int *end)
{
	head = NULL;
	for (int *p = begin; p != end; p++)
		insert(*p);
}

// リストの全データを表示
void SortedLinkedList::printALL() const
{
	for (Node *p = head; p; p = p->next)
		cout << p->data << "-->";
	cout << "END_OF_DATA" << endl;
}

// リストの要素数を返す
int SortedLinkedList::size() const
{
	int n = 0;
	for (Node *p = head; p; p = p->next)
		n++;
	return n;
}

// リストに要素nを昇順になるように挿入する
void SortedLinkedList::insert(int n)
{
	if (size() == 0)
	{
		cout << "size0";
		push(n);
	}
	else if (size() == 1)
	{
		head = new Node(n, head);
	}
	else
	{
		cout << head->data << " " << n << "\n";
		Node *node = head;
		for (Node *p = node; p; p = p->next)
		{
			head = new Node(n, p->next);
			if (n > p->data)
			{
				cout << "head" << p->data << "\n";
				break;
			}
		}
	}
}
// リストから値がnの要素の中で最も先頭にある要素を取り除く
void SortedLinkedList::remove(int n)
{
}

int main()
{
	int x[] = {0, 1, 2, 5, 3, 3, 5, 7, 8, 8};
	int n;
	char select;
	SortedLinkedList ichain(x, x + 10);
	cout << endl
		 << "Menu[I:Insert, R:Remove, S:Size, P:Print, C:Clear, Q:Quit]";
	while ((cout << endl
				 << "Select I/R/S/P/C/Q-->") &&
		   (cin >> select))
	{
		switch (select)
		{
		case 'I': // 新しいノードを追加
		case 'i':
			cout << "Input a data-->";
			cin >> n;
			ichain.insert(n);
			break;
		case 'R': // 指定したノードを削除
		case 'r':
			cout << "Input a data-->";
			cin >> n;
			ichain.remove(n);
			break;
		case 'S': // リストの要素数を表示
		case 's':
			cout << "Length=" << ichain.size() << endl;
			break;
		case 'P': // リストの全データを表示．iteratorという抽象化されたポインタでアクセスする
		case 'p':
			ichain.printALL();
			break;
			cout << "END_OF_DATA" << endl;
			break;
		case 'C': // リストの全データを削除
		case 'c':
			ichain.clear();
			break;
		case 'Q': // プログラムを終了
		case 'q':
			break;
		default:
			continue;
		}
		if ((select == 'Q') || (select == 'q'))
			break;
	}
	return 0;
}

/*
$ g++ prac06_skel.cpp -o prac06 && echo P S R 3 R 0 r 6 s p i 6 P r 8 r 8 p c s q | ./prac06

Menu[I:Insert, R:Remove, S:Size, P:Print, C:Clear, Q:Quit]
Select I/R/S/P/C/Q-->0-->1-->2-->3-->3-->5-->5-->7-->8-->8-->END_OF_DATA

Select I/R/S/P/C/Q-->Length=10

Select I/R/S/P/C/Q-->Input a data-->3 is released

Select I/R/S/P/C/Q-->Input a data-->0 is released

Select I/R/S/P/C/Q-->Input a data-->
Select I/R/S/P/C/Q-->Length=8

Select I/R/S/P/C/Q-->1-->2-->3-->5-->5-->7-->8-->8-->END_OF_DATA

Select I/R/S/P/C/Q-->Input a data-->
Select I/R/S/P/C/Q-->1-->2-->3-->5-->5-->6-->7-->8-->8-->END_OF_DATA

Select I/R/S/P/C/Q-->Input a data-->8 is released

Select I/R/S/P/C/Q-->Input a data-->8 is released

Select I/R/S/P/C/Q-->1-->2-->3-->5-->5-->6-->7-->END_OF_DATA

Select I/R/S/P/C/Q-->1 is released
2 is released
3 is released
5 is released
5 is released
6 is released
7 is released

Select I/R/S/P/C/Q-->Length=0
*/