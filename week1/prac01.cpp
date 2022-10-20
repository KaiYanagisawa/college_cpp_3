//prac01.cpp
#include <iostream>
using std::cout,std::cin,std::string;

//クラス Date 定義部分
class Date
{
private:
    int year;  // 年
    int month; // 月
    int day;   // 日

public:
    Date(){}//Personクラスのデータメンバになっているため，引数無しのコンストラクタかデフォルト引数の指定を行う
    //コンストラクタ：引数の値をデータメンバに格納
    Date(const int y, const int m, const int d)//引数なしのコンストラクタを定義しない場合はデフォルト引数の指定を行う
    {
        year = y;
        month = m;
        day = d;
    }

    // データメンバyear の値を返す
    int get_year() const
    {
        return year;
    }

    // データメンバmonth の値を返す
    int get_month() const
    {
        return month;
    }

    // データメンバday の値を返す
    int get_day() const
    {
        return day;
    }

    // プロトタイプ宣言
    int days_from_newyearsday();
};

// データメンバに格納されている日にちについて元日からの日数を計算する
int Date::days_from_newyearsday()
{
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = day;

    // 終了条件が (month-1) であることに注意．（例）2月5日の場合には 31+5 になる
    for (int i = 0; i < (month - 1); i++)
    {
        days += days_in_month[i];
    }
    return days - 1; // 元旦からの日数なので 1 を引く．（例）1月1日の場合は 0
}

//クラス Person 定義部分
class Person
{
private:
    string name;    // 名前
    Date birth_day; // 生年月日

public:
    // コンストラクタ：引数の値をデータメンバに格納
    Person(const string fn, const Date d)
    {
        name = fn;
        birth_day = d;
    }

    // データメンバname の値を返す
    string get_name()
    {
        return name;
    }

    // 名前と生年月日を出力する．（例）「Taroさんの誕生日：2002/9/29.」を出力
    // constメンバ関数になっているので，呼び出しされるメンバ関数もconst宣言にする
    void print_birth() const
    {
        cout << name << "さんの誕生日：" << birth_day.get_year() << "/" << birth_day.get_month() << "/" << birth_day.get_day() << ". \n";
    }

    int tobirthday(Date today); // 関数のプロトタイプ宣言
    int ages(Date today);       // 関数のプロトタイプ宣言

    // Person クラスのデストラクタの設定．「名前＋is released.」の表示
    ~Person()
    {
        cout << name << " is released.\n";
    }
};

// 引数から誕生日までの日数を計算し返す（「今日の日付」と「誕生日」との差を比較するため負の値になる可能性があることに注意）
int Person::tobirthday(Date today)
{
    return birth_day.days_from_newyearsday() - today.days_from_newyearsday();
}

// 引数から誕生日までの年数を計算し返す
int Person::ages(Date today)
{
    // 今日と誕生日の日付を比較して，今年誕生日がきているかどうかで場合分けする
    if (tobirthday(today) > 0)
    {
        return today.get_year() - birth_day.get_year() - 1;
    }
    else
    {
        return today.get_year() - birth_day.get_year();
    }
}

void print_day(int date)
{
    if (date > 0)
    {
        cout << "誕生日まであと" << date << "日です\n";
    }
    else if (date < 0)
    {
        cout << "今年の誕生日は過ぎてしまいました\n";
    }
    else
    {
        cout << "今日が誕生日です。お誕生日おめでとう！\n";
    }
}

// main 関数部分
int main()
{
    Date today(2022, 9, 29); // 今日の日付
    Person taro("Taro", Date(2002, 9, 29));
    Person peach("Peach-kun", Date(1923, 3, 3));
    Person jakob("Jakob", Date(1654, 12, 27));
    cout << "今日: " << today.get_year() << "/" << today.get_month() << "/" << today.get_day() << ". \n";
    taro.print_birth();
    peach.print_birth();
    jakob.print_birth();

    cout << "\n"; 
    cout << taro.get_name() << "さんは今 " << taro.ages(today) << " 歳です\n";
    print_day(taro.tobirthday(today));
    cout << peach.get_name() << "さんは今 " << peach.ages(today) << " 歳です\n";
    print_day(peach.tobirthday(today));
    cout << jakob.get_name() << "さんは今 " << jakob.ages(today) << " 歳です\n";
    print_day(jakob.tobirthday(today));

    return 0;
}
