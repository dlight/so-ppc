# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <gtk/gtk.h>

void sigchld_handler(int num)
{
	pid_t pid;
	int status;

	while((pid = waitpid((pid_t)-1, &status, WNOHANG)) > 0)
		if(WIFEXITED(status))
			printf("Filho de pid %d saiu.\n",
				(int)pid);
}

gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	return(FALSE);
}

void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void fork_me(GtkWidget *widget, gpointer data)
{
	pid_t pid = fork();

	if(pid == 0) {
		execlp("./questao03", "./questao03", NULL);
		_exit(-1);
	}
	else {
		printf("Criado um filho, de pid %d.\n", (int)pid);
	}
}

int main(int argc, char *argv[])
{
  GtkWidget *window, *button, *button2, *hbox;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position((GtkWindow *) window, GTK_WIN_POS_MOUSE);

  g_signal_connect(G_OBJECT (window), "delete_event",
		     G_CALLBACK(delete_event), NULL);
          
  g_signal_connect(G_OBJECT (window), "destroy",
		     G_CALLBACK(destroy), NULL);

  gtk_container_set_border_width(GTK_CONTAINER (window), 3);


  /* add a button to do something useful */
  button = gtk_button_new_with_label("Clonar");
  button2 = gtk_button_new_with_label("Fechar");

  g_signal_connect(G_OBJECT (button), "clicked",
		     G_CALLBACK(fork_me), NULL);


    g_signal_connect (button2, "clicked",
		      G_CALLBACK (destroy), NULL);

  hbox = gtk_hbox_new(TRUE, 3);

  gtk_container_add(GTK_CONTAINER(hbox), button);
  gtk_container_add(GTK_CONTAINER(hbox), button2);

  gtk_container_add(GTK_CONTAINER(window), hbox);
          
  gtk_widget_show (hbox);
  gtk_widget_show (button);
  gtk_widget_show (button2);
  gtk_widget_show (window);


  signal(SIGCHLD, sigchld_handler);

  gtk_main ();

  exit(0);         
}
