#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/sys.h>

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

static const char *opt_binary = NULL;
static const char *opt_romfile = NULL;
static int opt_cycles = 0;

static void usage(int argc, char **argv)
{
	printf("usage: %s [-b binary] [-r romfile]\n", argv[0]);

	exit(1);
}

static int init_sdl(void)
{
	atexit(SDL_Quit);

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	SDL_EnableUNICODE(1);

	return 0;
}

int main(int argc, char **argv)
{
	for(;;) {
		int c;
		int option_index = 0;

		static struct option long_options[] = {
			{"binary", 1, 0, 'b'},
			{"numcycles", 1, 0, 'n'},
			{"rom", 1, 0, 'r'},
		};
		
		c = getopt_long(argc, argv, "b:n:r:", long_options, &option_index);
		if(c == -1)
			break;

		switch(c) {
			case 'b':
				printf("load binary option: '%s'\n", optarg);
				opt_binary = optarg;
				break;
			case 'n':
				opt_cycles = atoi(optarg);
				printf("cycle count option: '%d'\n", opt_cycles);
				break;
			case 'r':
				printf("load romfile option: '%s'\n", optarg);
				opt_romfile = optarg;
				break;
			default:
				usage(argc, argv);
				break;
		}
	}

	// bring up the SDL system
	init_sdl();

	// initialize the system
	initialize_system(opt_binary, opt_romfile);

	// start the system, should spawn a cpu thread
	system_start(opt_cycles);

	// run the SDL message loop
	system_message_loop();

	return 0;
}

