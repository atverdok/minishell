/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:04:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/06/21 15:04:09 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_read_str(char **line, char *str2)
{
	if (*line == NULL)
		*line = str2;
	else
	{
		ft_memcpy((*line + ft_strlen(*line)), str2, ft_strlen(str2));
		ft_strdel(&str2);
	}
}

int		ft_get_char(void)
{
	static int		ch;
	static ssize_t	len = 0;

	len = read(STDIN_FILENO, &ch, 1);
	if (!len)
		return (EOF);
	else
		return (ch);
}
