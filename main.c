#define MINI_PATH "../minishell"
#define BASH_PATH "/bin/bash"
#define TEST_FILE "list_test"
#include <stdbool.h>
#include <sys/wait.h>
#include "Libft/all.h"

typedef struct s_tester
{
	int				test_list;
	int				script;
	int				bash_output;
	int				mini_output;
	unsigned char	exits;
}t_tester;

enum which
{
	MINI,
	BASH
};

int		get_test_lines(t_tester *data);
void	redir_input(t_tester *data, bool which);
//int		exec_test(t_tester *data, bool which);
int		exec_test(bool which);

int		exec_test(bool which)
{
	char	**argv = {NULL};
	//char	*num;
	int		exit_code;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (printf("vaffanculo"), 1);
	else if (pid == 0)
	{
		if (which == MINI)
		{
			execve(MINI_PATH, argv, __environ);
		}
		else if (which == BASH)
		{
			execve(BASH_PATH, argv, __environ);
		}
		exit(1);
	}
	wait(&exit_code);
	/*data->exits = exit_code;
	num = ft_itoa((int)data->exits);
	ft_putstr_fd(num, 1);
	ft_putstr_fd("\n", 1);*/
	return (0);
}

void	redir_input(t_tester *data, bool which)
{
	dup2(data->script, STDIN_FILENO);
	if (which == MINI)
	{
		dup2(data->mini_output, STDOUT_FILENO);
		dup2(data->mini_output, STDERR_FILENO);
	}
	else
	{
		dup2(data->bash_output, STDOUT_FILENO);
		dup2(data->bash_output, STDERR_FILENO);
	}
}
/* REVIEW 
If there is not script file

*/
int	get_test_lines(t_tester *data)
{
	char	*line;

	if (data->script < 0)
		return (1);
	line = gnl(data->test_list);
	if (line)
		unlink("script.sh");
	data->script = open("script.sh", O_RDWR | O_CREAT, 0666);
	while (1)
	{
		if (!line)
			return (1);
		if (ft_strncmp(line, "EOT", 3) == 0)
		{
			free(line);
			line = ft_strdup("exit $?\n");
			ft_putstr_fd(line, data->script);
			break ;
		}
		if (line[0] == '#' || line[0] == '\n')
		{
			free(line);
			line = gnl(data->test_list);
		}
		else
		{
			ft_putstr_fd(line, data->script);
			fd_printf(data->script, "echo Exit code of command: $?\n", line);
			free(line);
			line = gnl(data->test_list);
		}
	}
	close(data->script);
	data->script = open("script.sh", O_RDWR | O_CREAT, 0666);
	return (data->script == -1);
}

/* REVIEW
Check if there's a specific test, otherwise open basic test file
Check if files exist
Open 2 output files: 1 for bash and 1 for mini outputs
Exec get_next_line on test file until there's no other EOT (End Of Test) 
*/
int	main(int argc, char *argv[], char *env[])
{
	(void)argc, (void)env;
	t_tester	data;

	if (argv[1])
		data.test_list = open(argv[1], O_RDONLY);
	else
		data.test_list = open(TEST_FILE, O_RDONLY);
	printf("fd %d\n", data.test_list);
	if (data.test_list < 0)
	{
		if (argv[1])
			return (printf("\nCannot open |%s|\n", argv[1]));
		else
			return (printf("\nCannot open |%s|\n", argv[1]));
	}
	data.mini_output = open("mini_output", O_RDWR | O_CREAT | O_APPEND, 0777);
	data.bash_output = open("bash_output", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (get_test_lines(&data) == 0)
	{
		redir_input(&data, BASH);
		exec_test(BASH);
		redir_input(&data, MINI);
		exec_test(MINI);
	}
	close(data.test_list);
	close(data.script);
}