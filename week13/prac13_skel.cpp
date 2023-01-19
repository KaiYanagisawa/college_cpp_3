// ヒープソート実装のプログラム
#include <iostream>
#include <fstream>

// 関数プロトタイプ宣言
void downheap(int a[], int left, int right);
void swap(int &a, int &b);

// ヒープソートで配列aをソートする関数
void heap_sort(int a[], int n)
{
    // (i) 配列 a をヒープ化
    // (1) 処理を完成させる
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        downheap(a, i, n - 1);
    }

    // (ii) ヒープ再構築を用いたソート
    // (2) 処理を完成させる
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        downheap(a, 0, n - 1);
    }
}

// downheap処理: a[left] から a[right] をヒープ化させる
void downheap(int a[], int left, int right)
{
    // a[left]を下流の適切な位置まで下ろし, 葉に達するとループを抜ける
    int parent{left};
    int child{};
    while (parent < (right + 1) / 2)
    {
        // 左子の添字
        int cl = parent * 2 + 1; // (3) 完成させる
        // 右子の添字
        int cr = parent * 2 + 2; // (4) 完成させる

        // 右子があるか確認しつつ, 大きい方の子の添え字をchildへセットする
        // (5) 処理を完成させる
        if (cr <= right && a[cr] > a[cl])
        {
            child = cr;
        }
        else
        {
            child = cl;
        }

        // 子が親以下の値であればループを抜ける
        // (6) 処理を完成させる
        if (a[child] <= a[parent])
            break;

        // 大きい方の子と親の値を交換し, 下流に移る
        // (7) 処理を完成させる
        swap(a[parent], a[child]);
        parent = child;
    }
}

// 配列の内容の表示させる関数
void print_array(int a[], int n)
{
    for (int i{}; i < n; i++)
    {
        if (i != n - 1)
        {
            std::cout << a[i] << ",";
        }
        else
        {
            std::cout << a[i];
        }
    }
    std::cout << "\n";
}

// 2つのint型の変数の入れ替えを行う関数
void swap(int &a, int &b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    // ファイル読み込み : data13.csvはCoursePower上で配布
    std::ifstream fin("data13.csv");
    // エラーチェック
    if (!fin)
        std::cerr << "cannot open file"
                  << "\n";

    // データファイルを空読みしデータ要素数sizeを取得する
    int size{};
    std::string st;
    while (std::getline(fin, st, ','))
        size++;

    // ファイルポインタを初期位置に戻す
    fin.clear();
    fin.seekg(0, fin.beg);

    // 配列の動的確保
    int *array = new int[size];
    int i{};
    while (std::getline(fin, st, ','))
    {
        array[i] = std::stoi(st);
        i++;
    }

    // ソート前の結果を表示
    std::cout << "array before sorting\n";
    print_array(array, size);

    // ヒープソートを実行
    heap_sort(array, size);

    // ソート後の結果を表示
    std::cout << "array after sorting\n";
    print_array(array, size);

    return 0;
}
