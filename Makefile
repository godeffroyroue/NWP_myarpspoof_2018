##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

D_SRCH=	$(realpath ./include/)

DIR= $(realpath ./src)

NAME=	myARPspoof

OBJ=	$(SRC:.c=.o)

SRC =	$(DIR)/main.c			\
		$(DIR)/broadcast.c		\
		$(DIR)/create_socket.c	\
		$(DIR)/build_arp.c		\
		$(DIR)/build_eth.c		\
		$(DIR)/send.c			\
		$(DIR)/print_packet.c

CFLAGS += -Wall -Wextra -Iinclude $(D_SRCH)

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) -lcrypto $(OBJ) $(LDFLAGS) -o $(NAME)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f *.o

make re: fclean all
