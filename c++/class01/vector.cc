#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct uidmap
{
	int id;
	int id_map;
	int length;
	//对于向量元素是结构体的，可在结构体内部定义比较函数，下面按照id,length,width升序排序。
	bool operator< (const uid_map &a)  const
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

int main()
{
	vector<uid_map_t> vec_data;
	/**/
	int total;
	int uid,uid_map;
	ifstream infile;  //输入流
	ofstream outfile; //输出流	
	/*end*/


	/*测试*/
	infile.open("data.txt", ios::in); 
    if(!infile.is_open ())
        cout << "Open file failure" << endl;
  	uid_map_t uid_data;
    infile >> total ;                               /*先读取第一行，读取后续条数*/
    cout << "total:" << total<< endl;
	int cnt = total;
    while ( 0 != cnt )           
    {
    	infile >> uid_data.id >> uid_data.id_map ;  /*读取实际数据*/
		vec_data.push_back(uid_data);
		cnt --;
    }
 
    infile.close();   //关闭文件



	vector<uid_map_t>::iterator it=vec_data.begin();

	for(it = vec_data.begin(); it!= vec_data.end(); ++it)
		cout<< (*it).id <<" " << (*it).id_map <<endl;
	sort(vec_data.begin(),vec_data.end());

    outfile.open("data.txt", ios::out);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容
    if(!outfile.is_open())
        cout << "Open file failure" << endl;
		
   	outfile << total <<  endl;  								/*在result.txt中写入结果*/
	for(it = vec_data.begin(); it!= vec_data.end(); ++it){
    	outfile << (*it).id << "\t" << (*it).id_map <<  endl;   /*在result.txt中写入结果*/
	}

    outfile.close();


	return 0;
}
