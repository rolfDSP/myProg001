#include <gtk/gtk.h>
#include <librsvg/rsvg.h>
#include <string>

// SVG defined entirely as a C++ string — no file needed
static const std::string SVG_FROM_STRING = R"SVG(
<svg xmlns="http://www.w3.org/2000/svg" width="300" height="200" viewBox="0 0 300 200">
  <defs>
    <radialGradient id="bg" cx="50%" cy="50%" r="70%">
      <stop offset="0%"   stop-color="#1a237e"/>
      <stop offset="100%" stop-color="#000020"/>
    </radialGradient>
  </defs>

  <!-- Background -->
  <rect width="300" height="200" fill="url(#bg)"/>

  <!-- Stars -->
  <circle cx="30"  cy="20"  r="1.5" fill="white" opacity="0.9"/>
  <circle cx="80"  cy="10"  r="1"   fill="white" opacity="0.8"/>
  <circle cx="140" cy="30"  r="2"   fill="white" opacity="0.9"/>
  <circle cx="210" cy="15"  r="1.5" fill="white" opacity="0.7"/>
  <circle cx="270" cy="25"  r="1"   fill="white" opacity="0.9"/>
  <circle cx="50"  cy="50"  r="1"   fill="white" opacity="0.6"/>
  <circle cx="250" cy="55"  r="1.5" fill="white" opacity="0.8"/>
  <circle cx="170" cy="45"  r="1"   fill="white" opacity="0.7"/>

  <!-- Planet -->
  <circle cx="150" cy="100" r="60" fill="#1565C0"/>
  <!-- Ocean highlight -->
  <ellipse cx="130" cy="80" rx="35" ry="25" fill="#1E88E5" opacity="0.7"/>
  <!-- Continent -->
  <ellipse cx="165" cy="110" rx="28" ry="20" fill="#43A047" opacity="0.9"/>
  <ellipse cx="140" cy="120" rx="15" ry="10" fill="#388E3C" opacity="0.8"/>
  <!-- Atmosphere glow -->
  <circle cx="150" cy="100" r="60" fill="none"
          stroke="#42A5F5" stroke-width="6" opacity="0.35"/>
  <circle cx="150" cy="100" r="60" fill="none"
          stroke="#90CAF9" stroke-width="2" opacity="0.2"/>

  <!-- Moon -->
  <circle cx="245" cy="55" r="18" fill="#B0BEC5"/>
  <circle cx="251" cy="55" r="18" fill="#1a237e"/>  <!-- crescent cutout -->
  <circle cx="245" cy="55" r="18" fill="none"
          stroke="#90A4AE" stroke-width="1" opacity="0.5"/>

  <!-- Label -->
  <text x="150" y="185" text-anchor="middle"
        font-family="sans-serif" font-size="11" fill="#90CAF9" font-style="italic">
    Generated from an in-memory SVG string
  </text>
</svg>
)SVG";

static RsvgHandle *svg_handle = nullptr;

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer /*data*/)
{
    if (!svg_handle)
        return FALSE;

    const double widget_w = gtk_widget_get_allocated_width(widget);
    const double widget_h = gtk_widget_get_allocated_height(widget);

    gdouble svg_w = 0.0, svg_h = 0.0;
    if (!rsvg_handle_get_intrinsic_size_in_pixels(svg_handle, &svg_w, &svg_h)
        || svg_w <= 0.0 || svg_h <= 0.0)
    {
        svg_w = widget_w;
        svg_h = widget_h;
    }

    const double scale    = MIN(widget_w / svg_w, widget_h / svg_h);
    const double x_offset = (widget_w - svg_w * scale) / 2.0;
    const double y_offset = (widget_h - svg_h * scale) / 2.0;

    GError *error = nullptr;
    const RsvgRectangle viewport = { x_offset, y_offset, svg_w * scale, svg_h * scale };
    rsvg_handle_render_document(svg_handle, cr, &viewport, &error);

    if (error) {
        g_printerr("SVG render error: %s\n", error->message);
        g_error_free(error);
    }

    return FALSE;
}

static void on_window_destroy(GtkWidget * /*widget*/, gpointer /*data*/)
{
    gtk_main_quit();
}

// Load an RsvgHandle from a std::string containing SVG XML
static RsvgHandle *load_svg_from_string(const std::string &svg_xml)
{
    GError *error = nullptr;
    RsvgHandle *handle = rsvg_handle_new_from_data(
        reinterpret_cast<const guint8 *>(svg_xml.data()),
        static_cast<gsize>(svg_xml.size()),
        &error
    );
    if (!handle) {
        g_printerr("Failed to parse SVG string: %s\n",
                   error ? error->message : "unknown error");
        if (error)
            g_error_free(error);
    }
    return handle;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    if (argc > 1) {
        // Load from file if a path is given on the command line
        GError *error = nullptr;
        svg_handle = rsvg_handle_new_from_file(argv[1], &error);
        if (!svg_handle) {
            g_printerr("Failed to load '%s': %s\n", argv[1],
                       error ? error->message : "unknown error");
            if (error) g_error_free(error);
            return 1;
        }
    } else {
        // Otherwise render the SVG defined as a string above
        svg_handle = load_svg_from_string(SVG_FROM_STRING);
        if (!svg_handle)
            return 1;
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK-3 SVG from String");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), nullptr);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), nullptr);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show_all(window);

    gtk_main();

    g_object_unref(svg_handle);
    return 0;
}