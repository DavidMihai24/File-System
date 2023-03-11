/* GHELESEL David - 311CB */
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

#define LENGTH 50

typedef struct directory {
    char *name;
    struct directory *parent;
    struct file *files;
    struct directory *directories;
    struct directory *left, *right;
}*Dir;

typedef struct file {
    char *name;
    struct directory *parent;
    struct file *left, *right;
}*File;

File fileAllocation(char *name, Dir parent);
Dir directoryAllocation(char *name, Dir parent);
int dirSearch(Dir root, char *name);
int fileSearch(File root, char *name);
void lsFile(File root);
void lsDir(Dir root);
void touch(Dir parent, char *name);
void mkdir(Dir parent, char *name);
void ls(Dir currentDir);
File rm(File root, char *name);
Dir rmdir(Dir root, char *name);
Dir cd(Dir currentDir, char *name);
void pwd(Dir currentDir);
Dir minValueDir(Dir currentDir);
File minValueFile(File currentFile);
File fileSearch2(Dir root, char* name);
File findFile(Dir root, char* name);
Dir dirSearch2(Dir root, char* name);
Dir findDir(Dir root, char* name);
void destroyFile(File r);
void destroyDir(Dir r);
void DistrArb(Dir *a);