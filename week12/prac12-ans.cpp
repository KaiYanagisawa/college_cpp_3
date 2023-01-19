// マージソート
#include <iostream>
#include <fstream>
#include <sstream>

//2つの部分列をマージする
void merge(int a[],int left,int centerL,int centerR,int right)
{
	// 配列a[left]からa[centerL]まで(前半部)を動的に確保した配列buf1に格納
	int *buf1 = new int[centerL-left+1];
	for(int i{0}, j{left}; j <= centerL; i++, j++)
		buf1[i] = a[j];
	
	// 配列a[centerR]からa[right]までを動的に確保した配列buf2に格納
	int *buf2 = new int[right-centerR+1];
	for(int i{0}, j{centerR}; j <= right; i++, j++)
		buf2[i] = a[j];
	
	
	// b1: 配列 buf1の添字, b2: 配列 buf2の添字, p: 配列 aの添字
	int b1{0}, b2{0}, p{left};
	
	// ここからbuf1とbuf2をマージしていく（結果は配列 a に上書き）
	
	// buf1とbuf2どちらかが全走査されるまで小さい順に値を格納していく
	while( (b1 <= centerL-left) && (b2 <= right-centerR) )
	{
		if(buf1[b1] <= buf2[b2]){
			a[p++] = buf1[b1++];
		}else{
			a[p++] = buf2[b2++];
		}
	}

	// buf1 が全走査されていない場合の処理
	while(b1<=centerL-left){
		a[p++] = buf1[b1++];
	}

	// buf2 が全走査されていない場合の処理
	while(b2<=right-centerR){
		a[p++] = buf2[b2++];
	}

	delete[] buf1, buf2;
}

// マージソート
void merge_sort(int a[], int left, int right)
{
	if(left < right){
		int center = (left + right) / 2;

		// 前半部をマージソート
		merge_sort(a, left, center);

		// 後半部をマージソート
		merge_sort(a, center+1, right);

		// 配列aの前半部と後半部をマージ
		merge(a,left,center,center+1,right);
	}
}

// 配列の内容を表示する
void print_array(int a[], int n)
{
	for(int i = 0; i < n; i++){
		if(i == 0){
			std::cout << a[i];
		}else{
			std::cout << "," << a[i];
		}
	}
	std::cout << "\n";
} 

int main()
{
	int size{}; // 要素数を格納する
	int* array;   // ファイルから読み込んだ配列を格納

	// ファイル読み込み
	std::ifstream fin("./marge.csv");
	if (!fin) {
		std::cerr << "Can't open file\n";
		return 1;
	}

	// 空読みによる要素数の取得
	std::string tmp;
	while (std::getline(fin, tmp, ','))  size++;
	
	//EOFに達するとファイル位置移動関数が無効になるので，EOFフラグをリセット
	fin.clear();
	fin.seekg(0, fin.beg);

	// 配列の動的確保
	array  = new int[size];
	for(int i{0}; std::getline(fin, tmp, ','); i++)
		array[i] = std::stoi(tmp);
	
	// ソート前の結果表示
	std::cout << "-before sort-\n";
	print_array(array, size);

	// マージソートの実行
	merge_sort(array, 0, size-1);
	
	//結果を表示
	std::cout << "-after merge sort-\n";
	print_array(array, size);

}
