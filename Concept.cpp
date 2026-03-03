#include <iostream>
#include <vector>

using namespace std;
bool game();
int start();

int main(){
    start();
    return 0;
}

bool game(){
    // vector<char,char>client(50,50,NULL);
    // vector<char>snake(100);
    // snake[0] = '*';
    // while(true){
    //     for (size_t i = 0; i < 50; i++)
    //     {
    //         for (size_t j = 0; j < 50; j++)
    //         {
                
    //         }
            
    //     }
           
    // }
    return 0;
}

int start(){
    menu:
        system("clear");
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
        int select;
        cin >> select;
        switch (select)
        {
            case 1: goto game;
            case 2: goto searting;
            case 3: exit;
            default: break;
        };

    exit:return 0;

    game:
        system("clear");
        cout << "========Welcome========\n";
        game();

        goto menu;

    searting:
        system("clear");
        string pick_searting[] = {
            "------------Searting-----------\n",
            "|      1 - Screen Resolution   |\n",
            "|      2 - Velocity            |\n",
            "|      3 - Exit                |\n",
            "--------------------------------\n",
            "U pick: "
            };
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < pick_searting[i].size(); j++)
            {
                cout << pick_searting[i][j];
            }
            
        }
        int select_searting;
        cin >> select_searting;
        switch (select_searting)
        {
            case 1: 
            case 2:
            case 3: goto menu;
        };

    return 0;
}
