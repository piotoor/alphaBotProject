#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
using namespace std;

vector<string> track;
vector<string> car {".....", ".....", "O.O.O", ".....", "....."};
vector<string> screen;

typedef pair<int, int> point; // row, col
point carPos(make_pair(25, 15));
int windowHeight = 0;
int windowWidth = 0;


bool loadTrackFromFile(string fileName, vector<string> & track)
{
    fstream input(fileName);
    string line;
    if(input.is_open())
    {
        while(getline(input, line))
        {
            track.push_back(line);
            windowHeight++;
        }
        windowWidth = 50; // todo
        cout << "File loaded " << fileName << endl;
        return true;
    }
    else
    {
        cout << "Failed to load file " << fileName << endl;
        return false;
    }
}

void printTrack(const vector<string>& track)
{
    for(auto it = track.begin(); it != track.end(); it++)
    {
        cout << *it << endl;
    }
}

void rotateCarLeft()
{

}

void rotateCarRight()
{

}

void prepareScreen()
{
    // take current fragment of track
    // add car
    screen.clear();
    screen = track;
    int carR = carPos.first - 2;
    int carC = carPos.second - 2;
    for(int i = carR; i < carR + 5; i++)
    {
        for(int j = carC; j < carC + 5; j++)
        {
            if(car[i - carR][j - carC] == 'O')
            {
                screen[i][j] = 'O';
            }
        }
    }
}

void drawScreen()
{
    system("clear");
    printTrack(screen);
}

void handlePressed(char c)
{
    if(c == 'i')
    {
        if(carPos.first > 2)
        {
            carPos.first--;
        }
    }
    else if(c == 'j') // bedzie rotacja
    {
        if(carPos.second > 2)
        {
            carPos.second--;
        }
    }
    else if(c == 'k')
    {
        if(carPos.first < windowHeight - 3)
        {
            carPos.first++;
        }
    }
    else if(c == 'l') // bedzie rotacja
    {
        if(carPos.second < windowWidth - 3)
        {
            carPos.second++;
        }
    }
}

int main(int argc, char* argv[])
{

    struct termios oldSettings, newSettings;

    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );

    if(argc < 2)
    {
        cout << "No filename provided" << endl;
    }
    if(loadTrackFromFile(argv[1], track))
    {
        char c;
        do
        {
            prepareScreen();
            drawScreen();
            fd_set set;
            struct timeval tv;

            tv.tv_sec = 10;
            tv.tv_usec = 0;

            FD_ZERO( &set );
            FD_SET( fileno( stdin ), &set );

            int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );
            if( res > 0 )
            {
                read( fileno( stdin ), &c, 1 );

                handlePressed(c);
                //cout << c << endl;
            }

        }
        while(c != 'x');
    }
    cout << "bye!! " << endl;
    return 0;
}
