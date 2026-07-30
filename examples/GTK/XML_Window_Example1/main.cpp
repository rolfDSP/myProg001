#include <gtk/gtk.h>

extern "C" {

// Signal handler called when buttons are clicked
void on_button_clicked(GtkButton *button, gpointer /*user_data*/) {
    const gchar *label = gtk_button_get_label(button);
    g_print("%s pressed!\n", label);
}

// Signal handler called when window is closed
void on_main_window_destroy(GtkWidget * /*widget*/, gpointer /*user_data*/) {
    gtk_main_quit();
}

} // extern "C"

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    // 1. Create a new GtkBuilder instance
    builder = gtk_builder_new();

    // 2. Load the XML layout file
    if (gtk_builder_add_from_file(builder, "layout.xml", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // 3. Extract the top-level window object from the XML
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    // 4. Automatically connect XML-declared signals to C functions
    // Note: Compile with '-rdynamic' so GTK can look up function names globally
    gtk_builder_connect_signals(builder, NULL);

    // 5. Clean up the builder object and display the window
    g_object_unref(builder);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
