#include<iostream>
#include<string>
#include<fstream>
#define Max 100

using namespace std;

string Question[Max];
string answer[Max];

int input()
{
    int i = 0;
    ifstream ifs;
    ifs.open("question.txt",ios::in);
    if (!ifs.is_open())
    {
        cout << "文件打开异常" << endl;
        return i;
    }
    
    while (ifs >> Question[i])
    {
        cout << Question[i] << endl;
        i++;
    }
    // cout << i << endl;
    return i;
}

void calculate()
{
    
}

void output(int num)
{
    int i = 0;
    ofstream ofs;
    ofs.open("answer.txt",ios::out);
    for ( i = 0; i < num; i++)
    {
        ofs << Question[i] << "=" << answer[i] << endl;
    }
    ofs.close();
}

int main ()
{
    int num;
    num = input();
    output(num);
}