

CC = gcc

CFLAGS = -Wall --std=c11



client: client.c disp_menu.c send_data.c client_helper.c
	gcc -Wall  -o client client.c disp_menu.c send_data.c client_helper.c

server: server.c send_data.c server_functions.c read_files.c
	gcc -Wall -o server server.c send_data.c server_functions.c read_files.c


clean: 
	rm server client




