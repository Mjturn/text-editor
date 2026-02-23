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
            for(int i = 0; file_contents[i] != '\0'; i++) {
                addch(file_contents[i]);
            }
        }
    } else {
        file = fopen(filepath, "w");
    }

    fclose(file);
}

void handle_input() {
    raw();
    noecho();
    keypad(stdscr, TRUE);

    unsigned int y, x;

    const unsigned int length = 100;
    char characters[length][length] = {};
    unsigned int line_lengths[length] = {};
    unsigned int lines = 1;

    while(1) {
        int input = getch();

        getyx(stdscr, y, x);

        switch(input) {
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if(x == 0 && y == 0) {
                    break;
                }

                if(x > 0) {
                    move(y, x - 1);
                    delch();
                    characters[y][x - 1] = '\0';
                    line_lengths[y]--;
                } else {
                    move(y - 1, line_lengths[y - 1]);
                }

                break;
            case '\n':
                move(y + 1, 0);
                lines++;
                break;
            case KEY_UP:
                if(y != 0) {
                    move(y - 1, line_lengths[y - 1]);
                }

                break;
            case KEY_DOWN:
                if(y != lines) {
                    move(y + 1, line_lengths[y + 1]);
                }   

                break;
            case KEY_LEFT:
                if(x != 0) {
                    move(y, x - 1);
                }

                break;
            case KEY_RIGHT:
                if(x != line_lengths[y]) {
                    move(y, x + 1);
                }

                break;
            case 27:
                return;
            default:
                addch(input);
                characters[y][x] = input;
                line_lengths[y]++;
        }

        if(x == getmaxx(stdscr) - 2) {
            move(y + 1, 0);
            lines++;
        }
    }
}
