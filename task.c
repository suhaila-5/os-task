#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

void listFiles(char *path)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) != NULL)
    {
        printf("Files in directory %s:\n", path);
        while ((entry = readdir(dir)) != NULL)
        {
            printf("%s \n", entry->d_name);
        }
        closedir(dir);
    }
    else
    {
        perror("Unable to open directory");
    }
}

void changePermissions(char *file, mode_t mode)
{
    if (chmod(file, mode) == -1)
    {
        perror("chmod failed");
    }
    else
    {
        printf("Permissions changed successfully.\n");
    }
}

void createFile(char *file)
{
    if (creat(file, 0666) == -1)
    {
        perror("Failed to create file");
    }
    else
    {
        printf("File created successfully.\n");
    }
}

void deleteFile(char *file)
{
    if (remove(file) == -1)
    {
        perror("Failed to delete file");
    }
    else
    {
        printf("File deleted successfully.\n");
    }
}

void createDirectory(char *path)
{
    if (mkdir(path, 0777) == -1)
    {
        perror("Failed to create directory");
    }
    else
    {
        printf("Directory created successfully.\n");
    }
}

void deleteDirectory(char *path)
{
    if (rmdir(path) == -1)
    {
        perror("Failed to delete directory");
    }
    else
    {
        printf("Directory deleted successfully.\n");
    }
}



void createSymbolicLink(char *target, char *link)
{
    if (symlink(target, link) == -1)
    {
        perror("Failed to create symbolic link");
    }
    else
    {
        printf("Symbolic link created successfully.\n");
    }
}

void displayMenu()
{
    printf("\nMenu:\n");
    printf("1. List files/directories\n");
    printf("2. Change permissions of a file/directory\n");
    printf("3. Make a file\n");
    printf("4. Delete a file\n");
    printf("5. Make a directory\n");
    printf("6. Delete a directory\n");
    printf("7. Create symbolic link\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}
void runFileManager()
{
    char path[100], file[100], target[100], link[100];
    mode_t mode;
    int choice;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter directory path: ");
            scanf("%s", path);
            listFiles(path);
            break;
        case 2:
            printf("Enter file/directory path: ");
            scanf("%s", file);
            printf("Enter permissions (in octal): ");
            scanf("%o", (unsigned int *)&mode);
            changePermissions(file, mode);
            break;
        case 3:
            printf("Enter file name: ");
            scanf("%s", file);
            createFile(file);
            break;
        case 4:
            printf("Enter file name: ");
            scanf("%s", file);
            deleteFile(file);
            break;
        case 5:
            printf("Enter directory path: ");
            scanf("%s", path);
            createDirectory(path);
            break;
        case 6:
            printf("Enter directory path: ");
            scanf("%s", path);
            deleteDirectory(path);
            break;
        case 7:
            printf("Enter target file/directory path: ");
            scanf("%s", target);
            printf("Enter symbolic link path: ");
            scanf("%s", link);
            createSymbolicLink(target, link);
            break;
        case 8:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
}

int main()
{
    runFileManager();
    return 0;
}
