#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    char word[50];
    char string[100];
    int word_len = 0;
    int string_len = 0;
    bool found = false;
    bool misspelled = false;
    cout << "Enter Message: ";
    cin.getline(string, 100);
    ofstream fout("user.txt");
    fout << string;
    fout.close();
    ifstream fin_dic("dictionary.txt");
    ifstream fin_user("user.txt");
    while (fin_user >> string)
    {
        string_len = 0;
        for (int i = 0; string[i] != '\0'; i++)
        {
            string_len++;
        }
        found = false;
        misspelled = true;
        fin_dic.close();
        fin_dic.open("dictionary.txt");
        while (fin_dic >> word)
        {
            word_len = 0;
            for (int i = 0; word[i] != '\0'; i++)
            {
                word_len++;
            }
            if (string_len != word_len)
            {
                //NOTHING TO DO
            }
            else
            {
                bool match = true;
                for (int i = 0; i < word_len; i++)
                {
                    if (string[i] != word[i])
                    {
                        match = false;
                        break;
                    }
                }
                if (match==true)
                {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
        {
            cout << "Misspelled Word: " << string << endl;
            misspelled = true;
        }
        else
        {
            misspelled = false;
        }
    }
    if(!misspelled)
    {
        cout<<"No Misspelled Word Found";
    }
    return 0;
}

