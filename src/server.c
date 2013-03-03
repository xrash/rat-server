#include "server.h"
#include "events.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void run(char * port, int debug)
{
    int server = 0;
    int *x, *y;
    unsigned char code, buffer[5], buffer_x[sizeof(int)], buffer_y[sizeof(int)];
    struct addrinfo hints, *server_info;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_length = sizeof(client_addr);

    printf("%s\t%d\n", port, debug);

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port, &hints, &server_info);

    server = socket(server_info->ai_family,
		    server_info->ai_socktype,
		    server_info->ai_protocol);

    bind(server, server_info->ai_addr, server_info->ai_addrlen);

    printf("Listening on port: %s\n", port);

    while (1) {
	memset(buffer, 0, sizeof(buffer));
	recvfrom(server,
		 buffer,
		 sizeof(buffer),
		 0,
		 (struct sockaddr *)
		 &client_addr,
		 &client_addr_length);

	code = buffer[0];

	if (debug) {
	    int i = 0;
	    for (i = 0; i < sizeof(buffer); i++) {
		printf("\t0x%02x", buffer[i]);
	    }
	    printf("\n");
	    for (i = 0; i < sizeof(buffer); i++) {
		printf("\t%d", buffer[i]);
	    }
	    printf("\n");
	    printf("\n");
	}

	switch (code) {
	    case 0x10:
		left_mouse_button_press();
		left_mouse_button_release();
		break;

	    case 0x11:
		left_mouse_button_press();
		break;

	    case 0x12:
		left_mouse_button_release();
		break;

	    case 0x20:
		right_mouse_button_press();
		right_mouse_button_release();
		break;

	    case 0x21:
		right_mouse_button_press();
		break;

	    case 0x22:
		right_mouse_button_release();
		break;

	    case 0x30:
		mouse_wheel_up();
		break;

	    case 0x31:
		mouse_wheel_down();
		break;

	    case 0x40:
		memset(buffer_x, 0, sizeof(buffer_x));
		memset(buffer_y, 0, sizeof(buffer_y));
		buffer_x[0] = buffer[2];
		buffer_x[1] = buffer[1];
		buffer_y[0] = buffer[4];
		buffer_y[1] = buffer[3];

		x = (int *) buffer_x;
		y = (int *) buffer_y;

		mouse_move(*x, *y);
		break;

	    case 0xFF:
		sendto(server, (unsigned char *) "\xFF", 1, 0, (struct sockaddr*) &client_addr, client_addr_length);
		break;
	}
    }

    close(server);
}
