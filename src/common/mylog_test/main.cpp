#include "mylog.h"

using mylog::cout;

int main()
{
	cout.set_log_file("./testa.txt");
	
	cout<<"this is a test:\n";
	
	return 0;
}