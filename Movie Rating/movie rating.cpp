#include <iostream>  // Console input and output
#include <fstream>   // For file input and output
using namespace std;

// Function to compare two character arrays (strings)
bool Compare(char*, char*);
// Function to get the length of a character array (string)
int GetLength(char*);

int main()
{
	// Display a header for the Movie Rating program
	cout << "---------------------------------------------------------" << endl;
	cout << "                         Movie Rating                    " << endl;
	cout << "---------------------------------------------------------" << endl;

	int Track = 1; // Variable to track iterations
	// Open an output file stream to write to "check.txt"
	ofstream fout("check.txt");

	// Allocate memory for character arrays to store movie names and matches
	char* MovieName = new char[50] {};
	char* match = new char[50] {};
	char* Name = new char[50];
	int rating = 0;

	// Open an input file stream to read from "movie.txt"
	ifstream fin("movie.txt");

	// Write movie names from "movie.txt" to "check.txt"
	while (fin.getline(MovieName, 50))
	{
		fout << MovieName << endl;
	}
	fin.close(); // Close the file

	// Reopen "movie.txt" for further processing
	fin.open("movie.txt");

	int Rating = 0; // Variable to store ratings
	double count = 0; // Counter for reviews
	double sum = 0; // Sum of ratings

	// Open an output file stream to write to "duplicate.txt"
	ofstream fout1("duplicate.txt");

	// Read movie names and ratings from "movie.txt"
	while (fin.getline(MovieName, 50))
	{
		int count = 0; // Reset the count for each movie
		fin >> rating; // Read the rating
		fin.ignore(); // Ignore the newline

		fout1.close(); // Close "duplicate.txt"

		// Open "duplicate.txt" to check for duplicate movie names
		ifstream fin3("duplicate.txt");
		while (fin3.getline(Name, 50))
		{
			// Check for a duplicate movie name
			if (Compare(Name, MovieName))
			{
				count++; // Increment count if a duplicate is found
				break;
			}
		}

		// If the movie is unique (no duplicates found)
		if (count == 0)
		{
			// Append the movie name to "duplicate.txt"
			fout1.open("duplicate.txt", ios::app);
			fout1 << MovieName << endl;

			// Open "check.txt" to calculate average ratings and reviews
			ifstream fin2("check.txt");
			while (fin2.getline(match, 50))
			{
				fin2 >> Rating; // Read rating
				fin2.ignore(); // Ignore newline

				// If the movie name matches, update sum and count
				if (Compare(MovieName, match))
				{
					sum = sum + Rating;
					count++;
				}
			}
			fin2.close(); // Close "check.txt"

			// Display the average rating and reviews count for the movie
			cout << "Average of Rating Of Movie " << MovieName << " is: " << sum / count << " and has " << count << " Reviews " << endl;
			cout << "\n\t\t*************************************\n" << endl;
			Track++; // Increment track
			sum = 0; // Reset sum for the next movie
			count = 0; // Reset count for the next movie
		}
	}

	// Deallocate memory and set pointers to nullptr to prevent memory leaks
	delete[] MovieName;
	delete[] match;
	delete[] Name;
	MovieName = nullptr;
	match = nullptr;
	Name = nullptr;
}

// Function to compare two character arrays (strings)
bool Compare(char* arr1, char* arr2)
{
	int len1 = GetLength(arr1);
	int len2 = GetLength(arr2);

	// Compare the lengths of the arrays
	if (len1 != len2)
	{
		return false;
	}
	else
	{
		// Compare characters of the arrays
		for (int i = 0; i < len1; i++)
		{
			if (arr1[i] != arr2[i] && arr1[i] != arr2[i]+32 && arr1[i] != arr2[i]-32)
			{
				return false; // If characters differ, return false
			}
		}
		return true; // Arrays are equal
	}
}

// Function to get the length of a character array (string)
int GetLength(char* arr)
{
	int count = 0;
	// Iterate until the null terminator is found
	for (int i = 0; arr[i] != '\0'; i++)
	{
		count++;
	}
	return count; // Return the length of the array
}
