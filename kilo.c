/** includes **/
#include <stdio.h>
#include <errno.h> // error handling
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

/** data **/

struct termios original; // original terminal settings

/** terminal **/

void die(const char *s) // prints descriptive error message
{
    perror(s);
    exit(1);
}
void disableRawMode(void)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1)
    {
        die("tcsetattr");
    }
}
void enableRawMode(void)
{
    if (tcgetattr(STDIN_FILENO, &original) == -1) die("tcgetattr"); // getting original terminal attributes
    atexit(disableRawMode);

    struct termios raw = original;// creating an instance of termios struct from termios.h

    // changing attributes
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN |ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // setting new attributes from the struct

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/** init **/

int main(void)
{
    enableRawMode();

    while (1)
    {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }else
        {
            printf("%d ('%c')\r\n",c,c);
        }
        if (c=='q') break;
    }
    return 0;
}
