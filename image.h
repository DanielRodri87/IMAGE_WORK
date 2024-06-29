#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct dimensoes {
    int altura, largura;
} Dimensoes;

typedef struct pixelRGB {
    int red, blue, green;
} PixelRGB;

typedef struct pixelGray {
    int value;
} PixelGray;

typedef struct imageGray {
    Dimensoes dim;
    PixelGray *pixels;
} ImageGray;

typedef struct imageRGB {
    Dimensoes dim;
    PixelRGB *pixels;
} ImageRGB;

typedef struct imageHistoryNode {
    ImageRGB *image;
    struct imageHistoryNode *next;
    struct imageHistoryNode *prev;
} ImageHistoryNode;

typedef struct imageHistoryNodeGray {
    ImageGray *image;
    struct imageHistoryNodeGray *next;
    struct imageHistoryNodeGray *prev;
} ImageHistoryNodeGray;

typedef struct imageHistory {
    ImageHistoryNode *current;
} ImageHistory;

typedef struct imageHistoryGray {
    ImageHistoryNodeGray *current;
} ImageHistoryGray;

int comparar(const void *a, const void *b);
void salvar_imagem_arkv(ImageGray *img, FILE *gray_image); 
void salvar_imagem_arkv_rgb(ImageRGB *img, FILE *rgb_image);
void alocarGray(int altura, int largura, PixelGray **pixel); 
void alocarRGB(int altura, int largura, PixelRGB **pixel); 
ImageGray *create_image_gray(int largura, int altura); 
ImageGray *converter_para_gray(ImageRGB *img, ImageGray *imgray); 
void free_image_gray(ImageGray *image); 
ImageRGB *create_image_rgb(int largura, int altura);
void free_image_rgb(ImageRGB *image); 
void flip_vertical_gray(ImageGray *image, ImageGray *flipped_image); 
void flip_horizontal_gray(ImageGray *image, ImageGray *flipped_image);
void transpose_gray(const ImageGray *image, ImageGray *transposed_image);
void flip_vertical_rgb(ImageRGB *image, ImageRGB *flipped_image); 
void flip_horizontal_rgb(ImageRGB *image, ImageRGB *flipped_image); 
void transpose_rgb(const ImageRGB *image, ImageRGB *transposed_image);
ImageGray *clahe_gray(ImageGray *img, int num_bins, int limite); 
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size); 
ImageRGB *clahe_rgb(ImageRGB *img, int num_bins, int limite);
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);
void printPixelColor(int lin, int col, ImageRGB *img);
void printImageColor(ImageRGB *img); 
void ler_imagem_arkv(FILE *arq, ImageRGB *img);
void add_image_to_history_rgb(ImageHistory *history, ImageRGB *image);
void add_image_to_history_gray(ImageHistoryGray *history, ImageGray *image);
void desfazer_rgb(ImageHistory *history, ImageRGB *imrgb);
void refazer_rgb(ImageHistory *history, ImageRGB *imrgb);
void desfazer_gray(ImageHistoryGray *history, ImageGray *imgray);
void refazer_gray(ImageHistoryGray *history, ImageGray *imgray);
void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history);
void sortear_efeito_rgb(ImageRGB *imrgb, ImageHistory *history);
void sortear_efeito_gray(ImageGray *imgray, ImageHistoryGray *history);
ImageHistory *create_image_history();
ImageHistoryGray *create_image_history_gray();

#endif 