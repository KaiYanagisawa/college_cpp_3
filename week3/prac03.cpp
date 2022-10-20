#include <iostream>
#include <fstream>
#include <cstdlib>
using std::cout, std::string, std::endl;

class Transp
{
    string name;          //行列の名前
    int size;             //行列の大きさ
    double **probability; //行列の値を格納する2次元配列のポインタ
public:
    Transp() { size = 0; } //コンストラクタ
    void checkprob()
    { //行列の行の数値の和が1になっているかチェックする関数
        double sum;
        if (size == 0)
        { // sizeが0のとき警告を出して止める
            std::cerr << "sizeが0" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            for (int i = 0; i < (size - 1); i++)
            { //最後の行は0が入っているためチェックしない(遷移行列であるため)
                sum = probability[i][0];
                for (int j = 1; j < size; j++)
                {
                    sum += probability[i][j];
                }
                if ((sum < (1 - 0.00001e-01)) || ((1 + 0.00001e-01) < sum))
                { //誤差を許容する
                    std::cerr << i + 1 << "行目の値が1でない" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cout << name << "の" << i + 1 << "行目は正常でした\n";
                }
            }
        }
    }
    friend void readtransitionmatrix(string, Transp[]);
};

//引数で指定されたファイルにある<TRANSP>の数をリターンする
int gettranskosuu(string filename)
{
    string line;
    std::ifstream fin(filename);
    if (!fin)
    { //エラー処理
        std::cerr << "エラー：ファイルを開けません" << filename << "\n";
        exit(EXIT_FAILURE);
    }
    int num{0};
    while (fin >> line)
    { //<TRANSP>の数を調べるために空読み
        if (line == "<TRANSP>")
        {
            num++;
        }
    }
    return num;
}
// ファイルの情報をメモリをとりながらtransmatrixに読み込む
/* ファイルの中身：<TRANSP> 行列サイズ 名前
① string lineは<TRANSP>の文字列のチェックおよび名前用
② int sizematrixは行列のサイズを保存
*/
void readtransitionmatrix(string filename, Transp transmatrix[])
{
    string line;    //ファイルからの読み込み用
    int sizematrix; //行列の大きさ

    std::ifstream fin(filename);
    if (!fin)
    { //エラー処理
        std::cerr << "エラー：ファイルを開けません" << filename << "\n";
        exit(EXIT_FAILURE);
    }
    int num{0}; // transmatrix[num]
    while (fin >> line)
    {
        if (line != "<TRANSP>")
        { //エラー処理
            std::cerr << "エラー：<TRANSP>がありません" << filename << "\n";
            exit(EXIT_FAILURE);
        }
        if (fin >> sizematrix)
        {
            transmatrix[num].size = sizematrix;
            transmatrix[num].probability = new double *[sizematrix];// 行列の値を格納する2次元配列の動的確保(講義資料p.22以降参照)
            for (int i = 0; i < sizematrix; i++)
            { 
                transmatrix[num].probability[i] = new double[sizematrix];// 行列の値を格納する1次元配列の動的確保
            }
        }
        else
        {
            std::cerr << "エラー：行列の大きさがありません" << filename << "\n";
            exit(EXIT_FAILURE);
        }
        if (fin >> line)
        {
            transmatrix[num].name = line;
        }
        else
        {
            std::cerr << "エラー：名前がありません" << filename << "\n";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < sizematrix; i++)
        {
            for (int j = 0; j < sizematrix; j++)
            {
                if (fin >> transmatrix[num].probability[i][j])
                {
                }
                else
                {
                    std::cerr << "エラー：行列の値がありません" << filename << "\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
        num++;
    }
}

int main()
{
    string inputfile = "transition_matrix.txt";// 読み込むファイル
    Transp *transmatrix;

    // 必要なtransmatrix（遷移行列）の数を求めて、numtransに代入
    int numtrans = gettranskosuu(inputfile);

    // 上で求めらtransmatrix分の領域を確保する
    transmatrix = new Transp[numtrans];

    // ファイル内の数値の読み込み
    readtransitionmatrix(inputfile, transmatrix);

    // transmatrixの検証
    for (int i = 0; i < numtrans; i++)
    {
        transmatrix[i].checkprob();
    }

    return 0;
}
