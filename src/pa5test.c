#include <stdio.h>
#include <stdlib.h>

char * get_input(char * prompt) {
    printf("%s", prompt);
    char *input = NULL;
    size_t size = 0;
    size_t capacity = 1;
    input = malloc(capacity);
    if (input == NULL) {
        // perror("Memory allocation failed");
        return NULL;
    }
    
    char ch;
    while ((ch = getchar()) != '\n') {
        // Resize if needed
        if (size + 1 >= capacity) {
            capacity *= 2; // Double the capacity
            char *temp = realloc(input, capacity);
            if (temp == NULL) {
                // perror("Memory reallocation failed");
                free(input);
                return NULL;
            }
            input = temp;
        }
        if (ch == '\377') {
            free(input);
            return NULL;
        }
        input[size++] = ch;
    }
    input[size] = '\0'; // Null-terminate the string
    return input;
}

int str_to_int(char * str) {
    return strtol(str, NULL, 10);
}

void shutdown(FILE * file) {
    printf("\n");
    fflush(stdout);
    fclose(file);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    // Read file name
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open file
    FILE *file = fopen(argv[1], "r+");
    if (file == NULL)
    {
        printf("./pa5test error: invalid filename\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        // Ask user for operation
        char * input = get_input("Option (r for read, w for write, s for seek): ");
        // Check for EOF (Ctrl+D)
        if (input == NULL) {
            shutdown(file);
        }
        
        char operation = input[0];
        free(input);
        switch (operation)
        {
            case 'r': {
                char * bytes_str = get_input("Enter the number of bytes you want to read: ");
                if (bytes_str == NULL) {
                    shutdown(file);
                }
                int bytes = str_to_int(bytes_str);
                free(bytes_str);
                if (bytes == 0)
                {
                    // perror("Error reading number of bytes");
                    break;
                }
                // Read bytes
                char *data = malloc(bytes+1);
                if (data == NULL) {
                    // Handle memory allocation failure
                    break;
                }
                // prepare file for reading
                fseek (file , 0, SEEK_CUR);
                fread(data, 1, bytes, file);
                data[bytes] = '\0';
                printf("%s\n", data);
                free(data);
                break;
            }
            case 'w': {
                // Read input from user
                char *input = get_input("Enter the data you want to write: ");
                if (input == NULL)
                {
                    shutdown(file);
                }
                // prepare file for writing
                fseek (file , 0, SEEK_CUR);
                // Write the string to the file
                int res = fputs(input, file);
                if (res == EOF)
                {
                    perror("Error writing to file");
                }
                fflush(file);
                free(input);
                break;
            }
            case 's': {
                // Read offset
                char *offset_str = get_input("Enter an offset value: ");
                if (offset_str == NULL)
                {
                    shutdown(file);
                }
                int offset = str_to_int(offset_str);
                free(offset_str);

                // Read whence
                char *whence_str = get_input("Enter a value for whence: ");
                if (whence_str == NULL)
                {
                    shutdown(file);
                }
                int whence = str_to_int(whence_str);
                free(whence_str);
                
                // Seek to the offset
                fseek(file, offset, whence);

                break;
            }
            default: {
                break;
            }
        }
    }

    shutdown(file);

    return EXIT_SUCCESS;
}