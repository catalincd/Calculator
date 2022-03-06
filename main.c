// gcc main.c -o main.o `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
// gcc main.c -o main.o `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -w && ./main.o 
// gcc main.c grid.c -o main.o `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -w && ./main.o 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

static GtkWidget* topFrame;
static GtkWidget* topLabel;
static GtkWidget* equals;
static GtkWidget* clear;
static GtkWidget* plus;
static GtkWidget* minus;
static GtkWidget* backspace;
static PangoFontDescription* font;

static GtkWidget *digitsGrid;
static GtkWidget **digits;


void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *mainGrid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_resizable(GTK_WINDOW(window), 0);

  createMainGrid(window, mainGrid);  

  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.catalincd.calculator", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
