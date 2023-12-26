#include <iostream>
#include <fstream>
using namespace std;

void input_easy(char** arr, int row, int col);
void input_medium(char** arr, int row, int col);
void input_hard(char** arr, int row, int col);
void print(char** arr, int row, int col);
bool up(char** arr, int& current_row, int& current_col, int row, int col);
bool down(char** arr, int& current_row, int& current_col, int row, int col);
bool right(char** arr, int& current_row, int& current_col, int row, int col);
bool left(char** arr, int& current_row, int& current_col, int row, int col);
void updatefile(char** arr, int row, int col, char filename[]);
char** dynamic(int row, int col);
void read_stat(char arr[], int size);

int main()
{
    int row = 6, col = 6;

    cout << "\t  __  __ ____   ___  _     ___  ____  _     _____" << endl;
    cout << "\t |  \\/  / ___| / _ \\| |   / _ \\/ ___|| |   | ____|" << endl;
    cout << "\t | |\\/| \\___ \\| | | | |  | | | \\___ \\| |   |  _|" << endl;
    cout << "\t | |  | |___) | |_| | |__| |_| |___) | |___| |___ " << endl;
    cout << "\t |_|  |_|____/ \\___/|_____\\___/|____/|_____|_____|" << endl;
    cout << endl;
    cout << "\t===============================================" << endl;
    cout << "\t                Maze Runner Game                " << endl;
    cout << "\t===============================================" << endl << endl;
    cout << "|-------------------------------------------------------------|" << endl;
    cout << "|                 READ INSTRUCTION CAREFULLY                  |" << endl;
    cout << "|-------------------------------------------------------------|" << endl << endl << endl;
    cout << "+ is MONSTER , | is Blockage of Path , Complete path by Following * Symbol" << endl;
    cout << endl << endl << endl;

    char** path = dynamic(row, col);
    char game;
    cout << "Press S to Start" << endl;
    cout << "Press X to Exit" << endl;
    cout << "Enter you choice: ";
    cin >> game;
    system("CLS");
    if (game == 'X' || game == 'x')
    {
        cout << endl;
        cout << "\tGAME FINISHED" << endl;
        return 0;
    }
    else
    {
        while (true)
        {
            int i;
            int score = 0;
            char name[20];
            char mode;
            cout << endl << "===============================================" << endl;
            cout << "Enter Your Name with .txt: ";
            cin >> name;
            cout << "===============================================" << endl;
            cout << "===============================================" << endl;
            cout << "Press E for Easy" << endl;
            cout << "Press M for Medium" << endl;
            cout << "Press H for Hard" << endl;
            cout << "Press X to Exit" << endl;
            cout << "Press S to See Statistics" << endl;
            cout << "Press P to Pause" << endl;
            cout << "===============================================" << endl;
            cin >> mode;
            system("CLS");
            if (mode == 'x' || mode == 'X')
            {
                cout << "Thanks for Coming";
                return 0;
            }
            else if (mode == 'e' || mode == 'E')
            {
                input_easy(path, row, col);
            }
            else if (mode == 'm' || mode == 'M')
            {
                input_medium(path, row, col);
            }
            else if (mode == 'H' || mode == 'h')
            {
                input_hard(path, row, col);
            }
            else if (mode == 's' || mode == 'S')
            {
                char arr[50];
                int size = 50;
                read_stat(arr, size);
                continue;
            }
            else
            {
                cout << endl << "Invalid!" << endl;
                continue;
            }
            cout << "Given MAP::\n";
            print(path, row, col);
            cout << endl;
            int current_row = row - 1;
            int current_col = col - 1;
            char move;
            cout << endl << "Game Will Start From left bottom Corner:: " << endl;
            bool isPaused = false;
            for (int chance = 0; chance < 3; chance++)
            {
                cout << "(((((((((((((((" << chance + 1 << " Attempt)))))))))))))))" << endl;
                for (i = 0; i < 13; i++)
                {
                    if (isPaused)
                    {
                        cout << "Game Paused" << endl;
                        cout << "Press C to continue: " << endl;
                        char res;
                        cin >> res;
                        if (res == 'c' || res == 'C')
                        {
                            isPaused = false;
                            i--;
                            continue;
                        }
                        else
                        {
                            cout << "Invalid" << endl;
                        }
                    }
                    cout << "\nEnter U: up & L: Left & R: Right & D: Down(if you have move cannot come back): ";
                    cin >> move;
                    bool success = false;
                    if (i == 0 && (move == 'U' || move == 'u'))
                    {
                        success = true;
                        path[current_row][current_col] = '1';
                    }
                    else if (move == 'U' || move == 'u')
                    {
                        success = up(path, current_row, current_col, row, col);
                    }
                    else if (move == 'L' || move == 'l')
                    {
                        success = left(path, current_row, current_col, row, col);
                    }
                    else if (move == 'R' || move == 'r')
                    {
                        success = right(path, current_row, current_col, row, col);
                    }
                    else if (move == 'D' || move == 'd')
                    {
                        success = down(path, current_row, current_col, row, col);
                    }
                    else if (move == 'p' || move == 'P')
                    {
                        char res='$';
                        while (res != 'c' && res != 'C')
                        {
                            cout << "Game Paused" << endl;
                            cout << "Press C to continue: " << endl;
                            cin >> res;
                            if (res != 'c' && res != 'C')
                            {
                                cout << "Invalid" << endl;
                            }
                            else
                            {
                                break;
                            }
                        }
                        continue;
                    }
                    else
                    {
                        cout << "Invalid move. Please try again." << endl;
                    }
                    if (i >= 12 || (current_row == 0 && current_col == 0))
                    {
                        system("CLS");
                        print(path, row, col);
                        cout << "::Congratulations! You have completed all moves and Scored with 2 Bonus points::" << endl;
                        score += 2;
                        cout << endl << "Your Score is: " << score << endl;
                        ofstream fout2("stat.txt", ios::app);
                        for (int i = 0; name[i] != '.'; i++)
                        {
                            fout2 << name[i];
                        }
                        fout2 << " " << score << endl;
                        fout2.close();
                        break;
                    }
                    else if (success)
                    {
                        cout << "Nice Job!" << endl;
                        score++;
                        system("CLS");
                        print(path, row, col);
                        updatefile(path, row, col, name);
                    }
                    else if (isPaused)
                    {
                        continue;
                    }
                    else
                    {
                        system("CLS");
                        print(path, row, col);
                        cout << "::You Lose::" << endl;
                        break;
                    }
                }
                if ((current_row == 0 && current_col == 0))
                {
                    cout << "YOU COMPLETED IN 1ST ATTEMPT" << endl;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < row; i++)
    {
        delete[] path[i];
    }
    delete[] path;
    path = nullptr;
    return 0;
}
void input_easy(char** arr, int row, int col)
{
    ifstream fin("easy.txt");
    if (!fin.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            fin >> arr[r][c];
        }
    }

    fin.close();
}
void input_medium(char** arr, int row, int col)
{
    ifstream fin("medium.txt");
    if (!fin.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            fin >> arr[r][c];
        }
    }

    fin.close();
}
void input_hard(char** arr, int row, int col)
{
    ifstream fin("hard.txt");
    if (!fin.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            fin >> arr[r][c];
        }
    }
    fin.close();
}
void print(char** arr, int row, int col)
{
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            cout << arr[r][c] << " ";
        }
        cout << endl;
    }
}

