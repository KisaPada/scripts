/* TODO
 * - set up arg parsing (primitive)
 * - add functionality for hours, minutes, seconds, etc.
 * - clean up timer printing
 * - set up arg parsing (robust)
 * - set up help dialog
 */

#include <stdio.h>
#include <unistd.h>

void print_help_dialog();

int main(int argc, char* argv[]) {
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
    for(int i = 0; i < argc; ++i) {

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
