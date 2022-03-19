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

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>

using namespace std;
typedef enum usertype{
    USER_NTFS=1,
    USER_UNIX=2,
}user_type_t;

struct user_t{
    char name[1024];
    char type[1024];
    //user_type_t  type;
    int uid;
};

typedef struct permissmap
{
    int id;
    int id_map;
    int length;
    struct user_t user;
    struct user_t map_user;
    int priority;
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
class PermitContext
{
private:
    permit_data_t user_data;
    int total;
    map<string, map<int, permit_data_t>> permitmap;
    ifstream infile;  //输入流
    ofstream outfile; //输出流
    string update_time;
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
        auto && it = permitmap.find(user_data.user.name);
        if(it != permitmap.end()){
            auto && ret = it->second.insert(pair<int, permit_data_t>(user_data.priority, user_data));
            if(ret.second){
            //cout<<"Insert Successfully: uid "<< user_data.id <<endl;
            }
            else{
                cout<<"Insert Failure. username:" << user_data.user.name<<endl;
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
                auto && permitmapret = permitmap.insert(pair<string, map<int,permit_data_t>>(user_data.user.name, prioritymap));
                if(permitmapret.second){
                        //cout<<"Insert success permit map"<<endl;
                }else{
                        cout<<"Insert Failure permit map"<<endl;
                }
        }

}
void PermitContext::update_data()
{
    //int total;
    permit_data_t user_data;
    string record_time;
    string format;
    string username, type, map_username, map_type;
        /*测试*/
    infile.open("data.txt", ios::in);
    if(!infile.is_open ())
        cout << "Open file failure" << endl;

    infile >> record_time ;                         /* 先读取第一行，读取时间     */
    //infile >> total ;                               /* 先读取第二行，读取后续条数 */
    infile >> format;                               /* 读取数据保存格式           */

    cout << "total: " << total << "  " << "time" << " " << record_time << " format:" << format << endl;
	this->update_time = record_time;
    int cnt = 0;
    permitmap.clear();
    while (!infile.eof())
    {

            /* 读取映射数据               */
        infile >> username >> type >> user_data.user.uid
                >> map_username >> map_type >> user_data.map_user.uid
                >> user_data.priority;
        cout<< "cnt:" << cnt << " username:" << username <<endl;
         // if (username.eof()){
         //      break;
         //}
        strcpy(user_data.user.name, username.c_str());
        strcpy(user_data.user.type, type.c_str());
        strcpy(user_data.map_user.name, map_username.c_str());
        strcpy(user_data.map_user.type, map_type.c_str());
        #if 0
        /*查找是否有该key的map*/
        auto && it = permitmap.find(user_data.user.name);
        if(it != permitmap.end()){
            auto && ret = it->second.insert(pair<int, permit_data_t>(user_data.priority, user_data));
            if(ret.second){
            //cout<<"Insert Successfully: uid "<< user_data.id <<endl;
            }
            else{
                cout<<"Insert Failure. username:" << user_data.user.name<<endl;
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
                auto && permitmapret = permitmap.insert(pair<string, map<int,permit_data_t>>(user_data.user.name, prioritymap));
                if(permitmapret.second){
                        //cout<<"Insert success permit map"<<endl;
                }else{
                        cout<<"Insert Failure permit map"<<endl;
                }
        }
        #endif
		/*判断是否是通配符，没有则加入普通map，有则加入特殊map*/	
        this->insert_map(permitmap, user_data);
        /*
        pair<map<string, map<int,permit_data_t>>::iterator, bool> ret;
                ret = permitmap.insert(pair<string, map<int,permit_data_t>>(user_data.user.name, map));
        if(ret.second){
            cout<<"Insert Successfully: uid "<< user_data.id <<endl;
        }
        else{
            cout<<"Insert Failure"<<endl;
                        total =  cnt;
        }*/
        cnt ++;
    }
    total = cnt;
    infile.close();   //关闭文件

}

 void PermitContext::find_data(char *name){

    infile.open("data.txt", ios::in);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容

    if(!infile.is_open())
        cout << "Open file failure" << endl;

    auto && it = permitmap.find(name);
    if(it != permitmap.end()){
             auto && iter = it->second.begin();
            if(iter != it->second.end()){
                cout<<"find Successfully: username :" << iter->second.user.name
                    << ", uid:" << iter->second.user.uid
                    << ".   map_name: " << iter->second.map_user.name
                    << ", map_uid:" << iter->second.map_user.uid
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
    outfile.close();

}

int PermitContext::check_data()
{
    string time;
    //struct stat buf;
    infile.open("data.txt", ios::in);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容
    infile >> time ;                               /*先读取第一行，读取时间*/
    int ret = time.compare(this->update_time);
    infile.close();
    return ret;

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
                    cout << "update file" << endl;
                    uidcon->update_data();
                    //uidcon->save_data();
                    uidcon->find_data((char *)"username04");
            }
            usleep(1000000);
    }
    return 0;
}
