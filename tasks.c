/* GHELESEL David - 311CB */
#include "library.h"

void touch(Dir parent, char *name){
    int search = dirSearch(parent->directories, name); //parcurgem arborele de directoare

    while (search) {
        printf("Directory %s already exists!\n", name);
        return;
    }

    search = fileSearch(parent->files, name); // parcurgem arborele de fisiere
    if (search) {
        printf("File %s already exists!\n", name);
        return;
    }

    if (parent->files == NULL) {
        parent->files = fileAllocation(name, parent); // alocam fisier
        return;
    }

    else {
        File file = parent->files;
        while (file) {
            if (strcmp(name, file->name) > 0) {
                if (file->right == NULL){
                    file->right = fileAllocation(name, parent); // alocam fisier copil-drept
                    return;
                }
                file = file->right;
            }

            else {
                if (file->left == NULL){
                    file->left = fileAllocation(name, parent); // alocam fisier copil-stang
                    return;
                }
                file = file->left;
            }
        }
    }
}

void mkdir(Dir parent, char *name){
    int search = dirSearch(parent->directories, name);

    if (search) {
        printf("Directory %s already exists!\n", name);
        return;
    }

    search = fileSearch(parent->files, name);
    if (search) {
        printf("File %s already exists!\n", name);
        return;
    }

    if (parent->directories == NULL) {
        parent->directories = directoryAllocation(name, parent); // alocam director
        return;
    }

    else {
        Dir dir = parent->directories;
        while (dir) {
            if (strcmp(name, dir->name) > 0) {
                if (dir->right == NULL){
                    dir->right = directoryAllocation(name, parent); // alocam director copil-drept
                    return;
                }
                dir = dir->right;
            }

            else {
                if (dir->left == NULL){
                    dir->left = directoryAllocation(name, parent); // alocam director copil-stang
                    return;
                }
                dir = dir->left;
            }
        }
    }
}

void ls(Dir currentDir) {
    lsDir(currentDir->directories);
    lsFile(currentDir->files);
    printf("\n");
}

//efectuam operatia deleteNode pentru arbori de cautare, cu stringuri
File rm(File root, char *name) {
    int search = fileSearch(root, name);

    if (!search) {
        printf("File %s doesn't exist!\n", name);
        return root;
    }

    if (strcmp(name, root->name) < 0)
        root->left = rm(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = rm(root->right, name);
    else {
        if (root->left == NULL) {
            File temp = root->right;
            free(root->name);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            File temp = root->left;
            free(root->name);
            free(root);
            return temp;
        }
        File temp = minValueFile(root->right);
        strcpy(root->name, temp->name);
        root->right = rm(root->right, temp->name);
    }
    return root;
}

//efectuam operatia deleteNode pentru arbori de cautare, cu stringuri
Dir rmdir(Dir root, char *name) {
    int search = dirSearch(root, name);

    if (!search) {
        printf("Directory %s doesn't exist!\n", name);
        return root;
    }

    else {
        if (strcmp(name, root->name) < 0) {
            root->left = rmdir(root->left, name);
        }

        else if (strcmp(name, root->name) > 0) {
            root->right = rmdir(root->right, name);
        }

        else {
            if (root->left == NULL) {
                Dir temp = root->right;
                free(root->name);
                destroyDir(root->directories);
                destroyFile(root->files);
                free(root);
                return temp;
            } else if (root->right == NULL) {
                Dir temp = root->left;
                free(root->name);
                destroyDir(root->directories);
                destroyFile(root->files);
                free(root);
                return temp;
            }

            Dir temp = minValueDir(root->right);
            strcpy(root->name, temp->name);
            root->files = temp->files;
            root->directories = temp->directories;
            root->right = rmdir(root->right, temp->name);
        }
        return root;
    }
}

// parcurgem directoare si in functie de caz ne mutam pe copilul stang
// sau pe copilul drept
Dir cd(Dir currentDir, char* name){
    if(strcmp(name, "..") == 0) {
        if (currentDir->parent == NULL) {
            return currentDir;
        }
        else
            return currentDir->parent;
    }

    Dir dir = currentDir->directories;
    while(dir != NULL)
    {
        if(strcmp(name, dir->name) == 0 )
        {
            currentDir = dir;
            return currentDir;
        }
        if(strcmp(name, dir->name) < 0 )
            dir = dir->left;
        else if(strcmp(name, dir->name) > 0)
            dir = dir->right;
    }
    printf("Directory not found!\n");
    return currentDir;
}

// functia cauta recursiv directorul "currentDir" si printeaza calea pana la acesta
// daca currentDir este root printeaza /root
void pwd(Dir currentDir) {

    if (strcmp(currentDir->name, "root") != 0) {
        pwd(currentDir->parent);
    }
    printf("/%s", currentDir->name);
}

// functia cauta recursiv fisierul "name" incepand cu directorul root
File findFile(Dir root, char* name){
    if(root == NULL)
        return NULL;
    while(fileSearch2(root, name) != NULL )
        return fileSearch2(root, name);
    while(findFile(root->left, name) != NULL )
        return findFile(root->left, name);
    return findFile(root->right, name);
}

// functia cauta recursiv directorul "name" incepand cu directorul root
Dir findDir(Dir root, char* name){
    if(root == NULL)
        return NULL;
    while(dirSearch2(root, name) != NULL )
        return dirSearch2(root, name);
    while(findDir(root->left, name) != NULL )
        return findDir(root->left, name);
    return findDir(root->right, name);
}