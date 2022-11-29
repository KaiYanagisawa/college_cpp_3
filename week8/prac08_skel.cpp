#include <iostream>
using namespace std;

class BinTree
{
private:
    class Node
    { // 内部クラス
    public:
        string data; // ノードの値(単語の名前)
        int count;   // 単語の出現回数
        Node *left;  // 左のnextを指すポインタ
        Node *right; // 右のnextを指すポインタ
        Node(string a = "", int d = 1, Node *b = NULL, Node *c = NULL)
        { // コンストラクタ
            data = a;
            count = d;
            left = b;
            right = c;
        }
        ~Node() { cout << data << " is released.\n"; }             // デストラクタ
        void printNode() { cout << data << "[" << count << "] "; } // データの出力
    };
    Node *root;                          // 二分木の一番上のノードを指すポインタ
    void traverse(Node *rp);             // 二分木rpを出力
    Node *addNode(Node *rp, Node *node); // 二分木rpにnodeを追加
    Node *delNode(Node *rp, int x);      // 二分木rpから出現回数がxの単語を全て削除
    // void clearNode(Node *rp);            // 二分木rp以降を削除
public:
    BinTree() { root = NULL; }   // 引数なしコンストラクタ
    BinTree(string *, string *); // 引数ありコンストラクタ
    // ~BinTree() { clear(); }              // デストラクタ
    void printTree() { traverse(root); } // 二分木全体をアルファベット順に表示
    void insert(string x)
    {                             // 二分木にデータxを追加
        Node *np = new Node(x);   // データxを持つノードを作成
        root = addNode(root, np); // 二分木rootにノードを追加
    }
    void remove(int x) { root = delNode(root, x); } // 二分木から出現回数がxの単語を全て削除
    // void clear()
    // {
    //     clearNode(root);
    //     root = NULL;
    // } // 二分木から全データを削除
};

BinTree::BinTree(string *begin, string *end)
{
    root = NULL;
    for (string *p = begin; p != end; p++)
    {
        insert(*p);
    }
}

void BinTree::traverse(Node *rp)
{
    if (rp == NULL)
    {
        return;
    }
    else
    {
        traverse(rp->left);
        cout << rp->data << "[" << rp->count << "] ";
        traverse(rp->right);
    }
}

BinTree::Node *BinTree::addNode(Node *rp, Node *node)
{
    if (rp == NULL)
    {
        return node;
    }
    else if (node == NULL)
    {
        return rp;
    }
    else
    {
        if (node->data < rp->data)
        {
            rp->left = addNode(rp->left, node);
        }
        else if (node->data == rp->data)
        {
            rp->count++;
            delete node;
        }
        else
        {
            rp->right = addNode(rp->right, node);
        }
        return rp;
    }
}

BinTree::Node *BinTree::delNode(Node *rp, int x)
{
    if (rp == NULL)
    {
        return NULL;
    }
    else if (x == rp->count)
    {
        Node *lf = rp->left;
        Node *rt = rp->right;
        delete rp;
        rp->left = delNode(rp->left, x);
        rp->right = delNode(rp->right, x);
        return addNode(rt, lf);
    }
    else
    {
        rp->left = delNode(rp->left, x);
        rp->right = delNode(rp->right, x);
        return rp;
    }
}

int main(int argc, char *argv[])
{
    string a[] = {"apple", "apple", "banana", "peach", "banana", "peach", "banana", "peach", "melon", "melon", "lemon", "orange", "watermelon"};
    string newword;        // リストに追加する単語
    int n;                 // 頻度がnの場合削除する
    char select;           // select:メニュー項目の文字
    BinTree bt(a, a + 13); // 配列aと同じ要素を持つリストを作る
    // メニューを表示して対応する処理を行う
    cout << "\nMenu[I:Insert, R:Remove, P:Print, Q:Quit]";
    while ((cout << "\n  Select I/R/S/P/C/Q-->") && (cin >> select))
    {
        switch (select)
        {
        case 'I': // リストへ新規ノードの追加
        case 'i':
            cout << "Input a data-->";
            cin >> newword;
            bt.insert(newword);
            break;
        case 'R': // リストから指定ノードを削除
        case 'r':
            cout << "Remove a data-->";
            cin >> n;
            bt.remove(n);
            break;
        case 'P':
            bt.printTree();
            cout << "\n";
            break; // リストの全データを表示
        case 'Q':  // プログラムを終了
        case 'q':
            break;
        default:
            continue;
        }
        if ((select == 'Q') || (select == 'q'))
        {
            break;
        }
    }
    return 0;
}
