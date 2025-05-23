#include "header.h"

int		get_test_lines(t_tester *data);
void	redir_input(t_tester *data, bool which);
//int		exec_test(t_tester *data, bool which);
int		exec_test(bool which);

/*
void	rm_readline_prompt(t_tester *data)
{
	
}*/

int		exec_test(bool which)
{
	char	**argv = {NULL};
	unsigned char	n;
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
	n = (unsigned char)exit_code;
	l_printf("\nexit: %d\n\n", n);
	return (0);
}

void	redir_input(t_tester *data, bool which)
{
	data->script = open(SCRIPT_FILE, O_RDONLY);
	if (data->script < 0)
		perror("open");
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
		unlink(SCRIPT_FILE);
	data->script = open(SCRIPT_FILE, O_RDWR | O_CREAT, 0666);
	while (1)
	{
		if (!line)
			return (1);
		if (ft_strncmp(line, "EOT", 3) == 0)
		{
			free(line);
			//line = ft_strdup("exit\n");
			//ft_putstr_fd(line, data->script);
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
			//fd_printf(data->script, "echo $?\n");
			free(line);
			line = gnl(data->test_list);
		}
	}
	close(data->script);
	data->script = open(SCRIPT_FILE, O_RDWR | O_CREAT, 0666);
	return (data->script == -1);
}

/* REVIEW
//		1) 	if there's a specific test in argv[1],
			otherwise open basic test file TEST_FILE;
		2)	Check if files exist;
		3)	Open 2 output files: 1 for bash and 1 for mini outputs
		4)	a file named script.sh is created: inside is stored
			the list of command the shell should execute.
			for every test, the tester gets from the list of test
			one block of commands, and prints it on script.sh
		5)	While there are tests to do in the list of test,
			create script.sh files to execute;
		6)	Redir the STDIN on the script.sh file;
		7)	The output of bash is redirected in the bash_output file.
			The output of mini is redirected in the mini_output file.
		
		//TODO - A diff that works with mini and bash output files 	 
*/
int	main(int argc, char *argv[], char *env[])
{
	(void)argc, (void)env;
	t_tester	data;

	if (argv[1])
		data.test_list = open(argv[1], O_RDONLY);
	else
		data.test_list = open(TEST_FILE, O_RDONLY);
	if (data.test_list < 0)
	{
		if (argv[1])
			return (fd_printf(2, "\nCannot open |%s|\n", argv[1]));
		else
			return (fd_printf(2, "\nCannot open |%s|\n", argv[1]));
	}
	data.stdinput = dup(STDIN_FILENO);
	data.stdoutput = dup(STDOUT_FILENO);
	data.mini_output = open(MINI_OUT, O_RDWR | O_CREAT | O_TRUNC, 0777);
	data.bash_output = open(BASH_OUT, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!data.mini_output || !data.bash_output)
	{
		fd_printf(2, "\nOpen does not work\n");
		return (close(data.mini_output), close(data.bash_output), 1);
	}
	while (get_test_lines(&data) == 0) // scriviamo su script.sh 
	{
		redir_input(&data, BASH);
		exec_test(BASH);
		system("sed -Ei '/total/d' bash_output");
		close(data.script);
		redir_input(&data, MINI);
		exec_test(MINI);
		system("sed -Ei '/total/d' mini_output");
	}
	close(data.stdinput);
	close(data.stdoutput);
	close(data.test_list);
	close(data.script);
}
