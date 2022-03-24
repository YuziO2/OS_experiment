#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fk = fork();
    if (fk == 0)
    {
        execlp("date", "date", NULL);
    }
    else
    {
        int wc = wait(NULL);
        execlp("ls", "ls", "./", NULL);
    }
}