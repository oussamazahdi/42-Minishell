#include "include/minishell.h"

void ft_clear_node(t_token **token)
{
	if ((*token) && (*token)->content)
		free((*token)->content);
	(*token)->content = NULL;
	if (*token)
		free(*token);
	*token = NULL;
}

void ft_clear_empty_nodes(t_token **token)
{
	t_token *tmp;
	t_token *prev;

	// prev = *token;
	prev = NULL;
	while ((*token))
	{
		tmp = (*token)->next;
		if((*token) && !ft_strlen((*token)->content) && (*token)->flag == false)
		{
			/*
			 * i need to free the node
			 * token pointer should to point on tmp
			 * check if prev existe the next of prev = tmp
			 * 
			 * This function is used to free the memory allocated for a node and update the token pointer to point to the next node.
			 * It also checks if the previous node exists and updates the next pointer of the previous node to point to the next node.
			 */
			ft_clear_node(token);
			if (prev)
				prev->next = tmp;
			(*token) = tmp;
		}
		else
		{
			prev = *token;
			if (*token)
				(*token) = (*token)->next;
		}
	}
}
