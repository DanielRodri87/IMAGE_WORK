// Bibliotecas necessárias - Required libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // inicializa a semente do gerador de números aleatórios rand - initializes the seed of the random number generator rand
#include <gtk/gtk.h> // cria e gerencia a interface gráfica - creates and manages the graphical interface
#include "image.h"

#define WINDOW_WIDTH 1910 // define a largura da janela como 1910 pixels - sets the window width to 1910 pixels
#define WINDOW_HEIGHT 100 // define a altura da janela como 100 pixels - sets the window height to 100 pixels

// Funções necessárias - Required functions:
void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb); // Lê uma imagem RGB de um arqv e armazena os dados da imagem - Reads an RGB image from a file and stores the image data
void aplicar_blur_rgb(ImageRGB *imrgb, int intensidade); // Aplica o efeito blur à imagem RGB representada pelo ponteiro - Applies the blur effect to the RGB image represented by the pointer
void aplicar_clahe_rgb(ImageRGB *imrgb, int intensidade1, int intensidade2); // Aplica o efeito CLAHE à imagem RGB - Applies the CLAHE effect to the RGB image
void aplicar_transpose_rgb(ImageRGB *imrgb); // Transpõe a imagem RGB - Transposes the RGB image
void aplicar_flip_vertical_rgb(ImageRGB *imrgb); // Inverte a imagem RGB verticalmente - Flips the RGB image vertically
void aplicar_flip_horizontal_rgb(ImageRGB *imrgb); // Inverte a imagem RGB horizontalmente - Flips the RGB image horizontally
void aplicar_transpose_gray(ImageGray *imgray); // Transpõe a imagem gray - Transposes the grayscale image
void aplicar_clahe_gray(ImageGray *imgray, int intensidade1, int intensidade2); // Aplica o efeito CLAHE na imagem gray - Applies the CLAHE effect to the grayscale image
void aplicar_blur_gray(ImageGray *imgray, int intensidade); // Aplica o efeito blur na imagem gray - Applies the blur effect to the grayscale image
void aplicar_flip_vertical_gray(ImageGray *imgray); // Inverte a imagem gray verticalmente - Flips the grayscale image vertically
void aplicar_flip_horizontal_gray(ImageGray *imgray); // Inverte a imagem gray horizontalmente - Flips the grayscale image horizontally
void exibir_resultado_rgb(); // Exibe o resultado da imagem RGB processada na interface gráfica - Displays the processed RGB image result in the graphical interface
void aplicar_efeito_gray(ImageGray *imgray, int efeito, ImageHistoryGray *history); // Aplica um efeito na imagem gray e atualiza o histórico de imagens - Applies an effect to the grayscale image and updates the image history
void mostrar_menu(); // Mostra o menu principal - Shows the main menu
void sortear_efeito_rgb(ImageRGB *imrgb, ImageHistory *history); // Sorteia, aplica um efeito aleatório a imagem RGB e atualiza o histórico de imagens - Randomly selects and applies an effect to the RGB image and updates the image history
void sortear_efeito_gray(ImageGray *imgray, ImageHistoryGray *history); // Sorteia, aplica um efeito aleatório a imagem gray e atualiza o histórico de imagens - Randomly selects and applies an effect to the grayscale image and updates the image history
void abrir_imagem(const char *image_path); // Abre uma imagem a partir de um caminho de arquivo - Opens an image from a file path
void chamar_python(const char *script, const char *func, const char *input_path, const char *output_path); // Chama um script Python para executar uma função - Calls a Python script to execute a function
void on_apply_effects_rgb(GtkWidget *widget, gpointer data); // Aplica o efeito escolhido na imagem atual RGB - Applies the selected effect to the current RGB image
void on_convert_to_gray(GtkWidget *widget, gpointer data); // Converte a imagem RGB para gray - Converts the RGB image to grayscale
void on_apply_effects_gray(GtkWidget *widget, gpointer data); // Aplica o efeito escolhido na imagem atual gray - Applies the selected effect to the current grayscale image
void on_show_result(GtkWidget *widget, gpointer data); // Exibe a imagem final com todos os efeitos aplicados - Displays the final image with all applied effects
void show_effects_menu_rgb(); // Exibe um menu com várias opções de efeitos para a imagem RGB - Displays a menu with various effect options for the RGB image
void show_effects_menu_gray(); // Exibe um menu com várias opções de efeitos para a imagem gray - Displays a menu with various effect options for the grayscale image
void on_effect_selected_rgb(GtkWidget *widget, gpointer data); // Aplica o efeito selecionado pelo usuário na imagem RGB - Applies the user-selected effect to the RGB image
void on_effect_selected_gray(GtkWidget *widget, gpointer data); // Aplica o efeito selecionado pelo usuário na imagem gray - Applies the user-selected effect to the grayscale image
void on_sort_effect_rgb(GtkWidget *widget, gpointer data); // Escolhe um efeito RGB aleatório e aplica na imagem RGB - Randomly selects and applies an effect to the RGB image
void on_sort_effect_gray(GtkWidget *widget, gpointer data); // Escolhe um efeito gray aleatório e aplica na imagem gray - Randomly selects and applies an effect to the grayscale image
void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history); // Aplica um efeito específico à imagem RGB e atualiza o histórico para permitir desfazer ou refazer ações - Applies a specific effect to the RGB image and updates the history to allow undo/redo actions
void show_effects_sort_rgb(); // Exibe um menu para sortear e aplicar efeitos aleatórios em uma imagem RGB - Displays a menu to randomly select and apply effects to an RGB image
void show_effects_sort_gray(); // Exibe um menu para sortear e aplicar efeitos aleatórios em uma imagem gray - Displays a menu to randomly select and apply effects to a grayscale image
void update_status(const char *message); // Atualiza a mensagem de status na interface gráfica, exibindo informações ou feedback para o usuário - Updates the status message in the graphical interface, displaying information or feedback to the user
void on_intensity_selected(GtkWidget *widget, gpointer data); // Função onde o usuário seleciona a intensidade do efeito de blur - Function where the user selects the intensity of the blur effect
void on_intensity_selected_gray(GtkWidget *widget, gpointer data); // Função onde o usuário seleciona a intensidade do efeito de blur em tons de cinza - Function where the user selects the intensity of the blur effect in grayscale
void show_clahe_intensity_dialog(GtkWidget *parent, gpointer imrgb, gpointer history);
void show_clahe_intensity_dialog_gray(GtkWidget *parent, gpointer imgray, gpointer history);

