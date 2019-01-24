#include <cstdlib>

int main()
{
    system("g++ prog.cpp -g -o prog");
    system("./prog");
    system("emacs scoreboard.txt");
    system("clear");
    system("exit");
}