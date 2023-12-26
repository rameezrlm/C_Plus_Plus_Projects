/**************************************************************
*            University Of Central Punjab                     *
             Submitted By: RAMEEZ ALI
             Submitted to: Sir Imran Arshad
             Section: B17
**************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
    
    cout<<"\t\t+---------------+"<<endl;
    cout<<"\t\t¦    Welcome\t¦"<<endl;
    cout<<"\t\t+---------------+"<<endl;
    cout << "\t*************************************" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*          Employee System          *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*************************************" << endl;
    ofstream fout("employee.txt");
    if(!fout.is_open())
    {
    	cout<<"File Not Found"<<endl;
	}
	else
	{
    fout<<"Ahsan Khan,50000,IT\nAlia Shams,60000,Management\nNajam ul Saqib,30000,Sales\nAhmer Javed,50000,HR\n";
    fout.close();
    } 
    while (true)
    {
        cout<<endl;
        cout<<"+==================================================+"<<endl;
        cout<<"1. Press 'S': To add Record                        |" << endl;
        cout<<"2. Press 'P': To Display All Record                |" << endl;
        cout<<"3. Press 'E': To Display Maximum Salary Holder     |" << endl;
        cout<<"4. Press 'D': Department wise searching            |" << endl;
        cout<<"5. Press 'R': Remove A person whose going to leave |" << endl;
        cout<<"6. Press 'X': To Exit                              |" << endl;
        cout<<"+==================================================+"<<endl;
        char choice;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();
        if (choice=='X' || choice=='x')
        {
        	cout<<endl<<endl;
            cout<<"'''''''''''''''''''''''''''"<<endl;
			cout<<"|  Exit Successfully      |"<<endl;
			cout<<"'''''''''''''''''''''''''''" << endl;
            return 0;
        }
        else if (choice == 'S' || choice == 's')
        {
            fout.open("employee.txt", ios::app);
            char arr[50];
            cout<<"Enter Data to Add Seprated by space(name,salary,department)"<<endl;
            cout<<"Employee,Salary,Department"<<endl;
            for (int i=0;i<5;i++)
            {
                cin.getline(arr, 50);
                fout <<arr<<endl;
            }
            fout.close();
            cout<<endl<<"Record Added Successfully!"<<endl;
        }
        else if (choice=='P' || choice=='p')
        {
            ifstream fin("employee.txt");
            char name[50];
            cout<<"EMPLOYEE,SALARY,DEPARTMENT"<<endl;
            while (fin.getline(name,50,'\n'))
            {
                cout<< name<<endl;
            }
            fin.close();           	
			}
        else if(choice=='E' || choice=='e')
        {
           char arr[50];
           ifstream fin("employee.txt");
           if (!fin.is_open())
            {
                cout<<"File Not Found";
                return 1;
            }
           int num[50]={};
           int i = 0;
           while(fin.getline(arr,50,','))
          {
            fin>>num[i];
            fin.ignore();
            fin.getline(arr,50);
            i++;
          }
          fin.close();
          int max_loc=0;
          int max=num[0];
          for(int j=0;j<i;j++)
          {
            if(max<num[j])
            {
              max=num[j];
              max_loc=j;
            }
          }
        fin.open("employee.txt");
        if (!fin.is_open())
            {
                cout<<"File Not Found";
                return 1;
            }
        char name[50],dep[50];
        cout<<"Maximum :";
        i=0;
        while(fin.getline(name,50,','))
        {
          fin>>num[i];
          fin.ignore();
          fin.getline(dep,50);
          if(num[i]==max)
          {
            cout<<name<<" "<<num[i]<<" "<<dep<<endl;
          }
          i++;
        }
       fin.close();
	    }
	    else if(choice=='D' || choice=='d')
	    {
	      int len1=0,count=0;
    char department[50] = {};
    cout << "Enter Department to search: ";
    cin >> department;
    while (department[len1] != '\0')
    {
        len1++;
    }
    char name[50] = {}, dep[50] = {};
    int num;
    bool found = false; // initialize found flag to false

    ifstream fin("employee.txt");
    while (fin.getline(name, 50, ','))
    {
        fin >> num;
        fin.ignore();
        fin.getline(dep, 50, '\n');

        int len2 = 0;
        while (dep[len2] != '\0')
        {
            len2++;
        }
        if (len1 != len2)
        {
            found = false;
        }
        else
        {
            found = true;
            for (int i = 0; i < len1; i++)
            {
                if (department[i] != dep[i])
                {
                    found = false;
                    break;
                }
            }
        }
        if (found)
        {
            cout << name << " " << num << " " << dep << endl;
            count++;
        }
    }
    fin.close();
    if(count==0)
    {
    if (!found)
    {
        cout << "Department not found." << endl;
    }
	}
        }
        //Searching Ends Here
        else if(choice=='R'||choice=='r')
        {
    char search[90];
    int length=0;
    bool found=false;
    bool flag=false;
    int loc=0;
    cout<<endl<< "Enter data of person who is going to leave in format(name,salary,department): " << endl;
    cin.getline(search, 90);
    while (search[length] != '\0')
    {
        length++;
    }
    for (int i=0;i<length;i++)
    {
        if (search[i]>='a'&&search[i]<='z')
        {
            search[i]=search[i] - 32;
        }
    }

    ifstream fin("employee.txt");
    ofstream fout("newfile.txt");
    char name[90];
    while (fin.getline(name, 90))
    {
        int i=0;
        length=0;
        flag=false;
        while (name[length]!='\0')
        {
            length++;
        }
        for (int i = 0; i < length; i++)
        {
            if (name[i] >= 'a' && name[i] <= 'z')
            {
                name[i]=name[i]-32;
            }
        }
        i=0;
        bool skip=false;
        while (i<length && search[i]!='\0')
        {
            if (search[i]!=name[i])
            {
                flag=false;
                skip=false;
                break;
            }
            flag = true;
            i++;
        }

        if(flag&&i==length && search[i]=='\0') 
        {
            found=true;
            skip=true;
            cout<<"User with data (" << name << ")"<<" has been removed"<<endl;
        }
        if(!skip)
        {
            fout<<name<<endl;
        }
    }

    if(!found)
    {
        cout << endl << "Not Found // Or you may not have followed the format(name,salary,department)" << endl;
    }
    fin.close();
    fout.close();
    }
		//User To leave
		else
		{
			cout<<"''''''''''Invalid!''''''''''''"<<endl;
		}
        cout << "Do you want to see the menu again? (y/n) ";
        char response;
        cin >> response;
        if (response == 'n' || response == 'N') 
		{
			cout<<endl<<"''''''''Exited Successfully! Thanks for cooperation''''''''''";
            break;
        }
        cin.ignore();
    }
    system("pause");
	return 0;
}
