#include <iostream>
#include <cstring>
#include<string.h>

using namespace std;

int main()
{
     char* s=new char[4];
         s[0]='-3';
         s[1]='3';
         s[2]='-2';
         s[3]='33';
    for (int iterator = 0; iterator <4; iterator++)
    cout <<atoi(s) << endl;
    return 0;
}
