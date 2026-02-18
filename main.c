#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void open_file(char* filepath);
void handle_input();

int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "An invalid number of arguments were specified.");
        return 1;
    }

    initscr();

    open_file(argv[1]);
    handle_input();

    endwin();

    return 0;
}

void open_file(char* filepath) {
    FILE* file = fopen(filepath, "r");

    const unsigned int file_contents_length = 100;
    char file_contents[file_contents_length];

    if(file != NULL) {
        while(fgets(file_contents, file_contents_length, file)) {
            addstr(file_contents);
        }

        fclose(file);
    } else {
        endwin();
        fprintf(stderr, "The file you specified does not exist.");
        exit(1);
    }
}

void handle_input() {
    noecho();
    keypad(stdscr, TRUE);

    while(1) {
        int input = getch();

        switch(input) {
            case KEY_BACKSPACE:
            case 127:
            case 8:
                move(getcury(stdscr), (getcurx(stdscr) - 1));
                delch();
                break;
            case '\n':
                move((getcury(stdscr) + 1), 0);
                break;
            default:
                addch(input);
        }
    }
}
