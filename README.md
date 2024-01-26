GHELESEL David-Mihai

For the realization of this project, I used the following structures:
1. Dir - containing the corresponding fields for the directory trees
2. File - containing the corresponding fields for file trees

These are themselves binary search trees, each having a left-child and a right-child. The first structure has in addition the fields "directories" and "files", since directories can contain subdirectories and files. For several of the implemented functions I used the search function, which is a browse of both files and directories. We also used concepts such as recursion to solve certain tasks.

For memory freeing I used the functions for the destruction of a tree, performing "free" for all search trees.
