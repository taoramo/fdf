/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:21:15 by toramo            #+#    #+#             */
/*   Updated: 2023/11/10 13:21:16 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif
# ifndef FD_MAX
#  define FD_MAX 256
# endif
# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);
int			ft_strlen_gnl(char *str, int len, int flag);
char		*cp_and_move(char *str, int *strlen, int *in_buffer, char *buf);
char		*gnl_insert_null(char *str, int strlen);
char		*free_if_exists(char *str, int *in_buffer);
#endif
