#include <gtk/gtk.h>
#include "bt-5.0.0/inc/btree.h"
#include "dcallback.h"

//Global Object
GObject *window, 
            *info_button, *delete_button, *update_button, *add_button, *search_entry,
            *info_bar, *notify_label, *yes_delete, *yes_add, *yes_update, *no_button,
            *word_label, *meaning_textview,
            //No Shape Objects
            *textbuffer; 

//Global DATA
BTA * data = NULL;

//Global variable

//testing callback function
static void hello_word (GtkWidget * widget, gpointer data)
{
    printf("hola\n");
} 


void show_about_dialog(GtkButton * button, gpointer none)
{
  GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file_at_size("images/about.png",150,150,NULL);
  GtkWidget *dialog=gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog),"DICTIONARY");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"v1.0");
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"C Avanced Team: \n Nguyễn Đức Anh 20165735\nNguyễn Thế Vinh 20167446\nLê Thị Hải Yến 20164753\n");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"A project by C Avanced Team");
  gtk_about_dialog_set_website (GTK_ABOUT_DIALOG(dialog),"https://github.com/ruanshiron");
  gtk_about_dialog_set_website_label (GTK_ABOUT_DIALOG(dialog),"Github");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),pixbuf);
  g_object_unref(pixbuf),pixbuf=NULL;
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

int main (int argc, char *argv[])
{
    //Chuyen Txt than Tu Dien BTA
    if (argc == 2)    
    {
        convert_text_to_bt(argv[1]);
        g_print("export to resource.dat\n");
    }

    //Khoi tao data
    data = btopn ("resource.dat", 0, 1);

    //Khai bao cac doi tuong >> Local->Global
    GtkBuilder *builder;
    /*
    GObject *window, 
            *info_button, *delete_button, *update_button, *search_entry,
            *info_bar, *notify_label, *yes_delete, *yes_add, *yes_update, *no_button,
            *word_label, *meaning_textview, 
            //No Shape Objects
            *textbuffer; */

    //Khoi tao giao dien nguoi dung
    gtk_init (&argc, &argv);

    //Khoi tao GtkBuilder
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "glade/newW.glade", NULL);

    //Khoi tao Window >> Tin hieu "tat cua so"
    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    /* TODO Khoi tao tin hieu cua cac Object khac o day*/

        //Khoi tao Word Label
        word_label = gtk_builder_get_object (builder, "word_label");
        
        //Khoi tao Meaning TextView && TextBuffer
        meaning_textview = gtk_builder_get_object (builder, "meaning_textview");
        textbuffer = gtk_builder_get_object (builder, "textbuffer");

        //Khoi tao Info Button
        info_button = gtk_builder_get_object (builder, "info_button");
        g_signal_connect (info_button, "clicked", G_CALLBACK (show_about_dialog), NULL);

        //Khoi tao Delete Button
        delete_button = gtk_builder_get_object (builder, "delete_button");
        g_signal_connect (delete_button, "clicked", G_CALLBACK (delete_button_clicked), NULL);

        //Khoi tao Update Button
        update_button = gtk_builder_get_object (builder, "update_button");
        g_signal_connect (update_button, "clicked", G_CALLBACK (update_button_clicked), NULL);

        //Khoi tao Add Button
        add_button = gtk_builder_get_object (builder, "add_button");
        g_signal_connect (add_button, "clicked", G_CALLBACK (add_button_clicked), NULL);

        //Khoi tao Search Entry
        search_entry = gtk_builder_get_object (builder, "search_entry");
        g_signal_connect (search_entry, "activate", G_CALLBACK (search_entry_activate), NULL);

        // >> Tin hieu nhan Key Bat ki
        //g_signal_connect (search_entry, "key-press-event", G_CALLBACK (hello_word), NULL);    

        //Khoi tao Info Bar
        info_bar = gtk_builder_get_object (builder, "info_bar");

        //Khoi tao Notify Label
        notify_label = gtk_builder_get_object (builder, "notify_label");

        //Khoi tao Yes Button >> NO CALLBACK function 
        yes_delete = gtk_builder_get_object (builder, "yes_delete");
        g_signal_connect (yes_delete, "clicked", G_CALLBACK (yes_delete_clicked), NULL);

        yes_add = gtk_builder_get_object (builder, "yes_add");
        g_signal_connect (yes_add, "clicked", G_CALLBACK (hello_word), NULL);

        yes_update = gtk_builder_get_object (builder, "yes_update");
        g_signal_connect (yes_update, "clicked", G_CALLBACK (hello_word), NULL);

        //khoi tao No Button >> NO CALLBACK function 
        no_button = gtk_builder_get_object (builder, "no_button");
        g_signal_connect (no_button, "clicked", G_CALLBACK (no_button_clicked), NULL);

        
        
        
        
        
    //Hien thi Window va "Child"
    gtk_widget_show (window); 

    //Ngung tham chieu Builder (free)
    g_object_unref (builder);

    //Chay vong lap main (the main loop) cho den khi gtk_main_quit() duoc goi
    gtk_main ();

    //Ngung tham chieu DATA >> Tat chuong trinh
    btcls (data);

    return 0;
}