##
## EPITECH PROJECT, 2017
## makefile
## File description:
## makefile
##

SRC	=	main.c			\
		arp_spoof.c		\
		check.c			\
		print_packet.c		\
		init_packets.c		\
		socket.c		\
		receive.c		\
		my_free.c

OBJ	=	$(SRC:.c=.o)

NAME	=	myARPspoof

CFLAGS	=	-W -Wall -Werror -Wextra -L -I. -ggdb -g3

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f *# *~ $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
