#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "callbacks.h"

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

void createMainGrid(GtkWidget* window, GtkWidget* mainGrid)
{
  font = pango_font_description_from_string("Arial");
  pango_font_description_set_size(font, 20 * PANGO_SCALE);

  mainGrid = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), mainGrid);

  gtk_widget_override_font(mainGrid, font);

  topFrame = gtk_frame_new ("");
  gtk_widget_set_size_request(topFrame, -1, 90);
  gtk_widget_set_margin_start(topFrame, 17);
  gtk_widget_set_margin_end(topFrame, 17);
  gtk_box_pack_start(GTK_BOX(mainGrid), topFrame, TRUE, TRUE, 5);
  

  topLabel = gtk_label_new ("");
  gtk_widget_set_margin_end(topLabel, 17);
  GtkWidget* alignWidget = gtk_alignment_new(1, 0, 0, 0);
 
  gtk_container_add(topFrame, alignWidget);
  gtk_container_add(alignWidget, topLabel);
 

  digitsGrid = gtk_grid_new();
  gtk_box_pack_start(GTK_BOX(mainGrid), digitsGrid, TRUE, TRUE, 5);

  //gtk_box_set_homogeneous(GTK_BOX(mainGrid), TRUE);

  gtk_grid_set_column_spacing((GtkGrid*)digitsGrid, 5);
  gtk_grid_set_row_spacing((GtkGrid*)digitsGrid, 5);
  gtk_widget_set_margin_start(digitsGrid, 17);
  gtk_widget_set_margin_top(digitsGrid, 10);
  gtk_widget_set_margin_bottom(digitsGrid, 17);

  digits = (GtkWidget**)malloc(sizeof(GtkWidget*) * 10);

  for(int i=0;i<9;i++)
  {
    int current = 9 - i;

    char name[3];
    sprintf(name, "%d", current);
    
    digits[current] = gtk_button_new_with_label(name);
    gtk_widget_set_size_request(digits[current], 90, 90);
    
    
    int x = i % 3;
    int y = i / 3;
    gtk_grid_attach(GTK_GRID(digitsGrid), digits[current], x, y, 1, 1);
    g_signal_connect(digits[current], "clicked", G_CALLBACK(digitCallback), NULL);
  }

  digits[0] = gtk_button_new_with_label("0");
  gtk_widget_set_size_request(digits[0], 90, 90);
  gtk_grid_attach(GTK_GRID(digitsGrid), digits[0], 0, 3, 2, 1);
  g_signal_connect(digits[0], "clicked", G_CALLBACK(digitCallback), NULL);

  backspace = gtk_button_new_from_icon_name("edit-undo", GTK_ICON_SIZE_DND);
  gtk_grid_attach(GTK_GRID(digitsGrid), backspace, 2, 3, 1, 1);
  g_signal_connect(backspace, "clicked", G_CALLBACK(backCallback), NULL);

  plus = gtk_button_new_with_label("+");
  gtk_widget_set_size_request(minus, 180, 90);
  gtk_grid_attach(GTK_GRID(digitsGrid), plus, 3, 0, 2, 1);
  g_signal_connect(plus, "clicked", G_CALLBACK(signCallback), NULL);
  
  minus = gtk_button_new_with_label("-");
  gtk_widget_set_size_request(minus, 180, 90);
  gtk_grid_attach(GTK_GRID(digitsGrid), minus, 3, 1, 2, 1);
  g_signal_connect(minus, "clicked", G_CALLBACK(signCallback), NULL);

  clear = gtk_button_new_with_label("C");
  gtk_widget_set_size_request(clear, 180, 90);
  gtk_grid_attach(GTK_GRID(digitsGrid), clear, 3, 2, 2, 1);
  g_signal_connect(clear, "clicked", G_CALLBACK(clearCallback), NULL);

  equals = gtk_button_new_with_label("=");
  gtk_widget_set_size_request(equals, 180, 90);
  gtk_grid_attach(GTK_GRID(digitsGrid), equals, 3, 3, 2, 1);
  g_signal_connect(equals, "clicked", G_CALLBACK(equalsCallback), NULL);
}
