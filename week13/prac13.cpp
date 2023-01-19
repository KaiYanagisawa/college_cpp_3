// ヒープソート実装のプログラム: 解答例
#include <iostream>
#include <fstream>

// 関数プロトタイプ宣言
void downheap(int a[], int left, int right);
void swap(int &a, int &b);

// ヒープソートで配列aをソートする関数
void heap_sort(int a[], int n)
{
    // (i) 配列 a をヒープ化
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        // a[i] から a[n-1]をヒープ化
        downheap(a, i, n - 1);
    }

    // (ii) ヒープ再構築を用いたソート
    for (int i = n - 1; i > 0; i--)
    {
        // a[0] と a[i] の値を交換
        swap(a[0], a[i]);
        // a[0] から a[i-1]をヒープ化
        downheap(a, 0, i - 1);
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
        int cl = parent * 2 + 1;
        // 右子の添字
        int cr = parent * 2 + 2;

        // 右子があるか確認しつつ, 大きい方の子の添え字をchildへセットする
        if (cr <= right && a[cr] > a[cl])
        {
            child = cr;
        }
        else
        {
            child = cl;
        }

        // 子が親以下の値であればループを抜ける
        if (a[parent] >= a[child])
            break;

        // 大きい方の子と親の値を交換し, 下流に移る
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
