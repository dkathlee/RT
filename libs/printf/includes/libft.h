/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:02:24 by dkathlee          #+#    #+#             */
/*   Updated: 2020/03/24 21:51:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# ifndef INT_MIN
#  define INT_MIN		-2147483648
# endif
# ifndef INT_MAX
#  define INT_MAX		2147483647
# endif
# define ABS(Value)		(((Value) < 0) ? (-Value) : (Value))
# define MIN(A, B)		(((A) > (B)) ? (B) : (A))
# define MAX(A, B)		(((A) > (B)) ? (A) : (B))
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}				t_btree;
typedef struct	s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;
void			ft_bzero(void *buf, size_t count);
void			*ft_memset(void *buf, int ch, size_t count);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *src, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			*ft_strdup(const char *s1);
int				ft_isalpha(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *str);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t len);
char			*ft_strstr(const char *str, const char *to_find);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
void			ft_strclr(char *s);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin2(char const *s1, char const *s2, const char *s3);
char			*ft_strtrim(char const *s);
int				ft_word_count(char const *s, char c);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(long long n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_powi(int nb, int power);
int				ft_powr(int nb, int power);
void			ft_btree_apply_infix(t_btree *root, void (*applyf)(void *));
void			ft_btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void			ft_btree_apply_suffix(t_btree *root, void (*applyf)(void *));
t_btree			*ft_btree_create_node(void *item);
void			ft_btree_insert_data(t_btree **root, void *item,
									int (*cmpf)(void *, void *));
int				ft_btree_level_count(t_btree *root);
void			*ft_realloc(void *src, size_t old_size, size_t new_size);
t_dlist			*ft_dlst_create_elem(void *data);
t_dlist			*ft_dlst_create_elemc(void *data, size_t n);
void			ft_dlst_push_front(t_dlist **dlst, t_dlist *el);
void			ft_dlst_push_back(t_dlist **dlst, t_dlist *el);
void			ft_dlst_delete(t_dlist **dlst);
int				ft_dlst_deli(t_dlist **dlst, size_t i);
t_dlist			*ft_dlst_geti(t_dlist *dlst, size_t i);
t_dlist			*ft_dlst_popi(t_dlist **dlst, size_t i);
int				ft_dlst_len(t_dlist *dlst);
void			ft_dlst_push_sort(t_dlist **dl, t_dlist *el,
									int (*f)(t_dlist*, t_dlist*));
int				ft_dlst_index_of(t_dlist *dl, t_dlist *el);
t_dlist			*ft_dlst_pop(t_dlist **dlst, t_dlist *el);
int				get_next_line(const int fd, char **line);
int				ft_strind(char *str, char c);
char			*ft_itoa_base(unsigned long long nb, const char *base_str);
#endif
