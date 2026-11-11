
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char input[1000] = "";
    char line[200];
    char result[1000];

    // Create two FIFOs
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    printf("Enter sentences:\n");
    printf("(Enter END on a new line to finish)\n");

    // Accept sentences
    while(1)
    {
        fgets(line, sizeof(line), stdin);

        if(strcmp(line, "END\n") == 0)
            break;

        strcat(input, line);
    }

    // Open FIFO1 for writing
    int fd1 = open("fifo1", O_WRONLY);

    write(fd1, input, strlen(input) + 1);

    close(fd1);

    // Open FIFO2 for reading
    int fd2 = open("fifo2", O_RDONLY);

    int n = read(fd2, result, sizeof(result) - 1);

    result[n] = '\0';

    close(fd2);

    // Display result
    printf("\nResult received from Process 2:\n");
    printf("%s\n", result);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    char message[1000];
    char result[1000];

    // Open FIFO1 for reading
    int fd1 = open("fifo1", O_RDONLY);

    int n = read(fd1, message, sizeof(message) - 1);

    message[n] = '\0';

    close(fd1);

    // Count characters, words and lines
    int characters = strlen(message);
    int words = 0;
    int lines = 0;
    int inWord = 0;

    for(int i = 0; message[i] != '\0'; i++)
    {
        // Count lines
        if(message[i] == '\n')
            lines++;

        // Count words
        if(isspace((unsigned char)message[i]))
        {
            inWord = 0;
        }
        else if(inWord == 0)
        {
            words++;
            inWord = 1;
        }
    }

    // Write results into text file
    FILE *file = fopen("result.txt", "w");

    fprintf(file, "Number of characters: %d\n", characters);
    fprintf(file, "Number of words: %d\n", words);
    fprintf(file, "Number of lines: %d\n", lines);

    fclose(file);

    // Read contents from result file
    FILE *input = fopen("result.txt", "r");

    int count = fread(result, 1, sizeof(result) - 1, input);

    result[count] = '\0';

    fclose(input);

    // Open FIFO2 for writing
    int fd2 = open("fifo2", O_WRONLY);

    write(fd2, result, strlen(result) + 1);

    close(fd2);

    printf("Process 2 completed successfully.\n");

    return 0;
}
