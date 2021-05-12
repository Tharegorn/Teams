##
## EPITECH PROJECT, 2021
## my_teams
## File description:
## Makefile
##


all:
	@make --no-print-directory -C server
	@make --no-print-directory -C client
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

client:
	@make --no-print-directory -C client
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

server:
	@make --no-print-directory -C server
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

clean:
	@make clean --no-print-directory -C server
	@make clean --no-print-directory -C client
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

fclean:
	@make fclean --no-print-directory -C server
	@make fclean --no-print-directory -C client
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

re:
	@make re --no-print-directory -C server
	@make re --no-print-directory -C client
	@export LD_LIBRARY_PATH="$PWD/libs/myteams/"

.PHONY: all clean fclean re client server
