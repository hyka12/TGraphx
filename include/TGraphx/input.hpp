#ifndef INPUT_HEADER
#define INPUT_HEADER

#include<termios.h>
#include<unistd.h>

namespace TGraphx_Input{

void Disable_Terminal_Echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void Restore_Terminal_Echo() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
    
}

#endif
