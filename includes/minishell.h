/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:02:56 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 19:49:23 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	WORD,
	RED_I,
	RED_O,
	RED_A,
	RED_H,
	PIPE,
	T_NULL
}	t_type;

typedef enum s_error
{
	FILE_ERROR,
	CMD_ERROR,
	EXP_ERROR,
	UNSET_ERROR,
	NOT_SET_ERROR,
	NUM_ARG,
	MANY_ARG,
	EXEC_ERROR,
	PERM_ERROR,
}	t_error;

typedef struct s_env
{
	char					*var;
	char					*val;
	int						idx;
	struct s_env			*next;
}	t_env;

typedef struct s_parsing_node
{
	char					*str;
	t_type					type;
	struct s_parsing_node	*next;
}	t_parsing_node;

typedef struct s_infile_node
{
	int						is_heredoc;
	char					*file;
	char					*limiter;
	struct s_infile_node	*hnext;
	struct s_infile_node	*next;
}	t_infile_node;

typedef struct s_outfile_node
{
	char					*file;
	int						type;
	struct s_outfile_node	*next;
}	t_outfile_node;

typedef struct s_cmd_node
{
	int						idx;
	char					**cmd;
	t_infile_node			*infile_node;
	t_outfile_node			*outfile_node;
	struct s_cmd_node		*next;
}	t_cmd_node;

typedef struct s_data
{
	t_env					*envi;
	char					**ev;
	int						fd_in;
	int						fd_out;
	int						cmd_num;
	int						status;
	t_parsing_node			*parse;
	t_infile_node			*heredoc_node;
	t_cmd_node				*node_head;
	t_cmd_node				*curr;
}	t_data;

char		**ft_split_env(t_env *envp);
char		**ft_find_path(t_env *envp);
char		*ft_get_path(char *first_cmd, char **splited_path);
char		*make_exec_path(t_data *data);
void		exec_non_builtin(t_data *data);
int			remove_env(t_data *data, char *var);
void		exec_chdir(t_data *data, char *path, char *old_path);
char		*get_cd_path(t_data *data, char *var);
void		ft_unset(t_data *data);
void		ft_pwd(t_data *data);
void		ft_cd(t_data *data);
void		ft_env(t_data *data);
void		exec_builtin(t_data *data);
int			check_builtin(char *str);
int			no_cmd(t_data *data, int flag);
int			only_one_builtin(t_data *data);
void		run_waitpid(t_data *data, int pid, int i);
int			run_command(t_data *data);
int			print_syntax_err(const char *str);
int			check_pipe_err(t_parsing_node *parse, \
	t_parsing_node *now);
