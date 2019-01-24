#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstring>
#include <fstream>

using namespace std;

int sos_mat[22][22];

void zeroResult(int c, int d, char res[][22], char mat[][22]);
void showResult(int x, int y, bool lost, char res[][22]);
void lastResult(int x, int y, char mat[][22]);
int checkWon(int x, int stars_left, char res[][22]);
void playAgain(bool play);
void markMat(int x, char res[][22]);

//void zeroNum(int x, int y, char res[][22]);

int main()
{
    bool play=true;
    while (play)
    {
		bool lost = false;
		int stars_left = 0;
		int x = 20, y = 20, i, j, bombs = 20, a, b;
		char mat[22][22], res[22][22];
		int bomb_indicator[x + 2][y + 2];
		char playerName[30], mark[3];
		int isMark1, isMark2;

		cout << "Enter Your Name: ";
		cin >> playerName;

		// age in nabashe rand() har dafe hamoonja ro entekhab mikone!
		srand(time(NULL));

		//meghdaraye pishfarzo mirizam toosh ke bad mikham ++ konam ok bashe :)
		for (int i = 0; i < y + 2; i++)
		{
			for (int j = 0; j < x + 2; j++)
			{
				mat[i][j] = '0';
				bomb_indicator[i][j] = 0;
				res[i][j] = '*';
				sos_mat[i][j] = -1;
			}
		}

		// jaye random e bomb aro mizare oon if e vase inke yejaro hey select nakone
		for (int n = 0; n < bombs; n++)
		{
			i = rand() % x + 1;
			j = rand() % x + 1;
			if (mat[i][j] == '#')
			{
				n--;
			}
			else
			{
				mat[i][j] = '#';
			}
		}

		//inam vase inke bombaye doresho beshmore o age khodesh bomb nabood meghdar adade ( tedad bomb ha ) ro bezare jash
		for (int i = 1; i < y + 1; i++)
		{
			for (int j = 1; j < x + 1; j++)
			{
				if (mat[i - 1][j - 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i - 1][j] == '#')
					bomb_indicator[i][j]++;
				if (mat[i - 1][j + 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i][j - 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i][j + 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i + 1][j - 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i + 1][j] == '#')
					bomb_indicator[i][j]++;
				if (mat[i + 1][j + 1] == '#')
					bomb_indicator[i][j]++;
				if (mat[i][j] != '#')
					mat[i][j] = bomb_indicator[i][j] + '0';
			}
		}

		chrono::steady_clock sc; // ina vase time gereftan e bazian
		auto start = sc.now();   // nemidoonam yani chi ina! vali timer e dg! :) lol

		// do while vase inke ta vaghti voroodimoon jaye bomb nist edame bede o benevise
		do
		{
			showResult(x, y, lost, res);
			stars_left = checkWon(x, y, res);
			if (stars_left == bombs)
			{
				system("clear");
				cout << "\033[1;32m"
					<< "You Won!!!"
					<< "\033[0m" << endl;
				lastResult(x, y, mat);
				auto end = sc.now();                                                 // mese inke inja timer e ro stop mikone!
				auto time_span = static_cast<chrono::duration<double>>(end - start); // start o end o az ham kam mikone ;)
				cout << "Game Play Time: " << int(time_span.count()) << " seconds !!!" << endl;
				fstream scoreboard;
				scoreboard.open("scoreboard.txt", ios::app);
				scoreboard << playerName << " Won In:\t" << int(time_span.count()) << " Seconds!" << endl;
				scoreboard.close();
				playAgain(play);
				return 0;
			}
			cout << "Do You Want To Mark Somewhere?" << endl;
			cin >> mark;
			isMark1 = strcmp(mark, "yes");
			isMark2 = strcmp(mark, "YES");
			if (isMark1 == 0 || isMark2 == 0)
			{
				markMat(x, res);
			}
			else
			{
				cout << "Enter Row & Column: ";
				cin >> a >> b;
				while (res[a][b] == '^')
				{
					cout << "You Marked This Place. Are You Sure? ";
					cin >> mark;
					isMark1 = strcmp(mark, "yes");
					isMark2 = strcmp(mark, "YES");
					if (isMark1 == 0 || isMark2 == 0)
					{
						res[a][b] = mat[a][b];
						zeroResult(a, b, res, mat);
					}
					else
					{
						cout << "Enter Row & Column: ";
						cin >> a >> b;
					}
				}
				res[a][b] = mat[a][b];
				zeroResult(a, b, res, mat);
			}
		} while (res[a][b] != '#');

		showResult(x, y, lost, res);

		system("clear");
		cout << "\033[1;31m"
			<< "You Lost!!!"
			<< "\033[0m" << endl;

		lastResult(x, y, mat);

		auto end = sc.now();                                                 // mese inke inja timer e ro stop mikone!
		auto time_span = static_cast<chrono::duration<double>>(end - start); // measure time span between start & end
		cout << "Game Play Time: " << int(time_span.count()) << " seconds !!!" << endl;
		playAgain(play);
    }
    system("exit");
    return 0;
}

