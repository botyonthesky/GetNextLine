/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:17:50 by tmaillar          #+#    #+#             */
/*   Updated: 2023/05/23 17:15:41 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* utiliser pour liberer la memoire alloue pour chaque elememt de la liste.
	_on libere la memoire sur le contenu de l element courant.
	_on save l adresse de l elememt suivant dans next.
	_on libere la memoire sur l element courant.
	_maj du pointeur current avec next pour preparer la prochaine iteration. */

void	ft_free(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current != NULL)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

/* Utliser pour parcourir les elements de la reserve et
		conpter la longueur totale.
   _On calcul le nombre de caract dans la ligne en cours, 
  		en incluant le \n si il y en a un.
   _On alloue la memoire correspondante. 					*/

void	ft_line_size(t_list *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
	stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
}

/* Get_last retourne un pointer sur le dernier element de la stash.
	Ca nous evite de parcourir toute la liste depuis le debut.
	on utilise le pointeur current pour aller direct au dernier  */

t_list	*ft_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current != NULL && current->next != NULL)
		current = current->next;
	return (current);
}

/* On cherche le caract \n dans la liste chainee.
	Renvoie 1 si caracter est trouve, 0 sinon.		*/

int	ft_is_newline(t_list *stash)
{
	int		i;
	t_list	*last_element;

	if (stash == NULL)
		return (0);
	last_element = ft_get_last(stash);
	i = 0;
	while (last_element->content[i])
	{
		if (last_element->content[i] == '\n')
			return (1);
	i++;
	}
	return (0);
}
