#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include "image.h"

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 900

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb);
void aplicar_blur_rgb(ImageRGB *imrgb);
void aplicar_clahe_rgb(ImageRGB *imrgb);
void aplicar_transpose_rgb(ImageRGB *imrgb);
void aplicar_flip_vertical_rgb(ImageRGB *imrgb);
void aplicar_flip_horizontal_rgb(ImageRGB *imrgb);
void aplicar_transpose_gray(ImageGray *imgray);
void aplicar_clahe_gray(ImageGray *imgray);
void aplicar_blur_gray(ImageGray *imgray);
void aplicar_flip_vertical_gray(ImageGray *imgray);
void aplicar_flip_horizontal_gray(ImageGray *imgray);
void exibir_resultado_rgb();
void aplicar_efeito_gray(ImageGray *imgray, int efeito, ImageHistoryGray *history);
void mostrar_menu();
void sortear_efeito_rgb(ImageRGB *imrgb, ImageHistory *history);
void sortear_efeito_gray(ImageGray *imgray, ImageHistoryGray *history);
void abrir_imagem(const char *image_path);
void chamar_python(const char *script, const char *func, const char *input_path, const char *output_path);
void on_apply_effects_rgb(GtkWidget *widget, gpointer data);
void on_convert_to_gray(GtkWidget *widget, gpointer data);
void on_apply_effects_gray(GtkWidget *widget, gpointer data);
void on_show_result(GtkWidget *widget, gpointer data);
void show_effects_menu_rgb();
void show_effects_menu_gray();
void on_effect_selected_rgb(GtkWidget *widget, gpointer data);
void on_effect_selected_gray(GtkWidget *widget, gpointer data);
void on_sort_effect_rgb(GtkWidget *widget, gpointer data);
void on_sort_effect_gray(GtkWidget *widget, gpointer data);
void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history);
void show_effects_sort_rgb();
void show_effects_sort_gray();

ImageRGB imrgb;
ImageGray imgray;
ImageHistory *history_rgb;
ImageHistoryGray *history_gray;

GtkWidget *button_apply_effects_rgb;
GtkWidget *button_sort_effect_rgb;
GtkWidget *button_apply_effects_gray;
GtkWidget *button_sort_effect_gray;
GtkWidget *button_convert_to_gray;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    FILE *arq = fopen("utils/input_image_example_RGB.txt", "r");

    history_rgb = create_image_history();
    history_gray = create_image_history_gray();

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    remove("utils/input_imagem_final.txt");
    system("python3 utils/select_image.py");
    criar_imagem_rgb(arq, &imrgb);
    add_image_to_history_rgb(history_rgb, &imrgb);

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Editor de Imagens EaFotO");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Cria um grid para organizar os botões
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Define a espessura da borda do grid e espaçamento interno
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);

    // Cria os botões e os adiciona ao grid
    button_apply_effects_rgb = gtk_button_new_with_label("Aplicar Efeitos RGB");
    g_signal_connect(button_apply_effects_rgb, "clicked", G_CALLBACK(on_apply_effects_rgb), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_apply_effects_rgb, 0, 0, 1, 1);

    button_apply_effects_gray = gtk_button_new_with_label("Aplicar Efeitos Preto e Branco");
    g_signal_connect(button_apply_effects_gray, "clicked", G_CALLBACK(on_apply_effects_gray), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_apply_effects_gray, 1, 0, 1, 1);
    gtk_widget_set_sensitive(button_apply_effects_gray, FALSE);

    button_convert_to_gray = gtk_button_new_with_label("Converter para Preto e Branco");
    g_signal_connect(button_convert_to_gray, "clicked", G_CALLBACK(on_convert_to_gray), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_convert_to_gray, 2, 0, 1, 1);

    GtkWidget *button_show_result = gtk_button_new_with_label("Exibir Resultado");
    g_signal_connect(button_show_result, "clicked", G_CALLBACK(on_show_result), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_show_result, 3, 0, 1, 1);

    button_sort_effect_rgb = gtk_button_new_with_label("Sortear Efeito RGB");
    g_signal_connect(button_sort_effect_rgb, "clicked", G_CALLBACK(show_effects_sort_rgb), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_sort_effect_rgb, 4, 0, 1, 1);

    button_sort_effect_gray = gtk_button_new_with_label("Sortear Efeito Preto e Branco");
    g_signal_connect(button_sort_effect_gray, "clicked", G_CALLBACK(show_effects_sort_gray), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_sort_effect_gray, 5, 0, 1, 1);
    gtk_widget_set_sensitive(button_sort_effect_gray, FALSE);

    GtkWidget *button_exit = gtk_button_new_with_label("Sair da aplicação");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_exit, 6, 0, 1, 1);

    // Ajusta o tamanho homogêneo dos botões no grid
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb)
{
    ler_imagem_arkv(arq, imrgb);
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", "utils/input_image_example_RGB.txt", "utils/imagem_final.png");
    abrir_imagem("image_rgb.png");
}

void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history)
{
    const char *txt_filename = "utils/input_imagem_final.txt";
    const char *output_filename = "utils/imagem_final.png";

    switch (efeito)
    {
    case 1:
        printf("Aplicando Blur RGB\n");
        aplicar_blur_rgb(imrgb);
        add_image_to_history_rgb(history, imrgb);
        break;
    case 2:
        printf("Aplicando CLAHE RGB\n");
        aplicar_clahe_rgb(imrgb);
        add_image_to_history_rgb(history, imrgb);
        break;
    case 3:
        printf("Aplicando Transpose RGB\n");
        aplicar_transpose_rgb(imrgb);
        add_image_to_history_rgb(history, imrgb);
        break;
    case 4:
        printf("Aplicando Flip Vertical RGB\n");
        aplicar_flip_vertical_rgb(imrgb);
        add_image_to_history_rgb(history, imrgb);
        break;
    case 5:
        remove("utils/imagem_final.png");
        printf("Aplicando Flip Horizontal RGB\n");
        aplicar_flip_horizontal_rgb(imrgb);
        add_image_to_history_rgb(history, imrgb);
        break;
    case 7:
        printf("Desfazendo alteracao\n");
        desfazer_rgb(history, imrgb);

        break;
    case 8:
        printf("Refazendo alteracao\n");
        refazer_rgb(history, imrgb);
        break;
    default:
        printf("Opcao invalida\n");
        return;
    }

    FILE *input_txt = fopen(txt_filename, "w");
    salvar_imagem_arkv_rgb(imrgb, input_txt);
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", txt_filename, output_filename);
    abrir_imagem("image_rgb.png");
}

void aplicar_efeito_gray(ImageGray *imgray, int efeito, ImageHistoryGray *history)
{
    const char *txt_filename = "utils/input_imagem_final.txt";
    const char *output_filename = "utils/imagem_final.png";

    switch (efeito)
    {
    case 1:
        printf("Aplicando Blur Gray\n");
        aplicar_blur_gray(imgray);
        add_image_to_history_gray(history, imgray);
        break;
    case 2:
        printf("Aplicando CLAHE Gray\n");
        aplicar_clahe_gray(imgray);
        add_image_to_history_gray(history, imgray);
        break;
    case 3:
        printf("Aplicando Transpose Gray\n");
        aplicar_transpose_gray(imgray);
        add_image_to_history_gray(history, imgray);
        break;
    case 4:
        printf("Aplicando Flip Vertical Gray\n");
        aplicar_flip_vertical_gray(imgray);
        add_image_to_history_gray(history, imgray);
        break;
    case 5:
        printf("Aplicando Flip Horizontal Gray\n");
        aplicar_flip_horizontal_gray(imgray);
        add_image_to_history_gray(history, imgray);
        break;
    case 7:
        printf("Desfazendo alteracao\n");
        desfazer_gray(history, imgray);
        break;
    case 8:
        printf("Refazendo alteracao\n");
        refazer_gray(history, imgray);
        break;
    default:
        printf("Opcao invalida\n");
        return;
    }

    FILE *input_txt = fopen(txt_filename, "w");
    salvar_imagem_arkv(imgray, input_txt);
    chamar_python("utils/image_utils.py", "image_gray_from_txt", txt_filename, output_filename);
    abrir_imagem("image_rgb.png");
}

// chamar_python("utils/image_utils.py", "image_rgb_from_latest_txt", "utils/input_imagem_final.txt", "ritinha.png");
void chamar_python(const char *script, const char *func, const char *input_path, const char *output_path)
{
    char command[256];
    snprintf(command, sizeof(command), "python3 %s %s \"%s\" \"%s\"", script, func, input_path, output_path);
    system(command);
}

