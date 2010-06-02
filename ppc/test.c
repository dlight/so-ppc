# define _SVID_SOURCE 1

# include <gtk/gtk.h>

# include <dirent.h>

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>

char* ss(char* file)
{
	FILE* f = fopen(file, "r");

	char* a = malloc(1);
	a[0] = '\0';

	if (!f) { puts ("aaaaa"); return a; }

	free(a);

	char* s = malloc(255);

	//	int i, c;

	fgets(s, 40, f);

	if (!s) { puts ("aaaaa"); return a; }

	for (int i = 0; s[i] != '\0'; i++) {
		printf("%c %d\n", s[i], i);
		if (!isgraph(i)) i = ' ';
	}

	/*for (i = 0; i < 40 && ((c = fgetc(f)) != EOF); i++) {
		if (c == 
		s[i] = c;
	}

	s[i+1] = '\0';*/


	return s;
}

char* name(char* n)
{
	int q = 255;

	char* s = malloc(q);
	s[0] = '\0';

	char* x = strncat(
		strncat(
		strncat(s, "/proc/", q), n, q), "/cmdline", q);

	printf("Teste: %s\n");

	return x;
}

char* get_name(char* n)
{
	char* q = name(n);
	char* s = ss(q);
	//free(q);
	return s;
}


int filter(const struct dirent* d)
{
	for (int i = 0; d->d_name[i] != '\0'; i++)
		if (!isdigit(d->d_name[i]))
			return 0;

	return 1;
}

enum
{
  COL_NAME = 0,
  COL_AGE,
  NUM_COLS
} ;

void fill(GtkListStore* store	)
{
  GtkTreeIter    iter;
	gtk_list_store_clear(store);
	struct dirent **namelist;
	int n;
	n = scandir("/proc", &namelist, filter, 0);
	char a[255];
		for (int k = 0; k <n; k ++) {
			a[0] = '\0';

			char* q = get_name(namelist[k]->d_name);

	//for (int i = 0; i < strlen(q); i++)
	//	printf("c: %c, d: %d\n", q[i], q[i]);

  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      COL_NAME, namelist[k]->d_name,
                      COL_AGE, q,
                      -1);

			//free(q);

			free(namelist[k]);
		}

}

static GtkTreeModel *
create_and_fill_model (void)
{
  GtkListStore  *store;
  
  store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

  fill(store);
  
  return GTK_TREE_MODEL (store);
}

static GtkWidget *
create_view_and_model (void)
{
  GtkCellRenderer     *renderer;
  GtkTreeModel        *model;
  GtkWidget           *view;

  view = gtk_tree_view_new ();

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,      
                                               "PID",  
                                               renderer,
                                               "text", COL_NAME,
                                               NULL);


  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,      
                                               "Comando",  
                                               renderer,
                                               "text", COL_AGE,
                                               NULL);

  model = create_and_fill_model ();

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  g_object_unref (model);

gtk_tree_view_columns_autosize((GtkTreeView*)view);

  return view;
}

gboolean timer(gpointer data)
{
	GtkContainer* s = (GtkContainer*) data;

  GtkTreeModel        *model;

model = create_and_fill_model ();

  gtk_tree_view_set_model (GTK_TREE_VIEW (s	), model);

  g_object_unref (model);

gtk_tree_view_columns_autosize((GtkTreeView*)s);
	

	return TRUE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *view;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);

  gtk_widget_set_size_request(window, 320, 480);

  g_signal_connect (window, "delete_event", gtk_main_quit, NULL); /* dirty */

  view = create_view_and_model ();

  gtk_container_add(GTK_CONTAINER(scroll), view);

  gtk_container_add (GTK_CONTAINER (window), scroll);


  gtk_widget_show_all (window);

g_timeout_add_seconds(1, timer, view);


  gtk_main ();

  return 0;
}
