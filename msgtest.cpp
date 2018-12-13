#include <iostream>
#include<stdlib.h>  //atoi
#include <stdio.h>  //sprintf
#include<string>
#include<string.h> // strcpy

using namespace std;

char m_cBufferSS[20];

void ff(std::string a_strTab)
{
    strcpy (m_cBufferSS,a_strTab.c_str()  );    //copy string param to char array Buffer

    char index1[2];
    index1[0]=m_cBufferSS[0];
    index1[1]='\0';
    int intindex1= atoi (index1);    //char array number to int
    intindex1*=100;

    char index2[3];
    index2[0]=m_cBufferSS[2];
    index2[1]=m_cBufferSS[3];
    index2[2]='\0';
    int intindex2= atoi (index2);

    intindex1+=intindex2;

    char msg[6];
    sprintf(msg,"%d",intindex1);    //converts int to hexadecimal base char array

    cout<<msg<<endl;

}



int main()
{
    string mojstring("1023");
        cout << "zamienione " << mojstring<<" :" << endl;
    ff(mojstring);

    return 0;
}

