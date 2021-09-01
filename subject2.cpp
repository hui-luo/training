#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<sstream>
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
string adress[Max];
string birthday[Max];
string score[Max];
sort p;
int number;
int decide[Max];
string pri[Max];

void help();
int load();
void sort_score(int num);
void select( string info[],int num1,int num2);

int main ()
{
    string type;
    int wh;
    string info[Max];
    int count = 0;
    int judge = 0;   //判断有无adress
	string token;
    string size;
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
        else if (type.compare("exit") == 0)
        {
            break;
        }
        else
        {
            istringstream iss(type);
            for (int i = 0; i < count; i++)
            {
                info[i].erase(0);
            }
            count = 0;
            while (getline(iss, token, '_'))	// 以 _ 为分隔符
            {
                info[count] = token;
                count++; 
            }
            for (int i = 0; i < count; i++)
            {
                if (info[i].compare("where") == 0)
                {

                    judge = 1;
                    wh = i;
                    break;
                }
                
            }
            if (judge == 1)
            {
                select(info,number,wh);
                for (int i = 0; i < number; i++)
                {                                                //标记是否可以输出
                    decide[i] = 1;                              //初始化
                }
                
                for (int i = wh+1; i < count; i++)
                {
                    if(info[i].find("sex") != string::npos)    
                    {
                        if (info[i].find("man") != string::npos)
                        {
                           for (int j = 0; j < number; j++)
                           {
                               if (sex[j].compare("女") == 0)
                               {
                                   decide[j] = 0;
                               }
                           }
                        }
                        else
                        {
                            for (int j = 0; j < count; i++)
                           {
                               if (sex[j].compare("男") == 0)
                               {
                                   decide[j] = 0;
                               }
                           }
                        }
                    }      
                    if (info[i].find("score") != string::npos)
                    {
                        if (info[i].find(">") != string::npos)
                        {
                            size = info[i].substr(info[i].find(">")+1,2);
                            for (int j = 0; j < number; j++)
                            {
                                if (score[j] < size)
                                {
                                    decide[j] = 0;
                                }
                            }
                        }
                        else
                        {
                            size = info[i].substr(info[i].find("<")+1,2);
                            for (int j = 0; j < number; j++)
                            {
                                if (score[j] > size)
                                {
                                    decide[j] = 0;
                                }
                            }
                        }
                        
                    }
                              
                }
                for (int i = 0; i < number; i++)
                {
                    if (decide[i] == 1)
                    {
                        cout << pri[i] << endl;
                    }
                }
            }
            else
            {
                select(info,number,count);
                for (int i = 0; i < number; i++)
                {
                    cout << pri[i] << endl;
                }
            }
        }
    } while (type.compare("exit") != 0);
}

void help()
{
    cout << "load_data.txt" << endl;
    cout << "从目录中装入文件data.txt，并显示" << endl;
    cout << "sort_score" << endl;
    cout << "按“成绩”排序，并显示" << endl;
    cout << "select_ID_name" << endl;
    cout << "只显示学号、姓名两列，显示的列还可以其他的任意" << endl;
    cout << "select_ID_name adress score > 60" << endl;
    cout << "只显示学号、姓名两列，只包含成绩>60的行" << endl;
    cout << "select_*_adress_score>60_sex=man" << endl;
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
            adress[number] = data;
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
    for ( int i = 0; i < num; i++)                         //将score[]的值导入到p.ss[]中
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
                change = p.ss[j];                            //不改变score[]的值
                p.ss[j] = p.ss[i];
                p.ss[i] = change;
                t = p.order[j];                              //将顺序存入p.order
                p.order[j] = p.order[i];
                p.order[i] = t;
            }
        }
        
    }
    for (int i = 0; i < num; i++)
    {
        cout << ID[p.order[i]] << " " << name[p.order[i]] << " " <<sex[p.order[i]] << " " << adress[p.order[i]] << " " << birthday[p.order[i]] << " " << score[p.order[i]] << endl;
    }
}
void select(string info[],int num1,int num2)
{
    
    for (int i = 0; i < num1; i++)
    {
        pri[i].erase(0);
    }
    
    for (int i = 0; i < num2; i++)
    {
        if (info[i].compare("ID") == 0 )
        {
            for (int j = 0; j < num1; j++)
            {
                //cout << pri[j] << endl;
                pri[j] = pri[j] + " " + ID[j];
                
            }
            
        }
        else if (info[i].compare("name") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + name[j];
            }
        }
            
        else if (info[i].compare("sex") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + sex[j];
            }
        }
            
        else if (info[i].compare("adress") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + adress[j];
            }
        }
            
        else if (info[i].compare("birthday") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + birthday[j];
            }
        }
            
        else if (info[i].compare("score") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + score[j];
            }
        }
        else if (info[i].compare("*") == 0)
        {
            for (int j = 0; j < num1; j++)
            {
                pri[j] = pri[j] + " " + ID[j] + " " + name[j] + " " + sex[j] + " " + adress[j] +" "+ birthday[j] + " " + score[j];
            }
        }
        
    }
    
}