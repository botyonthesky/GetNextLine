/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:01:02 by tmaillar          #+#    #+#             */
/*   Updated: 2023/05/23 17:14:17 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* etapes: _on veut lire ce qu il y a dans notre fichier et le 
				mettre dans la liste chainee.
 * 	  	   _on veut sortir ce qu il y a dans la reserve et le
				mettre dans line.
 *         _on nettoie la reseve et on renvoie line 			*/

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	ft_read_and_store_data(fd, &stash);
	if (!stash)
		return (NULL);
	ft_build_final_line(stash, &line);
	ft_clean(&stash);
	if (line[0] == '\0')
	{
		ft_free(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* On utilise read pour lire les donnees du fd et elles sont 
	stockes dans la reserve.
   _Readed init a 1 pour garantir de rentrer au moins une fois dans la boucle 
    afin de gerer les cas ou il y aurai deja des donnee dans la reserve. 	*/

void	ft_read_and_store_data(int fd, t_list **stash)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_is_newline(*stash) && bytes_read > 0)
	{
		tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tmp)
			return ;
		bytes_read = (int)read(fd, tmp, BUFFER_SIZE);
		if ((*stash == NULL && bytes_read == 0) || bytes_read == -1)
		{
			free(tmp);
			return ;
		}
		tmp[bytes_read] = '\0';
		ft_insert_to_stash(stash, tmp, bytes_read);
		free(tmp);
	}
}

/* on utilise cette fonction pour ajouter le contenu de tmp,
   a la fin de la reserve et si la liste est vide, 
   il devient le premier element de la liste. 				*/

void	ft_insert_to_stash(t_list **stash, char *tmp, int bytes_read)
{
	int		i;
	t_list	*last_element;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * bytes_read + 1);
	if (new->content == NULL)
		return ;
	i = 0;
	while (tmp[i] && i < bytes_read)
	{
		new->content[i] = tmp[i];
		i++;
	}
	new->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new;
		return ;
	}
	last_element = ft_get_last(*stash);
	last_element->next = new;
}

/* on recupere les lignes stockees dans la stash, pour 
	construire la ligne finale. On parcours et on copie les 
	caracteres dans line et on s arrete au premier \n.		*/

void	ft_build_final_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	ft_line_size(stash, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/* Apres avoir extrait la ligne qui a ete lu, nous n avons plus besoin 
   de ces caract, cette fct nettoie la stash, pour que seulement les 
   caract qui n ont pas ete renvoye par gnl reste dans cette stash static.
   On alloue la memoire en calculant la difference entre la longueur totale
   du contenu et i qui correspond a la longueur du contenu avec le \n.  */

void	ft_clean(t_list **stash)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (clean == NULL || stash == NULL)
		return ;
	clean->next = NULL;
	last = ft_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content != NULL && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char)
			* (ft_strlen(last->content) - i + 1));
	if (clean->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	ft_free(*stash);
	*stash = clean;
}

// #include <stdio.h>
// int   main()
// {
//   char  *line;
//   int   fd;

//   fd = open("42", O_RDONLY);
//   if (fd == -1)
//   {
//         printf("error opening");
//         return (1);
//   }

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break;
// 		free(line);
// 	}
//   close(fd);
//   return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s;

// 	write(STDOUT_FILENO, "Type then press enter, type 'q' to exit :\n", 42);
// 	s = NULL;
// 	while (1)
// 	{
// 		free(s);
// 		write(STDOUT_FILENO, "<< ", 3);
// 		s = get_next_line(STDIN_FILENO);
// 		printf(">> %s", s);
// 		if (strcmp(s, "q\n") == 0)
// 		{
// 			free(s);
// 			break;
// 		}
// 	free(s);
// 	}
// 	free(s);
// 	printf("bye!\n");
// 	return (0);
// }