/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cbin3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:53 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/07 11:36:54 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_if1pip(t_pipe *comm, t_fill *fill, char *cmd)
{
	comm->cmd[fill->arg] = malloc(sizeof(char) * 400);
	fill->i++;
	while (cmd[fill->i] && cmd[fill->i] != 32)
	{
		comm->cmd[fill->arg][fill->argindex] = cmd[fill->i];
		fill->i++;
		fill->argindex++;
	}
	comm->cmd[fill->arg][fill->argindex] = '\0';
	fill->arg++;
	fill->argindex = 0;
}

void	fill_elsepip1(t_pipe *comm, t_fill *fill, char *cmd)
{
	comm->redir[fill->red] = malloc(sizeof(char) * 400);
	while (cmd[fill->i] && cmd[fill->i] != 32)
	{
		comm->redir[fill->red][fill->redindex] = cmd[fill->i];
		fill->i++;
		fill->redindex++;
	}
	comm->redir[fill->red][fill->redindex] = '\0';
	fill->red++;
	fill->redindex = 0;
}

void	fill_elsepip3(t_pipe *comm, t_fill *fill)
{
	comm->cmd[fill->arg] = malloc(sizeof(char) * 5);
	comm->cmd[fill->arg][fill->argindex] = '\0';
	fill->argindex = 0;
	fill->arg++;
	fill->i += 2;
}

void	fill_elsepip4(t_pipe *comm, t_fill *fill, char *cmd)
{
	comm->cmd[fill->arg] = malloc(sizeof(char) * 400);
	while (cmd[fill->i] && cmd[fill->i] != 32)
	{
		comm->cmd[fill->arg][fill->argindex] = cmd[fill->i];
		fill->i++;
		fill->argindex++;
	}
	if (cmd[fill->i] && cmd[fill->i] == 32)
		fill->i++;
	comm->cmd[fill->arg][fill->argindex] = '\0';
	fill->argindex = 0;
	fill->arg++;
}

void	fill_elsepip2(t_pipe *comm, t_fill *fill, char *cmd)
{
	if (cmd[fill->i] == '<' && cmd[fill->i + 1] && cmd[fill->i + 1] == '<'
		&& cmd[fill->i + 2]
		&& (cmd[fill->i + 2] != '<' && cmd[fill->i + 2] != '>'))
	{
		while (cmd[fill->i] && cmd[fill->i] != 32 && cmd[fill->i] != 24)
			fill->i++;
	}
	else
	{
		comm->redir[fill->red] = malloc(sizeof(char) * 400);
		while (cmd[fill->i] && cmd[fill->i] != 32)
		{
			comm->redir[fill->red][fill->redindex] = cmd[fill->i];
			fill->i++;
			fill->redindex++;
		}
		comm->redir[fill->red][fill->redindex] = '\0';
		fill->red++;
		fill->redindex = 0;
	}
}