void updatefile(char** arr, int row, int col, char filename[])
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            fout << arr[r][c] << " ";
        }
        fout << endl;
    }

    fout.close();
}

bool up(char** arr, int& cr, int& cc, int row, int col)
{
    if (cr - 1 >= 0 && arr[cr - 1][cc] == '*')
    {
        arr[cr - 1][cc] = '1';
        cr--;
        return true;
    }
    else
    {
        return false;
    }
}

bool left(char** arr, int& cr, int& cc, int row, int col)
{
    if (cc - 1 >= 0 && arr[cr][cc - 1] == '*')
    {
        arr[cr][cc - 1] = '1';
        cc--;
        return true;
    }
    else
    {
        return false;
    }
}

bool right(char** arr, int& cr, int& cc, int row, int col)
{
    if (cc + 1 < col && arr[cr][cc + 1] == '*')
    {
        arr[cr][cc + 1] = '1';
        cc++;
        return true;
    }
    else
    {
        return false;
    }
}

bool down(char** arr, int& cr, int& cc, int row, int col)
{
    if (cr + 1 < row && arr[cr + 1][cc] == '*')
    {
        arr[cr + 1][cc] = '1';
        cr++;
        return true;
    }
    else
    {
        return false;
    }
}
char** dynamic(int row, int col)
{
    char** temp = new char* [row];
    for (int i = 0; i < row; i++)
    {
        temp[i] = new char[col];
    }
    return temp;
}
void read_stat(char arr[], int size)
{
    ifstream fin("stat.txt");
    if (!fin.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }
    while (fin.getline(arr, size))
    {
        cout << arr << endl;
    }
    fin.close();
}
