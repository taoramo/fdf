/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:42:53 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 11:56:39 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_printf {
	va_list	arg_ptr;
	void	*arg;
	int		alt;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		dot;
	int		width;
	int		precision;
	char	type;
	int		written;
}	t_printf;

int			ft_printf(const char *s, ...);
int			count_words_printf(const char *s);
char		**ft_free_arr_printf(char **strs, int i);
int			ft_strlen_printf(const char *s);
void		printf_write_null(t_printf *tab);
int			ft_abs(int i);
void		reset_printf_tab(t_printf *tab);
void		printf_write_percentage(t_printf *tab);
char		**ft_split_printf(const char *s);
char		**ft_free_arr(char **strs, int i);
int			free_printf_mem(t_printf *tab, char **strs);
void		printf_assign_flags(char *str, t_printf *tab, int i);
void		update_tab(char *str, t_printf *tab, va_list arg_ptr);
void		write_pad_chars(char c, int i, t_printf *tab);
void		printf_write_char(t_printf *tab);
void		printf_write_string(t_printf *tab);
int			int_str_size_printf(int n, t_printf *tab);
void		printf_write_int(t_printf *tab);
void		printf_write_int2(t_printf *tab, char pad,
				int padsize, int intlength);
int			int_str_size_printf_us(unsigned int n, t_printf *tab);
void		printf_write_int_us(t_printf *tab);
void		pointer_to_hex_str(char *str, unsigned long int n);
void		unsigned_to_hex_str(char *str,
				unsigned int n, t_printf *tab, int i);
void		printf_write_pointer(t_printf *tab);
int			ft_hexlength(char *str, t_printf *tab);
void		printf_write_hex(t_printf *tab);
void		printf_write_hex2(t_printf *tab, char *str, int padsize, char pad);
void		conversion(char *str, t_printf *tab, va_list arg_ptr);
t_printf	*ft_init_printf_tab(void);
void		ft_putnbr_fd_us(unsigned int nb, int fd);
#endif
