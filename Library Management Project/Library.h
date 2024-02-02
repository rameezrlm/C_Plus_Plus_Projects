#pragma once
#include <iostream>
#include <fstream>
using namespace std;
void copy(char*, char*);
bool cmp(char*, char*);
int len(char*);
class Library
{
protected:
	char* admissionNumber;
	char* bookNumber;
	int days;
public:
	Library()
	{
		days = 0;
		bookNumber = nullptr;
		admissionNumber = nullptr;
	}
	Library(char* Adnumber = new char[50], char* booknum = new char[50],int day=0)
	{
		admissionNumber = new char[50] {};
		copy(admissionNumber, Adnumber);
		bookNumber = new char[50] {};
		copy(bookNumber, booknum);
		days = day;
	}
	bool bookIssue()
	{
		char* id=new char[50];
		char* bookName=new char[50];
		char* authorName=new char[50];
		char* studentName = new char[50] {};
		char* uni = new char[30] {};
		bool flag = false;
		bool isFound=false;
		ifstream fin("student.txt");
		while (fin >> id)
		{
			fin.ignore();
			fin.getline(studentName, 50,'@');
			fin.getline(uni, 50);
			if (cmp(id, admissionNumber)) {
				flag = true;
				break;
			}
		}
		fin.close();
		ofstream fout;
		if (flag == true)
		{
			fin.open("Library.txt");
			while (fin >> id)
			{
				fin.ignore();
				fin.getline(bookName, 50, '@');
				fin.getline(authorName, 50);
				if (cmp(id, bookNumber))
				{
					ifstream read("BookIssued.txt");
					fout.open("BookIssued.txt",ios::app);
					cout << "============================================" << endl;
					cout << "Student Id: " << admissionNumber << "\nBook Id: " << bookNumber << "\nBook Name: " << bookName << "\nBook Author: " << authorName << endl;
					cout << "============================================" << endl;
					fout << bookNumber << " " << admissionNumber << endl;
					fout.close();
					isFound = true;
					break;
				}
			}
			fin.close();
			if (isFound == false)
			{
				cout << "Book Not Found!" << endl;
				delete[] id;
				delete[] bookName;
				delete[] authorName;
				return false;
			}
		}
		else
		{
			cout << "Student Not Found!" << endl;
			delete[] id;
			delete[] bookName;
			delete[] authorName;
			return false;
		}
		return true;
	}

	bool depositBook()
	{
		char* booknum = new char[50] {};
		char* studentid = new char[50] {};
		ifstream fin("BookIssued.txt");
		ofstream print("copy.txt");
		bool flag = false;
		while (fin >> booknum)
		{
			fin >> studentid;
			if (cmp(booknum, bookNumber) && cmp(studentid,admissionNumber))
			{
				flag = true;
				continue;
			}
			print << booknum << " " << studentid << endl;
		}
		print.close();
		fin.close();
		if (flag == true)
		{
			fin.open("copy.txt");
			print.open("BookIssued.txt");
			while (fin >> booknum)
			{
				fin >> studentid;
				print << booknum << " " << studentid << endl;
			}
			fin.close();
			print.close();
			if (days > 10) {
				int finePerDay = days - 10;
				cout << "Fine: " << finePerDay * 10 << endl;
			}
			else {
				cout << "Book return no fine Is charged!" << endl;
				return true;
			}
		}
		else
		{
			cout << "Book was not issued by this Id!" << endl;
			return false;
		}
		return false;
	}

