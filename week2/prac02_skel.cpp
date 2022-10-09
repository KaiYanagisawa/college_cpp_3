//prac02_skel.cpp
#include <iostream>
#include <cstdlib>
using std::cin, std::cout, std::endl, std::cerr;

class Fraction
{
private:
    int numerator;   // 分子
    int denominator; // 分母
    int gcd(int x, int y) const
    {                 //最大公約数を求める関数(ユークリッドの互除法)　外部関数でも良い
        int z{x % y}; // xをyで割った余りをzとすると、xとyの最大公約数はyとzの最大公約数に等しい
        while (z != 0)
        {
            x = y;
            y = z;
            z = x % y;
        }
        return y;
    }

public:
    Fraction(int n = 0, int d = 1)
    { // コンストラクタ（デフォルト引数の指定）
        numerator = n;
        denominator = d;
        if (denominator < 0)
        { //分母が負の場合、代わりに分子の符号を変更
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    void reduce()
    {
        if (denominator == 0)
        {
            cerr << "??分母が0!!" << endl; //分母が0のとき警告を出して止める
            exit(EXIT_FAILURE);
        }
        else if (numerator == 0)
        { // 何もしない。出力の際に0が表示される
        }
        else
        {
            int bunshi = numerator;
            if (bunshi < 0)
            { // 分子が負のとき
                bunshi = -bunshi;
            }
            int bunbo = denominator;
            if (bunbo < 0)
            { // 分母が負のとき
                bunbo = -bunbo;
            }
            int saidaikouyakusuu = gcd(bunshi, bunbo);
            numerator /= saidaikouyakusuu;
            denominator /= saidaikouyakusuu;
        }
    }
    //  ・>>演算子のオーバーロード：分母が0の場合、「標準入力で分母に0が設定されています」とエラー文を出す。
    //  　分母がマイナスの場合、分子にマイナスが付くようにする
    friend std::istream &operator>>(std::istream &stin, Fraction &g);
    //  ・<<演算子のオーバーロード：分子が0の場合、0を出力。分母が1の場合、分母が出力されないようにする
    //  ・+演算子のオーバーロード：分数の足し算をする
    //  ・-演算子のオーバーロード：分数の引き算をする
    //  ・*演算子のオーバーロード：「定数*分数」と「分数*定数」にも対応できるようにする
    //  ・/演算子のオーバーロード：分数の割り算をする
};

    std::istream &operator>>(std::istream& stin, Fraction& g) {
        stin >> g.numerator >> g.denominator;
        return stin;
    }

int main()
{
    Fraction g1, g2, ans;
    int n{2};

    cout << "分数を入力(g1)-->"; // 分子、分母の順で入力 3 4 など
    cin >> g1;
    cout << "分数を入力(g2)-->";
    cin >> g2;
    // ans = g1 + g2;
    // cout << "g1+g2 = " << g1 << "+" << g2 << " = " << ans << "\n";
    // ans = g1 - g2;
    // cout << "g1-g2 = " << g1 << "-" << g2 << " = " << ans << "\n";
    // ans = g1 * g2;
    // cout << "g1*g2 = " << g1 << "*" << g2 << " = " << ans << "\n";
    // ans = g1 / g2;
    // cout << "g1/g2 = " << g1 << "/" << g2 << " = " << ans << "\n";
    // ans = g1 * n;
    // cout << "g1*定数 = " << g1 << "*" << n << " = " << ans << "\n";
    // ans = n * g1;
    // cout << "定数*g1 = " << n << "*" << g1 << " = " << ans << "\n";

    return 0;
}