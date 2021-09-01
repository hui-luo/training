#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#define Max 1000

using namespace std;

typedef struct Sort
{
    string ss[Max];
    int order[Max];
}sort;


string ID[Max];
string name[Max];
string sex[Max];
string where[Max];
string birthday[Max];
string score[Max];
sort p;
int number;

void help();
int load();
void sort_score(int num);

int main ()
{
    string type;
    do
    {
        cout << "请输入命令（输入help显示帮助信息）：";
        cin >> type;
        
        if (type.compare("help") == 0)
        {
            help();
        }
        else if (type.compare("load_data.txt") == 0)
        {
            number = load();
            
        }
        else if (type.compare("sort_score") == 0)
        {
            sort_score(number);
        }
    } while (type.compare("exit") != 0);
}

void help()
{
    cout << "load_data.txt" << endl;
    cout << "从目录中装入文件data.txt，并显示" << endl;
    cout << "sort_score" << endl;
    cout << "按“成绩”排序，并显示" << endl;
    cout << "select 学号 姓名" << endl;
    cout << "只显示学号、姓名两列，显示的列还可以其他的任意" << endl;
    cout << "select 学号 姓名 where 成绩 > 60" << endl;
    cout << "只显示学号、姓名两列，只包含成绩>60的行" << endl;
    cout << "select * where 成绩>60 性别=男" << endl;
    cout << "只显示姓名、学号两列，只包含成绩>60且性别为男的行" << endl;
    cout << "其他组合，从上边类推" << endl;
    cout << "exit" << endl;
    cout << "退出程序" << endl;    
}
int load()
{
    ifstream ifs;
    ifs.open("data.txt",ios::in);
    if (!ifs.is_open())
    {
        cout << "文件打开异常" << endl;
        return -1;
    }
    string data;
    char a[10];
    int n = 1,choose,number;
    while ( ifs >> data )
    {
        cout << data << " ";
        choose = n%6;
        number = n/6;
        switch (choose)
        {
        case 1:
            ID[number] = data;
            break;
        case 2:
            name[number] = data;
            break;
        case 3:
            sex[number] = data;
            break;        
        case 4:
            where[number] = data;
            break;
        case 5:
            birthday[number] = data;
            break;
        case 0:
            score[number-1] = data;
            cout << endl;
            break;
        }
        n++;
    }
    ifs.close();
    return number;
}
void sort_score(int num)
{
    for ( int i = 0; i < num; i++)
    {
        p.ss[i] = score[i];
        p.order[i] = i;
    }
    string change;
    int t;
    for (int i = 0; i < num-1; i++)
    {
        for (int j = i+1; j < num; j++)
        {
            if (p.ss[j] > p.ss[i])
            {
                change = p.ss[j];
                p.ss[j] = p.ss[i];
                p.ss[i] = change;
                t = p.order[j];
                p.order[j] = p.order[i];
                p.order[i] = t;
            }
        }
        
    }
    for (int i = 0; i < num; i++)
    {
        cout << ID[p.order[i]] << " " << name[p.order[i]] <<" " <<sex[p.order[i]] <<" " << where[p.order[i]] <<" " << birthday[p.order[i]] <<" " <<score[p.order[i]] << endl;
    }
}