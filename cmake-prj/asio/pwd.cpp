#include <termios.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <pwd.h>
#include <unistd.h>

using namespace std;
ssize_t
my_getpass (char **lineptr, size_t *n, FILE *stream)
{
    struct termios old, new1;
    int nread;

    /* Turn echoing off and fail if we can't. */
    if (tcgetattr (fileno (stream), &old) != 0)
        return -1;
    new1 = old;
    new1.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stream), TCSAFLUSH, &new1) != 0)
        return -1;

    /* Read the password. */
    nread = getline (lineptr, n, stream);

    /* Restore terminal. */
    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old);

    return nread;
}

int main()
{
   char line[128];
   size_t sz = sizeof(line);

   std::string pass = getpass("input password");

   cout << pass << endl;

   return 0;
}