/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:50:57 by tmaillar          #+#    #+#             */
/*   Updated: 2023/05/22 17:22:05 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	ft_read_and_store_data(int fd, t_list **stash);
void	ft_insert_to_stash(t_list **stash, char *tmp, int bytes_read);
void	ft_build_final_line(t_list *stash, char **line);
void	ft_line_size(t_list *stash, char **line);
void	ft_clean(t_list **stash);
void	ft_free(t_list *stash);
int		ft_is_newline(t_list *stash);
t_list	*ft_get_last(t_list *stash);
int		ft_strlen(const char *s);

#endif
