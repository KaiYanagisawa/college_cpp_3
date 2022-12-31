#include <iostream>
#include <fstream>

// 配列の内容を表示する
void print_array(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			std::cout << a[i];
		}
		else
		{
			std::cout << "," << a[i];
		}
	}
	std::cout << "\n";
}

// クイックソート
void quick_sort(int a[], int left, int right)
{
	if (left == right)
	{ // 要素が１つのときはなにもしない
		return;
	}
	else
	{

		int idx1{left};					// 左カーソル
		int idx2{right};				// 右カーソル
		int pvt = a[(idx1 + idx2) / 2]; // ピボットの設定
		// std::cout << "pvt=" << pvt << std::endl; /*debug*/

		// 左右の検索位置が逆転するまで繰り返す
		do
		{
			/*
			  空欄(3) ピボット以上の要素が見つかるまでidx1をずらす．
			*/
			while (a[idx1] < pvt)
			{
				idx1++;
			}
			// std::cout << "idx1=" << a[idx1] << std::endl; /*debug*/

			/*
			  空欄(4) ピボット以下の要素が見つかるまでidx2をずらす．
			*/
			while (a[idx2] > pvt)
			{
				idx2--;
			}
			// std::cout << "idx2=" << a[idx2] << std::endl; /*debug*/

			/*
			  空欄(5) idx1とidx2が指す要素を入れ替え
			*/
			if (idx1 < idx2)
			{
				int tmp{a[idx1]};
				a[idx1] = a[idx2];
				a[idx2] = tmp;
			}
			if (idx1 <= idx2)
			{
				idx1++;
				idx2--;
			}

			// print_array(a, right + 1); /*debug*/
		} while (idx1 <= idx2);

		// std::cout <<"(a[idx1], a[idx2]=("<< a[idx1] << ", " << a[idx2] <<")"<< std::endl; /*debug*/

		if (left < idx2)
		{ // ピボット以下グループが空で無ければ
			/*
			  空欄(6) ピボット以下グループでクイックソート
			*/
			quick_sort(a, left, idx2);
		}

		if (right > idx1)
		{ // ピボット以上グループが空で無ければ
			/*
			  空欄(7) ピボット以上グループでクイックソート
			*/
			quick_sort(a, idx1, right);
		}
	}
}

int main()
{
	int size{0}; // 要素数を格納する
	int *array;	 // ファイルから読み込んだ配列を格納

	// ファイル読み込み
	std::ifstream fin("./quick.csv");
	if (!fin)
	{
		std::cerr << "Can't open file\n";
		return 1;
	}

	// 空読みによる要素数の取得
	std::string tmp;
	while (std::getline(fin, tmp, ','))
		size++;

	// EOFに達するとファイル位置移動関数が無効になるので，EOFフラグをリセット
	fin.clear();
	fin.seekg(0, fin.beg); // ファイルポインタを初期位置に戻す

	// 配列の動的確保
	array = new int[size];
	for (int i{0}; std::getline(fin, tmp, ','); i++)
		array[i] = std::stoi(tmp);

	// ソート前の結果表示
	std::cout << "-before sort-\n";
	print_array(array, size);

	// クイックソート
	quick_sort(array, 0, size - 1);

	// 結果を表示
	std::cout << "-after quick sort-\n";
	print_array(array, size);

	return 0;
}