int			check_red_err(t_parsing_node *now);
int			check_quote_err(char *line);
void		ft_interpret(t_parsing_node *parse, t_env *envi, int status);
void		rm_quote(t_parsing_node *node);
char		*interpret(char *str, t_env *envi, int status);
int			get_len_ev(char *str, t_env *envi, int status);
int			key_to_value(char *str, t_env *envi, char **value, int status);
int			is_n_option(char *str);
void		ft_echo(t_data *data);
int			ft_errcm(t_data *data, char *s1, char *s2, int status);
void		ft_werr(char *cmd, char *arg, char *comment, t_error error);
int			ft_error(t_data *data, char *arg, t_error error, int status);
void		make_exec(t_data *data, int flag);
int			run_process(t_data *data, pid_t pid, int fd[2], int prev_fd);
int			make_pipe(t_data *data, int prev_fd);
pid_t		exec_last(t_data *data, int prev_fd);
int			ft_isdigit_str(char *str, int i);
int			ft_exit_atoi(char *str, int *is_not_num, int i);
int			ft_exit_reg(int idx);
int			ft_exit_with_arg(t_data *data, int exit_arg, int is_not_num);
void		ft_exit(t_data *data);
int			ft_search_char(char *s, char c);
int			is_invalid_key(char *s, int flag);
char		*get_env_path(t_env *n_env, char *var);
char		*make_arg(char *cmd, int start, int end);
char		**make_key_value(char *cmd);
void		swap_envp_node(t_env *curr, t_env *next);
void		restore_envp_order(t_data *data);
void		envp_ascending_order(t_data *data);
t_env		*make_envp_node(char *var, char *val);
void		add_env(t_data *data, char *var, char *val);
void		show_export(t_data *data);
void		export_add_key(t_data *data, int i);
void		ft_export(t_data *data);
void		outfile_node_clear(t_outfile_node	*nodes);
void		infile_node_clear(t_infile_node	*nodes);
void		cmd_node_clear(t_cmd_node *nodes);
void		parse_node_clear(t_parsing_node	*nodes);
void		ft_free_data(t_data *data);
void		free_one_input(t_infile_node *input);
void		ft_input_clear(t_infile_node **inputs);
void		free_one_output(t_outfile_node *output);
void		ft_output_clear(t_outfile_node **outputs);
void		*ft_free(void *ptr);
void		free_one_node(t_cmd_node *node);
void		free_double_char(char **cmd);
void		make_sep(char *s, int *index, int *len);
int			is_sep(char *str, int index);
int			is_quote(char *s, int index);
int			get_type(char *str);
void		make_cmd_list(t_parsing_node *parse, t_data *data);
t_cmd_node	*new_cmd_node(t_parsing_node **parse, int i, t_data *data);
char		**set_cmd(t_parsing_node *parsing, t_data *data);
int			get_cmd_num(t_parsing_node *parsing, t_data *data);
void		init_cmd_node(t_cmd_node *node);
t_env		*parse_envp(char **ev);
t_env		*new_envp_node(char *envp);
char		*ft_substr(char *s, int start, int len);
char		*get_value_by_key(t_env *envi, char *var, int len);
void		set_red_lst(t_parsing_node *parse, t_cmd_node *node, t_data *data);
void		set_red(t_parsing_node *parsing, t_cmd_node *node, t_data *data);
void		set_infile_node(t_parsing_node *parsing, void *node);
void		set_outfile_node(t_parsing_node *parsing, void *node);
void		*ft_malloc(int size);
int			make_token(char *line, t_data *data);
char		*ft_worddup(char *str, int index, int len);
void		ft_parse(char *s, t_parsing_node **parse);
int			add_parsing_node(t_parsing_node **now, char *str);
void		append_infile_node(t_infile_node *lst, void *red_node);
void		append_heredoc_node(t_infile_node *lst, void *red_node);
void		append_outfile_node(t_outfile_node *lst, void *red_node);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			read_line(char *limiter, int infile);
char		*make_tmp_name(int idx);
char		*make_heredoc(char *limiter, int idx);
void		set_heredoc(t_data *data);
void		clear_heredoc(t_data *data);
int			input_redirect(t_data *data);
int			ft_fdout(t_outfile_node *curr, int fd_out);
int			ft_fdoutapp(t_outfile_node *curr, int fd_out);
int			output_redirect(t_data *data);
void		action(int signum);
void		rm_ctrl(void);
int			ft_nbchar(char *str, int i, char c);
int			ft_word_cnt(char *str, char c);
char		**ft_setsplit(char *s, char **str, char c);
char		**ft_split(char *str, char c);
void		ft_free_str(char **s1, char **s2);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
size_t		ft_double_strlen(char **str);
int			ft_strlen(char *str);
int			cnt_len(int n);
void		convert_minus(char *arr, int *n, int *len);
char		*ft_itoa(int n);
char		*ft_strdup(const char *s1);
char		*ft_strcat(char *str, char *value);
int			check_dollar(char *str);
void		ft_store_data(t_data **data, char *line, int status, t_env *envi);
void		ft_set_std(t_data *data);
void		run_and_restore(t_data *data);
void		sig_handle(int signum);
int			main(int argc, char **argv, char **env);

#endif
