#include "image.h"
#include <stdio.h>
#include <stdlib.h>


void salvar_imagem_arkv(ImageGray *img, FILE *gray_image)
{
    fprintf(gray_image, "%d\n", img->dim.altura);
    fprintf(gray_image, "%d\n", img->dim.largura);

    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int x = 0; x < img->dim.largura; x++)
        {
            fprintf(gray_image, "%d %d %d,", img->pixels[(i * img->dim.largura) + x].value, img->pixels[(i * img->dim.largura) + x].value, img->pixels[(i * img->dim.largura) + x].value);
        }
        fprintf(gray_image, "\n");
    }

    fclose(gray_image);
}

void salvar_imagem_arkv_rgb(ImageRGB *img, FILE *rgb_image)
{
    fprintf(rgb_image, "%d\n", img->dim.altura);
    fprintf(rgb_image, "%d\n", img->dim.largura);

    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int x = 0; x < img->dim.largura; x++)
        {
            fprintf(rgb_image, "%d %d %d,", img->pixels[(i * img->dim.largura) + x].red, img->pixels[(i * img->dim.largura) + x].green, img->pixels[(i * img->dim.largura) + x].blue);
        }
        fprintf(rgb_image, "\n");
    }

    fclose(rgb_image);
}



void alocarGray(int altura, int largura, PixelGray **pixel)
{
    *pixel = (PixelGray *)calloc(sizeof(PixelGray), altura * largura);
}

void alocarRGB(int altura, int largura, PixelRGB **pixel)
{
    *pixel = (PixelRGB *)calloc(sizeof(PixelRGB), altura * largura);
}


// funcão que converte a RBG pra Gray (basicamente a mesma coisa, so muda pra se adequar nas definições da nova lista.h)
ImageGray *converter_para_gray(ImageRGB *img, ImageGray *imgray)
{
    imgray->dim.altura = img->dim.altura;
    imgray->dim.largura = img->dim.largura;

    alocarGray(imgray->dim.altura, imgray->dim.largura, &(imgray->pixels));

    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {

            int gray = (img->pixels[i * img->dim.largura + j].red + img->pixels[i * img->dim.largura + j].green + img->pixels[i * img->dim.largura + j].blue) / 3;

            imgray->pixels[i * img->dim.largura + j].value = gray;
        }
    }
}


// cria a imagemgray, basicamente a mesma coisa tambem 
ImageGray *create_image_gray(int largura, int altura) {
    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image) {
        fprintf(stderr, "Erro ao alocar memoria para imagem em escala de cinza.\n");
        exit(1);
    }
    image->dim.largura = largura;
    image->dim.altura = altura;
    image->pixels = (PixelGray *)malloc(largura * altura * sizeof(PixelGray));
    if (!image->pixels) {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem em escala de cinza.\n");
        free(image);
        exit(1);
    }
    return image;
}
// libera o ponteiro pixels(caso n seja nulo) e libera a memória alocada para a estrutura  
void free_image_gray(ImageGray *image) {
    if (image) {
        if (image->pixels) {
            free(image->pixels);
        }
        free(image);
    }
}

// testando....


ImageRGB *create_image_rgb(int largura, int altura)
{
    ImageRGB *img = calloc(1, sizeof(ImageRGB));
    img->dim.altura = altura;
    img->dim.largura = largura;
    img->pixels = calloc(altura * largura, sizeof(PixelRGB));
    return img;
}

void ler_imagem_arkv(FILE *arq, ImageRGB *img)
{
    fscanf(arq, "%d", &img->dim.altura);
    fscanf(arq, "%d", &img->dim.largura);
    img->pixels = (PixelRGB *)calloc(sizeof(PixelRGB), img->dim.altura * img->dim.largura);
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int x = 0; x < img->dim.largura; x++)
        {
            fscanf(arq, "%d %d %d,", &img->pixels[(i * img->dim.largura) + x].red, &img->pixels[(i * img->dim.largura) + x].green, &img->pixels[(i * img->dim.largura) + x].blue);
        }
    }
    fclose(arq);
}


void free_image_rgb(ImageRGB *image)
{
    free(image->pixels);
    free(image);
}


void flip_vertical_gray(ImageGray *image, ImageGray *flipped_image)
{
    if (image == NULL || image->pixels == NULL || flipped_image == NULL)
    {
        fprintf(stderr, "Erro: Uma das imagens é NULL.\n");
        return;
    }

    int largura = image->dim.largura;
    int altura = image->dim.altura;

    flipped_image->dim.largura = largura;
    flipped_image->dim.altura = altura;

    alocarGray(altura, largura, &(flipped_image->pixels));

    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            flipped_image->pixels[(altura - y - 1) * largura + x] = image->pixels[y * largura + x];
        }
    }
}

void flip_vertical_rgb(ImageRGB *image, ImageRGB *flipped_image)
{
    if (image == NULL || image->pixels == NULL || flipped_image == NULL)
    {
        fprintf(stderr, "Erro: Uma das imagens é NULL.\n");
        return;
    }

    int largura = image->dim.largura;
    int altura = image->dim.altura;

    flipped_image->dim.largura = largura;
    flipped_image->dim.altura = altura;

    flipped_image->pixels = (PixelRGB *)calloc(sizeof(PixelRGB), altura * largura);

    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            flipped_image->pixels[(altura - y - 1) * largura + x] = image->pixels[y * largura + x];
        }
    }
}


void printPixelColor(int lin, int col, ImageRGB *img)
{
    printf("\033[38;2;%d;%d;%dm**\033[0m", img->pixels[lin * img->dim.largura + col].red, img->pixels[lin * img->dim.largura + col].green, img->pixels[lin * img->dim.largura + col].blue);
}

void printImageColor(ImageRGB *img)
{
    for (int i = 0; i < img->dim.altura; i++) {
        for (int j = 0; j < img->dim.largura; j++) {
            printPixelColor(i, j, img);
        }
        printf("\n");
    }
}
