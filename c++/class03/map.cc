#include <stdio.h>
#include <iostream>
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

typedef struct uidmap
{
        int id;
        int id_map;
        int length;
        //对于向量元素是结构体的，可在结构体内部定义比较函数，下面按照id,length,width升序排序。
        bool operator< (const uidmap &a)  const
        {
                if(id != a.id)
                        return id < a.id;
                else
                {
                        if(id_map != a.id_map)
                                return id_map < a.id_map;
                        else
                                return length < a.length;
                }
        }
}uid_map_t;
int cost[10][10];

class UidContext
{

private:
    uid_map_t uid_data;
	int total;
    map<int, uid_map_t> uidmap;

    ifstream infile;  //输入流
    ofstream outfile; //输出流  
	string update_time;

public:
	//UidContext();
	void update_data();
	void save_data();
	int check_data();
	string gettime();
	//~UidContext();
};
void UidContext::update_data()
{
    //int total;
    uid_map_t uid_data;
	string record_time;
        /*测试*/
    infile.open("data.txt", ios::in);
    if(!infile.is_open ())
        cout << "Open file failure" << endl;

    infile >> record_time ;                               /*先读取第一行，读取时间*/
	
    infile >> total ;                               /*先读取第二行，读取后续条数*/
    cout << "total: " << total << " " << "time" << " " << record_time<< endl;
    int cnt = 0;
    uidmap.clear();	
    while ( total > cnt )
    {

        infile >> uid_data.id >> uid_data.id_map ;  /*读取实际数据*/

        pair<map<int, uid_map_t>::iterator, bool> ret;
        ret = uidmap.insert(pair<int, uid_map_t>(uid_data.id, uid_data));
        if(ret.second){
            cout<<"Insert Successfully: uid "<< uid_data.id <<endl;
		}
        else{
            cout<<"Insert Failure"<<endl;
			total =  cnt;
		}
        cnt ++;
    }
    infile.close();   //关闭文件

}
void UidContext::save_data(){

    outfile.open("data.txt", ios::out);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容

    if(!outfile.is_open())
        cout << "Open file failure" << endl;
	this->update_time = this->gettime();
	outfile << this->update_time <<  endl;
    outfile << total <<  endl;                                  /*在result.txt中写入结果*/
    map<int, uid_map_t>::iterator iter=uidmap.begin();
    for(iter = uidmap.begin(); iter != uidmap.end(); iter++)
    {
        cout<< (*iter).first <<" " <<endl;
        outfile << (*iter).first << "\t" << (*iter).second.id_map <<  endl;   /*在result.txt中写入结果*/
    }
    outfile.close();

}
int UidContext::check_data()
{
	string time;
	struct stat buf;
    infile.open("data.txt", ios::in);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容
	
    infile >> time ;                               /*先读取第一行，读取时间*/
	int ret = time.compare(this->update_time);
	//cout << "time " << time << endl;
	//cout << "update " << this->update_time << endl;
	//cout << "check_data " << ret << endl;
    infile.close();
//	FILE *fp;
//	fp = fopen("data.txt","r"); 
//	int fd = fileno(fp);
//	fstat(fd,&buf);
//	long time = buf.st_mtime;
//	cout << "time" << time << endl;
	return ret;

}
string UidContext::gettime()
{
    char buf[100];
	struct tm T;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &T);
	int millisecond = tv.tv_usec/1000;

	sprintf(buf, "%02d-%02d-%02d-%02d:%02d:%02d-%03d", T.tm_year+1900,T.tm_mon+1, T.tm_mday, T.tm_hour, T.tm_min, T.tm_sec, millisecond);
 
	return string(buf);
}

int main()
{

	UidContext *uidcon = new UidContext(); 
	uidcon->update_data();
	/*
	if (total <= 0){
		cout << "update file failed" << endl;
	}
	else{
		cout << "update file success"  << total << endl;
	}*/
	uidcon->save_data();
	while(1){
		if(uidcon->check_data()){
			cout << "update file" << endl;
			
			uidcon->update_data();
			uidcon->save_data();
		} 
		usleep(1000000);
	}
    return 0;
}
