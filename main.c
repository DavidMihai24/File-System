/* GHELESEL David - 311CB */
#include "library.h"

int main() {

    // initializam directorul curent cu root;
    Dir root = directoryAllocation("root", NULL);
    Dir currentDir = root;
    char *buffer;
    char *function;
    char *name;
    buffer = malloc(LENGTH);

    while (true) {
        fgets(buffer, LENGTH, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        function = strtok(buffer, " \n");

        if (function != NULL) {
            switch(strcmp(function, "touch")) {
                case 0:
                    name = strtok(NULL, "\n");
                    touch(currentDir, name);
            }

            switch (strcmp(function, "mkdir")) {
                case 0:
                    name = strtok(NULL, "\n");
                    mkdir(currentDir, name);
            }

            switch (strcmp(function, "ls")) {
                case 0:
                    ls(currentDir);
            }

            switch (strcmp(function, "rm")) {
                case 0:
                    name = strtok(NULL, "\n");
                    currentDir->files = rm(currentDir->files, name);
            }

            switch (strcmp(function, "rmdir")) {
                case 0:
                    name = strtok(NULL, "\n");
                    currentDir->directories = rmdir(currentDir->directories, name);
            }

            switch (strcmp(function, "cd")) {
                case 0:
                    name = strtok(NULL, "\n");
                    currentDir = cd(currentDir, name);
            }

            switch (strcmp(function, "pwd")) {
                case 0:
                    pwd(currentDir);
                    printf("\n");
            }

            if (strcmp(function, "find") == 0) {
                char *fd = strtok(NULL, " ");
                name = strtok(NULL, "\n");
                if (strcmp(fd, "-f") == 0) {
                    File file_point = fileSearch2(root, name);
                    if (file_point) {
                        printf("File %s found!\n", file_point->name);
                        pwd(file_point->parent);
                        printf("\n");
                        continue;
                    }
                    printf("File %s not found!\n", name);
                }
                else if (strcmp(fd, "-d") == 0) {
                    Dir dir_point = dirSearch2(root, name);
                    if (dir_point) {
                        printf("Directory %s found!\n", dir_point->name);
                        pwd(dir_point);
                        printf("\n");
                        continue;
                    }
                    printf("Directory %s not found!\n", name);
                }
            }

            if (strcmp(function, "quit") == 0) {
                DistrArb(&root);
                free(buffer);
                root = NULL;
                break;
            }
        }
    }
    return 0;
}