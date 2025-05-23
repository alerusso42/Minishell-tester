
#define MINI_PATH "../minishell"
#define BASH_PATH "/bin/bash"
#define TEST_FILE "list_test"
#define SCRIPT_FILE "script.sh"
#define MINI_OUT "mini_output"
#define BASH_OUT "bash_output"
#include <stdbool.h>
#include <sys/wait.h>
#include "../Libft/all.h"

typedef struct s_tester
{
	int				test_list;
	int				script;
	int				bash_output;
	int				mini_output;
	int				stdinput;
	int				stdoutput;
	unsigned char	exits;
}t_tester;

enum which
{
	MINI,
	BASH
};