ImageRGB imrgb; // Variável que representa uma imagem RGB - Variable representing an RGB image
ImageGray imgray; // Variável que representa uma imagem gray - Variable representing a grayscale image
ImageHistory *history_rgb; // Ponteiro para uma estrutura que armazena o histórico de alterações da imagem RGB - Pointer to a structure that stores the history of changes to the RGB image
ImageHistoryGray *history_gray; // Ponteiro para uma estrutura que armazena o histórico de alterações da imagem gray - Pointer to a structure that stores the history of changes to the grayscale image

GtkWidget *button_apply_effects_rgb; // Botão que aplica os efeitos escolhidos à imagem RGB - Button that applies the selected effects to the RGB image
GtkWidget *button_sort_effect_rgb; // Botão que sorteia e aplica um efeito aleatório na imagem RGB - Button that randomly selects and applies an effect to the RGB image
GtkWidget *button_apply_effects_gray; // Botão que aplica os efeitos escolhidos à imagem gray - Button that applies the selected effects to the grayscale image
GtkWidget *button_sort_effect_gray; // Botão que sorteia e aplica um efeito aleatório na imagem gray - Button that randomly selects and applies an effect to the grayscale image
GtkWidget *button_convert_to_gray; // Botão que converte a imagem RGB para uma imagem gray - Button that converts the RGB image to a grayscale image
GtkWidget *label_status; // Rótulo usado para exibir mensagens de status - Label used to display status messages
GtkWidget *window;


int main(int argc, char *argv[])
{
    // Inicializa a semente do gerador de números aleatórios
    // Initializes the seed of the random number generator
    srand(time(NULL));

    // Abre o arquivo de entrada contendo a imagem RGB
    // Opens the input file containing the RGB image

    FILE *arq = fopen("utils/input_image_example_RGB.txt", "r");

    // Cria histórico para imagens RGB e grayscale
    // Creates history for RGB and grayscale images

    history_rgb = create_image_history();
    history_gray = create_image_history_gray();

    // Verifica se o arquivo foi aberto corretamente
    // Checks if the file was opened correctly

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Remove o arquivo de imagem final, executa script Python e cria imagem RGB a partir do arquivo
    // Removes the final image file, executes Python script, and creates RGB image from file
    remove("utils/input_imagem_final.txt");
    system("python3 utils/select_image.py");
    criar_imagem_rgb(arq, &imrgb);

     // Adiciona a imagem RGB criada ao histórico
    // Adds the created RGB image to the history
    add_image_to_history_rgb(history_rgb, &imrgb);

    // Inicializa a biblioteca GTK
    // Initializes the GTK library
    gtk_init(&argc, &argv);

    // Carregar o arquivo CSS
    // Load the CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "frontend/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Criar janela principal
    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Editor de Imagens EaFotO");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Criar container vertical para organização dos widgets
    // Create vertical container for widget organization
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Criar grid para os botões
    // Create grid for buttons
    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10); // Espaço reduzido entre colunas

    // Criar botões com tamanho ajustado
    // Create buttons with adjusted size
    button_apply_effects_rgb = gtk_button_new_with_label("Aplicar RGB");
    g_signal_connect(button_apply_effects_rgb, "clicked", G_CALLBACK(on_apply_effects_rgb), NULL);
    gtk_widget_set_hexpand(button_apply_effects_rgb, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_apply_effects_rgb, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_apply_effects_rgb, 0, 0, 1, 1);

    button_apply_effects_gray = gtk_button_new_with_label("Aplicar P&B");
    g_signal_connect(button_apply_effects_gray, "clicked", G_CALLBACK(on_apply_effects_gray), NULL);
    gtk_widget_set_hexpand(button_apply_effects_gray, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_apply_effects_gray, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_apply_effects_gray, 1, 0, 1, 1);

    button_convert_to_gray = gtk_button_new_with_label("Converter P&B");
    g_signal_connect(button_convert_to_gray, "clicked", G_CALLBACK(on_convert_to_gray), NULL);
    gtk_widget_set_hexpand(button_convert_to_gray, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_convert_to_gray, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_convert_to_gray, 2, 0, 1, 1);

    GtkWidget *button_show_result = gtk_button_new_with_label("Exibir Resultado");
    g_signal_connect(button_show_result, "clicked", G_CALLBACK(on_show_result), NULL);
    gtk_widget_set_hexpand(button_show_result, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_show_result, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_show_result, 3, 0, 1, 1);

    button_sort_effect_rgb = gtk_button_new_with_label("Sortear RGB");
    g_signal_connect(button_sort_effect_rgb, "clicked", G_CALLBACK(show_effects_sort_rgb), NULL);
    gtk_widget_set_hexpand(button_sort_effect_rgb, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_sort_effect_rgb, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_sort_effect_rgb, 4, 0, 1, 1);

    button_sort_effect_gray = gtk_button_new_with_label("Sortear P&B");
    g_signal_connect(button_sort_effect_gray, "clicked", G_CALLBACK(show_effects_sort_gray), NULL);
    gtk_widget_set_hexpand(button_sort_effect_gray, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_sort_effect_gray, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_sort_effect_gray, 5, 0, 1, 1);

    // Inicialmente desativar botões de P&B e Sortear P&B
    // Initially disable grayscale and Sort grayscale buttons
    gtk_widget_set_sensitive(button_apply_effects_gray, FALSE);
    gtk_widget_set_sensitive(button_sort_effect_gray, FALSE);

    // Criar botão de sair
    // Create exit button
    GtkWidget *button_exit = gtk_button_new_with_label("Sair");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_hexpand(button_exit, TRUE);    // Expansão horizontal
    gtk_widget_set_margin_bottom(button_exit, 5); // Margem inferior
    gtk_grid_attach(GTK_GRID(grid), button_exit, 6, 0, 1, 1);

    // Criar label de status
    // Create status label
    label_status = gtk_label_new("Status: Pronto");
    gtk_widget_set_name(label_status, "status");
    gtk_box_pack_end(GTK_BOX(vbox), label_status, FALSE, FALSE, 0);

    // Carregar a logo com tamanho específico
    // Load the logo with specific size
    GtkWidget *logo_image = gtk_image_new_from_file("frontend/logo_editor.png");
    gtk_image_set_pixel_size(GTK_IMAGE(logo_image), 250); // Ajustar para 850x850 pixels

    // Criar um box para centralizar a logo
    // Create a box to center the logo
    GtkWidget *logo_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), logo_box, FALSE, FALSE, 0);
    gtk_widget_set_halign(logo_box, GTK_ALIGN_CENTER);

   // Adicionar a logo ao box
    // Add the logo to the box
    gtk_container_add(GTK_CONTAINER(logo_box), logo_image);
    gtk_widget_show_all(logo_box);

    // Exibir todos os widgets da janela
    // Show all widgets in the window
    gtk_widget_show_all(window);

    // Iniciar loop principal GTK
    // Start main GTK loop
    gtk_main();

    return 0;
}

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb)
{
    // Lê a imagem do arquivo
    // Reads the image from the file
    ler_imagem_arkv(arq, imrgb);

    // Chama um script Python para criar uma imagem RGB a partir de um arquivo de texto e salvá-la como uma imagem PNG
    // Calls a Python script to create an RGB image from a text file and save it as a PNG image
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", "utils/input_image_example_RGB.txt", "utils/imagem_final.png");

    // Abre a imagem resultante para visualização
    // Opens the resulting image for viewing
    abrir_imagem("out_image.png");
}

