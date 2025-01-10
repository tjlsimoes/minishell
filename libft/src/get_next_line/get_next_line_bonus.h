/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:13:05 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/18 13:14:37 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_FD 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*ft_strjoin_and_free(char const *s1, char const *s2);
char		*get_next_line(int fd);
char		*ft_read_to_leftover(int fd, char *leftover);
char		*ft_get_line(char *leftover);
char		*ft_new_leftover(char *leftover);

#endif