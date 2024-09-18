/* TODO
 * - add functionality for hours, minutes, seconds, etc.
 * - clean up timer printing
 * - set up arg parsing (robust)
 * - set up help dialog
 */

#include <stdio.h>
#include <unistd.h>

void print_help_dialog();

int main(int argc, char* argv[]) {
    int opt = -1;
    int time_in_seconds = 0;
    int hours = 0, minutes = 0, seconds = 0;

    // printing args
    printf("argc: %d\n", argc);
    for(int i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    // parsing args
    if(argc == 1) {
        print_help_dialog();
        return 1;
    }
    while((opt = getopt(argc, argv, "hT:H:m:s:t:")) != -1) {
        switch(opt) {
            case 'h':
                print_help_dialog();
                return 0;
            case 'T': // accept an argument in the form HH:mm:ss
                break;
            case 'H':
                break;
            case 'm':
                break;
            case 't': // same as case 's'
            case 's':
                break;
            default:
                fprintf(stderr, "<default case placeholder help dialog>\n");
                return 1;
        }
    }
    if(optind < argc) { // checking for non-option arguments
        fprintf(stderr, "unexpected argument: %s\n", argv[optind]);
        return 1;
    }

    // running the timer
    for(int time = 3; time > 0; --time) {
        printf("%03d\n", time);
        sleep(1);
    }

    printf("Done!\n");
    return 0;
}

void print_help_dialog() {
    printf("<placeholder help dialog>\n");
}
