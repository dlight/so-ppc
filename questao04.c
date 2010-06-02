# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Uso: %s <pid> [s | c | k]\n", argv[0]);
		exit(0);
	}

	int p = atoi(argv[1]);
	char* o;

	if (argc < 3)
		o = "k";

	else
		o = argv[2];

	if (!strcmp(o, "s"))
		printf("Pausando processo %d.. %s.\n",
			p,
			kill(p, SIGSTOP) == 0 ? "sucesso" : "falhou");

	else if (!strcmp(o, "c"))
		printf("Continuando processo %d.. %s.\n",
			p,
			kill(p, SIGCONT) == 0 ? "sucesso" : "falhou");

	else
		printf("Matando processo %d.. %s.\n",
			p,
			kill(p, SIGKILL) == 0 ? "sucesso" : "falhou");

}
