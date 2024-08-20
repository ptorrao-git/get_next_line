/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:48:25 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/06/21 15:33:59 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_strclen(char *str, char c);

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strndup(char *s, int len);
char	*ft_strjoin(char *s1, char *s2);

#endif