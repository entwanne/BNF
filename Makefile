##
## Makefile for parse in /home/rozo_a/temprendu/xml
##
## Made by antoine rozo
## Login <rozo_a@epitech.net>
##
## Started on  Thu Sep 01 12:47:12 2011 antoine rozo
## Last update Tue Jun 11 08:38:41 2013 Antoine Rozo
##

BIN_DIR	=	.
SRC_DIR	=	.
OBJ_DIR	=	obj
CC	=	gcc -W -Wall -ansi -pedantic
EXT	=	c
NAME	=	bnf

SRC	=	$(shell find $(SRC_DIR) -name "*.$(EXT)")
OBJ	=	$(SRC:$(SRC_DIR)/%.$(EXT)=$(OBJ_DIR)/%.o)
TMP	=	$(SRC:%=%~)
DEPS	=	$(OBJ:.o=.d)

OBJDBG	=	$(OBJ:%=%.dbg)
DEPSDBG	=	$(DEPS:%=%.dbg)
NAMEDBG	=	$(NAME:%=%.dbg)

LIB	=	
INC	=	 -I./

ifeq "$(wildcard $(SRC_DIR)/main.$(EXT))" "" # S'il n'y a aucun fichier main
SHARED	=	-shared
else
SHARED	=	
endif

$(NAME)	:	$(OBJ)
		@mkdir -p $(BIN_DIR)
		$(CC) $(SHARED) -o $(NAME) $(OBJ) $(LIB) $(INC)

-include $(DEPS) # Inclue les fichiers .d s'ils sont à jour
# Sinon, recrée chaque fichiers .d et .o
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.$(EXT)
			@mkdir -p `dirname $@`
			$(CC) -MM -MF $(@:.o=.d) -MT $@ $< $(INC)
			$(CC) -c -o $@ $< $(INC)


$(NAMEDBG)	:	$(OBJDBG)
			@mkdir -p $(BIN_DIR)
			$(CC) $(SHARED) -g -o $(NAMEDBG) $(OBJDBG) $(LIB) $(INC)

-include $(DEPSDBG)
$(OBJ_DIR)/%.o.dbg	:	$(SRC_DIR)/%.$(EXT)
				@mkdir -p `dirname $@`
				$(CC) -MM -MF $(@:.o.dbg=.d.dbg) -MT $@ $< $(INC)
				$(CC) -g -c -o $@ $< $(INC)


all	:	$(NAME)

debug	:	$(NAMEDBG)

clean	:
		rm -rf $(OBJ) $(TMP) $(DEPS) $(OBJDBG) $(DEPSDBG) *~

fclean	:	clean
		rm -rf $(NAME) $(NAMEDBG)

re	:	fclean all

redebug	:	fclean debug

run	:	$(NAME)
		@./$(NAME) $(ARGS)
