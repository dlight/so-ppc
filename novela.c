# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

# include <stdio.h>

const int FILHO1_NASCEU = 10;
const int FILHO2_NASCEU = 20;

const int NETO1_NASCEU = 25;
const int NETO2_NASCEU = 35;

const int FILHO1_MATA_PAI = 50;
const int FILHO1_MATA_FILHO = 55;

const int NETO2_MATA_PAI = 60;

pid_t neto1()
{
	printf("*** Neto1 nasceu. ***\n");
	fflush(stdout);

	pid_t p = fork();
	if (!p) for (int i = 0;; i++) {
		printf("#  Neto1:\t%d\t%d\t%d\n",
			i, getpid(), getppid());

		sleep(1);
	}
	else {
		return p;
	}
}

void qkill(char* from, char* to, pid_t target)
{
	printf("~~~ %s mata %s ~~~\n", from, to);
	fflush(stdout);
	kill(target, SIGKILL);
}

void filho1()
{
	printf("*** Filho1 nasceu. ***\n");
	fflush(stdout);

	pid_t neto;
	if (!fork()) for (int i = 0;; i++) {
		printf("* Filho1:\t%d\t%d\t%d\n",
			i, getpid(), getppid());
		fflush(stdout);

		if (i == NETO1_NASCEU - FILHO1_NASCEU)
			neto = neto1();

		if (i == FILHO1_MATA_PAI - FILHO1_NASCEU)
			qkill("Filho1", "Pai", getppid());

		if (i == FILHO1_MATA_FILHO - FILHO1_NASCEU)
			qkill("Filho1", "Neto1", neto);

		if (i == FILHO1_MATA_FILHO - FILHO1_NASCEU + 2)
			qkill("Filho1", "a si mesmo", getpid());

		sleep(1);
	}
}

void neto2()
{
	printf("*** Neto2 nasceu. ***\n");
	fflush(stdout);

	if (!fork()) for (int i = 0;; i++) {
		printf("#  Neto2:\t%d\t%d\t%d\n",
			i, getpid(), getppid());
		fflush(stdout);

		if (i == NETO2_MATA_PAI - NETO2_NASCEU)
			qkill("Neto2", "Filho2", getppid());

		if (i == NETO2_MATA_PAI - NETO2_NASCEU + 3)
			qkill("Neto2", "a si mesmo", getpid());

		sleep(1);
	}
}

void filho2()
{
	printf("*** Filho2 nasceu. ***\n");
	fflush(stdout);

	if (!fork()) for (int i = 0;; i++) {
		printf("* Filho2:\t%d\t%d\t%d\n",
			i, getpid(), getppid());
		fflush(stdout);

		if (i == NETO2_NASCEU - FILHO2_NASCEU)
			neto2();

		sleep(1);
	}
}

int main()
{
	printf("    Nome\tIdade\tPID\tPPID\n");
	fflush(stdout);
	for (int i = 0;; i++) {
		printf("-    Pai:\t%d\t%d\t%d\n",
			i, getpid(), getppid());
		fflush(stdout);

		if (i == FILHO1_NASCEU)
			filho1();

		if (i == FILHO2_NASCEU)
			filho2();


		sleep(1);
	}
}