void show_blur_intensity_dialog(GtkWidget *parent, gpointer imrgb, gpointer history) {
 // Criando uma janela de diálogo
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Selecione a intensidade do Blur",
                                                    GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    "Cancelar",
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);

    // Adicionando botões com os valores de intensidade
    GtkWidget *button_5 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Fraco", GTK_RESPONSE_OK);
    GtkWidget *button_10 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Médio", GTK_RESPONSE_OK);
    GtkWidget *button_15 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Forte", GTK_RESPONSE_OK);

    // Conectar os sinais dos botões aos handlers correspondentes
    g_signal_connect(button_5, "clicked", G_CALLBACK(on_intensity_selected), GINT_TO_POINTER(5));
    g_signal_connect(button_10, "clicked", G_CALLBACK(on_intensity_selected), GINT_TO_POINTER(10));
    g_signal_connect(button_15, "clicked", G_CALLBACK(on_intensity_selected), GINT_TO_POINTER(15));

    // Mostrar todos os widgets
    gtk_widget_show_all(dialog);

    // Aguardar até que o usuário escolha uma opção
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    // O loop principal de eventos do GTK será bloqueado até que o diálogo seja fechado
    // Aqui você pode adicionar qualquer lógica adicional baseada na escolha do usuário, se necessário

    // Uma vez que o usuário escolheu uma opção e o diálogo foi fechado, você pode destruí-lo
    gtk_widget_destroy(dialog);
}

void show_blur_intensity_dialog_gray(GtkWidget *parent, ImageGray *imgray, ImageHistoryGray *history) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Selecione a intensidade do Blur",
                                                    GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    "Cancelar",
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);

    GtkWidget *button_5 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Fraco", GTK_RESPONSE_OK);
    GtkWidget *button_10 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Médio", GTK_RESPONSE_OK);
    GtkWidget *button_15 = gtk_dialog_add_button(GTK_DIALOG(dialog), "Forte", GTK_RESPONSE_OK);

    g_signal_connect(button_5, "clicked", G_CALLBACK(on_intensity_selected_gray), GINT_TO_POINTER(5));
    g_signal_connect(button_10, "clicked", G_CALLBACK(on_intensity_selected_gray), GINT_TO_POINTER(10));
    g_signal_connect(button_15, "clicked", G_CALLBACK(on_intensity_selected_gray), GINT_TO_POINTER(15));

    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK) {
        gpointer data = g_object_get_data(G_OBJECT(dialog), "intensity");
        if (data != NULL) {
            int intensidade = GPOINTER_TO_INT(data);
            aplicar_blur_gray(imgray, intensidade); // Aplica o blur
        }
    }

    gtk_widget_destroy(dialog);
}


// Função de callback para tratar a seleção de intensidade
void on_intensity_selected(GtkWidget *widget, gpointer data) {
    int intensidade = GPOINTER_TO_INT(data);
    // Aqui você pode aplicar o blur com a intensidade selecionada
    aplicar_blur_rgb(&imrgb, intensidade); // Verifique se imrgb é um ponteiro ImageRGB *
    gtk_widget_destroy(GTK_WIDGET(gtk_widget_get_parent(widget)));
}

void on_intensity_selected_gray(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(widget);
    g_object_set_data(G_OBJECT(dialog), "intensity", data);
    gtk_dialog_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
}

void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history)
{
    const char *txt_filename = "utils/input_imagem_final.txt";
    const char *output_filename = "utils/imagem_final.png";

    switch (efeito)
    {
    case 1:
        update_status("Blur RGB aplicado com sucesso");
        show_blur_intensity_dialog(GTK_WIDGET(window), imrgb, history);

        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_rgb(history, imrgb);
        break;
    case 2:
        // Atualiza o status e aplica o efeito CLAHE na imagem RGB
        // Updates status and applies CLAHE effect to RGB image
        update_status("CLAHE RGB aplicado com sucesso");
        show_clahe_intensity_dialog(GTK_WIDGET(window), imrgb, history);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_rgb(history, imrgb);
        break;
    case 3:
        // Atualiza o status e aplica o efeito de transposição na imagem RGB
        // Updates status and applies transpose effect to RGB image
        update_status("Transpose RGB aplicado com sucesso");
        aplicar_transpose_rgb(imrgb);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_rgb(history, imrgb);
        break;
    case 4:
         // Atualiza o status e aplica o efeito de flip vertical na imagem RGB
        // Updates status and applies vertical flip effect to RGB image
        update_status("Flip Vertical RGB aplicado com sucesso");
        aplicar_flip_vertical_rgb(imrgb);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_rgb(history, imrgb);
        break;
    case 5:
        // Atualiza o status e aplica o efeito de flip horizontal na imagem RGB
        // Updates status and applies horizontal flip effect to RGB image
        update_status("Flip Horizontal RGB aplicado com sucesso");
        aplicar_flip_horizontal_rgb(imrgb);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_rgb(history, imrgb);
        break;
    case 7:
         // Atualiza o status e desfaz a última alteração na imagem RGB
        // Updates status and undoes the last change to RGB image
        update_status("Desfazendo alteração");
        desfazer_rgb(history, imrgb);
        break;
    case 8:
         // Atualiza o status e refaz a última alteração desfeita na imagem RGB
        // Updates status and redoes the last undone change to RGB image
        update_status("Refazendo alteração");
        refazer_rgb(history, imrgb);
        break;
    default:
        // Atualiza o status para indicar que a opção é inválida
        // Updates status to indicate that the option is invalid
        update_status("Opção inválida");
        return;
    }

    // Abre o arquivo de texto para salvar a imagem modificada
    // Opens the text file to save the modified image
    FILE *input_txt = fopen(txt_filename, "w");

    // Salva a imagem modificada no arquivo de texto
    // Saves the modified image to the text file
    salvar_imagem_arkv_rgb(imrgb, input_txt);

    // Chama um script Python para criar uma imagem RGB a partir do arquivo de texto e salvá-la como uma imagem PNG
    // Calls a Python script to create an RGB image from the text file and save it as a PNG image
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", txt_filename, output_filename);

    // Abre a imagem resultante para visualização
    // Opens the resulting image for viewing
    abrir_imagem("out_image.png");
}


