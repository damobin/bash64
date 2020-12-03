#include <bash64.h>
#include <public.h>
#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	BASH64 bash64("qq286711902@163.com");
	cout << "start main" << endl;
	bash64.bashfun();
	cout <<bash64;
	bash64.rebashfun();
	cout <<bash64;	
	return 0;
}