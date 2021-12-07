/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:09 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/07 12:11:16 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_str(char **str)
{
	int	line;

	line = 0;
	while (str[line])
	{
		free(str[line]);
		line++;
	}
	free(str);
}

void	free_comm(t_comm comm)
{
	int	i;

	i = 0;
	if (comm.cmd)
		free_str(comm.cmd);
	if (comm.env)
		free_str(comm.env);
	if (comm.redir)
		free_str(comm.redir);
	if (comm.redir_temp)
		free_str(comm.redir_temp);
}

void	free_pipe(t_pipe *comm)
{
	t_pipe	*elem;

	while (comm)
	{
		elem = comm->next;
		free(comm->path);
		free_str(comm->cmd);
		free_str(comm->redir);
		if (comm->file_to_in)
			free(comm->file_to_in);
		if (comm->file_to_out)
			free(comm->file_to_out);
		free(comm);
		comm = elem;
	}
}

int	free_uniqq_norme(t_uniqq *uniqq)
{
	free_str(uniqq->path);
	free(uniqq);
	g_retval = 127;
	return (127);
}
