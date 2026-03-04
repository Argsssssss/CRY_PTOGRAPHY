#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
#if defined(_WIN32) || defined(_WIN64) 
    #define WINDOWS
    #include <conio.h>

#elif defined(unix)
    #define UNIX
    char getch(void);
#else
    #error "Platform is not supported"
#endif

void clear (void) {
    #ifdef WINDOWS
        printf("\033[2J");
        printf("\033[0;0f");
    #else
        system("clear");
    #endif
}

#ifdef UNIX
    char getch (void) {
        char ch;
        system("stty raw");
        ch = getchar();
        system("stty cooked");
        return ch;
    }
#endif


bool game();
int start();
int main(){
    start();
    return 0;
}
void print_searting(string pick, int ){

}
bool game(){
    vector<vector<char>>map(20,vector<char>(20,'Z'));
    vector<char>snake(40,'*');
    snake[0] = '*';
    while(true){
        for (size_t i = 0; i < 20; i++)
        {
            for (size_t j = 0; j < 20; j++)
            {
                cout << map[i][j] << ' ';
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
        clear();
    }
    return 0;
}

int start(){
    int client[2]{10,10}; // Размер карты
    int speed_snake = 500; // Скорость, по факту тайминг обновления карты в МС
    menu:
        clear();
        string pick[] = {
            "--------Select--------\n",
            "|      1 - Start     |\n",
            "|      2 - Searting  |\n",
            "|      3 - Exit      |\n",
            "----------------------\n",
            "U pick: "
            };
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < pick[i].size(); j++)
            {
                cout << pick[i][j];
            }
        }
        
        char select = 0;
        select = getch();
        switch (select)
        {
            case '1': goto game;
            case '2': goto searting;
            case '3': exit;
            default: break;
        };

    exit:return 0;

    game:
        clear();
        cout << "========Welcome========\n";
        game();

        goto menu;

    searting:
        clear();
        string pick_searting[] = {
            "-------------Searting------------\n",
            "|  1 - Screen Resolution %d x %d|\n",
            "|  2 - Velocity          %d     |\n",
            "|  3 - Exit                     |\n",
            "---------------------------------\n",
            "U pick: "
            };

        printf("-------------Searting------------\n");
        printf("|  1 - Screen Resolution %d x %d|\n",client[0], client[1]);
        printf("|  2 - Velocity          %d (MS)|\n",speed_snake);
        printf("|  3 - Exit                     |\n---------------------------------\nU pick: ");
        char select_searting  = getch();
        switch (select_searting)
        {
            case '1': 
                cout << "\nEnter X: ";
                cin >> client[0];
                cout << endl;
                cout << "Enter Y: ";
                cin >> client[1];
                goto searting;
            case '2':
                cout << "\nEnter the speed parameter: ";
                cin >> speed_snake;
                goto searting;
            case '3': goto menu;
            default: goto searting;
        };

    return 0;
}
