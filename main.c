#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void open_file(int argc, char** argv);

int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "An invalid number of arguments were specified.");
        return 1;
    }

    initscr();

    open_file(argc, argv);
    getch();

    endwin();

    return 0;
}

void open_file(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");

    const unsigned int file_contents_length = 100;
    char file_contents[file_contents_length];

    if(file != NULL) {
        while(fgets(file_contents, file_contents_length, file)) {
            printw("%s", file_contents);
        }

        fclose(file);
    } else {
        endwin();
        fprintf(stderr, "The file you specified does not exist.");
        exit(1);
    }
}
