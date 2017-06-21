/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 10:26:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/26 10:26:16 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler(int signum)
{
	ft_putstr_fd("\nCaught signal (", 2);
	ft_putnbr_fd(signum, 2);
	ft_putendl_fd(") CTRL+C, coming out...", 2);
	exit(1);
}

int		execute(char **args, char **env)
{
	if (args[0] == NULL)
		return (1);
	else if (ft_strequ_case_insen(args[0], "echo"))
		return (!ft_echo(args));
	else if (ft_strequ_case_insen(args[0], "setenv"))
		return (make_setenv(args, env));
	else if (ft_strequ_case_insen(args[0], "unsetenv"))
		return (make_unsetenv(args, env));
	else if (ft_strequ_case_insen(args[0], "env"))
		return (!ft_env(args, env));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args));
	else if (ft_strequ_case_insen(args[0], "cd"))
		return (ft_cd(args, env));
	if (is_file_or_directory(args[0], env))
		return (1);
	return (launch(args, env));
}

int		handling_args(char *args_del, char **env)
{
	int		status;
	char	*line;
	char	**args;

	line = make_str(args_del, env);
	args = ft_split_del(line, DELIM);
	args = delite_q(args);
	status = execute(args, env);
	ft_memdel((void *)&args);
	ft_strdel(&line);
	return (status);
}

void	ft_shell(char **env)
{
	char	*line;
	char	**args_del;
	int		status;
	int		i;

	status = 1;
	while (status)
	{
		ft_putstr(ft_getenv("PROMPT", env));
		line = read_line(env);
		args_del = ft_split_del(line, ";");
		i = -1;
		while (args_del[++i])
			status = handling_args(args_del[i], env);
		ft_memdel((void *)&args_del);
		ft_strdel(&line);
	}
}

int		main(int argc, char **argv, char **env)
{
	char *path_minishell;

	set_input_mode();
	if (argc > 1)
	{
		ft_print_error("minishell: ", argv[1], ERR_IA);
		ft_putendl_fd("usage: ./minishell", 2);
		return (0);
	}
	env = copy_arr_str(env, BUF_ENV);
	ft_setenv("PROMPT", "$> ", 1, env);
	ft_setenv("PROMPT2", "> ", 1, env);
	if ((path_minishell = get_full_path_lokal(argv[0])) != NULL)
	{
		ft_setenv("SHELL", path_minishell, 1, env);
		ft_strdel(&path_minishell);
	}
	signal(SIGINT, sighandler);
	ft_shell(env);
	reset_input_mode();
	return (0);
}
