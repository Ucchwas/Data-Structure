#include <iostream>
#include <cstring>
using namespace std;

int main ()
{
    string name,Fname,Lname;
    cout << "Enter full name (last,first): ";
    cin >> name;
    for(int i=0;i<name.size();i++)
    {
            if(name.at(i)==','){
                 Fname=name.substr(0,i);
                 Lname=name.substr(i+1);
            }
    }
    cout << "First name: " << Fname<<endl;
    cout << "Last name: " << Lname<<endl;
//    system("pause");
}
