# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <unistd.h>

# include <errno.h>

typedef struct {
	int pid;
	int vivo;
	int nascimento;
	char* nome;
} membro;


void sou_filho();
void dizer_situacao(membro f[], int agora);
void criar_filho(membro *filho, int agora);
void sou_pai();


int main()
{
	sou_pai();
}


void dizer_situacao(membro f[], int agora)
{
	for (int i = 0; i < 4; i++)
		if (f[i].vivo == 1)
			printf("* %s VIVO (pid %d), com %d anos.\n",
				f[i].nome,
				f[i].pid,
				agora - f[i].nascimento);
		else if (!f[i].vivo)
			printf("* %s morto (pid %d).\n",
				f[i].nome,
				f[i].pid);
	printf("\n");
	fflush(stdout);
}

void criar_filho(membro* filho, int agora)
{
	pid_t i = fork();
	
	if (i == -1) {
		perror("fork");
	}
	else if (i) {
		filho->vivo = 1;
		filho->pid = i;
		filho->nascimento = agora;
	}
	else {
		sou_filho();
	}
}

void ver_morte(membro *filho)
{
	int status;

	waitpid(filho->pid, &status, 0);
	filho->vivo = 0;
}

void sou_pai()
{
	membro familia[4];

	familia[0].nome = "Pai";
	familia[1].nome = "Zezinho";
	familia[2].nome = "Huguinho";
	familia[3].nome = "Luizinho";

	familia[0].nascimento = 0;

	familia[0].vivo = 1;
	familia[1].vivo =
	familia[2].vivo =
	familia[3].vivo = -1;

	familia[0].pid = getpid();

	for (int idade = 0; idade < 91; idade++) {
		if (idade == 20)
			criar_filho(&familia[1], 20);
		if (idade == 25)
			criar_filho(&familia[2], 25);
		if (idade == 30)
			criar_filho(&familia[3], 30);

		if (idade == 20+60)
			ver_morte(&familia[1]);
		if (idade == 25+60)
			ver_morte(&familia[2]);
		if (idade == 30+60)
			ver_morte(&familia[3]);

		if (idade == 60)
			familia[0].vivo = 0;

		if (idade >= 20)
			dizer_situacao(familia, idade);

		sleep(1);
	}
	exit(0);
}

void sou_filho()
{
	for (int idade = 0; idade < 60; idade++)
		sleep(1);
	exit(0);
}
