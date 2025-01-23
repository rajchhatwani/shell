
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_executable(const char *path) { return access(path, X_OK) == 0; }

char *find_in_path(const char *command)
{
  char *path_env = getenv("PATH");
  if (path_env == NULL)
  {
    return NULL; 
  }
  char *path_copy = strdup(path_env);
  // printf("%s- this is path_copy\n", path_copy);
  char *dir = strtok(path_copy, ":");
  // printf("%s- this is tokened dir\n", dir);
  static char full_path[1024];

  while (dir != NULL)
  {
    snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
    // printf("%s- this is full path\n", full_path);
    if (is_executable(full_path))
    {
      free(path_copy);
      return full_path;
    }
    dir = strtok(NULL, ":");
  }

  free(path_copy);
  return NULL;
}

void fork_and_exec_cmd(char *full_path, int argc, char **argv)
{
  pid_t pid = fork();
  if (pid == 0)
  {
    execv(full_path, argv);
    perror("execv");
    exit(1);
  }
  else if (pid < 0)
    perror("fork");
  else
  {
    int status;
    waitpid(pid, &status, 0);
  }
}

int main()
{
  setbuf(stdout, NULL);

  char input[100];
  char userCommand[100];

  while (1)
  {
    printf("$ ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';

    if (strlen(input) == 0)
    {
      continue;
    }

    if (!strcmp(input, "exit 0"))
      exit(0);

    if (strncmp(input, "echo", strlen("echo")) == 0)
    {
      printf("%s\n", input + 5);
      continue;
    }

    if (strncmp(input, "type", strlen("type")) == 0)
    {
      memset(userCommand, 0, sizeof(userCommand));
      strncpy(userCommand, input + 5, sizeof(userCommand) - 1);

      if (strncmp(userCommand, "echo", strlen(userCommand)) == 0 || strncmp(userCommand, "exit", strlen(userCommand)) == 0 || strncmp(userCommand, "type", strlen(userCommand)) == 0)
      {
        printf("%s is a shell builtin\n", userCommand);
      }
      else
      {
        // printf("%s: not found\n", userCommand);
        char *path = find_in_path(userCommand);
        // printf("%s- path\n", path);
        if (path)
        {
          printf("%s is %s\n", userCommand, path);
        }
        else
        {
          printf("%s: not found\n", userCommand);
        }
      }

      memset(userCommand, 0, sizeof(userCommand));

      continue;
    }

    // printf("%s: command not found\n", input);

    char *argv[10];
    int argc = 0;
    char *token = strtok(input, " ");
    while (token != NULL && argc < 10)
    {
      argv[argc++] = token;
      token = strtok(NULL, " ");
    }
    argv[argc] = NULL;
    char *cmd_path = find_in_path(argv[0]);
    if (cmd_path)
    {
      fork_and_exec_cmd(cmd_path, argc, argv);
    }
    else
      printf("%s: command not found\n", argv[0]);

    fflush(stdout);
  }

  return 0;
}