void zeroResult(int c, int d, char res[][22], char mat[][22])
{
    if (mat[c][d] == '0' && sos_mat[c][d] == -1)
    {
        sos_mat[c][d] = 1;
        if (mat[c - 1][d - 1] != '#' && c > 1 && d > 1)
        {
            res[c - 1][d - 1] = mat[c - 1][d - 1];
            zeroResult(c - 1, d - 1, res, mat);
        }
        if (mat[c - 1][d] != '#' && c > 1 && d >= 1)
        {
            res[c - 1][d] = mat[c - 1][d];
            zeroResult(c - 1, d, res, mat);
        }
        if (mat[c - 1][d + 1] != '#' && c > 1 && d > -1)
        {
            res[c - 1][d + 1] = mat[c - 1][d + 1];
            zeroResult(c - 1, d + 1, res, mat);
        }
        /////
        if (mat[c][d - 1] != '#' && c >= 1 && d > 1)
        {
            res[c][d - 1] = mat[c][d - 1];
            zeroResult(c, d - 1, res, mat);
        }
        if (mat[c][d + 1] != '#' && c >= 1 && d > -1)
        {
            res[c][d + 1] = mat[c][d + 1];
            zeroResult(c, d + 1, res, mat);
        }
        /////
        if (mat[c + 1][d - 1] != '#' && c > -1 && d > 1)
        {
            res[c + 1][d - 1] = mat[c + 1][d - 1];
            zeroResult(c + 1, d - 1, res, mat);
        }
        if (mat[c + 1][d] != '#' && c > -1 && d >= 1)
        {
            res[c + 1][d] = mat[c + 1][d];
            zeroResult(c + 1, d, res, mat);
        }
        if (mat[c + 1][d + 1] != '#' && c > -1 && d > -1)
        {
            res[c + 1][d + 1] = mat[c + 1][d + 1];
            zeroResult(c + 1, d + 1, res, mat);
        }
        /////
    }
}

void showResult(int x, int y, bool lost, char res[][22])
{
    system("clear");
    cout << "    ";
    for (int j = 1; j < x + 1; j++)
    {
        if (j >= 10)
            cout << "\033[1;34m" << j << "\033[0m  ";
        else
            cout << "\033[1;34m" << j << "\033[0m   ";
    }
    cout << endl;
    for (int i = 1; i < y + 1; i++)
    {
        if (i >= 10)
            cout << "\033[1;34m" << i << "\033[0m  ";
        else
            cout << "\033[1;34m" << i << "\033[0m   ";

        for (int j = 1; j < x + 1; j++)
        {
            if (res[i][j] == '#')
            {
                cout << "\033[1;31m" << res[i][j] << "\033[0m   ";
                lost = true;
            }
            else if (res[i][j] == '^')
            {
                cout << "\033[1;96m" << res[i][j] << "\033[0m   ";
            }
            else if (res[i][j] != '*')
            {
                cout << "\033[1;32m" << res[i][j] << "\033[0m   ";
            }
            else
                cout << res[i][j] << "   ";
        }
        cout << endl;
        cout << endl;
    }
}

void lastResult(int x, int y, char mat[][22])
{
    cout << "    ";
    for (int j = 1; j < x + 1; j++)
    {
        if (j >= 10)
            cout << "\033[1;34m" << j << "\033[0m  ";
        else
            cout << "\033[1;34m" << j << "\033[0m   ";
    }
    cout << endl;
    for (int i = 1; i < y + 1; i++)
    {
        if (i >= 10)
            cout << "\033[1;34m" << i << "\033[0m  ";
        else
            cout << "\033[1;34m" << i << "\033[0m   ";

        for (int j = 1; j < x + 1; j++)
        {
            if (mat[i][j] == '#')
            {
                cout << "\033[1;31m" << mat[i][j] << "\033[0m   ";
            }
            else
            {
                cout << "\033[1;32m" << mat[i][j] << "\033[0m   ";
            }
        }
        cout << endl;
        cout << endl;
    }
}

void playAgain(bool play)
{
    char choice[3];
    int f_res, s_res;
    cout << endl
         << "\033[1;34m"
         << "Do You Want To Play Again?"
         << "\033[0m" << endl;
    cin >> choice;
    f_res = strcmp(choice, "yes");
    s_res = strcmp(choice, "YES");
	system("clear");
    if (f_res == 0 || s_res == 0)
    {
        play = true;
    }
	else
	{
		play = false;
	}
}

int checkWon(int x, int stars_left, char res[][22])
{
    stars_left = 0;
    for (int i = 1; i < x + 1; i++)
    {
        for (int j = 1; j < x + 1; j++)
        {
            if (res[i][j] == '*' || res[i][j] == '^')
                stars_left++;
        }
    }
    return stars_left;
}

void markMat(int x, char res[][22])
{
    int f, s;
    cout << "Enter Row & Column: ";
    cin >> f >> s;
    while (res[f][s] != '*')
    {
        cout << "Position Is Already Revealed!" << endl;
        cout << "Enter Row & Column: ";
        cin >> f >> s;
    }
    res[f][s] = '^';
}
