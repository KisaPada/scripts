#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRBUF 32

void clearLine() {
    printf("\r");
    for (int i = 0; i < 32; i++) {
        printf(" ");
    }
    printf("\r");
    return;
}

void formatTimer(char *formatStr, int timerLen) {
    int prntRtn = 0;
    if (timerLen > 60) {
        prntRtn = snprintf(formatStr, STRBUF, "%dm", (int)(timerLen/60));
    } else {
        prntRtn = snprintf(formatStr, STRBUF, "%ds", timerLen);
    }

    if (prntRtn >= STRBUF) {
        printf("ERROR: snprintf output truncated\n");
    }
    return;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("ERROR: Takes exactly 1 arg.\n");
        return 1;
    }
    if (strlen(argv[1]) + 1 >= STRBUF) {
        printf("ERROR: argv[1] too long.\n");
        return 1;
    }

    char argv1[STRBUF] = {0};
    strcpy(argv1, argv[1]);

    char unit = argv1[strlen(argv1) - 1];
    argv1[strlen(argv1) - 1] = '\0';

    int timerLen = 0;
    switch(unit) {
        case 'h': {
            timerLen = (int)(atof(argv1) * 3600);
            break;
        }
        case 'm': {
            timerLen = (int)(atof(argv1) * 60);
            break;
        }
        case 's': {
            timerLen = (int)atof(argv1);
            break;
        }
        default: {
            printf("ERROR: Invalid time unit (%c)\n", unit);
            return 1;
        }
    }

    char formatStr[STRBUF] = {0};
    while (timerLen > 0) {
        clearLine();
        formatTimer(formatStr, timerLen);
        printf("Timer: %s", formatStr);
        fflush(stdout);
        timerLen--;
        sleep(1);
    }
    clearLine();
    printf("timer: 0s\nDING DING DING");

    system(
        "mpv "
        "/home/jovan/honka-honka_new/Music/Sound\\ Effects/apple-radar-alarm.m4a "
        "--start=+2 "
        "--volume=35 "
        "--loop-file=2 "
    );

    return 0;
}