void aplicar_efeito_gray(ImageGray *imgray, int efeito, ImageHistoryGray *history)
{
    // Define os nomes dos arquivos de entrada e saída
    // Defines the input and output file names
    const char *txt_filename = "utils/input_imagem_final.txt";
    const char *output_filename = "utils/imagem_final.png";

    // Aplica um efeito baseado no valor de 'efeito'
    // Applies an effect based on the value of 'efeito'
    switch (efeito)
    {
    case 1:
        // Atualiza o status e aplica o efeito de blur na imagem em tons de cinza
        // Updates status and applies blur effect to grayscale image
        update_status("Blur Gray aplicado com sucesso");
        show_blur_intensity_dialog_gray(GTK_WIDGET(window), imgray, history);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_gray(history, imgray);
        break;
    case 2:
        // Atualiza o status e aplica o efeito CLAHE na imagem em tons de cinza
        // Updates status and applies CLAHE effect to grayscale image
        update_status("CLAHE Gray aplicado com sucesso");
        show_clahe_intensity_dialog_gray(GTK_WIDGET(window), imgray, history);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_gray(history, imgray);
        break;
    case 3:
        // Atualiza o status e aplica o efeito de transposição na imagem em tons de cinza
        // Updates status and applies transpose effect to grayscale image
        update_status("Transpose Gray aplicado com sucesso");
        aplicar_transpose_gray(imgray);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_gray(history, imgray);
        break;
    case 4:
        // Atualiza o status e aplica o efeito de flip vertical na imagem em tons de cinza
        // Updates status and applies vertical flip effect to grayscale image
        update_status("Flip Vertical Gray aplicado com sucesso");
        aplicar_flip_vertical_gray(imgray);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_gray(history, imgray);
        break;
    case 5:
        // Atualiza o status e aplica o efeito de flip horizontal na imagem em tons de cinza
        // Updates status and applies horizontal flip effect to grayscale image
        update_status("Flip Horizontal Gray aplicado com sucesso");
        aplicar_flip_horizontal_gray(imgray);
        // Adiciona a imagem modificada ao histórico
        // Adds the modified image to history
        add_image_to_history_gray(history, imgray);
        break;
    case 7:
        // Atualiza o status e desfaz a última alteração na imagem em tons de cinza
        // Updates status and undoes the last change to grayscale image
        update_status("Desfazendo alteração");
        desfazer_gray(history, imgray);
        break;
    case 8:
        // Atualiza o status e refaz a última alteração desfeita na imagem em tons de cinza
        // Updates status and redoes the last undone change to grayscale image
        update_status("Refazendo alteracao\n");
        refazer_gray(history, imgray);
        break;
    default:
        // Indica que a opção é inválida
        // Indicates that the option is invalid
        printf("Opcao invalida\n");
        return;
    }

    // Abre o arquivo de texto para salvar a imagem modificada
    // Opens the text file to save the modified image
    FILE *input_txt = fopen(txt_filename, "w");
    
    // Salva a imagem modificada no arquivo de texto
    // Saves the modified image to the text file
    salvar_imagem_arkv(imgray, input_txt);
    
    // Chama um script Python para criar uma imagem em tons de cinza a partir do arquivo de texto e salvá-la como uma imagem PNG
    // Calls a Python script to create a grayscale image from the text file and save it as a PNG image
    chamar_python("utils/image_utils.py", "image_gray_from_txt", txt_filename, output_filename);
    
    // Abre a imagem resultante para visualização
    // Opens the resulting image for viewing
    abrir_imagem("out_image.png");

}

// chamar_python("utils/image_utils.py", "image_rgb_from_latest_txt", "utils/input_imagem_final.txt", "ritinha.png");
// Função para chamar um script Python com parâmetros especificados
// Function to call a Python script with specified parameters
void chamar_python(const char *script, const char *func, const char *input_path, const char *output_path)
{
    // Define um comando para chamar o script Python com os parâmetros
    // Defines a command to call the Python script with parameters
    char command[256];
    snprintf(command, sizeof(command), "python3 %s %s \"%s\" \"%s\"", script, func, input_path, output_path);
    
    // Executa o comando no sistema
    // Executes the command in the system
    system(command);
}

// Função para aplicar efeito de blur em uma imagem RGB
// Function to apply blur effect on an RGB image
void aplicar_blur_rgb(ImageRGB *imrgb, int intensidade)
{
    ImageRGB blur_rgb;
    // Define as dimensões da imagem de blur
    // Sets the dimensions of the blur image
    blur_rgb.dim.altura = imrgb->dim.altura;
    blur_rgb.dim.largura = imrgb->dim.largura;
    // Aloca memória para os pixels da imagem de blur
    // Allocates memory for the pixels of the blur image
    alocarRGB(blur_rgb.dim.altura, blur_rgb.dim.largura, &(blur_rgb.pixels));

    // Aplica o filtro de mediana para criar o efeito de blur
    // Applies the median filter to create the blur effect
    blur_rgb = *median_blur_rgb(imrgb, intensidade);

    // Atualiza a imagem original com a imagem de blur
    // Updates the original image with the blur image
    *imrgb = blur_rgb;
}

void show_clahe_intensity_dialog(GtkWidget *parent, gpointer imrgb, gpointer history)
{
    // Criando uma janela de diálogo
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Selecione as intensidades do CLAHE",
                                                    GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    "Cancelar",
                                                    GTK_RESPONSE_CANCEL,
                                                    "Aplicar",
                                                    GTK_RESPONSE_ACCEPT,
                                                    NULL);

    // Criando containers para os campos de entrada
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Criando rótulos e campos de entrada para as intensidades
    GtkWidget *label_intensidade1 = gtk_label_new("Intensidade 1:");
    GtkWidget *entry_intensidade1 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_intensidade1), "256"); 

    GtkWidget *label_intensidade2 = gtk_label_new("Intensidade 2:");
    GtkWidget *entry_intensidade2 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_intensidade2), "40"); 

    // Adicionando os widgets à grade
    gtk_grid_attach(GTK_GRID(grid), label_intensidade1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_intensidade1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_intensidade2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_intensidade2, 1, 1, 1, 1);

    // Mostrar todos os widgets
    gtk_widget_show_all(dialog);

    // Aguardar até que o usuário escolha uma opção
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Se o usuário clicou em "Aplicar"
    if (result == GTK_RESPONSE_ACCEPT)
    {
        int intensidade1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_intensidade1)));
        int intensidade2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_intensidade2)));

        // Verificar se os valores estão dentro do intervalo permitido
        if (intensidade1 < 2 || intensidade2 < 2 && intensidade1 > 256 || intensidade2 > 256)
        {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Valor inválido para intensidade. Deve estar entre 2 e 256.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
        else
        {
            aplicar_clahe_rgb((ImageRGB *)imrgb, intensidade1, intensidade2); 
        }
    }

    gtk_widget_destroy(dialog);
}

void show_clahe_intensity_dialog_gray(GtkWidget *parent, gpointer imgray, gpointer history)
{
    // Criando uma janela de diálogo
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Selecione as intensidades do CLAHE",
                                                    GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    "Cancelar",
                                                    GTK_RESPONSE_CANCEL,
                                                    "Aplicar",
                                                    GTK_RESPONSE_ACCEPT,
                                                    NULL);

    // Criando containers para os campos de entrada
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Criando rótulos e campos de entrada para as intensidades
    GtkWidget *label_intensidade1 = gtk_label_new("Intensidade 1:");
    GtkWidget *entry_intensidade1 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_intensidade1), "256"); 

    GtkWidget *label_intensidade2 = gtk_label_new("Intensidade 2:");
    GtkWidget *entry_intensidade2 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_intensidade2), "40"); 

    // Adicionando os widgets à grade
    gtk_grid_attach(GTK_GRID(grid), label_intensidade1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_intensidade1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_intensidade2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_intensidade2, 1, 1, 1, 1);

    // Mostrar todos os widgets
    gtk_widget_show_all(dialog);

    // Aguardar até que o usuário escolha uma opção
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Se o usuário clicou em "Aplicar"
    if (result == GTK_RESPONSE_ACCEPT)
    {
        int intensidade1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_intensidade1)));
        int intensidade2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry_intensidade2)));

        // Verificar se os valores estão dentro do intervalo permitido
        if (intensidade1 < 2 || intensidade2 < 2 && intensidade1 > 256 || intensidade2 > 256)
        {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Valor inválido para intensidade. Deve estar entre 2 e 256.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
        else
        {
            aplicar_clahe_gray((ImageGray *)imgray, intensidade1, intensidade2); 
        }

    }

    gtk_widget_destroy(dialog);
}


// Função para aplicar CLAHE em uma imagem RGB
// Function to apply CLAHE on an RGB image
void aplicar_clahe_rgb(ImageRGB *imrgb, int intensidade1, int intensidade2)
{
    ImageRGB clahe_rgb_img;
    // Define as dimensões da imagem CLAHE
    // Sets the dimensions of the CLAHE image
    clahe_rgb_img.dim.altura = imrgb->dim.altura;
    clahe_rgb_img.dim.largura = imrgb->dim.largura;
    // Aloca memória para os pixels da imagem CLAHE
    // Allocates memory for the pixels of the CLAHE image
    alocarRGB(clahe_rgb_img.dim.altura, clahe_rgb_img.dim.largura, &(clahe_rgb_img.pixels));

    // Aplica o algoritmo CLAHE para melhorar o contraste
    // Applies the CLAHE algorithm to enhance contrast
    clahe_rgb_img = *clahe_rgb(imrgb, intensidade1, intensidade2);

    // Atualiza a imagem original com a imagem CLAHE
    // Updates the original image with the CLAHE image
    *imrgb = clahe_rgb_img;
}

// Função para aplicar transposição em uma imagem RGB
// Function to apply transpose effect on an RGB image
void aplicar_transpose_rgb(ImageRGB *imrgb)
{
    ImageRGB transpose_rgb_var;
    // Define as dimensões da imagem transposta
    // Sets the dimensions of the transposed image
    transpose_rgb_var.dim.altura = imrgb->dim.altura;
    transpose_rgb_var.dim.largura = imrgb->dim.largura;
    // Aloca memória para os pixels da imagem transposta
    // Allocates memory for the pixels of the transposed image
    alocarRGB(transpose_rgb_var.dim.altura, transpose_rgb_var.dim.largura, &(transpose_rgb_var.pixels));

    // Aplica a transposição na imagem
    // Applies the transpose effect on the image
    transpose_rgb(imrgb, &transpose_rgb_var);

    // Atualiza a imagem original com a imagem transposta
    // Updates the original image with the transposed image
    *imrgb = transpose_rgb_var;
}

// Função para aplicar flip vertical em uma imagem RGB
// Function to apply vertical flip on an RGB image
void aplicar_flip_vertical_rgb(ImageRGB *imrgb)
{
    ImageRGB flip_rgb_vertical;
    // Define as dimensões da imagem de flip vertical
    // Sets the dimensions of the vertically flipped image
    flip_rgb_vertical.dim.altura = imrgb->dim.altura;
    flip_rgb_vertical.dim.largura = imrgb->dim.largura;
    // Aloca memória para os pixels da imagem de flip vertical
    // Allocates memory for the pixels of the vertically flipped image
    alocarRGB(flip_rgb_vertical.dim.altura, flip_rgb_vertical.dim.largura, &(flip_rgb_vertical.pixels));

    // Aplica o flip vertical na imagem
    // Applies the vertical flip on the image
    flip_vertical_rgb(imrgb, &flip_rgb_vertical);

    // Atualiza a imagem original com a imagem de flip vertical
    // Updates the original image with the vertically flipped image
    *imrgb = flip_rgb_vertical;
}

// Função para aplicar flip horizontal em uma imagem RGB
// Function to apply horizontal flip on an RGB image
void aplicar_flip_horizontal_rgb(ImageRGB *imrgb)
{
    ImageRGB flip_rgb_horizontal;
    // Define as dimensões da imagem de flip horizontal
    // Sets the dimensions of the horizontally flipped image
    flip_rgb_horizontal.dim.altura = imrgb->dim.altura;
    flip_rgb_horizontal.dim.largura = imrgb->dim.largura;
    // Aloca memória para os pixels da imagem de flip horizontal
    // Allocates memory for the pixels of the horizontally flipped image
    alocarRGB(flip_rgb_horizontal.dim.altura, flip_rgb_horizontal.dim.largura, &(flip_rgb_horizontal.pixels));

    // Aplica o flip horizontal na imagem
    // Applies the horizontal flip on the image
    flip_horizontal_rgb(imrgb, &flip_rgb_horizontal);

    // Atualiza a imagem original com a imagem de flip horizontal
    // Updates the original image with the horizontally flipped image
    *imrgb = flip_rgb_horizontal;
}


// Função para aplicar transposição em uma imagem em escala de cinza
// Function to apply transpose effect on a grayscale image
void aplicar_transpose_gray(ImageGray *imgray)
{
    ImageGray transpose_gray_var;
    // Define as dimensões da imagem transposta
    // Sets the dimensions of the transposed image
    transpose_gray_var.dim.altura = imgray->dim.altura;
    transpose_gray_var.dim.largura = imgray->dim.largura;
    // Aloca memória para os pixels da imagem transposta
    // Allocates memory for the pixels of the transposed image
    alocarGray(transpose_gray_var.dim.altura, transpose_gray_var.dim.largura, &(transpose_gray_var.pixels));

    // Aplica a transposição na imagem
    // Applies the transpose effect on the image
    transpose_gray(imgray, &transpose_gray_var);

    // Atualiza a imagem original com a imagem transposta
    // Updates the original image with the transposed image
    *imgray = transpose_gray_var;
}

// Função para aplicar CLAHE em uma imagem em escala de cinza
// Function to apply CLAHE on a grayscale image
void aplicar_clahe_gray(ImageGray *imgray, int intensidade1, int intensidade2)
{
    ImageGray clahe_gray_saida;
    // Define as dimensões da imagem CLAHE
    // Sets the dimensions of the CLAHE image
    clahe_gray_saida.dim.altura = imgray->dim.altura;
    clahe_gray_saida.dim.largura = imgray->dim.largura;
    // Aloca memória para os pixels da imagem CLAHE
    // Allocates memory for the pixels of the CLAHE image
    alocarGray(clahe_gray_saida.dim.altura, clahe_gray_saida.dim.largura, &(clahe_gray_saida.pixels));

    // Aplica o algoritmo CLAHE para melhorar o contraste
    // Applies the CLAHE algorithm to enhance contrast
    clahe_gray_saida = *clahe_gray(imgray, intensidade1, intensidade2);

    // Atualiza a imagem original com a imagem CLAHE
    // Updates the original image with the CLAHE image
    *imgray = clahe_gray_saida;
}

// Função para aplicar blur em uma imagem em escala de cinza
// Function to apply blur effect on a grayscale image
void aplicar_blur_gray(ImageGray *imgray, int intensidade)
{
    ImageGray blur_gray;
    // Define as dimensões da imagem de blur
    // Sets the dimensions of the blur image
    blur_gray.dim.altura = imgray->dim.altura;
    blur_gray.dim.largura = imgray->dim.largura;
    // Aloca memória para os pixels da imagem de blur
    // Allocates memory for the pixels of the blur image
    alocarGray(blur_gray.dim.altura, blur_gray.dim.largura, &(blur_gray.pixels));

    // Aplica o filtro de mediana para criar o efeito de blur
    // Applies the median filter to create the blur effect
    blur_gray = *median_blur_gray(imgray, intensidade);

    // Atualiza a imagem original com a imagem de blur
    // Updates the original image with the blur image
    *imgray = blur_gray;
}

// Função para aplicar flip vertical em uma imagem em escala de cinza
// Function to apply vertical flip on a grayscale image
void aplicar_flip_vertical_gray(ImageGray *imgray)
{
    ImageGray flip_gray_vertical;
    // Define as dimensões da imagem de flip vertical
    // Sets the dimensions of the vertically flipped image
    flip_gray_vertical.dim.altura = imgray->dim.altura;
    flip_gray_vertical.dim.largura = imgray->dim.largura;
    // Aloca memória para os pixels da imagem de flip vertical
    // Allocates memory for the pixels of the vertically flipped image
    alocarGray(flip_gray_vertical.dim.altura, flip_gray_vertical.dim.largura, &(flip_gray_vertical.pixels));

    // Aplica o flip vertical na imagem
    // Applies the vertical flip on the image
    flip_vertical_gray(imgray, &flip_gray_vertical);

    // Atualiza a imagem original com a imagem de flip vertical
    // Updates the original image with the vertically flipped image
    *imgray = flip_gray_vertical;
}

// Função para aplicar flip horizontal em uma imagem em escala de cinza
// Function to apply horizontal flip on a grayscale image
void aplicar_flip_horizontal_gray(ImageGray *imgray)
{
    ImageGray flip_gray_horizontal_var;
    // Define as dimensões da imagem de flip horizontal
    // Sets the dimensions of the horizontally flipped image
    flip_gray_horizontal_var.dim.altura = imgray->dim.altura;
    flip_gray_horizontal_var.dim.largura = imgray->dim.largura;
    // Aloca memória para os pixels da imagem de flip horizontal
    // Allocates memory for the pixels of the horizontally flipped image
    alocarGray(flip_gray_horizontal_var.dim.altura, flip_gray_horizontal_var.dim.largura, &(flip_gray_horizontal_var.pixels));

    // Aplica o flip horizontal na imagem
    // Applies the horizontal flip on the image
    flip_horizontal_gray(imgray, &flip_gray_horizontal_var);

    // Atualiza a imagem original com a imagem de flip horizontal
    // Updates the original image with the horizontally flipped image
    *imgray = flip_gray_horizontal_var;
}

// Função para abrir uma imagem no Windows
// Function to open an image on Windows
void abrir_imagem(const char *image_path)
{
    char command[256];
    // Define o comando para abrir a imagem usando um script Python
    // Defines the command to open the image using a Python script
    snprintf(command, sizeof(command), "python3 utils/abrir_imagem_sistemas.py %s", image_path);
    // Executa o comando no sistema e verifica o retorno
    // Executes the command in the system and checks the return value
    int ret = system(command);
    if (ret != 0)
    {
        // Imprime uma mensagem de erro se a imagem não pôde ser aberta
        // Prints an error message if the image could not be opened
        printf("Erro ao abrir a imagem. Código de retorno: %d\n", ret);
    }
}


// ####################### ZONA DE RISCO

// Função para aplicar efeitos em uma imagem RGB
// Function to apply effects on an RGB image
void on_apply_effects_rgb(GtkWidget *widget, gpointer data)
{
    show_effects_menu_rgb();
}

// Função para converter uma imagem RGB para escala de cinza
// Function to convert an RGB image to grayscale
void on_convert_to_gray(GtkWidget *widget, gpointer data)
{
    // Converte a imagem RGB para escala de cinza
    // Converts the RGB image to grayscale
    converter_para_gray(&imrgb, &imgray);
    // Abre um arquivo para salvar a imagem final em texto
    // Opens a file to save the final image as text
    FILE *input_txt = fopen("utils/input_imagem_final.txt", "w");
    salvar_imagem_arkv(&imgray, input_txt);
    // Chama um script Python para processar a imagem
    // Calls a Python script to process the image
    chamar_python("utils/image_utils.py", "image_gray_from_txt", "utils/input_imagem_final.txt", "utils/imagem_final.png");
    // Adiciona a imagem ao histórico de imagens em escala de cinza
    // Adds the image to the grayscale image history
    add_image_to_history_gray(history_gray, &imgray);

    // Desabilita botões de efeitos RGB e habilita botões de efeitos grayscale
    // Disables RGB effects buttons and enables grayscale effects buttons
    gtk_widget_set_sensitive(button_apply_effects_rgb, FALSE);
    gtk_widget_set_sensitive(button_sort_effect_rgb, FALSE);
    gtk_widget_set_sensitive(button_apply_effects_gray, TRUE);
    gtk_widget_set_sensitive(button_sort_effect_gray, TRUE);

    // Abre a imagem RGB
    // Opens the RGB image
    abrir_imagem("out_image.png");
}

// Função para aplicar efeitos em uma imagem em escala de cinza
// Function to apply effects on a grayscale image
void on_apply_effects_gray(GtkWidget *widget, gpointer data)
{
    show_effects_menu_gray();
}

// Função para mostrar o resultado final da imagem
// Function to show the final result of the image
void on_show_result(GtkWidget *widget, gpointer data)
{
    abrir_imagem("utils/imagem_final.png");
}

// Função para mostrar o menu de seleção de efeitos para imagens RGB
// Function to show the effect selection menu for RGB images
void show_effects_menu_rgb()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button7, *button8, *cancel_button;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    // Cria um diálogo para o menu de efeitos
    // Creates a dialog for the effects menu
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Escolha o Efeito RGB");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    // Obtém a área de conteúdo do diálogo
    // Gets the content area of the dialog
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Cria um grid para organizar os botões
    // Creates a grid to organize the buttons
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Cria botões para os diferentes efeitos e conecta os sinais de clique
    // Creates buttons for different effects and connects the click signals
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

    // Mostra todos os widgets do diálogo
    // Shows all the dialog widgets
    gtk_widget_show_all(dialog);
}

void show_effects_menu_gray()
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button7, *button8, *cancel_button;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    // Create a new dialog window
    // Cria uma nova janela de diálogo
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Escolha o Efeito Gray");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    // Get the content area of the dialog
    // Obtém a área de conteúdo do diálogo
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create a new grid and set spacing between rows and columns
    // Cria um novo grid e define o espaçamento entre linhas e colunas
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Create and configure the "Blur Gray" button
    // Cria e configura o botão "Blur Gray"
    button1 = gtk_button_new_with_label("Blur Gray");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)1);
    gtk_widget_set_hexpand(button1, TRUE);
    gtk_widget_set_vexpand(button1, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 2, 1);

    // Create and configure the "CLAHE Gray" button
    // Cria e configura o botão "CLAHE Gray"
    button2 = gtk_button_new_with_label("CLAHE Gray");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)2);
    gtk_widget_set_hexpand(button2, TRUE);
    gtk_widget_set_vexpand(button2, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 2, 1);

    // Create and configure the "Transpose Gray" button
    // Cria e configura o botão "Transpose Gray"
    button3 = gtk_button_new_with_label("Transpose Gray");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)3);
    gtk_widget_set_hexpand(button3, TRUE);
    gtk_widget_set_vexpand(button3, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 2, 2, 1);

    // Create and configure the "Flip Vertical Gray" button
    // Cria e configura o botão "Flip Vertical Gray"
    button4 = gtk_button_new_with_label("Flip Vertical Gray");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)4);
    gtk_widget_set_hexpand(button4, TRUE);
    gtk_widget_set_vexpand(button4, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button4, 0, 3, 2, 1);

    // Create and configure the "Flip Horizontal Gray" button
    // Cria e configura o botão "Flip Horizontal Gray"
    button5 = gtk_button_new_with_label("Flip Horizontal Gray");
    g_signal_connect(button5, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)5);
    gtk_widget_set_hexpand(button5, TRUE);
    gtk_widget_set_vexpand(button5, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button5, 0, 4, 2, 1);

    // Create and configure the "Undo" button
    // Cria e configura o botão "Desfazer"
    button7 = gtk_button_new_with_label("Desfazer");
    g_signal_connect(button7, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)7);
    gtk_widget_set_hexpand(button7, TRUE);
    gtk_widget_set_vexpand(button7, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button7, 0, 5, 1, 1);

    // Create and configure the "Redo" button
    // Cria e configura o botão "Refazer"
    button8 = gtk_button_new_with_label("Refazer");
    g_signal_connect(button8, "clicked", G_CALLBACK(on_effect_selected_gray), (gpointer)8);
    gtk_widget_set_hexpand(button8, TRUE);
    gtk_widget_set_vexpand(button8, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button8, 1, 5, 1, 1);

    // Show all widgets in the dialog
    // Exibe todos os widgets no diálogo
    gtk_widget_show_all(dialog);
}

