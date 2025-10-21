#include "parsing.h"

static bool	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND);
}

static bool	validate_pipe(int i, t_token_type prev, const char *cmdline)
{
	if (i == 0 || prev == TOKEN_PIPE)
	{
		syntax_error_unexpected_token("|", cmdline);
		return (false);
	}
	return (true);
}

static bool	validate_heredoc(char **tokens, int i)
{
	if (!tokens[i + 1] || get_token_type(tokens[i + 1]) != TOKEN_WORD)
	{
		syntax_error_unexpected_token(tokens[i + 1], NULL);
		return (false);
	}
	return (true);
}

static bool	validate_redir(char **tokens, int i, const char *cmdline)
{
	if (!tokens[i + 1] || get_token_type(tokens[i + 1]) != TOKEN_WORD)
	{
		syntax_error_unexpected_token(tokens[i + 1], cmdline);
		return (false);
	}
	return (true);
}

// bool	validate_current_token(char **tokens, int i, t_token_type curr,
// 	t_token_type prev, const char *cmdline)
// {
// 	if (curr == TOKEN_PIPE)
// 	{
// 		if (!validate_pipe(i, prev, cmdline))
// 			return (false);
// 	}
// 	if (curr == TOKEN_HEREDOC)
// 	{
// 		if (!validate_heredoc(tokens, i))
// 			return (false);
// 	}
// 	if (is_redir_token(curr))
// 	{
// 		if (!validate_redir(tokens, i, cmdline))
// 			return (false);
// 	}
// 	return (true);
// }

bool	validate_current_token(t_validate_ctx *ctx, int i)
{
	if (ctx->curr == TOKEN_PIPE)
	{
		if (!validate_pipe(i, ctx->prev, ctx->cmdline))
			return (false);
	}
	if (ctx->curr == TOKEN_HEREDOC)
	{
		if (!validate_heredoc(ctx->tokens, i))
			return (false);
	}
	if (is_redir_token(ctx->curr))
	{
		if (!validate_redir(ctx->tokens, i, ctx->cmdline))
			return (false);
	}
	return (true);
}
