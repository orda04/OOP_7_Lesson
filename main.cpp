#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class date
{
private:
    int Year,Month,Day;
public:
    friend ostream& operator<<(ostream& os, const date &d);
    friend istream &operator>>(istream &in,date &d);
    date(){}
    date(int yy, int mm, int dd):Year(yy),Month(mm),Day(dd){}

    //p - это сткрока с параметрами, указывающими какие поля структур не следует использовать при сравнении

   bool Less(const date &d1,const date &d2)
   //bool Less(const date &d1,const date &d2,char *p)  //*p добавлено для будущей реализации исключения из сравнения дней или месяцев или годов
   {
       // size_t end=strlen(p);//если включаем  p  необходимо раскомментить строки с p ниже
       if (d1.Year < d2.Year )return true;
       // if (d1.Year < d2.Year && !find(p,p+end,'y'))return true;
       if (d1.Month < d2.Month )return true;
       // if (d1.Month < d2.Month &&!find(p,p+end,'m'))return true;
       if (d1.Day < d2.Day)return true;
       // if (d1.Day < d2.Day && !find(p,p+end,'d'))return true;
        return false;
    }
    //функция возвращает количество дней между датами
    void Swapme(date &d1, date&d2)
    {


            if (&d1 != &d2)
            {
                date tmp = d1;
                d1 = d2;
                d2 = tmp;
            }

    }
    int operator-(date d2)
    {
        date d1(*this);
        //если d2 раньше d1 поменять их местами, это сделано потому что
        //далее в функции весь код адекватен при условии что d1 раньше d2.
        if (Less(d2,d1))swap(d1,d2);
        //разница между датами в днях
        int diff=0;
        //между какими месяцами будем считать
        int from=d1.Month, to=d2.Month;
        //разница между годами в годах
        int diffyear=abs(d2.Year - d1.Year);
        //сколько дней между датами прошло, считая только по месяцам
        if (diffyear==0)
            for (int i=from; i < to; i++)
            {
                switch(i)
                {
                    case 1:diff+=31; break;
                    case 2:diff+=28; break;
                    case 3:diff+=31; break;
                    case 4:diff+=30; break;
                    case 5:diff+=31; break;
                    case 6:diff+=30; break;
                    case 7:diff+=31; break;
                    case 8:diff+=31; break;
                    case 9:diff+=30; break;
                    case 10:diff+=31; break;
                    case 11:diff+=30; break;
                    case 12:diff+=31; break;
                }
            }
        else
        {
            for (int i=from; i <= 12; i++)
            {
                switch(i)
                {
                    case 1:diff+=31; break;
                    case 2:diff+=28; break;
                    case 3:diff+=31; break;
                    case 4:diff+=30; break;
                    case 5:diff+=31; break;
                    case 6:diff+=30; break;
                    case 7:diff+=31; break;
                    case 8:diff+=31; break;
                    case 9:diff+=30; break;
                    case 10:diff+=31; break;
                    case 11:diff+=30; break;
                    case 12:diff+=31; break;
                }
            }
            for (int i=1; i < to; i++)
            {
                switch(i)
                {
                    case 1:diff+=31; break;
                    case 2:diff+=28; break;
                    case 3:diff+=31; break;
                    case 4:diff+=30; break;
                    case 5:diff+=31; break;
                    case 6:diff+=30; break;
                    case 7:diff+=31; break;
                    case 8:diff+=31; break;
                    case 9:diff+=30; break;
                    case 10:diff+=31; break;
                    case 11:diff+=30; break;
                    case 12:diff+=31; break;
                }
            }
        }
        //коррекция по дням
        diff-=d1.Day;
        diff+=d2.Day;
        //сколько лет прошло между датами
        diff+=((diffyear > 1)?(diffyear - 1):(0))*365;
        //сколько было весокосных лет в промежутке между датами
        diff+=diffyear/4;
        //считаем были ли весокосный год между датами если они оличатюся менее чем на 4 года.
        for (int i=d2.Year-diffyear;i<=d2.Year;i++)
        {
            //год является високосным, если он кратен 4 и при этом не кратен 100, либо кратен 400.
            if (((i%4==0) && !(i%100==0))||(i%400==0))
            {
            diff+=1; break;
            }
        }
        return diff;
    }
    date operator+(int days)
    {

        date d(*this);
        d.Year+=int(days/365);
        int diff=0;
        for (int i=Month;i < 13;i++)
        {
            switch(i)
            {
                case 1:diff+=31; break;
                case 2:diff+=28; break;
                case 3:diff+=31; break;
                case 4:diff+=30; break;
                case 5:diff+=31; break;
                case 6:diff+=30; break;
                case 7:diff+=31; break;
                case 8:diff+=31; break;
                case 9:diff+=30; break;
                case 10:diff+=31; break;
                case 11:diff+=30; break;
                case 12:diff+=31; break;
            }
        }
        int out_of_year=(days - int(days/365) * 365);
        for (int i=1; diff < out_of_year-31; i++)
        {
            switch(i)
            {
                case 1:diff+=31; break;
                case 2:diff+=28; break;
                case 3:diff+=31; break;
                case 4:diff+=30; break;
                case 5:diff+=31; break;
                case 6:diff+=30; break;
                case 7:diff+=31; break;
                case 8:diff+=31; break;
                case 9:diff+=30; break;
                case 10:diff+=31; break;
                case 11:diff+=30; break;
                case 12:diff+=31; break;
            }
        }
        d.Month+= out_of_year/diff;
        return d;
    }
};
ostream &operator<<(ostream &out,const date &d)
{
        out << d.Year << '-' << d.Month << '-' << d.Day;
        return out;
}
istream &operator>>(istream &in,date &d)
{
    char c;
    in >> d.Year;
    in >> c;
    if (c=='-'||'.'||' '||':')
    {
        in >> d.Month;
        in >> c;
        if (c=='-'||'.'||' '||':') in >> d.Day;
        else cout << "wrong date format, excepted '-' after month, variable is not complete\n";
    }
    else cout << "wrong date format, excepted '-' after years, variable is not complete\n";
    return in;
}
int main()
{
    date D1,D2;

    cout << "Enter some date yy-mm-dd: ";
    cin >> D1;
    cout << "Enter some other date yy-mm-dd: ";
    cin >> D2;
    cout << "first date " << D1 << ", second date " << D2 << '\n';
   if(D1.Less(D1,D2))
    {
    cout << "считаем что вторая дата больше\n";
    }
    else
    {
      cout << "считаем что первая дата больше\n";
     }

           D1.Swapme(D1,D2);
           cout<<"после обмена"<<endl;
           cout<<D1<<endl;
           cout<<D2<<endl;

    return 0;
}
