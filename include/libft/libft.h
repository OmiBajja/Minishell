/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:48:50 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:42:05 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// KOLOR
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// BALD KOLOR
# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BPURPLE "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

// UNDERLINE
# define UBLACK "\033[4;30m"
# define URED "\033[4;31m"
# define UGREEN "\033[4;32m"
# define UYELLOW "\033[4;33m"
# define UBLUE "\033[4;34m"
# define UPURPLE "\033[4;35m"
# define UCYAN "\033[4;36m"
# define UWHITE "\033[4;37m"

# define CLEAR "\033c"
# define RESET_COLOR "\e[m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Alloue de la mémoire et l'initialise à zéro */
void				*ft_calloc(size_t elementCount, size_t elementSize);

/* Vérifie si le caractère est dans la table ASCII */
int					ft_isascii(int str);

/* Duplique un tableau de chaînes de caractères */
char				**ft_strsndup(char **src, size_t size);

/* Libère la mémoire d'un tableau de chaînes */
void				ft_freestrs(char **tab);

/* Convertit un entier en chaîne de caractères */
char				*ft_itoa(int n);

char				*ft_itoa_long(long long n);

/* Affiche un caractère (version pour ft_printf) */
int					ft_putchar_pf(char c);

int					ft_putchar_pfd(int fd, char c);

/* Affiche une chaîne (version pour ft_printf) */
int					ft_putstr_pf(char *s);

int					ft_putstr_pfd(int fd, char *s);

/* Remplit une zone mémoire avec une valeur donnée */
void				*ft_memset(void *str, int a, size_t n);

/* Écrit un nombre sur un descripteur de fichier */
void				ft_putnbr_fd(int n, int fd);

/* Affiche un nombre entier */
void				ft_putnbr(int n);

/* Recherche un caractère dans une chaîne */
char				*ft_strchr(const char *str, int tofind);

/* Concatène deux chaînes de caractères */
char				*ft_strjoin(char const *s1, char const *s2);

/* Calcule la longueur d'une chaîne */
int					ft_strlen(const char *str);

/* Recherche une sous-chaîne dans une chaîne avec limite */
char				*ft_strnstr(const char *str, const char *tofind, int n);

/* Extrait une sous-chaîne d'une chaîne */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/* Convertit une chaîne en entier */
int					ft_atoi(const char *str);

long long			ft_atoi_long(const char *str);

/* Vérifie si le caractère est alphanumérique */
int					ft_isalnum(int str);

/* Vérifie si le caractère est un chiffre */
int					ft_isdigit(int str);

/* Copie une zone mémoire vers une autre */
void				*ft_memcpy(void *dest, const void *src, size_t size);

/* Écrit un caractère sur un descripteur de fichier */
void				ft_putchar_fd(char c, int fd);

/* Affiche un caractère */
void				ft_putchar(char c);

/* Écrit une chaîne sur un descripteur de fichier */
void				ft_putstr_fd(char *s, int fd);

/* Affiche une chaîne de caractères */
void				ft_putstr(char *s);

/* Duplique une chaîne de caractères */
char				*ft_strdup(const char *src);

/* Concatène deux chaînes avec une taille maximale */
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/* Applique une fonction à chaque caractère d'une chaîne */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Recherche la dernière occurrence d'un caractère */
char				*ft_strrchr(const char *str, int tofind);

/* Convertit un caractère en minuscule */
int					ft_tolower(int c);

/* Initialise à zéro une zone mémoire */
void				*ft_bzero(void *str, size_t n);

/* Vérifie si le caractère est alphabétique */
int					ft_isalpha(int str);

/* Vérifie si le caractère est imprimable */
int					ft_isprint(int str);

/* Déplace une zone mémoire vers une autre (même chevauchante) */
void				*ft_memmove(void *dest, const void *src, size_t size);

/* Recherche un octet dans une zone mémoire */
void				*ft_memchr(const void *str, int searchedChar, size_t size);

/* Compare deux zones mémoire */
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t size);

/* Écrit une chaîne suivie d'un retour à la ligne */
void				ft_putendl_fd(char *s, int fd);

/* Divise une chaîne selon un délimiteur */
char				**ft_split(char const *s, char c);

/* Applique une fonction à chaque caractère avec index */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/* Copie une chaîne avec une taille maximale */
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/* Compare deux chaînes avec limite */
int					ft_strncmp(const char *str1, const char *str2, int n);

/* Compare deux chaînes */
int					ft_strcmp(const char *str1, const char *str2);

/* Supprime des caractères au début et à la fin d'une chaîne */
char				*ft_strtrim(char const *s1, char const *s2);

/* Convertit un caractère en majuscule */
int					ft_toupper(int c);

/* Crée un nouvel élément de liste chaînée */
t_list				*ft_lstnew(void *content);

/* Ajoute un élément au début de la liste */
void				ft_lstadd_front(t_list **lst, t_list *new);

/* Compte le nombre d'éléments dans une liste */
int					ft_lstsize(t_list *lst);

/* Retourne le dernier élément d'une liste */
t_list				*ft_lstlast(t_list *lst);

/* Ajoute un élément à la fin de la liste */
void				ft_lstadd_back(t_list **lst, t_list *new);

/* Supprime un élément de la liste */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/* Supprime et libère une liste entière */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/* Applique une fonction à chaque élément de la liste */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/* Crée une nouvelle liste en appliquant une fonction */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/* Version personnalisée de printf */
int					ft_printf(const char *str, ...);

int					ft_printf_fd(int fd, const char *str, ...);

/* Affiche une adresse mémoire (pour ft_printf) */
int					ft_printadress(unsigned long ptr);

int					ft_printadress_fd(int fd, unsigned long ptr);

/* Affiche un caractère (pour ft_printf) */
int					ft_putchar_pf(char c);

/* Affiche une chaîne (pour ft_printf) */
int					ft_putstr_pf(char *s);

int					ft_putstr_pfd(int fd, char *s);

/* Affiche un nombre non signé (pour ft_printf) */
int					ft_putnbr_upf(unsigned int n, int *count);

int					ft_putnbr_upfd(int fd, unsigned int n, int *count);

/* Affiche un nombre (pour ft_printf) */
int					ft_putnbr_pf(int n, int *count);

int					ft_putnbr_pfd(int fd, int n, int *count);

/* Affiche un nombre en hexadécimal minuscule */
int					ft_putnbrhexalow(unsigned int n, int *count);

int					ft_putnbrhexalow_fd(int fd, unsigned int n, int *count);

/* Affiche un nombre en hexadécimal majuscule */
int					ft_putnbrhexaupp(unsigned int n, int *count);

int					ft_putnbrhexaupp_fd(int fd, unsigned int n, int *count);

/* Calcule le nombre de chaînes dans un tableau de chaînes */
int					ft_strslen(char **str);

char				*ft_strstr(char *str, char *to_find);

char				**ft_split_str(char *str, char *charset);

#endif
