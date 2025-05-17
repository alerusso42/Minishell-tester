#–– Compiler settings
CC       = cc
CFLAGS   = -g -Wall -Werror -Wextra -I./$(LIBFT_DIR)
LDFLAGS  = -lreadline -lhistory -lncurses

#–– Library
LIBFT_DIR = Libft
DEBUG_DIR = debug_dir
LIBFT     = $(LIBFT_DIR)/libft.a

#–– Target
NAME     = tester

#––	Suppression file
SUPP_FILE = $(shell pwd)/supp.supp

#–– All source files, with their relative paths
SRCS = \
  main.c \

#–– Object files go under obj/, mirroring the tree
OBJ_DIR = obj
OBJS    = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))


all: $(NAME)

#–– Link the final minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

#–– Build libft (bonus) before anything else
$(LIBFT): 
	$(MAKE) all -C $(LIBFT_DIR)

#–– Single pattern rule for every .c → .o
#––   - mkdir -p $(dir $@) makes sure subdirs exist
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean frm
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --track-origins=yes -s -q --suppressions=$(SUPP_FILE) ./minishell

supp: 
	$(MAKE) val -C executor/
	mv $(DEBUG_DIR)/v.supp .
	mv v.supp $(SUPP_FILE)

deb:
	$(MAKE) gdb -C $(DEBUG_DIR)/
	mv $(DEBUG_DIR)/a.gdb .

frm: 
	rm -f *.txt *.gdb *.supp
	rm -f mini_output bash_output

git: fclean 
	git add . && git commit -m "$(M)" && git push && echo "Push done" || echo "Usage: make git M=\"msg\""

re: fclean all

#–– phony targets
.PHONY: all clean fclean re

.SILENT: