#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar as dimensões de uma imagem
// Structure to store the dimensions of an image
typedef struct dimensoes {
    int altura, largura;
} Dimensoes;

// Estrutura para armazenar um pixel em uma imagem RGB
// Structure to store a pixel in an RGB image
typedef struct pixelRGB {
    int red, blue, green;
} PixelRGB;

// Estrutura para armazenar um pixel em uma imagem em tons de cinza
// Structure to store a pixel in a grayscale image
typedef struct pixelGray {
    int value;
} PixelGray;

// Estrutura para armazenar uma imagem em tons de cinza
// Structure to store a grayscale image
typedef struct imageGray {
    Dimensoes dim;
    PixelGray *pixels;
} ImageGray;

// Estrutura para armazenar uma imagem RGB
// Structure to store an RGB image
typedef struct imageRGB {
    Dimensoes dim;
    PixelRGB *pixels;
} ImageRGB;

// Estrutura para um nó de histórico de imagem RGB
// Structure for an RGB image history node
typedef struct imageHistoryNode {
    ImageRGB *image;
    struct imageHistoryNode *next;
    struct imageHistoryNode *prev;
} ImageHistoryNode;

// Estrutura para um nó de histórico de imagem em tons de cinza
// Structure for a grayscale image history node
typedef struct imageHistoryNodeGray {
    ImageGray *image;
    struct imageHistoryNodeGray *next;
    struct imageHistoryNodeGray *prev;
} ImageHistoryNodeGray;

// Estrutura para o histórico de imagens RGB
// Structure for RGB image history
typedef struct imageHistory {
    ImageHistoryNode *current;
} ImageHistory;

// Estrutura para o histórico de imagens em tons de cinza
// Structure for grayscale image history
typedef struct imageHistoryGray {
    ImageHistoryNodeGray *current;
} ImageHistoryGray;

// Função para comparar dois valores
// Function to compare two values
int comparar(const void *a, const void *b);

// Função para salvar uma imagem em tons de cinza em um arquivo
// Function to save a grayscale image to a file
void salvar_imagem_arkv(ImageGray *img, FILE *gray_image);

// Função para salvar uma imagem RGB em um arquivo
// Function to save an RGB image to a file
void salvar_imagem_arkv_rgb(ImageRGB *img, FILE *rgb_image);

// Função para alocar memória para pixels em tons de cinza
// Function to allocate memory for grayscale pixels
void alocarGray(int altura, int largura, PixelGray **pixel);

// Função para alocar memória para pixels RGB
// Function to allocate memory for RGB pixels
void alocarRGB(int altura, int largura, PixelRGB **pixel);

// Função para criar uma nova imagem em tons de cinza
// Function to create a new grayscale image
ImageGray *create_image_gray(int largura, int altura);

// Função para converter uma imagem RGB para tons de cinza
// Function to convert an RGB image to grayscale
ImageGray *converter_para_gray(ImageRGB *img, ImageGray *imgray);

// Função para liberar a memória de uma imagem em tons de cinza
// Function to free the memory of a grayscale image
void free_image_gray(ImageGray *image);

// Função para criar uma nova imagem RGB
// Function to create a new RGB image
ImageRGB *create_image_rgb(int largura, int altura);

// Função para liberar a memória de uma imagem RGB
// Function to free the memory of an RGB image
void free_image_rgb(ImageRGB *image);

// Função para inverter verticalmente uma imagem em tons de cinza
// Function to vertically flip a grayscale image
void flip_vertical_gray(ImageGray *image, ImageGray *flipped_image);

// Função para inverter horizontalmente uma imagem em tons de cinza
// Function to horizontally flip a grayscale image
void flip_horizontal_gray(ImageGray *image, ImageGray *flipped_image);

// Função para transpor uma imagem em tons de cinza
// Function to transpose a grayscale image
void transpose_gray(const ImageGray *image, ImageGray *transposed_image);

// Função para inverter verticalmente uma imagem RGB
// Function to vertically flip an RGB image
void flip_vertical_rgb(ImageRGB *image, ImageRGB *flipped_image);

// Função para inverter horizontalmente uma imagem RGB
// Function to horizontally flip an RGB image
void flip_horizontal_rgb(ImageRGB *image, ImageRGB *flipped_image);

// Função para transpor uma imagem RGB
// Function to transpose an RGB image
void transpose_rgb(const ImageRGB *image, ImageRGB *transposed_image);

// Função para aplicar CLAHE a uma imagem em tons de cinza
// Function to apply CLAHE to a grayscale image
ImageGray *clahe_gray(ImageGray *img, int num_bins, int limite);

// Função para aplicar desfoque mediano a uma imagem em tons de cinza
// Function to apply median blur to a grayscale image
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);

// Função para aplicar CLAHE a uma imagem RGB
// Function to apply CLAHE to an RGB image
ImageRGB *clahe_rgb(ImageRGB *img, int num_bins, int limite);

// Função para aplicar desfoque mediano a uma imagem RGB
// Function to apply median blur to an RGB image
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);

// Função para imprimir a cor de um pixel específico
// Function to print the color of a specific pixel
void printPixelColor(int lin, int col, ImageRGB *img);

// Função para imprimir as cores de uma imagem
// Function to print the colors of an image
void printImageColor(ImageRGB *img);

// Função para ler uma imagem de um arquivo
// Function to read an image from a file
void ler_imagem_arkv(FILE *arq, ImageRGB *img);

// Função para adicionar uma imagem RGB ao histórico
// Function to add an RGB image to the history
void add_image_to_history_rgb(ImageHistory *history, ImageRGB *image);

// Função para adicionar uma imagem em tons de cinza ao histórico
// Function to add a grayscale image to the history
void add_image_to_history_gray(ImageHistoryGray *history, ImageGray *image);

// Função para desfazer a última alteração em uma imagem RGB
// Function to undo the last change in an RGB image
void desfazer_rgb(ImageHistory *history, ImageRGB *imrgb);

// Função para refazer a última alteração em uma imagem RGB
// Function to redo the last change in an RGB image
void refazer_rgb(ImageHistory *history, ImageRGB *imrgb);

// Função para desfazer a última alteração em uma imagem em tons de cinza
// Function to undo the last change in a grayscale image
void desfazer_gray(ImageHistoryGray *history, ImageGray *imgray);

// Função para refazer a última alteração em uma imagem em tons de cinza
// Function to redo the last change in a grayscale image
void refazer_gray(ImageHistoryGray *history, ImageGray *imgray);

// Função para aplicar um efeito a uma imagem RGB
// Function to apply an effect to an RGB image
void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history);

// Função para sortear e aplicar um efeito a uma imagem RGB
// Function to randomly select and apply an effect to an RGB image
void sortear_efeito_rgb(ImageRGB *imrgb, ImageHistory *history);

// Função para sortear e aplicar um efeito a uma imagem em tons de cinza
// Function to randomly select and apply an effect to a grayscale image
void sortear_efeito_gray(ImageGray *imgray, ImageHistoryGray *history);

// Função para criar um histórico de imagens RGB
// Function to create an RGB image history
ImageHistory *create_image_history();

// Função para criar um histórico de imagens em tons de cinza
// Function to create a grayscale image history
ImageHistoryGray *create_image_history_gray();

#endif
