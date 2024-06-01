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

int comparar(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

// ######################################################################################

ImageGray *median_blur_gray(const ImageGray *image, int kernel_size) {
    if (image == NULL || image->pixels == NULL) {
        fprintf(stderr, "Erro: A imagem é nula.\n");
        return NULL;
    }

    int width = image->dim.largura;
    int height = image->dim.altura;

    ImageGray *blurred_image = create_image_gray(width, height);
    if (blurred_image == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a imagem desfocada em escala de cinza.\n");
        exit(1);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0;
            int count = 0;
            for (int dy = -kernel_size / 2; dy <= kernel_size / 2; dy++) {
                for (int dx = -kernel_size / 2; dx <= kernel_size / 2; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        sum += image->pixels[ny * width + nx].value;
                        count++;
                    }
                }
            }
            int median = sum / count;
            blurred_image->pixels[y * width + x].value = median;
        }
    }

    return blurred_image;
}

// Função para calcular a mediana de um array de inteiros
int mediana(int *valores, int tamanho) {
    qsort(valores, tamanho, sizeof(int), comparar);
    if (tamanho % 2 == 0) {
        return (valores[tamanho / 2 - 1] + valores[tamanho / 2]) / 2;
    } else {
        return valores[tamanho / 2];
    }
}

// Função para aplicar o filtro de mediana em uma imagem RGB
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size) {
    int altura = image->dim.altura;
    int largura = image->dim.largura;
    ImageRGB *result = (ImageRGB *)malloc(sizeof(ImageRGB));
    result->dim.altura = altura;
    result->dim.largura = largura;
    alocarRGB(altura, largura, &(result->pixels));

    int half_kernel = kernel_size / 2;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int red_values[kernel_size * kernel_size];
            int green_values[kernel_size * kernel_size];
            int blue_values[kernel_size * kernel_size];
            int count = 0;

            for (int ki = -half_kernel; ki <= half_kernel; ki++) {
                for (int kj = -half_kernel; kj <= half_kernel; kj++) {
                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni >= 0 && ni < altura && nj >= 0 && nj < largura) {
                        red_values[count] = image->pixels[ni * largura + nj].red;
                        green_values[count] = image->pixels[ni * largura + nj].green;
                        blue_values[count] = image->pixels[ni * largura + nj].blue;
                        count++;
                    }
                }
            }

            result->pixels[i * largura + j].red = mediana(red_values, count);
            result->pixels[i * largura + j].green = mediana(green_values, count);
            result->pixels[i * largura + j].blue = mediana(blue_values, count);
        }
    }

    return result;
}