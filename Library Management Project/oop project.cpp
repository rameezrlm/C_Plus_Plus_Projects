#include <iostream>
#include <fstream>
#include <windows.h>
#include "Library.h"
using namespace std;

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "======================================================" << endl;
	cout << "              LIBRARY MANAGEMENT SYSTEM               " << endl;
	cout << "======================================================" << endl;
	char* UniversityName = new char[50] {};
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "_\n" << endl;
	cout << "       Credit Goes To : Sir Malik Junaid Aziz           \n" << endl;
	cout << "_" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Grateful for Sir Junaid Aziz's exceptional guidance and teaching in the OOP (Object-Oriented Programming) course in C++. His expertise has been invaluable to our learning journey. " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "\n    ************** Developer Team **************" << endl << endl;
	cout << "Rameez Ali - L1F22BSCS0374\n" << endl;
	cout << "Numan Alvi - L1F22BSCS0440\n" << endl;
	cout << "Saad Sultan - L1F22BSCS0451\n" << endl;

	cout << "University Name: University of Central Punjab" << endl << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	system("pause");

	system("CLS");                             //Clear the screen and show main menu
	int option = 0;                            //For user input to start the program

	char* admission = new char[50];
	char* booknum = new char[50];
	while (true)
	{
	MainMenu:
		system("CLS");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "======================================================" << endl;
		cout << "                         MAIN MENU                    " << endl;
		cout << "======================================================" << endl;
		cout << "1. Book Issue\n2. Book Deposit\n3. Administrator Menu\n4. Exit" << endl;
		cout << "Please Select your Option (1-4): "; cin >> option;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Library Book(UniversityName, UniversityName, 0);
		if (option == 1)   //If user enters 1 then, Issue a book to student
		{

			cout << "Enter admission Number: "; cin >> admission;
			cout << "Enter Book Number: "; cin >> booknum;
			Library books(admission, booknum, 0);
			if (books.bookIssue())
			{
				cout << "Book Issued!" << endl; //if Book issued Succefully show information and then verfication message
			}

		}
		else if (option == 2)
		{
			int day = 0;
			cout << "Enter admission Number: "; cin >> admission;
			cout << "Enter Book Number: "; cin >> booknum;
			cout << "Book returned in days: "; cin >> day;
			Library book1(admission, booknum, day);
			if (book1.depositBook()) {
				cout << "Book deposited!" << endl; //if Book issued deposited show information and then verfication message
			}
		}
		else if (option == 3)
		{
			Library books(admission, booknum, 0);
			int choice = 0;
		admin:
			system("CLS");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "==================================================" << endl;
			cout << "              Administrator Menu                  " << endl;
			cout << "==================================================" << endl;
			cout << "1. Create Student Record" << endl;
			cout << "2. Display All Records" << endl;
			cout << "3. Display Specific Student Record" << endl;
			cout << "4. Modify Student Record" << endl;
			cout << "5. Delete Student Record" << endl;
			cout << "6. Create Book" << endl;
			cout << "7. Display All Books" << endl;
			cout << "8. Display Specific Book" << endl;
			cout << "9. Modify Book" << endl;
			cout << "10. Delete Book" << endl;
			cout << "11. Back to Main Menu" << endl;
			cout << "Enter Your Choice ";
			cin >> choice;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (choice == 1)
			{
				cin.ignore();
				char* id = new char[20] {};
				char* Name = new char[50] {};
				char* Uni = new char[50] {};
				char response;
				ofstream fout("student.txt", ios::app);
				if (!fout.is_open())
				{
					cout << "File Not Found!" << endl;
					system("pause");
					goto admin;
				}
				while (true)
				{
					cout << "Enter Student ID: "; cin.getline(id, 20);
					cout << "Enter Student Name: "; cin.getline(Name, 50);
					cout << "Enter Your University: "; cin.getline(Uni, 50);

					fout << id << " " << Name << "@ " << Uni << endl;
					cout << "Do you want to add more (y/n) : "; cin >> response;
					if (response == 'n' || response == 'N')
					{
						cout << " Student Added Successfully " << endl;
						system("pause");
						goto admin;
						break;
					}
					else
					{
						cout << "************************ New Entry ************************" << endl;
						cin.ignore();
					}
				}
				delete[] id;
				delete[] Name;
				delete[] Uni;
				id = nullptr;
				Name = nullptr;
				Uni = nullptr;
				fout.close();
			}
			else if (choice == 2)
			{
				system("CLS");
				books.displayRecord();
				system("pause");
				goto admin;
			}
			else if (choice == 3)
			{
				char* id = new char[20] {};
				cout << "Enter Student Id: ";
				cin >> id;
				Library search(id, UniversityName, 0);
				search.searchStudent();
				system("pause");
				goto admin;
			}
			else if (choice == 4)
			{
				char* id = new char[20] {};
				cout << "Enter Student Id: ";
				cin >> id;
				Library search(id, UniversityName, 0);
				cin.ignore();
				char* name = new char[50] {}; cout << "Enter New Name: "; cin.getline(name, 50);
				char* newid = new char[50] {}; cout << "Enter New Id: "; cin.getline(newid, 50);
				if (search.modifyStudent(newid, name))
				{
					cout << "Student Data Modified!" << endl;
				}
				system("pause");
				goto admin;
			}
			else if (choice == 5)
			{
				char* id = new char[20] {};
				cout << "Enter Student Id: ";
				cin >> id;
				Library search(id, UniversityName, 0);
				cin.ignore();
				if (search.deleteStudent())
				{
					cout << "Student Data Removed!" << endl;
				}
				system("pause");
				goto admin;
			}
			else if (choice == 6)
			{
				char test;
				char* bookId = new char[20] {};
				char* author = new char[30] {};
				char* bookName = new char[40] {};
				ofstream fout("Library.txt", ios::app);
				if (!fout.is_open())
				{
					cout << "File Not Found!" << endl;
					system("pause");
					goto admin;
				}
				while (true)
				{
					cout << "Enter Book Id: "; cin >> bookId; cin.ignore();
					cout << "Enter Book Author: "; cin.getline(author, 30);
					cout << "Enter Book Name: "; cin.getline(bookName, 40);

					fout << endl << bookId << " " << bookName << "@ " << author << endl;
					cout << "============================================" << endl;
					cout << "             Book Added !" << endl;
					cout << "============================================" << endl;
					cout << "Do  you Want to Add more (y/n) : "; cin >> test;
					if (test == 'n' || test == 'N')
					{
						system("pause");
						goto admin;
						break;
					}
				}
				fout.close();
			}
			else if (choice == 7)
			{
				Book.displayBooks();
				system("Pause");
				goto admin;
			}
			else if (choice == 8)
			{
				char* id = new char[4] {};
				cout << "Enter Book Number: "; cin >> id;
				Library BooksList(UniversityName, id);
				if (BooksList.searchBook()) {
					cout << "DATA DISPLAYED!" << endl;
				}
				else
				{
					cout << " Book Not Found " << endl;
				}
				system("pause");
				goto admin;
			}
			else if (choice == 9)
			{
				char* newbook = new char[40] {};
				char* newid = new char[30] {};
				char* author = new char[50] {};
				cout << "Enter Book Id: "; cin >> newid; cin.ignore();
				cout << "Enter Book Author: "; cin.getline(author, 30);
				cout << "Enter Book Name: "; cin.getline(newbook, 40);
				Library modify(newbook, newid, 0);
				if (modify.modifyBook(newbook, newid, author))
				{
					cout << "Book Modified!" << endl;
				}
				else
				{
					cout << " Book Not Found " << endl;
				}
				system("pause");
				goto admin;
			}
			else if (choice == 10)
			{
				char* id = new char[4] {};
				cout << "Enter Book Number: "; cin >> id;
				Library BooksList(UniversityName, id);
				if (BooksList.deleteBook()) {
					cout << "Book Deleted" << endl;
				}
				system("pause");
				goto admin;
			}
			else if (choice == 11)
			{
				goto MainMenu;
			}
		}
		else if (option == 4)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			cout << "====================================================" << endl;
			cout << "     Special Thanks to Sir Junaid Aziz              " << endl;
			cout << "====================================================" << endl;
			return 0;
		}
	}
	delete[] UniversityName;
	delete[] admission;
	delete[] booknum;

}