void aplicar_blur_rgb(ImageRGB *imrgb)
{
    ImageRGB blur_rgb;
    blur_rgb.dim.altura = imrgb->dim.altura;
    blur_rgb.dim.largura = imrgb->dim.largura;
    alocarRGB(blur_rgb.dim.altura, blur_rgb.dim.largura, &(blur_rgb.pixels));

    blur_rgb = *median_blur_rgb(imrgb, 15);

    *imrgb = blur_rgb;
}

void aplicar_clahe_rgb(ImageRGB *imrgb)
{
    ImageRGB clahe_rgb_img;
    clahe_rgb_img.dim.altura = imrgb->dim.altura;
    clahe_rgb_img.dim.largura = imrgb->dim.largura;
    alocarRGB(clahe_rgb_img.dim.altura, clahe_rgb_img.dim.largura, &(clahe_rgb_img.pixels));

    clahe_rgb_img = *clahe_rgb(imrgb, 256, 40);

    *imrgb = clahe_rgb_img;
}

void aplicar_transpose_rgb(ImageRGB *imrgb)
{
    ImageRGB transpose_rgb_var;
    transpose_rgb_var.dim.altura = imrgb->dim.altura;
    transpose_rgb_var.dim.largura = imrgb->dim.largura;
    alocarRGB(transpose_rgb_var.dim.altura, transpose_rgb_var.dim.largura, &(transpose_rgb_var.pixels));

    transpose_rgb(imrgb, &transpose_rgb_var);

    *imrgb = transpose_rgb_var;
}

void aplicar_flip_vertical_rgb(ImageRGB *imrgb)
{
    ImageRGB flip_rgb_vertical;
    flip_rgb_vertical.dim.altura = imrgb->dim.altura;
    flip_rgb_vertical.dim.largura = imrgb->dim.largura;
    alocarRGB(flip_rgb_vertical.dim.altura, flip_rgb_vertical.dim.largura, &(flip_rgb_vertical.pixels));

    flip_vertical_rgb(imrgb, &flip_rgb_vertical);

    *imrgb = flip_rgb_vertical;
}

void aplicar_flip_horizontal_rgb(ImageRGB *imrgb)
{
    ImageRGB flip_rgb_horizontal;
    flip_rgb_horizontal.dim.altura = imrgb->dim.altura;
    flip_rgb_horizontal.dim.largura = imrgb->dim.largura;
    alocarRGB(flip_rgb_horizontal.dim.altura, flip_rgb_horizontal.dim.largura, &(flip_rgb_horizontal.pixels));

    flip_horizontal_rgb(imrgb, &flip_rgb_horizontal);

    *imrgb = flip_rgb_horizontal;
}

void aplicar_transpose_gray(ImageGray *imgray)
{
    ImageGray transpose_gray_var;
    transpose_gray_var.dim.altura = imgray->dim.altura;
    transpose_gray_var.dim.largura = imgray->dim.largura;
    alocarGray(transpose_gray_var.dim.altura, transpose_gray_var.dim.largura, &(transpose_gray_var.pixels));

    transpose_gray(imgray, &transpose_gray_var);

    *imgray = transpose_gray_var;
}

void aplicar_clahe_gray(ImageGray *imgray)
{
    ImageGray clahe_gray_saida;
    clahe_gray_saida.dim.altura = imgray->dim.altura;
    clahe_gray_saida.dim.largura = imgray->dim.largura;
    alocarGray(clahe_gray_saida.dim.altura, clahe_gray_saida.dim.largura, &(clahe_gray_saida.pixels));

    clahe_gray_saida = *clahe_gray(imgray, 256, 90);

    *imgray = clahe_gray_saida;
}

void aplicar_blur_gray(ImageGray *imgray)
{
    ImageGray blur_gray;
    blur_gray.dim.altura = imgray->dim.altura;
    blur_gray.dim.largura = imgray->dim.largura;
    alocarGray(blur_gray.dim.altura, blur_gray.dim.largura, &(blur_gray.pixels));

    blur_gray = *median_blur_gray(imgray, 15);

    *imgray = blur_gray;
}

void aplicar_flip_vertical_gray(ImageGray *imgray)
{
    ImageGray flip_gray_vertical;
    flip_gray_vertical.dim.altura = imgray->dim.altura;
    flip_gray_vertical.dim.largura = imgray->dim.largura;
    alocarGray(flip_gray_vertical.dim.altura, flip_gray_vertical.dim.largura, &(flip_gray_vertical.pixels));

    flip_vertical_gray(imgray, &flip_gray_vertical);

    *imgray = flip_gray_vertical;
}

void aplicar_flip_horizontal_gray(ImageGray *imgray)
{
    ImageGray flip_gray_horizontal_var;
    flip_gray_horizontal_var.dim.altura = imgray->dim.altura;
    flip_gray_horizontal_var.dim.largura = imgray->dim.largura;
    alocarGray(flip_gray_horizontal_var.dim.altura, flip_gray_horizontal_var.dim.largura, &(flip_gray_horizontal_var.pixels));

    flip_horizontal_gray(imgray, &flip_gray_horizontal_var);

    *imgray = flip_gray_horizontal_var;
}

// Aqui irei fazer uma funcao que vai abrir fotos no windows
void abrir_imagem(const char *image_path)
{
    char command[256];
    snprintf(command, sizeof(command), "python3 utils/abrir_imagem_sistemas.py %s", image_path);
    int ret = system(command);
    if (ret != 0)
    {
        printf("Erro ao abrir a imagem. Código de retorno: %d\n", ret);
    }
}

// ####################### ZONA DE RISCO

void on_apply_effects_rgb(GtkWidget *widget, gpointer data)
{
    show_effects_menu_rgb();
}

void on_convert_to_gray(GtkWidget *widget, gpointer data)
{
    converter_para_gray(&imrgb, &imgray);
    FILE *input_txt = fopen("utils/input_imagem_final.txt", "w");
    salvar_imagem_arkv(&imgray, input_txt);
    chamar_python("utils/image_utils.py", "image_gray_from_txt", "utils/input_imagem_final.txt", "utils/imagem_final.png");
    add_image_to_history_gray(history_gray, &imgray);

    gtk_widget_set_sensitive(button_apply_effects_rgb, FALSE);
    gtk_widget_set_sensitive(button_sort_effect_rgb, FALSE);
    gtk_widget_set_sensitive(button_apply_effects_gray, TRUE);
    gtk_widget_set_sensitive(button_sort_effect_gray, TRUE);

    abrir_imagem("image_rgb.png");
}

void on_apply_effects_gray(GtkWidget *widget, gpointer data)
{
    show_effects_menu_gray();
}

void on_show_result(GtkWidget *widget, gpointer data)
{
    abrir_imagem("utils/imagem_final.png");
}

void show_effects_menu_rgb()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button7, *button8, *cancel_button;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Escolha o Efeito RGB");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    button1 = gtk_button_new_with_label("Blur RGB");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)1);
    gtk_widget_set_hexpand(button1, TRUE);
    gtk_widget_set_vexpand(button1, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 2, 1);

    button2 = gtk_button_new_with_label("CLAHE RGB");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)2);
    gtk_widget_set_hexpand(button2, TRUE);
    gtk_widget_set_vexpand(button2, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 2, 1);

    button3 = gtk_button_new_with_label("Transpose RGB");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)3);
    gtk_widget_set_hexpand(button3, TRUE);
    gtk_widget_set_vexpand(button3, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 2, 2, 1);

    button4 = gtk_button_new_with_label("Flip Vertical RGB");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)4);
    gtk_widget_set_hexpand(button4, TRUE);
    gtk_widget_set_vexpand(button4, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button4, 0, 3, 2, 1);

    button5 = gtk_button_new_with_label("Flip Horizontal RGB");
    g_signal_connect(button5, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)5);
    gtk_widget_set_hexpand(button5, TRUE);
    gtk_widget_set_vexpand(button5, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button5, 0, 4, 2, 1);

    button7 = gtk_button_new_with_label("Desfazer");
    g_signal_connect(button7, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)7);
    gtk_widget_set_hexpand(button7, TRUE);
    gtk_widget_set_vexpand(button7, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button7, 0, 5, 1, 1);

    button8 = gtk_button_new_with_label("Refazer");
    g_signal_connect(button8, "clicked", G_CALLBACK(on_effect_selected_rgb), (gpointer)8);
    gtk_widget_set_hexpand(button8, TRUE);
    gtk_widget_set_vexpand(button8, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button8, 1, 5, 1, 1);

    gtk_widget_show_all(dialog);
}


