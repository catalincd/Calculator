#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include <string.h>
#include "utils.h"


static GtkWidget* topLabel; 

void digitCallback(GtkWidget* button, gpointer data)
{
    char* buttonText = gtk_button_get_label((GtkButton*)button);

    char* current = gtk_label_get_text(topLabel);
    int len = strlen(current);

    for(int i=0;i<len;i++)
    {
        if(current[i] == '=')
            return;
    }

    char* next = (char*)malloc(len + 1);
    strcpy(next, current);
    strcpy(next+len, buttonText);

    gtk_label_set_text(topLabel, next);
}

void clearCallback(GtkWidget* button, gpointer data)
{
    gtk_label_set_text(topLabel, "");
}

void backCallback(GtkWidget* button, gpointer data)
{
    char* current = gtk_label_get_text(topLabel);
    int len = strlen(current);
    current[len - 1] = '\0';
    gtk_label_set_text(topLabel, current);
}

void signCallback(GtkWidget* button, gpointer data)
{
    char* buttonText = gtk_button_get_label((GtkButton*)button);

    char* current = gtk_label_get_text(topLabel);
    int len = strlen(current);

    for(int i=0;i<len;i++)
    {
        if(current[i] == '=')
            return;
    }

    char* next = (char*)malloc(len + 3);
    strcpy(next, current);


    if(len < 1 || isdigit(next[len - 1]))
    {
        strcpy(next+len, buttonText);
    }
    else
    {
        next[len - 1] = buttonText[0];
    }

    gtk_label_set_text(topLabel, next);
}

void equalsCallback(GtkButton* button, gpointer data)
{
    char* text = gtk_label_get_text(topLabel);
    int len = strlen(text);
    int opLen = len / 2 + 2;


    for(int i=0;i<len;i++)
    {
        if(text[i] == '=')
            return;
    }

    int operators[opLen];
    int currentOperator = 0;
    int currentFirst = (!isdigit(text[0]));
    long long result = 0;

    operators[0] = (text[0] == '-')? -1 : 1;
    
    for(int i=currentFirst;i<=len;i++)
    {
        if(!isdigit(text[i]) || text[i] == '\0')
        {
            result += operators[currentOperator++] * getNum(text, currentFirst, i);
            operators[currentOperator] = (text[i] == '-')? -1 : 1;
            currentFirst = i + 1;
        }
    }

    char next[200];
    sprintf(next, "%s=%d", text, result);

    gtk_label_set_text(topLabel, next);
}

#endif