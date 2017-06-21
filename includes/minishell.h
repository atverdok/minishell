/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 13:40:24 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/28 13:40:49 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

# include "../libft/libft.h"

/*
** waitpid
*/
# include <sys/types.h>
# include <sys/wait.h>

/*
** getcwd MAXPATHLEN
*/
# include <sys/param.h>

/*
** lstat
*/
# include <sys/stat.h>

# include <termios.h>

# define EOF	(-1)
# define BUF_SIZE 32
# define BUF_ENV 256
# define DELIM " "

/*
** 0 -> flag
** 1 -> '
** 2 -> "
** 3 -> `
** 4 -> \
*/
# define IS_FLAG(param_quote) ((param_quote >> 0) & 1)
# define IS_QUOTE(param_quote) ((param_quote >> 1) & 1)
# define IS_DQUOTE(param_quote) ((param_quote >> 2) & 1)
# define IS_BACKSLASH(param_quote) ((param_quote >> 4) & 1)

# define KEY_DOWN	'B'
# define KEY_UP		'A'
# define KEY_LEFT	'D'
# define KEY_RIGHT	'C'

/*
** code errors
*/
# define ERR_PD		1
# define ERR_NSFOD	2
# define ERR_NAD	3
# define ERR_CNF	4
# define ERR_SNIPWD	5
# define ERR_TMA	6
# define ERR_NVITC	7
# define ERR_IA		8
# define ERR_ERROR	9
# define ERR_ILLOP	10

struct termios	g_saved_attributes;

int		ft_echo(char **argv);
int		ft_cd(char **args, char **env);
int		ft_env(char **args, char **env);
int		ft_setenv(char *name, char *value, int ov, char **env);
int		ft_unsetenv(char *name, char **env);
int		ft_exit(char **args);

/*
** launch
*/
int		execute(char **args, char **env);
int		launch(char **args, char **env);
void	ft_shell(char **env);

/*
** env
*/
char	*ft_getenv(char *name, char **env);
char	**copy_arr_str(char **env, size_t size);
int		make_unsetenv(char **args, char **env);
int		make_setenv(char **args, char **env);
int		is_env(char *name, char **env);
void	print_env(char **env);
char	*get_value_env(char **str, char **env);

/*
** util
*/
int		len_arr_str(char **arr);
void	del_arr_str(char **env);
char	*get_full_path_lokal(char *str);
char	*get_pwd(void);
int		hangling_dquote(int *f_q_dq, int c);
int		ft_strequ_case_insen(char const *s1, char const *s2);
char	*ft_del_strstr(char *str, char *str2);
void	move_char(char **str_ptr);
void	ft_print_error(char *name, char *arg, int code);
char	*make_str(char *str, char **env);
int		is_file_or_directory(char *arg, char **env);
char	*read_line(char **env);
char	*ft_strtok_quote(char *str, char *del);
void	*ft_realoc(void *ptr, size_t size);
char	**ft_split_del(char *str, char *delim);
char	**delite_q(char **args);

/*
** util_mode_terminal
*/
void	set_input_mode(void);
void	reset_input_mode(void);

/*
** move_cursor
*/
void	move_left_right(char *buf, int c, int *pos, char **env);
void	move_up_down(char **buf, int c, int *pos, char **env);

/*
** history_command
*/
char	*history(char *buf, int key);

/*
** util_read
*/
void	make_read_str(char **line, char *str2);
int		ft_get_char(void);

/*
** util_read_bufer
*/
int		add_to_buff(char **buf, int *pos, int c);

#endif
