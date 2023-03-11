/* GHELESEL David - 311CB */
#include "library.h"

//alocam fisiere si directoare
File fileAllocation(char *name, Dir parent){
    File temp;
    temp = malloc(sizeof(struct file));

    temp->name = malloc(LENGTH);
    strcpy(temp->name, name);
    temp->parent = parent;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Dir directoryAllocation(char *name, Dir parent){
    Dir temp;
    temp = malloc(sizeof(struct directory));

    if (temp == NULL) {
        printf("Error!\n");
        return NULL;
    }

    temp->name = malloc(LENGTH);
    strcpy(temp->name, name);
    temp->parent = parent;
    temp->files = NULL;
    temp->directories = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

//parcurgem arborii de cautare
int fileSearch(File root, char *name){
    if (root == NULL)
        return 0;

    if (strcmp(name, root->name) == 0) {
        return 1;
    }

    if (strcmp(name, root->name) > 0)
        return fileSearch(root->right, name);
    else
        return fileSearch(root->left, name);
}

int dirSearch(Dir root, char *name){
    if (root == NULL)
        return 0;

    if (strcmp(name, root->name) == 0)
        return 1;

    else if (strcmp(name, root->name) > 0)
        return dirSearch(root->right, name);

    else
        return dirSearch(root->left, name);
}

void lsFile(File root){
    if (root == NULL)
        return;
    else {
        lsFile(root->left);
        printf("%s ", root->name);
        lsFile(root->right);
    }
}

void lsDir(Dir root){
    if (root == NULL)
        return;
    else {
        lsDir(root->left);
        printf("%s ", root->name);
        lsDir(root->right);
    }
}

File minValueFile(File currentFile) {
    File current = currentFile;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Dir minValueDir(Dir currentDir) {
    Dir current = currentDir;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

//parcurgem arborii pentru functia find
File fileSearch2(Dir root, char* name){
    File file = root->files;
    while(file != NULL)
    {
        if(strcmp(name, file->name) == 0)
            return file;

        if(strcmp(name, file->name) > 0)
            file = file->right;
        else
            file = file->left;
    }

    file = findFile(root->directories, name);
    return file;
}

Dir dirSearch2(Dir root, char* name) {
    Dir dir = root->directories;
    while (dir != NULL) {
        if (strcmp(name, dir->name) == 0)
            return dir;
        if (strcmp(name, dir->name) > 0)
            dir = dir->right;
        else
            dir = dir->left;
    }
    dir = findDir(root->directories, name);
    return dir;
}

// eliberam arborii de cautare
void destroyFile(File r) {
    if (!r)
        return;
    destroyFile (r->right); /* distruge subarborele drept */
    destroyFile (r->left); /* distruge subarborele stang */
    free(r->name);
    free(r); /* distruge nodul radacina */
}

void destroyDir(Dir r) {
    if (!r)
        return;
    destroyDir (r->left);
    destroyDir (r->right);
    destroyDir(r->directories);
    destroyFile(r->files);
    free(r->name);
    free(r);
}

void DistrArb(Dir *a) {
    if(!(*a))
        return;
    destroyDir(*a);
    *a = NULL;
}