	void displayRecord()
	{
		char* id = new char[20] {};
		char* name = new char[50] {};
		char* uni = new char[50] {};
		char* bookid = new char[5];
		char* studentid = new char[10] {};
		cout << "================================================" << endl;
		cout << "Id   Student Name    University    Book Issued " << endl;
		cout << "================================================" << endl;
		ifstream read("student.txt");
		while (read >> id)
		{
			read.ignore();
			read.getline(name, 50, '@');
			read.getline(uni, 50);
			bool flag = false;
			ifstream fin("BookIssued.txt");
			while (fin >> bookid)
			{
				fin >> studentid;
				if (cmp(studentid, id))
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
			{
				cout << id << "\t" << name << "\t" << uni << "\t" << 1 << endl;
			}
			else
			{
				cout << id << "\t" << name << "\t" << uni << "\t" << 0 << endl;
			}
			fin.close();
		}
		read.close();
	}

	void searchStudent()
	{
		char* id = new char[20] {};
		char* name = new char[50] {};
		char* uni = new char[50] {};
		ifstream read("student.txt");
		bool flag = false;
		while (read >> id)
		{
			read.ignore();
			read.getline(name, 50, '@');
			read.getline(uni, 50);

			if (cmp(id, admissionNumber))
			{
				flag = true;
				cout << "=====================================" << endl;
				cout << "Student Id: " << id << endl;
				cout << "Name is: " << name << endl;
				cout << "University: " << uni << endl;
				cout << "=====================================" << endl;
			}
			
		}
		if (flag == false)
		{
			cout << "_________ No Student Found!!! _________" << endl;
		}
		read.close();
	}
	bool modifyStudent(char* newId,char* newName)
	{
		char* id = new char[20] {};
		char* name = new char[50] {};
		char* uni = new char[50] {};
		ifstream read("student.txt");
		ofstream fout("copy.txt");
		bool flag = false;
		while (read >> id)
		{
			read.ignore();
			read.getline(name, 50, '@');
			read.getline(uni, 50);
			if (cmp(id, admissionNumber))
			{
				flag = true;
				fout << newId << " " << newName << "@" << uni << endl;
				continue;
			}
			fout << id << " " << name << "@" << uni << endl;
		}
		fout.close();
		read.close();
		if (flag == false)
		{
			cout << "_________ No Student Found!!! _________" << endl;
			return false;
		}
		else
		{
			read.open("copy.txt",ios::in);
			fout.open("student.txt",ios::out);
			bool flag = false;
			while (read >> id)
			{
				read.ignore();
				read.getline(name, 50, '@');
				read.getline(uni, 50);
				fout << id << " " << name << "@ " << uni << endl;
			}
		}
		read.close();
		fout.close();
		return true;
	}
	bool deleteStudent()
	{
		char* id = new char[20] {};
		char* name = new char[50] {};
		char* uni = new char[50] {};
		ifstream read("student.txt");
		ofstream fout("copy.txt");
		bool flag = false;
		while (read >> id)
		{
			read.ignore();
			read.getline(name, 50, '@');
			read.getline(uni, 50);
			if (cmp(id, admissionNumber))
			{
				flag = true;
				continue;
			}
			fout << id << " " << name << "@" << uni << endl;
		}
		fout.close();
		read.close();
		if (flag == false)
		{
			cout << "_________ No Student Found!!! _________" << endl;
			return false;
		}
		else
		{
			read.open("copy.txt", ios::in);
			fout.open("student.txt", ios::out);
			bool flag = false;
			while (read >> id)
			{
				read.ignore();
				read.getline(name, 50, '@');
				read.getline(uni, 50);
				fout << id << " " << name << "@ " << uni << endl;
			}
		}
		read.close();
		fout.close();
		return true;
	}
	void displayBooks()
	{
		char* bookId = new char[6] {};
		char* author = new char[40] {};
		char* name = new char[50] {};
		ifstream fin("Library.txt");
		cout << "================================================" << endl;
		cout << "Book Id            Book Name              Author" << endl;
		cout << "================================================" << endl;
		while (fin >> bookId) {
			fin.ignore();
			fin.getline(name, 50,'@');
			fin.getline(author, 40);
			cout << bookId <<"\t" <<name <<"      "<<author<< endl;
		}
		fin.close();
	}
	bool searchBook()
	{
		char* bookId = new char[6] {};
		char* author = new char[40] {};
		char* name = new char[50] {};
		ifstream fin("Library.txt");
		cout << "================================================" << endl;
		cout << "Book Id            Book Name              Author" << endl;
		cout << "================================================" << endl;
		bool flag = false;
		while (fin >> bookId) 
		{
			fin.ignore();
			fin.getline(name, 50, '@');
			fin.getline(author, 40);
			if (cmp(bookId, bookNumber))
			{
				cout << bookId << "\t" << name << "\t\t" << author << endl;
				flag = true;
			}
		}
		if (flag == false)
		{
			return false;
		}
		else {
			return true;
		}
		fin.close();
	}
	bool deleteBook()
	{
		char* bookId = new char[6] {};
		char* author = new char[40] {};
		char* name = new char[50] {};
		ifstream fin("Library.txt");
		ofstream fout("copy.txt");
		bool flag = false;
		while (fin >> bookId)
		{
			fin.ignore();
			fin.getline(name, 50, '@');
			fin.getline(author, 40);
			if (cmp(bookId, bookNumber))
			{
				flag = true;
				continue;
			}
			fout << bookId << " " << name << "@ " << author << endl;
		}
		fin.close();
		fout.close();
		if (flag == false)
		{
			return false;
		}
		fout.open("Library.txt",ios::out);
		fin.open("copy.txt",ios::in);
		flag = false;
		while (fin >> bookId)
		{
			fin.ignore();
			fin.getline(name, 50, '@');
			fin.getline(author, 40);
			fout << bookId << " " << name << "@ " << author << endl;
		}
		fin.close();
		fout.close();
		return true;
	}
	bool modifyBook(char* newbook,char* newid,char* newauthor)
	{
		char* bookId = new char[6] {};
		char* author = new char[40] {};
		char* name = new char[50] {};
		ifstream fin("Library.txt");
		ofstream fout("copy.txt");
		bool flag = false;
		while (fin >> bookId)
		{
			fin.ignore();
			fin.getline(name, 50, '@');
			fin.getline(author, 40);
			if (cmp(bookId, bookNumber))
			{
				fout << newid << " " << newbook << "@ " << newauthor << endl;
				flag = true;
				continue;
			}
			fout << bookId << " " << name << "@ " << author << endl;
		}
		if (flag == false)
		{
			return false;
		}
		fin.close();
		fout.close();

		fout.open("Library.txt", ios::out);
		fin.open("copy.txt", ios::in);
		while (fin >> bookId)
		{
			fin.ignore();
			fin.getline(name, 50, '@');
			fin.getline(author, 40);
			fout << bookId << " " << name << "@ " << author << endl;
		}
		fin.close();
		fout.close();
		return true;
	}
};
void copy(char* arr1, char* arr2)
{
	int i = 0;
	for (i = 0; arr2[i] != '\0'; i++)
	{
		arr1[i] = arr2[i];
	}
	arr1[i] = '\0';
}
bool cmp(char* arr1, char* arr2)
{
	int len1 = len(arr1);
	int len2 = len(arr2);
	if (len1 != len2)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < len1; i++)
		{
			if (arr1[i] != arr2[i] && arr1[i] != arr2[i] + 32 && arr1[i] != arr2[i] - 32) {
				return false;
			}
		}
		return true;
	}
}
int len(char* arr)
{
	int count = 0;
	for (int i = 0; arr[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}