#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sys/time.h>
#include <list>
#include <vector>

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>

using namespace std;
int main(){
	cout << "hello c++" <<endl;
	list<int> mylist;
	list<int>::iterator it;
	it =  mylist.begin();
	++it;
	it =  mylist.insert(it,10);
	it =  mylist.insert(it,2,30);
	--it;
	for(it=mylist.begin(); it!=mylist.end(); ++it)	
		cout << " " << *it;
	cout<<'\n';

	return 0;
}
