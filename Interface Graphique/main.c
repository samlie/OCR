#include <gtk/gtk.h>
#include "grayscale.h"
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "decoupage.h"

// Structure of the graphical user interface.
typedef struct UserInterface
{
    GtkWindow* window;                // Main window
    GtkButton* Save_button;            // New button
    GtkButton* Start_button;          // Start button
    GtkFileChooserButton* SelectFile_Button; // Image file chooser
    GtkTextView* textBox;            // Writing zone of the final text

    char* text;
    char* filename;                 //Path

} UserInterface;

/*
void file_selected(GtkFileChooserButton *filechooserbutton, UserInterface* ui) {
    g_print("IMAGE SELECTED\n");
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    printf("%s\n", filename);
}
*/


void on_Start_button_activate(GtkButton *button, UserInterface* ui) {
    ui->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->SelectFile_Button));
    main2(ui->filename);
    ui->text = "Hello world";
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(ui->textBox), ui->text, -1);
}


int main2(char *path)
{

    init_sdl();
    //Create the sdl surface we'll use
    SDL_Surface* image_surface = load_image(path);

    FILE * fp;

    /* open the file for writing*/
    fp = fopen("sortie.txt","w");
    fclose (fp);

    int width = getwidth(image_surface);
    int height = getheight(image_surface);
    printf("%d %d \n", width, height);

    // Create a matrix of the corresponding size
    int res[height][width];

    // Fill the matrix with the 
    matrix(image_surface, width, height, res);

    // Print the matrix on screen
    //print_matrix("matrix", width, height, res);

    // Displays the color image in a window and 
    SDL_Surface* screen_surface = display_image(image_surface);
    wait_for_keypressed();
    // We know that we have three lines of text, but otherwise the function is 
    // able to determine the number of lines 
    //int x = getNbOfLines(width, height, res);
    int a[4][4];
    getLineBlocks(height, width, res, 4, a);

    for (int i = 0; i<4; i++) {
        // Draws a red rectangle around the detected text line
        isoleTacheFromLine(height, width, res, a[i]);
        encadre(image_surface, a[i][0], a[i][1], a[i][2], a[i][3]);
    }

    // Update the surface on screen
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();

    // Release the surface in memory
    SDL_FreeSurface(image_surface);

    // Isolates, resizes and prints every connex region of pixels (supposedly a character)
    //isoleTache(height, width, res);

    return 0;
}

/*
void on_save(GtkButton *button, UserInterface* ui) {
    const char* filename = gtk_entry_get_text(ui->filename);
    char savefolderpath[1000];
    snprintf(savefolderpath, 1000, "%s/%s.txt", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->TextOutput)), filename);

    FILE* fp;
    fp = fopen(savefolderpath, "w");
    fprintf(fp, "%s", ui->text);
    fclose(fp);
}
*/

int main(int argc, char const *argv[]) {
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new ();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "50shades.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GtkButton* Save_button = GTK_BUTTON(gtk_builder_get_object(builder, "Save_button"));
    GtkButton* Start_button = GTK_BUTTON(gtk_builder_get_object(builder, "Start_button"));

    GtkFileChooserButton* SelectFile_Button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "SelectFile_Button"));

    GtkTextView* textBox = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textBox"));


    UserInterface ui =
    {
        .window = window,
        .Save_button = Save_button,
        .Start_button = Start_button,
        .SelectFile_Button = SelectFile_Button,
        .textBox = textBox,
        .text = "",
        .filename = "",
    };



    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //g_signal_connect(Save_button, "clicked", G_CALLBACK(on_save), &ui);
    g_signal_connect(Start_button, "clicked", G_CALLBACK(on_Start_button_activate), &ui);

    //g_signal_connect(SelectFile_Button, "file-set", G_CALLBACK(file_selected), &ui);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
