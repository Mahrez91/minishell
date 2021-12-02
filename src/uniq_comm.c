#include "../inc/minishell.h"

int	wejdene(t_comm comm, t_uniq *uniq)
{
	while (comm.redir[uniq->i])
	{
		if ((comm.redir[uniq->i] && (ft_strchr(comm.redir[uniq->i], '>') == 1
					|| ft_strchr(comm.redir[uniq->i], '>') == 2)))
		{
			uniq->retnd = open_file2(comm.redir[uniq->i]);
			close(uniq->retnd);
			if (uniq->retnd == -1)
				return (uniq->retnd);
			uniq->to_write = uniq->i;
		}
		if (comm.redir[uniq->i] && ft_strchr(comm.redir[uniq->i], '<') == 1)
		{
			uniq->retnd = open_file(comm.redir[uniq->i]);
			if (uniq->retnd == -1)
				return (uniq->retnd);
			uniq->to_read = uniq->i;
		}
		uniq->i++;
	}
	return (1);
}

void	reflechir(t_uniq *uniq, char *str, t_comm comm)
{
	if (access(str, F_OK) != 0)
	{
		if (comm.cmd[0])
			printf("%s: command not found\n", comm.cmd[0]);
		g_retval = 1;
		return ;
	}
	else
	{
		uniq->k = fork();
		if (uniq->k == 0)
		{
			exec_cmd(str, comm);
			exit(0);
		}
		else
		{
			waitpid(uniq->k, &uniq->status, 0);
			uniq->k = WEXITSTATUS(uniq->status);
			g_retval = uniq->k;
		}
	}
}

int	red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list)
{
	t_uniq	*uniq;

	uniq = malloc(sizeof(t_uniq) * 1);
	if (!uniq)
		exit(EXIT_FAILURE);
	uniq->to_read = -1;
	uniq->to_write = -1;
	uniq->i = 0;
	if (wejdene(comm, uniq) != 1)
		return (-1);
	if (uniq->to_read >= 0)
		comm.read_file = open_file(comm.redir[uniq->to_read]);
	if (uniq->to_write >= 0)
		comm.write_file = open_file2(comm.redir[uniq->to_write]);
	if (uniq->to_read >= 0 && uniq->to_write >= 0)
		rw_redirection(comm, a_list, b_list, str);
	else if (uniq->to_read < 0 && uniq->to_write >= 0)
		w_redirection(comm, a_list, b_list, str);
	else if (uniq->to_read >= 0 && uniq->to_write < 0)
		r_redirection(comm, a_list, b_list, str);
	else
		reflechir(uniq, str, comm);
	return (1);
}

int	uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list)
{
	t_uniqq	*uniqq;

	if (uniqq_setup(&uniqq, comm, a_list, b_list) != 0)
		return (1);
	if (comm.cmd[0] && access(comm.cmd[0], F_OK) == 0)
		uniqq->str = comm.cmd[0];
	else if (comm.cmd[0] && uniqq->path)
		fill_while(uniqq, comm);
	else if (comm.cmd[0])
	{
		g_retval = 127;
		return (127);
	}
	if (access(uniqq->str, F_OK) != 0)
		return (fill_if(uniqq, comm));
	if (comm.cmd[0] && comm.redir[0])
		return (fill_ret(uniqq, comm, a_list, b_list));
	else
		uniqq_exec(uniqq, comm);
	free_str(uniqq->path);
	g_retval = uniqq->k;
	return (uniqq->k);
}