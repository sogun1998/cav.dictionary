#ifndef D_CALLBACK_
#define D_CALLBACK_

#include <string.h>
#include <gtk/gtk.h>

#include "bt-5.0.0/inc/btree.h"

#define WORD_LENGHT 255
#define MEANING_LENGHT 10000

extern  GObject *window, 
                *info_button, *delete_button, *update_button, *add_button, *search_entry,
                *info_bar, *notify_label, *yes_delete, *yes_add, *yes_update, *no_button,
                *word_label, *meaning_textview,
                //No Shape Objects
                *textbuffer; 

//Global DATA
extern BTA * data;

int convert_text_to_bt(char *);

void search_entry_activate (GtkEntry *, gpointer);

void delete_button_clicked (GtkButton *, gpointer);

void update_button_clicked (GtkButton * button, gpointer NONE);

void add_button_clicked (GtkButton * button, gpointer NONE);

void no_button_clicked (GtkButton *, gpointer);

void yes_delete_clicked(GtkButton *, gpointer);


#endif