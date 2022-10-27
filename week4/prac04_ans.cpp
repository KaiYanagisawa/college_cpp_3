#include <iostream>
using namespace std;

class Node {
    int value; Node* nextp;
public:
    Node(int a, Node* p = nullptr) :value{ a }, nextp{ p } {}
    int getData() const { return value; }
    Node* getNext() const { return nextp; }
    void setNext(Node* pNext) { nextp = pNext; }
};

class Stack {
    Node* ptr{ nullptr }; // スタックトップ（単方向リストの先頭）
public:
    ~Stack() { while (!empty()) pop(); }    // デストラクタ
    void push(int);                       // 値xを持つノードをスタックトップに追加
    void pop();                             // スタックトップのノードを削除する
    int top() const;                        // スタックトップのノードの値を返す
    bool empty() const { return ptr == nullptr; }   // スタックが空かの判定
    size_t size() const;                       // スタックの要素数を返す
};

// 値xを持つノードをスタックトップに追加する
void Stack::push(int v) {
    ptr = new Node(v, ptr);
}

// スタックトップのノードの値を返す
int Stack::top() const {
    return ptr->getData(); // C++II第14回（valueはprivateなのでptr->valueはできない）
}

// スタックトップのノードを削除し，スタックトップのnextをスタックトップにする
void Stack::pop() {
    auto tmp{ ptr };
    ptr = ptr->getNext(); // C++II第14回（nextpはprivateなのでptr->nextpはできない）
    delete tmp;
}

// スタックの要素数を返す
size_t Stack::size() const {
    size_t count{ 0 };              // 要素数をカウント
    auto node = ptr;          // 最初はスタックトップのノードを指すようにする
    while (node!=nullptr) {   // nodeがnullptrでないかぎり
        count++;                    // ノードをカウントして
        node = node->getNext(); // 次のノードをnodeが指すようにする
    }
    return count;
}

// 先に取り出したほうをbに，後に取り出したほうをaに詰める
void get2numberfromstack(Stack& st, int& a, int& b) {
    if (st.empty()) {
        cerr << "エラー：スタックにデータがない" << "\n";
        exit(EXIT_FAILURE);
    }
    b = st.top();
    st.pop();
    if (st.empty()) {
        cerr << "エラー：スタックにデータがない" << "\n";
        exit(EXIT_FAILURE);
    }
    a = st.top();
    st.pop();
}


int main() {
    Stack st;  // 空のスタックを作る
    string input[200];
    size_t count{ 0 };
    int number, a, b;
    cout << "数式--> ";
    while (cin >> input[count]) {
        if (input[count] == "$") break;
        count++;
    }
    for (size_t i{ 0 }; i < count; i++) {
        if (input[i] == "+") {
            get2numberfromstack(st, a, b);
            st.push(a + b);
        }
        else if (input[i] == "-") {
            get2numberfromstack(st, a, b);
            st.push(a - b);
        }
        else if (input[i] == "*") {
            get2numberfromstack(st, a, b);
            st.push(a * b);
        }
        else if (input[i] == "/") {
            get2numberfromstack(st, a, b);
            st.push(a / b);
        }
        else {
            number = atof(input[i].c_str());
            st.push(number);
        }
    }
    if (st.size() != 1) {
        cerr << "エラー：スタックにデータが2つ以上ある，もしくは全くない" << "\n";
        exit(EXIT_FAILURE);
    }
    a = st.top();
    cout << a << "\n";
    return 0;
}

/*
g++ prac04_ans.cpp -o prac04
echo "12 3 2 * / $" | ./prac04
数式--> 2
echo "100 30 12 + 2 * - 5 4 * + 2 / $" | ./prac04
数式--> 18
echo "50 10 - 20 - $" | ./prac04
数式--> 20
echo "50 10 20 - - $" | ./prac04
数式--> 60
*/