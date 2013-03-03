#include "events.h"
#include "server.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

print_help(char * program_name)
{
    printf("Usage: %s [-p <port>] [-d] [-h]\n", program_name);
}

int main(int argc, char *argv[])
{
    int debug = 0;
    char * port = "4500";
    int opt;

    while ((opt = getopt(argc, argv, "hdp:")) != -1) {
	switch (opt) {
	    case 'd':
		debug = 1;
		break;
	    case 'p':
		port = optarg;
		break;
	    case 'h':
	    default:
		print_help(argv[0]);
		return EXIT_SUCCESS;
 	}
    }

    setup();
    run(port, debug);
    return EXIT_SUCCESS;
}