void show_effects_sort_rgb()
{
    GtkWidget *dialog, *content_area, *grid, *image;
    GtkWidget *button1, *button2, *button3, *button4;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    // Create a new dialog window with buttons
    // Cria uma nova janela de diálogo com botões
    dialog = gtk_dialog_new_with_buttons("Escolha o Efeito RGB",
                                         NULL,
                                         flags,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    // Set the default size of the dialog window
    // Define o tamanho padrão da janela de diálogo
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);

    // Get the content area of the dialog
    // Obtém a área de conteúdo do diálogo
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create a new grid and set it to be homogeneous
    // Cria um novo grid e define para ser homogêneo
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Create and configure the "Reshuffle" button
    // Cria e configura o botão "Sortear Novamente"
    button1 = gtk_button_new_with_label("Sortear Novamente");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(1));
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

    // Create and configure the "Undo Last Shuffle" button
    // Cria e configura o botão "Desfazer Último Sorteio"
    button2 = gtk_button_new_with_label("Desfazer Último Sorteio");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(2));
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);

    // Create and configure the "Redo Last Shuffle" button
    // Cria e configura o botão "Refazer Último Sorteio"
    button3 = gtk_button_new_with_label("Refazer Último Sorteio");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(3));
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1);

    // Create and configure the "Back to Main Menu" button
    // Cria e configura o botão "Voltar ao Menu Principal"
    button4 = gtk_button_new_with_label("Voltar ao Menu Principal");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_sort_effect_rgb), GINT_TO_POINTER(4));
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1);

    // Add an image to the grid
    // Adiciona uma imagem ao grid
    image = gtk_image_new_from_file("frontend/dado_imagem.png");
    gtk_grid_attach(GTK_GRID(grid), image, 0, 2, 2, 1);

    // Connect the destroy signal to the "Back to Main Menu" button
    // Conecta o sinal de destruir ao botão "Voltar ao Menu Principal"
    g_signal_connect_swapped(button4, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    // Show all widgets in the dialog
    // Exibe todos os widgets no diálogo
    gtk_widget_show_all(dialog);
}

void show_effects_sort_gray()
{
    GtkWidget *dialog, *content_area, *grid, *image;
    GtkWidget *button1, *button2, *button3, *button4;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    // Create a new dialog with buttons
    // Cria um novo diálogo com botões
    dialog = gtk_dialog_new_with_buttons("Escolha o Efeito Gray",
                                         NULL,
                                         flags,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    // Set the default size of the dialog
    // Define o tamanho padrão do diálogo
    gtk_window_set_default_size(GTK_WINDOW(dialog), 500, 500);

    // Get the content area of the dialog
    // Obtém a área de conteúdo do diálogo
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create a new grid for layout
    // Cria uma nova grade para o layout
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Create a button to sort the effect again
    // Cria um botão para sortear o efeito novamente
    button1 = gtk_button_new_with_label("Sortear Novamente");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(1));
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

    // Create a button to undo the last sort
    // Cria um botão para desfazer o último sorteio
    button2 = gtk_button_new_with_label("Desfazer Último Sorteio");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(2));
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);

    // Create a button to redo the last sort
    // Cria um botão para refazer o último sorteio
    button3 = gtk_button_new_with_label("Refazer Último Sorteio");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(3));
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1);

    // Create a button to go back to the main menu
    // Cria um botão para voltar ao menu principal
    button4 = gtk_button_new_with_label("Voltar ao Menu Principal");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_sort_effect_gray), GINT_TO_POINTER(4));
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1);

    // Add an image to the grid
    // Adiciona uma imagem à grade
    image = gtk_image_new_from_file("frontend/dado_imagem.png");
    gtk_grid_attach(GTK_GRID(grid), image, 0, 2, 2, 1);

    // Connect the destroy signal to the button to close the dialog
    // Conecta o sinal de destruir ao botão para fechar o diálogo
    g_signal_connect_swapped(button4, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    // Show all widgets in the dialog
    // Mostra todos os widgets no diálogo
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
        // Update status and apply the RGB sort effect
        // Atualiza o status e aplica o efeito de sorteio RGB
        update_status("Sorteando efeito RGB");
        sortear_efeito_rgb(&imrgb, history_rgb);
        break;
    case 2:
        // Update status and undo the last change
        // Atualiza o status e desfaz a última alteração
        update_status("Desfazendo alteração");
        aplicar_efeito_rgb(&imrgb, 7, history_rgb);
        break;
    case 3:
        // Update status and redo the last change
        // Atualiza o status e refaz a última alteração
        update_status("Refazendo alteração");
        aplicar_efeito_rgb(&imrgb, 8, history_rgb);
        break;
    case 4:
        // Do nothing for this action
        // Não faz nada para esta ação
        break;
    default:
        // Print an invalid option message
        // Imprime uma mensagem de opção inválida
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
        // Apply a new gray effect
        // Aplica um novo efeito gray
        sortear_efeito_gray(&imgray, history_gray);
        break;
    case 2:
        // Undo the last gray effect
        // Desfaz o último efeito gray
        aplicar_efeito_gray(&imgray, 7, history_gray);
        break;
    case 3:
        // Redo the last gray effect
        // Refaz o último efeito gray
        aplicar_efeito_gray(&imgray, 8, history_gray);
        break;
    case 4:
        // No action (exit)
        // Nenhuma ação (sair)
        break;
    default:
        // Print an invalid option message
        // Imprime uma mensagem de opção inválida
        printf("Opção inválida\n");
        break;
    }
}
void on_effect_selected_rgb(GtkWidget *widget, gpointer data)
{
    int effect = GPOINTER_TO_INT(data);

    // Apply the selected RGB effect
    // Aplica o efeito RGB selecionado
    aplicar_efeito_rgb(&imrgb, effect, history_rgb);
}

void on_effect_selected_gray(GtkWidget *widget, gpointer data)
{
    int effect = GPOINTER_TO_INT(data);

    // Apply the selected gray effect
    // Aplica o efeito gray selecionado
    aplicar_efeito_gray(&imgray, effect, history_gray);
}

void update_status(const char *message)
{
    // Update the status label with the provided message
    // Atualiza o rótulo de status com a mensagem fornecida
    gtk_label_set_text(GTK_LABEL(label_status), message);
}