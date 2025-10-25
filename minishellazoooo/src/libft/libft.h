/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:53:51 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/24 04:40:10 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <inttypes.h>
# include <stddef.h>
# include <limits.h>
# include <sys/types.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t	ft_strlen(const char *str);
int		ft_strlen_pf(const char *str);
int		ft_int_strlen(char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strncpy(char *dest, char *src, int size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f) (unsigned int, char*));

//puts
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//lists
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_printf
int		ft_putchar_fd_pf(char c, int fd);
int		ft_putnbr_fd_pf(int nbr, int fd);
int		ft_putstr_fd_pf(char *str, int fd);
int		ft_putnbr_base_fd(unsigned long nbr, char *base, int fd);
int		ft_put_ptr_fd(void *ptr, int fd);
int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);

//gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(char *str, int c);
char	*ft_substr_gnl(char *s, int start, int len);
char	*read_buffer(int fd, char *storage);
char	*add_line(char *storage);
char	*clean(char *storage);

//so_long
void	free_map(char **map, int lines);
char	**copy_matrix(char **matrix);

//freeing
void	free_array(char **array);
void	free_int_array(int **array, int count);
#endif