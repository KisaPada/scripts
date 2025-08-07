#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clearLine() {
    printf("\r");
    for (int i = 0; i < 32; i++) {
        printf(" ");
    }
    printf("\r");
    return;
}

void formatTimer(char *formatStr, int timerLen) {
    if (timerLen > 60) {
        snprintf(formatStr, 32, "%dm", (int)(timerLen/60));
    } else {
        snprintf(formatStr, 32, "%ds", timerLen);
    }
    return;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("ERROR: Takes exactly 1 arg.\n");
        return 1;
    }

    char unit = argv[1][strlen(argv[1]) - 1];
    argv[1][strlen(argv[1]) - 1] = '\0';

    int timerLen = 0;
    switch(unit) {
        case 'h': {
            timerLen = (int)(atof(argv[1]) * 3600);
            break;
        }
        case 'm': {
            timerLen = (int)(atof(argv[1]) * 60);
            break;
        }
        case 's': {
            timerLen = (int)atof(argv[1]);
            break;
        }
        default: {
            printf("ERROR: Invalid time unit (%c)\n", unit);
            return 1;
        }
    }

    char formatStr[32] = {0};
    while (timerLen > 0) {
        clearLine();
        formatTimer(formatStr, timerLen);
        printf("Timer: %s", formatStr);
        fflush(stdout);
        timerLen--;
        sleep(1);
    }
    clearLine();
    printf("timer: 0s\n");

    printf("DING DING DING\n");
    system(
        "mpv "
        "/home/jovan/honka-honka_new/Music/Sound\\ Effects/apple-radar-alarm.m4a "
        "--volume=35 "
        "--loop-file=2 " // play 3 times total
    );

    return 0;
}
