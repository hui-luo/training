#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#define Max 100

using namespace std;

string Question[Max];
int answer[Max];

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
    return i;                                   //返回有多少行数据
}

void calculate(int num)
{
    int number1,number2,j,k,l;
    int K,L;
    char num1[10],num2[10];
    char type[10];                            //存放计算类型
    for (int i = 0; i < num ; i++)
    {
        K = 0;
        L = 0;
        for ( j = 0; Question[i][j] != '('; j++)
        {
            type[j] = Question[i][j];
        }
        type[j] = '\0';

        memset(num1,0,sizeof(num1));                          //赋初始值
        memset(num2,0,sizeof(num2));

        for ( k = j + 1; Question[i][k] != ')' && Question[i][k] != ','; k++)
        {
            num1[K] = Question[i][k];
            K++;
        }
        num1[K] = '\0';
        if (Question[i][k] == ',')
        {
            for ( l = k + 1; Question[i][l] != ')'; l++)
            {
                num2[L] = Question[i][l];
                L++;
            }
            num2[L] = '\0';
            
            number2 = atoi(num2);
        }
        
        //cout << num1 << endl;
        number1 = atoi(num1);
        if (strcmp(type,"add") == 0)
        {
            answer[i] = number1 + number2;
        }
        else if (strcmp(type,"sub") == 0)
        {
            answer[i] = number1 - number2;
        }
        else if (strcmp(type,"muti") == 0)
        {
            answer[i] = number1 * number2;
        }
        else if (strcmp(type,"div") == 0)
        {
            answer[i] = number1 / number2;
        }
        else if (strcmp(type,"doubleMe") == 0)
        {
            answer[i] = number1 + number1;
        }
        //cout << number1 << " " << number2 << endl;
    }
    // for (int i = 0; i < num; i++)
    // {
    //     cout << answer[i];
    // }
    
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
    calculate(num);
    output(num);
}