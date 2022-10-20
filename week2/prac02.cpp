#include <iostream>
#include <cstdlib>
using std::cin,std::cout,std::endl,std::cerr;

class Fraction {
private:
    int numerator;			// 分子
    int denominator;		// 分母
    int gcd(int x, int y) const{	//最大公約数を求める関数(ユークリッドの互除法)　外部関数でも良い
        int z{x%y};			//xをyで割った余りをzとすると、xとyの最大公約数はyとzの最大公約数に等しい
        while( z !=0 ){ x=y; y=z; z=x%y; }
        return y;
    }
public:
    Fraction(int n=0, int d=1){	// コンストラクタ（デフォルト引数の指定）
        numerator=n;    
        denominator=d;
        if( denominator<0 ){		//分母が負の場合、代わりに分子の符号を変更
            numerator=-numerator;
            denominator=-denominator;
        }
    }
    void reduce(){			
        if(denominator==0){
            cerr << "??分母が0!!" << endl;	//分母が0のとき警告を出して止める
            exit(EXIT_FAILURE);
        } else if(numerator==0){	// 何もしない。出力の際に0が表示される
        } else{
            int bunshi=numerator;
            if(bunshi<0){   // 分子が負のとき
                bunshi=-bunshi;
            }
            int bunbo=denominator;
            if(bunbo<0){   // 分母が負のとき
                bunbo=-bunbo;
            }
            int saidaikouyakusuu=gcd(bunshi,bunbo);
            numerator/=saidaikouyakusuu;
            denominator/=saidaikouyakusuu;
        }
    }

    friend std::istream& operator>>(std::istream& , Fraction& );
    friend std::ostream& operator<<(std::ostream& , const Fraction &);
    friend Fraction operator+(const Fraction &, const Fraction &);
    friend Fraction operator-(const Fraction &, const Fraction &);
    friend Fraction operator*(const Fraction &, const Fraction &);
    friend Fraction operator/(const Fraction &, const Fraction &);
};

std::istream& operator>>(std::istream& inst, Fraction& a){
    inst >> a.numerator >> a.denominator;
    if(a.denominator == 0){
        std::cerr << "標準入力で分母に0が設定されています" << endl;
        exit(EXIT_FAILURE);
    }
    if(a.denominator < 0){
        a.numerator = -a.numerator;
        a.denominator = -a.denominator;
    }
    a.reduce();
    return inst;
}


std::ostream& operator<<(std::ostream& outst, const Fraction & a){
    if(a.numerator==0){			//分子が0のときの処理
        outst << "0";
    } else if(a.denominator==1){		//分母が1のときの処理
        outst << a.numerator;
    } else{
        outst << "(" << a.numerator << "/" << a.denominator << ")";
    }
    return outst;
}
Fraction operator*(const Fraction & a, const Fraction & b){
    Fraction tmp;
    tmp.numerator=a.numerator*b.numerator;
    tmp.denominator=a.denominator*b.denominator;
    tmp.reduce();
    return tmp;
}

Fraction operator/(const Fraction & a, const Fraction & b){
    Fraction tmp;
    tmp.numerator=a.numerator*b.denominator;
    tmp.denominator=a.denominator*b.numerator;
    tmp.reduce();
    if( tmp.denominator<0 ){
        tmp.numerator=-tmp.numerator;
        tmp.denominator=-tmp.denominator;
    }
    return tmp;
}

Fraction operator+(const Fraction & a, const Fraction & b){
    Fraction tmp;
    tmp.numerator=a.numerator*b.denominator+b.numerator*a.denominator;
    tmp.denominator=a.denominator*b.denominator;
    tmp.reduce();
    return tmp;
}

Fraction operator-(const Fraction & a, const Fraction & b){
    Fraction tmp;
    tmp.numerator=a.numerator*b.denominator-b.numerator*a.denominator;
    tmp.denominator=a.denominator*b.denominator;
    tmp.reduce();
    return tmp;
}

int main(){
    Fraction g1, g2, ans;
    int n{2};
  
    cout << "分数を入力(g1)-->";			// 分子、分母の順で入力 3 4 など
    cin >> g1;
    cout << "分数を入力(g2)-->";
    cin >> g2;
    ans = g1+g2;
    cout << "g1+g2 = " << g1 << "+" << g2 << " = " << ans << "\n";
    ans = g1-g2;
    cout << "g1-g2 = " << g1 << "-" << g2 << " = " << ans << "\n";
    ans = g1*g2;
    cout << "g1*g2 = " << g1 << "*" << g2 << " = " << ans << "\n";
    ans = g1/g2;
    cout << "g1/g2 = " << g1 << "/" << g2 << " = " << ans << "\n";
    ans = g1*n;
    cout << "g1*定数 = " << g1 << "*" << n << " = " << ans << "\n";
    ans = n*g1;
    cout << "定数*g1 = " << n << "*" << g1 << " = " << ans << "\n";

    return 0;
}