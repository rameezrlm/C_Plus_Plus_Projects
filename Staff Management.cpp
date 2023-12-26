#include <iostream>
#include <fstream>
using namespace std;
void print(ifstream& fin);
void read(ofstream& fout,char* arr);
bool cmp(char* arr1,char* arr2);
int length(char* arr1);
void search(char* name);
void delete_row(char* name);
void display_all();

int main ()
{
	cout<<"================================================================"<<endl;
	cout<<"                          MENU                                  "<<endl;
	cout<<"                    1.  Add more Staff                          "<<endl;
	cout<<"                    2.  Search Staff Info                       "<<endl;
	cout<<"                    3.  Delete Staff Info                       "<<endl;
	cout<<"                    4.  Print Data                              "<<endl;
	cout<<"                    5.  Print Contacts                          "<<endl;
	cout<<"                    6.  Exit                                    "<<endl;
	cout<<"================================================================"<<endl;
     while (true)
     {
     	int choice;
     	cout<<"Enter Your choice< ";
     	cin>>choice;
     	cin.ignore();
     	if(choice==6)
     	{
     		cout<<"You Exited";
     		return 0;
		}
		else if(choice==1)
		{
		char* arr=new char[100];
		ofstream fout("input.txt",ios::app);
	    read(fout,arr);
		}
		else if(choice==2)
		{
			char name[50];
			cout<<"Enter Name to Search Contact and gmail: ";
	        cin.getline(name,50);
            search(name);
		}
		else if(choice==3)
		{
	          char name[50];
			cout<<"Enter Name to Delete its Contact and gmail: ";
	        cin.getline(name,50);
            delete_row(name);
		}
		else if(choice==4)
		{
	ifstream fin("input.txt");
	print(fin);
		}
		else if(choice==5)
		{
		    display_all();	
		}		 
	}
}
void print(ifstream& fin)
{
	char* arr=new char[100];
	while(fin.getline(arr,100))
	{
		cout<<arr<<endl;
	}
	delete[] arr;
	fin.close();
}
void read(ofstream& fout,char* arr)
{
	cout<<"Enter Record (name, gmail, phone number)>: ";
	cin.getline(arr,50);
	fout<<arr<<endl;
	fout.close();
}
bool cmp(char* arr1,char* arr2)
{
	int l1,l2;
	l1=length(arr1);
	l2=length(arr2);
	if(l1!=l2)
	{
		return false;
	}
	else
	{
		for(int i=0;i<l1;i++)
		{
			if(arr1[i]!=arr2[i] && arr1[i]!=arr2[i]+32 && arr1[i]!=arr2[i]-32)
			{
				return false;
			}
		}
		return true;
	}
}
int length(char* arr1)
{
	int len=0;
	for(int i=0;arr1[i]!='\0';i++)
	{
		len++;
	}
	return len;
}
void search(char* name)
{
	char* arr=new char[30];
	char* waste=new char[50];
	ifstream fin("input.txt");
	int count=0;
	while(fin.getline(arr,30,','))
	{
		fin.getline(waste,50);
		if(cmp(name,arr))
	    {
	    	cout<<name<<", "<<waste<<endl;
		    count++;
		}
	}
	if(count==0)
	{
		cout<<"No Record Found";
	}
}
void delete_row(char* name)
{
	char* arr=new char[50];
	char* waste=new char[50];
	ifstream fin("input.txt");
	int count=0;
	int loc=-1;
	while(fin.getline(arr,50,','))
	{
		fin.getline(waste,50);
		count++;
		if(cmp(name,arr))
	    { 
	      loc=count;
		}
	}
    count=0;
    fin.close();
    if(loc==-1)
    {
    	cout<<"No Match Found! ";
	}
	else
	{
		fin.open("input.txt",ios::in);
    ofstream fout("Copy.txt");
   	while(fin.getline(arr,50))
	{
		count++;
		if(count!=loc)
		{
			fout<<arr<<endl;
		}
	}
	fout.close();
	ifstream fin1("Copy.txt");
	ofstream fout1("input.txt");
	   	while(fin1.getline(arr,50))
	{
      fout1<<arr<<endl;
	}
	cout<<"Data Removed! "<<endl;
	}
}
void display_all()
{
	ifstream fin("input.txt");
	char waste[50];
	char contact[30];
	while(fin.getline(waste,50,','))
	{
		fin.getline(waste,50,',');
		fin.getline(contact,50);
		cout<<contact<<endl;
	}
	fin.close();
}
