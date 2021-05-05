##
## EPITECH PROJECT, 2021
## my_teams
## File description:
## Makefile
##


all:
	@make --no-print-directory -C server
	@make --no-print-directory -C client

client:
	@make --no-print-directory -C client

server:
	@make --no-print-directory -C server

clean:
	@make clean --no-print-directory -C server
	@make clean --no-print-directory -C client

fclean:
	@make fclean --no-print-directory -C server
	@make fclean --no-print-directory -C client

re:
	@make re --no-print-directory -C server
	@make re --no-print-directory -C client

.PHONY: all clean fclean re client server
