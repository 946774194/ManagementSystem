#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static char welcome[6][56] = {" __          ________ _      _____ ____  __  __ ______ \0",
                       " \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____|\0",
                       "  \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__   \0",
                       "   \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|  \0",
                       "    \\  /\\  /  | |____| |___| |___| |__| | |  | | |____ \0",
                       "     \\/  \\/   |______|______\\_____\\____/|_|  |_|______|\0"
};

static char tms[6][112] ={"  _                                                                      _                   _\0",
                " | |_ ___    _ __ ___   __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_   ___ _   _ ___| |_ ___ _ __ ___\0",
                " | __/ _ \\  | '_ ` _ \\ / _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __| / __| | | / __| __/ _ \\ '_ ` _ \\\0",
                " | || (_) | | | | | | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_  \\__ \\ |_| \\__ \\ ||  __/ | | | | |\0",
                "  \\__\\___/  |_| |_| |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |___/\\__, |___/\\__\\___|_| |_| |_|\0",
                "                                         |___/                                     |___/\0"
};

static char bool[6][56];

static void show(){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 56; j++){
            putchar(bool[i][j] ? welcome[i][j] : ' ');
        }
        putchar(10);
    }
    putchar(10);
}

extern void showWelcomeScreen() {
    for (int i = 0; i < 55; i += 5) {
        for (int j = 0; j < 6; ++j) {
            bool[j][i] = 1;
            bool[j][i + 1] = 1;
            bool[j][i + 2] = 1;
            bool[j][i + 3] = 1;
            bool[j][i + 4] = 1;
        }
        system("cls");
        show();
        usleep(80000);
    }
    for (int i = 0; i < 6; ++i) {
        printf("%s\n", tms[i]);
    }
    usleep(1500000);
    memset(bool, 0, sizeof(bool));
}