void show_effects_menu_gray()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button7, *button8, *cancel_button;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Escolha o Efeito Gray");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    button1 = gtk_button_new_with_label("Blur Gray");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)1);
    gtk_widget_set_hexpand(button1, TRUE);
    gtk_widget_set_vexpand(button1, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 2, 1);

    button2 = gtk_button_new_with_label("CLAHE Gray");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)2);
    gtk_widget_set_hexpand(button2, TRUE);
    gtk_widget_set_vexpand(button2, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 2, 1);

    button3 = gtk_button_new_with_label("Transpose Gray");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)3);
    gtk_widget_set_hexpand(button3, TRUE);
    gtk_widget_set_vexpand(button3, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 2, 2, 1);

    button4 = gtk_button_new_with_label("Flip Vertical Gray");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)4);
    gtk_widget_set_hexpand(button4, TRUE);
    gtk_widget_set_vexpand(button4, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button4, 0, 3, 2, 1);

    button5 = gtk_button_new_with_label("Flip Horizontal Gray");
    g_signal_connect(button5, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)5);
    gtk_widget_set_hexpand(button5, TRUE);
    gtk_widget_set_vexpand(button5, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button5, 0, 4, 2, 1);

    button7 = gtk_button_new_with_label("Desfazer");
    g_signal_connect(button7, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)7);
    gtk_widget_set_hexpand(button7, TRUE);
    gtk_widget_set_vexpand(button7, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button7, 0, 5, 1, 1);

    button8 = gtk_button_new_with_label("Refazer");
    g_signal_connect(button8, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)8);
    gtk_widget_set_hexpand(button8, TRUE);
    gtk_widget_set_vexpand(button8, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button8, 1, 5, 1, 1);

    gtk_widget_show_all(dialog);   
}


void show_effects_sort_rgb()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Escolha o Efeito RGB",
                                         NULL,
                                         flags,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    button1 = gtk_button_new_with_label("Sortear Novamente");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(1));
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

    button2 = gtk_button_new_with_label("Desfazer Último Sorteio");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(2));
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);

    button3 = gtk_button_new_with_label("Refazer Último Sorteio");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(3));
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1);

    button4 = gtk_button_new_with_label("Voltar ao Menu Principal");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(4));
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1);

    gtk_widget_show_all(dialog);
}


void show_effects_sort_gray()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Escolha o Efeito Gray",
                                         NULL,
                                         flags,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    button1 = gtk_button_new_with_label("Sortear Novamente");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(1));
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

    button2 = gtk_button_new_with_label("Desfazer Último Sorteio");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(2));
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);

    button3 = gtk_button_new_with_label("Refazer Último Sorteio");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(3));
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1);

    button4 = gtk_button_new_with_label("Voltar ao Menu Principal");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(4));
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1);

    gtk_widget_show_all(dialog);
}


void on_sort_effect_rgb(GtkWidget *widget, gpointer data)
{
    int action = GPOINTER_TO_INT(data);
    const char *txt_filename = "utils/input_imagem_final.txt";
    const char *output_filename = "utils/imagem_final.png";

    switch (action)
    {
    case 1:
        sortear_efeito_rgb(&imrgb, history_rgb);
        break;
    case 2:
        aplicar_efeito_rgb(&imrgb, 7, history_rgb);
        break;
    case 3:
        aplicar_efeito_rgb(&imrgb, 8, history_rgb);
        break;
    case 4:
        break;
    default:
        printf("Opção inválida\n");

        break;
    }
}

void on_sort_effect_gray(GtkWidget *widget, gpointer data)
{
    int action = GPOINTER_TO_INT(data);

    switch (action)
    {
    case 1:
        sortear_efeito_gray(&imgray, history_gray);
        break;
    case 2:
        aplicar_efeito_gray(&imgray, 7, history_gray);
        break;
    case 3:
        aplicar_efeito_gray(&imgray, 8, history_gray);
        break;
    case 4:
        break;
    default:
        printf("Opção inválida\n");
        break;
    }
}

void on_effect_selected_rgb(GtkWidget *widget, gpointer data)
{
    int effect = GPOINTER_TO_INT(data);
    aplicar_efeito_rgb(&imrgb, effect, history_rgb);
}

void on_effect_selected_gray(GtkWidget *widget, gpointer data)
{
    int effect = GPOINTER_TO_INT(data);
    aplicar_efeito_gray(&imgray, effect, history_gray);
}