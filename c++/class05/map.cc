#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <sys/time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


using namespace std;
typedef enum maptype{
    USER_NTFS=1,
    USER_UNIX=2,
}map_type_t;

struct user_t{
    char srcname[1024];
	char dstname[1024];
    char strtype[1024];
	int priority;
	map_type_t type;
};

typedef struct permissmap
{
    int id;
    int id_map;
    int length;
    char srcuser[1024];
	char dstuser[1024];
    char strtype[1024];
	int priority;
	map_type_t type;
    //char format[1024];

    //对于向量元素是结构体的，可在结构体内部定义比较函数，下面按照id,length,width升序排序。
    bool operator< (const permissmap &p)  const
    {
        if(id != p.id)
                return id < p.id;
        else
        {
            if(priority != p.priority)
                return priority < p.priority;
            else
                return 1;
        }
    }
}permit_data_t;

int cost[10][10];



/***
*        按指定字符截取字符串
*/
static void splitstring(const string& str, vector<string>& ret_, const string &sep)
{
    if (str.empty())
    {
        return ;
    }

    string tmp;
    string::size_type pos_begin = 0;//str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        ret_.push_back(tmp);
    }
}

/***
*        删除字符串中空格，制表符tab等无效字符
*/
static string trim(string& str)
{
    str.erase(0,str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

class PermitContext
{
private:
    permit_data_t user_data;
    int total;
    map<string, map<int, permit_data_t>> permitmap;
    ifstream infile;  //输入流
    ofstream outfile; //输出流
    long int update_time;
public:
    //PermitContext();
    void update_data();
    //void save_data();
    int check_data();
    void find_data(char*);
    void insert_map(map<string, map<int, permit_data_t>> &permitmap,  permit_data_t user_data);
    //string gettime();
    //~PermitContext();
};
void PermitContext::insert_map(map<string, map<int, permit_data_t>> &permitmap,  permit_data_t user_data)
{

        /*查找是否有该key的map*/
        auto && it = permitmap.find(user_data.srcuser);
        if(it != permitmap.end()){
            auto && ret = it->second.insert(pair<int, permit_data_t>(user_data.priority, user_data));
            if(ret.second){
            //cout<<"Insert Successfully: uid "<< user_data.id <<endl;
            }
            else{
                cout<<"Insert Failure. username:" << user_data.srcuser<<endl;
                        //    total =  cnt;
            }
        }
        else{
                map<int,permit_data_t> prioritymap;
                auto && ret_prio = prioritymap.insert(pair<int,permit_data_t>(user_data.priority,user_data));
                if(ret_prio.second){
                        //cout<<"Insert success priority map"<<endl;
                }else{
                        cout<<"Insert Failure priority map"<<endl;
                }
                auto && permitmapret = permitmap.insert(pair<string, map<int,permit_data_t>>(user_data.srcuser, prioritymap));
                if(permitmapret.second){
                        //cout<<"Insert success permit map"<<endl;
                }else{
                        cout<<"Insert Failure permit map"<<endl;
                }
        }

}
void PermitContext::update_data()
{
    permit_data_t user_data;
    string record_time;
    string format;
    //string username, type, map_username, map_type;
        /*测试*/
    infile.open("data.csv", ios::in);
    if(!infile.is_open ())
        cout << "Open file failure" << endl;

    //infile >> format;                               /* 读取数据保存格式           */

    //cout << "update file format:" << format << endl;
    int cnt = 0;

    string line;
    int line_count = 0;
    permitmap.clear();

    /* 读取映射数据               */
    while (getline(infile, line)) /*整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取*/
    {
		line_count ++;
        vector<string> fields; //声明一个字符串向量
        string field;
        splitstring(line, fields, ",");
        if (fields.size() != 5){
			cout << "fields" << fields.size() << endl;
            continue;
        }
		if (line_count == 1)
		{
            continue;
		}
        //string username =     trim(fields[0]);
        //string type =         trim(fields[1]);
        //string uid =          trim(fields[2]);
        //string map_username = trim(fields[3]);
        //string map_type     = trim(fields[4]);
        //string map_uid      = trim(fields[5]);
        //string priority     = trim(fields[6]);

        //strcpy(user_data.user.name, username.c_str());
        //strcpy(user_data.user.type, type.c_str());
        //user_data.user.uid = stoi(uid);
        //strcpy(user_data.map_user.name, map_username.c_str());
        //strcpy(user_data.map_user.type, map_type.c_str());
        //user_data.map_user.uid = stoi(uid);
		string num      =     trim(fields[0]);
		string type     =     trim(fields[1]);
		string srcuser  =     trim(fields[2]);
		string dstuser  =     trim(fields[3]);
		string priority =     trim(fields[4]);
		
		strcpy(user_data.srcuser, srcuser.c_str());
		strcpy(user_data.dstuser, dstuser.c_str());
		strcpy(user_data.strtype, type.c_str());
		cout << "num" <<  num <<endl;
		user_data.id = std::stoi(num);
		user_data.priority = std::stoi(priority);
		
		cout<< "num"<< user_data.id
		             <<"find Successfully: username :" << user_data.srcuser
                     << ".   map_name: " << user_data.dstuser
                     << ", prio:" << user_data.priority<<endl;		
        /*判断是否是通配符，没有则加入普通map，有则加入特殊map*/
        this->insert_map(permitmap, user_data);

    }
    total = line_count;
    infile.close();   //关闭文件

}

 void PermitContext::find_data(char *name){

    this->infile.open("data.csv", ios::in);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容

    if(!this->infile.is_open())
        cout << "Open file failure" << endl;

    auto && it = permitmap.find(name);
    if(it != permitmap.end()){
             auto && iter = it->second.begin();
            if(iter != it->second.end()){
                cout<<"find Successfully: username :" << iter->second.srcuser
                    << ".   map_name: " << iter->second.dstuser
                    << ", prio:" << iter->second.priority<<endl;
            }
            else{
                cout<<"find Failure"<<endl;
            }

    }
    /*没找到就需要去找通配符特殊map中查找， 遍历匹配正则表达式，（考虑最小最大匹配）*/


    auto && iter=permitmap.begin();
    for(iter = permitmap.begin(); iter != permitmap.end(); iter++)
    {
        //cout<< (*iter).first <<" " <<endl;
        //outfile << (*iter).first << "\t" << (*iter).second.id <<  endl;   /*在result.txt中写入结果*/
    }
    this->infile.close();

}

int PermitContext::check_data()
{
    string time;
    struct stat buf;
    stat("data.csv", &buf);
    //cout << "oldtime:" << this->update_time << "mtime:" << buf.st_mtime <<endl;
    if( this->update_time != (long int)buf.st_mtime ){
            this->update_time = (long int)buf.st_mtime;
            return 1;
    }
    return 0;

}
#if 0
void PermitContext::save_data(){

    outfile.open("data.txt", ios::out);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容
        int i;
    if(!outfile.is_open())
        cout << "Open file failure" << endl;
    for(i=0; i<10000; i++)
    {
        outfile<< "username03  NTFS    02  name2   NTFS    13  "<<i <<endl;
    }
    outfile.close();

}
#endif
//void PermitContext::PermitContext()
//{
//
//
//}
//void PermitContext::~PermitContext()
//{
//
//}
int main()
{
    PermitContext *uidcon = new PermitContext();
    uidcon->update_data();
    char *name=(char *)"username";

    /*
    if (total <= 0){
            cout << "update file failed" << endl;
    }
    else{
            cout << "update file success"  << total << endl;
    }*/
    uidcon->find_data(name);
    //uidcon->save_data();
    while(1){
            if(uidcon->check_data()){
                    //cout << "update file" << endl;
                    uidcon->update_data();
                    uidcon->find_data((char *)"username04");
            }
            usleep(1000000);
    }
    return 0;
}
