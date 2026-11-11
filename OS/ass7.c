
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;

    char filename[100];
    char buffer[1024];
    int fd, n;

    // Create two pipes
    pipe(pipe1);
    pipe(pipe2);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    // Parent Process
    if (pid > 0)
    {
        close(pipe1[0]); // Close reading end of pipe1
        close(pipe2[1]); // Close writing end of pipe2

        printf("Enter file name: ");
        scanf("%99s", filename);

        // Send filename to child
        write(pipe1[1], filename, strlen(filename) + 1);

        close(pipe1[1]);

        printf("\nContents of file:\n");

        // Read file contents from child
        while ((n = read(pipe2[0], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(pipe2[0]);

        wait(NULL);
    }

    // Child Process
    else
    {
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2

        // Read filename from parent
        read(pipe1[0], filename, sizeof(filename));

        close(pipe1[0]);

        // Open the file
        fd = open(filename, O_RDONLY);

        if (fd < 0)
        {
            char msg[] = "Error: Unable to open file.\n";
            write(pipe2[1], msg, strlen(msg));
        }
        else
        {
            // Read file and send contents to parent
            while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            {
                write(pipe2[1], buffer, n);
            }

            close(fd);
        }

        close(pipe2[1]);
        exit(0);
    }

    return 0;
}
