#include "../header/minishell.h"


void	print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD)
			printf("[WORD]      :\t%s\n", tokens->str);
		else if (tokens->type == TOKEN_PIPE)
			printf("[PIPE]      :\t%s\n", tokens->str);
 		else if (tokens->type == TOKEN_REDIR_IN)
			printf("[REDIR_IN]  :\t%s\n", tokens->str);
		else if (tokens->type == TOKEN_REDIR_OUT)
			printf("[REDIR_OUT] :\t%s\n", tokens->str);
		else if (tokens->type == TOKEN_APPEND)
			printf("[APPEND]    :\t%s\n", tokens->str);
		else if (tokens->type == TOKEN_HEREDOC)
			printf("[HERE_DOC]  :\t%s\n", tokens->str);
		tokens = tokens->next;
	}
}

void	teste_token(void)
{
	t_token	*head = NULL;
	
	ft_token_add_back(&head, ft_token_new("hello", TOKEN_WORD));
	ft_token_add_back(&head, ft_token_new("World", TOKEN_WORD));
	ft_token_add_back(&head, ft_token_new("|", TOKEN_PIPE));
	ft_token_add_back(&head, ft_token_new(">", TOKEN_REDIR_OUT));
	
	print_token(head);
}
