#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printImageGray(const ImageGray *img) {
    int i, j;
    for (i = 0; i < img->dim.altura; i++) {
        for (j = 0; j < img->dim.largura; j++) {
            printf("%d ", img->pixels[i * img->dim.largura + j].value);
        }
        printf("\n");
    }
}

void flip_horizontal_rgb(ImageRGB *image, ImageRGB *flipped_image) {
    if (image == NULL || image->pixels == NULL || flipped_image == NULL) {
        fprintf(stderr, "Erro: Uma das imagens é NULL.\n");
        return;
    }

    int width = image->dim.largura;
    int height = image->dim.altura;

    flipped_image->dim.largura = width;
    flipped_image->dim.altura = height;

    flipped_image->pixels = (PixelRGB *)calloc(sizeof(PixelRGB), height * width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            flipped_image->pixels[y * width + x] = image->pixels[y * width + (width - x - 1)];
        }
    }
}

// ######################################################################################
int mediana(int *valores, int tamanho) {
    qsort(valores, tamanho, sizeof(int), comparar);
    if (tamanho % 2 == 0) {
        return (valores[tamanho / 2 - 1] + valores[tamanho / 2]) / 2;
    } else {
        return valores[tamanho / 2];
    }
}

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


ImageGray *median_blur_gray(const ImageGray *image, int kernel_size)
{
    if (image == NULL || image->pixels == NULL)
    {
        fprintf(stderr, "Erro: A imagem é nula.\n");
        return NULL;
    }

    int width = image->dim.largura;
    int height = image->dim.altura;

    ImageGray *blurred_image = create_image_gray(width, height);
    if (blurred_image == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para a imagem desfocada em escala de cinza.\n");
        exit(1);
    }

    int half_kernel = kernel_size / 2;
    int window_size = kernel_size * kernel_size;
    int *window = (int *)malloc(window_size * sizeof(int));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int count = 0;
            for (int dy = -half_kernel; dy <= half_kernel; dy++)
            {
                for (int dx = -half_kernel; dx <= half_kernel; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        window[count++] = image->pixels[ny * width + nx].value;
                    }
                }
            }
            blurred_image->pixels[y * width + x].value = mediana(window, count);
        }
    }

    free(window);
    return blurred_image;
}

ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size)
{
    int altura = image->dim.altura;
    int largura = image->dim.largura;
    ImageRGB *result = create_image_rgb(largura, altura);

    int half_kernel = kernel_size / 2;
    int window_size = kernel_size * kernel_size;
    int *red_values = (int *)malloc(window_size * sizeof(int));
    int *green_values = (int *)malloc(window_size * sizeof(int));
    int *blue_values = (int *)malloc(window_size * sizeof(int));

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            int count = 0;

            for (int ki = -half_kernel; ki <= half_kernel; ki++)
            {
                for (int kj = -half_kernel; kj <= half_kernel; kj++)
                {
                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni >= 0 && ni < altura && nj >= 0 && nj < largura)
                    {
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

    free(red_values);
    free(green_values);
    free(blue_values);

    return result;
}


void calcular_histograma_rgb(const ImageRGB *img, int *hist_red, int *hist_green, int *hist_blue, int num_bins)
{
    int bin_size = 256 / num_bins;

    for (int i = 0; i < num_bins; i++)
    {
        hist_red[i] = 0;
        hist_green[i] = 0;
        hist_blue[i] = 0;
    }

    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            int red_bin = img->pixels[i * img->dim.largura + j].red / bin_size;
            int green_bin = img->pixels[i * img->dim.largura + j].green / bin_size;
            int blue_bin = img->pixels[i * img->dim.largura + j].blue / bin_size;

            hist_red[red_bin]++;
            hist_green[green_bin]++;
            hist_blue[blue_bin]++;
        }
    }
}

ImageRGB *clahe_rgb(ImageRGB *img, int num_bins, int limite)
{
    int hist_red[256] = {0};
    int hist_green[256] = {0};
    int hist_blue[256] = {0};

    calcular_histograma_rgb(img, hist_red, hist_green, hist_blue, num_bins);

    int total_pixels = img->dim.altura * img->dim.largura;

    int cdf_red[256] = {0};
    int cdf_green[256] = {0};
    int cdf_blue[256] = {0};

    cdf_red[0] = hist_red[0];
    cdf_green[0] = hist_green[0];
    cdf_blue[0] = hist_blue[0];

    for (int i = 1; i < 256; i++)
    {
        cdf_red[i] = cdf_red[i - 1] + hist_red[i];
        cdf_green[i] = cdf_green[i - 1] + hist_green[i];
        cdf_blue[i] = cdf_blue[i - 1] + hist_blue[i];
    }

    int min_cdf_red = cdf_red[0];
    int min_cdf_green = cdf_green[0];
    int min_cdf_blue = cdf_blue[0];

    for (int i = 1; i < 256; i++)
    {
        if (cdf_red[i] != 0 && cdf_red[i] < min_cdf_red)
            min_cdf_red = cdf_red[i];
        if (cdf_green[i] != 0 && cdf_green[i] < min_cdf_green)
            min_cdf_green = cdf_green[i];
        if (cdf_blue[i] != 0 && cdf_blue[i] < min_cdf_blue)
            min_cdf_blue = cdf_blue[i];
    }

    ImageRGB *equalized_img = create_image_rgb(img->dim.largura, img->dim.altura);

    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            int pixel_pos = i * img->dim.largura + j;
            int red_value = img->pixels[pixel_pos].red;
            int green_value = img->pixels[pixel_pos].green;
            int blue_value = img->pixels[pixel_pos].blue;

            equalized_img->pixels[pixel_pos].red = (cdf_red[red_value] - min_cdf_red) * 255 / (total_pixels - min_cdf_red);
            equalized_img->pixels[pixel_pos].green = (cdf_green[green_value] - min_cdf_green) * 255 / (total_pixels - min_cdf_green);
            equalized_img->pixels[pixel_pos].blue = (cdf_blue[blue_value] - min_cdf_blue) * 255 / (total_pixels - min_cdf_blue);
        }
    }

    return equalized_img;
}

void transpose_gray(const ImageGray *image, ImageGray *transposed_image) {
    if (image == NULL || image->pixels == NULL || transposed_image == NULL) {
        fprintf(stderr, "Erro: Alguma das imagens é NULL.\n");
        return;
    }

    int width = image->dim.largura;
    int height = image->dim.altura;

    transposed_image->dim.largura = height; // Transpose width and height
    transposed_image->dim.altura = width;

    alocarGray(height, width, &(transposed_image->pixels));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            transposed_image->pixels[j * height + i].value = image->pixels[i * width + j].value;
        }
    }
}

void transpose_rgb(const ImageRGB *image, ImageRGB *transposed_image) {
    if (image == NULL || image->pixels == NULL || transposed_image == NULL) {
        fprintf(stderr, "Erro: Alguma das imagens é NULL.\n");
        return;
    }

    int width = image->dim.largura;
    int height = image->dim.altura;

    transposed_image->dim.largura = height; // Transpose width and height
    transposed_image->dim.altura = width;

    alocarRGB(height, width, &(transposed_image->pixels));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            transposed_image->pixels[j * height + i].red = image->pixels[i * width + j].red;
            transposed_image->pixels[j * height + i].green = image->pixels[i * width + j].green;
            transposed_image->pixels[j * height + i].blue = image->pixels[i * width + j].blue;
        }
    }
}
