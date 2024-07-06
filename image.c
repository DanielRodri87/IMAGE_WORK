#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Essa função é responsável por ler a imagem em escala de cinza, ou seja, a imagem que contém apenas um canal de cor.
// This function is responsible for reading the grayscale image, that is, the image that contains only one color channel.
void salvar_imagem_arkv(ImageGray *img, FILE *gray_image)
{
    // O padrão dos arquivos .txt contém duas linhas iniciais, que contém a altura e largura da imagem, e aqui estamos escrevendo essas duas linhas.
    // The standard .txt files contain two initial lines, which contain the height and width of the image, and here we are writing these two lines.
    fprintf(gray_image, "%d\n", img->dim.altura);
    fprintf(gray_image, "%d\n", img->dim.largura);


    // Esse loop é responsável por percorrer a matriz de pixels da imagem e escrever o valor de cada pixel no arquivo .txt. Cada píxel é composto por três valores: Red (R), Green (G) e Blue (B).
    // This loop is responsible for traversing the image's pixel matrix and writing the value of each pixel to the .txt file. Each pixel is composed of three values: Red (R), Green (G) and Blue (B).
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int x = 0; x < img->dim.largura; x++)
        {
            // Aqui estamos escrevendo o valor do pixel no arquivo .txt.
            // Here we are writing the pixel value to the .txt file.
            fprintf(gray_image, "%d %d %d,", img->pixels[(i * img->dim.largura) + x].value, img->pixels[(i * img->dim.largura) + x].value, img->pixels[(i * img->dim.largura) + x].value);
        }
        // Ao terminar de escrever os valores de todos os pixels de uma linha, pulamos uma linha.
        // After finishing writing the values of all pixels in a row, we skip a line.
        fprintf(gray_image, "\n");
    }

    // Por fim, fechamos o arquivo.
    // Finally, we close the file.
    fclose(gray_image);
}

// De forma análoga à função anterior, essa função é responsável por salvar a imagem colorida. Irei poupar os comentários, já que é a mesma coisa, porém recebendo uma imagem colorida.
// Analogously to the previous function, this function is responsible for saving the colored image. I will spare the comments, since it is the same thing, but receiving a colored image.
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

// Essa função irá alocar memoria para a matriz de pixels da imagem em escala de cinza
// This function will allocate memory for the grayscale image pixel matrix
void alocarGray(int altura, int largura, PixelGray **pixel)
{
    // Por meio do cálculo entre a altura e largura da imagem, é possível saber necessariamente quantos pixels a imagem possui, e assim, alocar a memória necessária.
    // Through the calculation between the height and width of the image, it is possible to know necessarily how many pixels the image has, and thus, allocate the necessary memory.
    *pixel = (PixelGray *)calloc(sizeof(PixelGray), altura * largura);
}

// Essa função irá alocar memoria para a matriz de pixels da imagem colorida
// This function will allocate memory for the colored image pixel matrix
void alocarRGB(int altura, int largura, PixelRGB **pixel)
{
    // Por meio do cálculo entre a altura e largura da imagem, é possível saber necessariamente quantos pixels a imagem possui, e assim, alocar a memória necessária.
    // Through the calculation between the height and width of the image, it is possible to know necessarily how many pixels the image has, and thus, allocate the necessary memory.
    *pixel = (PixelRGB *)calloc(sizeof(PixelRGB), altura * largura);
}

// Essa função recebe como parâmetro inicial uma imagem em escala de cinza e uma imagem colorida, e a função irá converter a imagem colorida para escala de cinza por meio da média dos valores de R, G e B.
// This function receives as initial parameter a grayscale image and a colored image, and the function will convert the colored image to grayscale by averaging the values of R, G and B.
ImageGray *converter_para_gray(ImageRGB *img, ImageGray *imgray)
{
    // A imagem em escala de cinza irá possuir a mesma altura e largura da imagem colorida. Para isso, ela recebe os valores de altura e largura da imagem colorida.
    // The grayscale image will have the same height and width as the colored image. For this, it receives the height and width values of the colored image.
    imgray->dim.altura = img->dim.altura;
    imgray->dim.largura = img->dim.largura;

    // Alocamos a memória necessária para a matriz de pixels da imagem em escala de cinza.
    // We allocate the necessary memory for the grayscale image pixel matrix.
    alocarGray(imgray->dim.altura, imgray->dim.largura, &(imgray->pixels));

    // Esses laços são responsáveis por percorrer a matriz de pixels da imagem colorida e calcular a média dos valores de R, G e B, e atribuir esse valor ao pixel da imagem em escala de cinza.
    // These loops are responsible for traversing the pixel matrix of the colored image and calculating the average of the values of R, G and B, and assigning this value to the pixel of the grayscale image.
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            // Calculamos a média dos valores de R, G e B, (Red+Green+Blue)/3.
            // We calculate the average of the values of R, G and B.
            int gray = (img->pixels[i * img->dim.largura + j].red + img->pixels[i * img->dim.largura + j].green + img->pixels[i * img->dim.largura + j].blue) / 3;

            // Atribuímos o valor da média ao value do pixel da imagem em escala de cinza.
            // We assign the average value to the value of the pixel of the grayscale image.
            imgray->pixels[i * img->dim.largura + j].value = gray;
        }
    }
}

// A função irá receber dois parâmetros iniciais, a largura e altura da imagem
// The function will receive two initial parameters, the width and height of the image
ImageGray *create_image_gray(int largura, int altura)
{
    // Alocamos a memória necessária para a estrutura da imagem em escala de cinza.
    // We allocate the necessary memory for the grayscale image structure.
    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));

    // Caso a memória não seja alocada, a função irá imprimir uma mensagem de erro e encerrar o programa.
    // If memory is not allocated, the function will print an error message and terminate the program.
    if (!image)
    {
        fprintf(stderr, "Erro ao alocar memoria para imagem em escala de cinza.\n");
        exit(1);
    }

    // É definido o tamanho das dimensões a partir dos valores de largura e altura que foram passados como parâmetro.
    // The size of the dimensions is defined from the width and height values that were passed as a parameter.
    image->dim.largura = largura;
    image->dim.altura = altura;

    // Alocamos a memória necessária para a matriz de pixels da imagem em escala de cinza.
    // We allocate the necessary memory for the grayscale image pixel matrix.
    image->pixels = (PixelGray *)malloc(largura * altura * sizeof(PixelGray));

    // Caso a memória não seja alocada, a função irá imprimir uma mensagem de erro e encerrar o programa.
    // If memory is not allocated, the function will print an error message and terminate the program.
    if (!image->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem em escala de cinza.\n");
        free(image);
        exit(1);
    }

    // Retornamos a imagem em escala de cinza.
    // We return the grayscale image.
    return image;
}


// Aqui é feito o mesmo processo da função anterior, porém para a imagem colorida
// Here the same process as the previous function is done, but for the colored image
ImageRGB *create_image_rgb(int largura, int altura)
{
    ImageRGB *img = calloc(1, sizeof(ImageRGB));
    if (!img)
    {
        fprintf(stderr, "Erro ao alocar memoria para imagem colorida.\n");
        exit(1);
    }

    img->dim.altura = altura;
    img->dim.largura = largura;

    img->pixels = calloc(altura * largura, sizeof(PixelRGB));

    if (!img->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem colorida.\n");
        free(img);
        exit(1);
    }
    return img;
}

// Essa função recebe dois parâmetros. arq: é um ponteiro para o caminho do arquivo e a img: é um ponteiro para a estrutura de imagem colorida
// This function receives two parameters. arq: is a pointer to the file path and img: is a pointer to the colored image structure
void ler_imagem_arkv(FILE *arq, ImageRGB *img)
{
    // Esses dois fscanf são responsáveis por ler a altura e largura da imagem que estão no arquivo .txt.
    // These two fscanf are responsible for reading the height and width of the image that are in the .txt file.
    fscanf(arq, "%d", &img->dim.altura);
    fscanf(arq, "%d", &img->dim.largura);

    // Aloco a memória necessária para a matriz de pixels da imagem colorida.
    // I allocate the necessary memory for the pixel matrix of the colored image.
    img->pixels = (PixelRGB *)calloc(sizeof(PixelRGB), img->dim.altura * img->dim.largura);

    // Os dois laços são responsáveis por percorrer a matriz de pixels da imagem
    // The two loops are responsible for traversing the image's pixel matrix
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int x = 0; x < img->dim.largura; x++)
        {
            // Esse fscanf é responsável por ler os valores de R, G e B de cada pixel da imagem.
            // This fscanf is responsible for reading the values of R, G and B of each pixel of the image.
            fscanf(arq, "%d %d %d,", &img->pixels[(i * img->dim.largura) + x].red, &img->pixels[(i * img->dim.largura) + x].green, &img->pixels[(i * img->dim.largura) + x].blue);
        }
    }
    // Por fim, fechamos o arquivo.
    // Finally, we close the file.
    fclose(arq);
}


// Funções para liberar a memória alocada para as imagens
// Functions to free the allocated memory for the images
void free_image_rgb(ImageRGB *image)
{
    free(image->pixels);
    free(image);
}
void free_image_gray(ImageGray *image)
{
    free(image->pixels);
    free(image);
}

// Esta função inverte uma imagem em escala de cinza verticalmente e armazena o resultado em outra estrutura de imagem. Recebe dois parâmetros ImageGray
// This function inverts a grayscale image vertically and stores the result in another image structure. Receives two parameters ImageGray
void flip_vertical_gray(ImageGray *image, ImageGray *flipped_image)
{
    // Verifica se a imagem é nula, se a matriz de pixels é nula ou se a imagem invertida é nula.
    // Checks if the image is null, if the pixel matrix is null or if the inverted image is null.
    if (image == NULL || image->pixels == NULL || flipped_image == NULL)
    {
        fprintf(stderr, "Erro: Uma das imagens é NULL.\n");
        return;
    }

    // Copio a largura e altura da imagem original para a imagem invertida.
    // I copy the width and height of the original image to the inverted image.
    int largura = image->dim.largura;
    int altura = image->dim.altura;
    flipped_image->dim.largura = largura;
    flipped_image->dim.altura = altura;

    // Aloco a memória necessária para a matriz de pixels da imagem invertida.
    // I allocate the necessary memory for the pixel matrix of the inverted image.
    alocarGray(altura, largura, &(flipped_image->pixels));

    // Percorro toda a matriz de pixels da imagem original
    // I go through the entire pixel matrix of the original image
    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            /*
                Vamos revisar o exemplo fornecido para uma matriz 3x3 e esclarecer os cálculos. A função flip_vertical_gray deve inverter a posição vertical
                dos pixels, trocando a primeira linha pela última, a segunda linha pela penúltima, e assim por diante. Vamos analisar os cálculos
                detalhadamente:

                [0,0] [0,1] [0,2]       [2,0] [2,1] [2,2]
                [1,0] [1,1] [1,2]  =>   [1,0] [1,1] [1,2]
                [2,0] [2,1] [2,2]       [0,0] [0,1] [0,2]  

                Vamos pegar o primeiro valor da matriz 3x3. O valor é [0,0] e quando invertido será [2,0]
                3 - 0 - 1 = 2
                3 * 0 + 0 = 0. Então a posição de [0,0] na matriz 3x3 é [2,0]

            */

            /*
                Let's review the example provided for a 3x3 matrix and clarify the calculations. The flip_vertical_gray function should invert the vertical position
                of the pixels, swapping the first row for the last, the second row for the penultimate, and so on. Let's analyze the calculations
                in detail:

                [0,0] [0,1] [0,2]       [2,0] [2,1] [2,2]
                [1,0] [1,1] [1,2]  =>   [1,0] [1,1] [1,2]
                [2,0] [2,1] [2,2]       [0,0] [0,1] [0,2]  

                Let's take the first value of the 3x3 matrix. The value is [0,0] and when inverted it will be [2,0]
                3 - 0 - 1 = 2
                3 * 0 + 0 = 0. So the position of [0,0] in the 3x3 matrix is [2,0]
            */
            flipped_image->pixels[(altura - y - 1) * largura + x] = image->pixels[y * largura + x];
        }
    }
}

// Função para inverter uma imagem em escala colorida. A ideia e o funcionamento é mesmo, o que vai mudar é que será para valores coloridos
// Function to invert a image colored. The idea and operation are the same, what will change is that it will be for colored values
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

// Essa função está desabilitada. Porque atualmente o programa printa imagem RGB em um arquivo png e o exibe. Mas antes, ele printava no terminal por meio de pixels coloridos
// This function is disabled. Because currently the program prints RGB image. But before, it printed in the terminal through colored pixels
void printPixelColor(int lin, int col, ImageRGB *img)
{
    printf("\033[38;2;%d;%d;%dm**\033[0m", img->pixels[lin * img->dim.largura + col].red, img->pixels[lin * img->dim.largura + col].green, img->pixels[lin * img->dim.largura + col].blue);
}

// Essas funções estão desabilitadas. Porque atualmente o programa printa imagem RGB. Mas antes, ele printava no terminal por meio de pixels coloridos
// These functions are disabled. Because currently the program prints RGB image. But before, it printed in the terminal through colored pixels
void printImageColor(ImageRGB *img)
{
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            printPixelColor(i, j, img);
        }
        printf("\n");
    }
}
void printImageGray(const ImageGray *img) 
{
    int i, j;
    for (i = 0; i < img->dim.altura; i++)
    {
        for (j = 0; j < img->dim.largura; j++)
        {
            printf("%d ", img->pixels[i * img->dim.largura + j].value);
        }
        printf("\n");
    }
}


// Função para inverter uma imagem colorida
// Function to invert a colored image
void flip_horizontal_rgb(ImageRGB *image, ImageRGB *flipped_image)
{
    // Verifica se a imagem é nula, se a matriz de pixels é nula ou se a imagem invertida é nula.
    // Checks if the image is null, if the pixel matrix is null or if the inverted image is null.
    if (image == NULL || image->pixels == NULL || flipped_image == NULL)
    {
        fprintf(stderr, "Erro: Uma das imagens é NULL.\n");
        return;
    }

    // Copio a largura e altura da imagem original para a imagem invertida.
    // I copy the width and height of the original image to the inverted image.
    int width = image->dim.largura;
    int height = image->dim.altura;
    flipped_image->dim.largura = width;
    flipped_image->dim.altura = height;

    // Aloco a memória necessária para a matriz de pixels da imagem invertida.
    // I allocate the necessary memory for the pixel matrix of the inverted image.
    flipped_image->pixels = (PixelRGB *)calloc(sizeof(PixelRGB), height * width);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            /*
            Da das matrizes original e horizontalmente invertida:
                
                [0,0] [0,1] [0,2]       [0,2] [0,1] [0,0]
                [1,0] [1,1] [1,2]  =>   [1,2] [1,1] [1,0]
                [2,0] [2,1] [2,2]       [2,2] [2,1] [2,0]

            Peguemos o ponto [0,0] que terá a posição [0,2] na matriz invertida.
            Calculemos:
            3 * 0 + 0 = 0 | 3 - 0 - 1 = 2, logo [0,0] -> [0,2]
            */

            /*
            From the original and horizontally inverted matrices:
                
                [0,0] [0,1] [0,2]       [0,2] [0,1] [0,0]
                [1,0] [1,1] [1,2]  =>   [1,2] [1,1] [1,0]
                [2,0] [2,1] [2,2]       [2,2] [2,1] [2,0]
            
            Let's take the point [0,0] which will have the position [0,2] in the inverted matrix.
            Let's calculate:
            3 * 0 + 0 = 0 | 3 - 0 - 1 = 2, so [0,0] -> [0,2]
            */
            flipped_image->pixels[y * width + x] = image->pixels[y * width + (width - x - 1)];
        }
    }
}
// É feita a mesma coisa da função anterior, porém para a imagem em escala de cinza
// The same thing is done as the previous function, but for the grayscale image
void flip_horizontal_gray(ImageGray *image, ImageGray *flipped_image)
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
            flipped_image->pixels[y * largura + (largura - x - 1)] = image->pixels[y * largura + x];
        }
    }
}


// Calculo da mediana de um vetor de inteiros
int mediana(int *valores, int tamanho)
{
    // Para fazer o cálculo da mediana, é necessário ordenar o vetor de inteiros.
    // To calculate the median, it is necessary to sort the integer array.
    qsort(valores, tamanho, sizeof(int), comparar);
    // Se o tamanho do vetor for par, a mediana é a média dos dois valores centrais.
    // If the size of the vector is even, the median is the average of the two central values.
    if (tamanho % 2 == 0)
    {
        return (valores[tamanho / 2 - 1] + valores[tamanho / 2]) / 2;
    }
    // Se não, a mediana é o valor central.
    // If not, the median is the central value.
    else
    {
        return valores[tamanho / 2];
    }
}

// Função para comparar dois inteiros usada pela qsort
// Function to compare two integers used by qsort
int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Calculo da mediana de um vetor de inteiros
// Calculation of the median of an integer array
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size)
{

    if (image == NULL || image->pixels == NULL)
    {
        fprintf(stderr, "Erro: A imagem é nula.\n");
        return NULL;
    }

    // Copio a largura e altura da imagem original para a imagem desfocada.
    // I copy the width and height of the original image to the blurred image.
    int width = image->dim.largura;
    int height = image->dim.altura;

    // Aloco a memória necessária para a matriz de pixels da imagem desfocada em escala de cinza.
    // I allocate the necessary memory for the pixel matrix of the blurred grayscale image.
    ImageGray *blurred_image = create_image_gray(width, height);
    if (blurred_image == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para a imagem desfocada em escala de cinza.\n");
        exit(1);
    }

    // Calculo o ponto central do kernel
    // Calculate the central point of the kernel
    int half_kernel = kernel_size / 2;
    // Calculo o tamanho da janela
    // Calculate the window size
    int window_size = kernel_size * kernel_size;
    // Aloco a memória necessária para a janela
    // I allocate the necessary memory for the window
    int *window = (int *)malloc(window_size * sizeof(int));

    // A sequencia de laços é responsável por percorrer a matriz de pixels da imagem e calcular a mediana dos valores dos pixels vizinhos.
    // The sequence of loops is responsible for traversing the image's pixel matrix and calculating the median of the values of neighboring pixels.
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int count = 0;
            // A sequencia de laços é responsável por percorrer a janela do kernel e armazenar os valores dos pixels vizinhos.
            // The sequence of loops is responsible for traversing the kernel window and storing the values of neighboring pixels.
            for (int dy = -half_kernel; dy <= half_kernel; dy++)
            {
                for (int dx = -half_kernel; dx <= half_kernel; dx++)
                {
                    // Para cada deslocamento (dx, dy), calculamos as coordenadas nx e ny, que representam a posição do pixel na janela do kernel ao redor do pixel central (x, y).
                    // To each offset (dx, dy), we calculate the coordinates nx and ny, which represent the position of the pixel in the kernel window around the central pixel (x, y).
                    int nx = x + dx;
                    int ny = y + dy;
                    // Verificamos se as coordenadas nx e ny estão dentro dos limites da imagem.
                    // We check if the coordinates nx and ny are within the limits of the image.
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        window[count++] = image->pixels[ny * width + nx].value;
                    }
                }
            }
            /*
                Após coletar todos os valores dos pixels na janela do kernel, a função mediana é chamada para calcular a mediana desses
                valores. O resultado é atribuído ao pixel correspondente na imagem desfocada blurred_image.
            */
            /*
                After collecting all the pixel values in the kernel window, the median function is called to calculate the median of these
                values. The result is assigned to the corresponding pixel in the blurred image blurred_image.
            */
            blurred_image->pixels[y * width + x].value = mediana(window, count);
        }
    }

    free(window);
    return blurred_image;
}

//  Os passos são semelhantes ao da função anterior, porém para a imagem colorida. O que pode-se destacar é que a mediana é calculada para cada canal de cor separadamente.
// The steps are similar to the previous function, but for the colored image. What can be highlighted is that the median is calculated for each color channel separately.
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

// A função calcular_histograma_rgb calcula o histograma de uma imagem RGB. O histograma é uma representação de distribuição de frequência dos valores de cor.
// The calcular_histograma_rgb function calculates the histogram of an RGB image. The histogram is a representation of the frequency distribution of color values.
void calcular_histograma_rgb(const ImageRGB *img, int *hist_red, int *hist_green, int *hist_blue, int num_bins)
{
    int bin_size = 256 / num_bins; // Calcula o tamanho de cada bin (faixa) no histograma

    // Aqui, a função inicializa os histogramas de vermelho (hist_red), verde (hist_green) e azul (hist_blue) com zeros. A variável bin_size determina quantos valores de cor serão agrupados em cada bin do histograma.
    // Here, the function initializes the red (hist_red), green (hist_green) and blue (hist_blue) histograms with zeros. The bin_size variable determines how many color values will be grouped in each bin of the histogram.
    for (int i = 0; i < num_bins; i++)
    {
        hist_red[i] = 0;
        hist_green[i] = 0;
        hist_blue[i] = 0;
    }

    // Nesta parte, a função percorre cada pixel da imagem e determina em qual bin do histograma cada valor de cor cai, incrementando o valor correspondente no histograma.
    // In this part, the function traverses each pixel of the image and determines in which bin of the histogram each color value falls, incrementing the corresponding value in the histogram.
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            // Calcula o bin de cada canal de cor (red, green, blue) para o pixel atual.
            // Calculates the bin of each color channel (red, green, blue) for the current pixel.
            int red_bin = img->pixels[i * img->dim.largura + j].red / bin_size;
            int green_bin = img->pixels[i * img->dim.largura + j].green / bin_size;
            int blue_bin = img->pixels[i * img->dim.largura + j].blue / bin_size;

            // Incrementa o valor do bin correspondente no histograma.
            // Increments the value of the corresponding bin in the histogram.
            hist_red[red_bin]++;
            hist_green[green_bin]++;
            hist_blue[blue_bin]++;
        }
    }
}

// A função calcular_histograma_rgb calcula o histograma de uma imagem RGB. O histograma é uma representação de distribuição de frequência dos valores de cor.
// The calcular_histograma_rgb function calculates the histogram of an RGB image. The histogram is a representation of the frequency distribution of color values.
ImageRGB *clahe_rgb(ImageRGB *img, int num_bins, int limite)
{
    // Inicializa os histogramas para cada canal de cor. Todos os valores são inicializados com 0.
    // Initializes the histograms for each color channel. All values are initialized to 0.
    int hist_red[256] = {0};
    int hist_green[256] = {0};
    int hist_blue[256] = {0};

    // Calcula o histograma da imagem RGB.
    // Calculates the histogram of the RGB image.
    calcular_histograma_rgb(img, hist_red, hist_green, hist_blue, num_bins);

    // Calcula o número total de pixels na imagem.
    // Calculates the total number of pixels in the image. 
    int total_pixels = img->dim.altura * img->dim.largura;

    // Calcula o histograma acumulado (CDF) para cada canal de cor. CDF é a soma acumulada dos valores do histograma.
    // Calculates the cumulative histogram (CDF) for each color channel. CDF is the accumulated sum of the histogram values.
    int cdf_red[256] = {0};
    int cdf_green[256] = {0};
    int cdf_blue[256] = {0};

    // Inicializa o CDF com o valor do primeiro bin do histograma.
    // Initializes the CDF with the value of the first bin of the histogram.
    cdf_red[0] = hist_red[0];
    cdf_green[0] = hist_green[0];
    cdf_blue[0] = hist_blue[0];

    // A função calcula a distribuição acumulada (CDF) para cada canal de cor. A CDF é usada para mapear os valores de intensidade de cor para melhorar o contraste.
    // The function calculates the cumulative distribution (CDF) for each color channel. The CDF is used to map color intensity values to improve contrast.
    for (int i = 1; i < 256; i++)
    {
        cdf_red[i] = cdf_red[i - 1] + hist_red[i];
        cdf_green[i] = cdf_green[i - 1] + hist_green[i];
        cdf_blue[i] = cdf_blue[i - 1] + hist_blue[i];
    }

    // Aqui, a função encontra o menor valor não zero na CDF de cada canal de cor. Isso é necessário para a equalização do histograma.
    // Here, the function finds the smallest non-zero value in the CDF of each color channel. This is necessary for histogram equalization.
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

    // A função cria uma nova imagem RGB para armazenar a imagem equalizada.
    // The function creates a new RGB image to store the equalized image.
    ImageRGB *equalized_img = create_image_rgb(img->dim.largura, img->dim.altura);

    // Esses dois laços são responsáveis por percorrer a matriz de pixels da imagem e equalizar os valores de intensidade de cor.
    // These two loops are responsible for traversing the image's pixel matrix and equalizing the color intensity values.
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

void calcular_histograma_gray(const ImageGray *img, int *hist, int num_bins) {
    int bin_size = 256 / num_bins;

    for (int i = 0; i < num_bins; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < img->dim.altura; i++) {
        for (int j = 0; j < img->dim.largura; j++) {
            int bin = img->pixels[i * img->dim.largura + j].value / bin_size;
            hist[bin]++;
        }
    }
}

ImageGray *clahe_gray(ImageGray *img, int num_bins, int limite) {
    int hist[256] = {0};
    calcular_histograma_gray(img, hist, num_bins);

    int total_pixels = img->dim.altura * img->dim.largura;

    // Calculate CDF
    int cdf[256] = {0};
    cdf[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }

    int min_cdf = cdf[0];
    for (int i = 1; i < 256; i++) {
        if (cdf[i] != 0 && cdf[i] < min_cdf) {
            min_cdf = cdf[i];
        }
    }

    ImageGray *equalized_img = create_image_gray(img->dim.largura, img->dim.altura);
    for (int i = 0; i < img->dim.altura; i++) {
        for (int j = 0; j < img->dim.largura; j++) {
            int pixel_pos = i * img->dim.largura + j;
            int value = img->pixels[pixel_pos].value;
            equalized_img->pixels[pixel_pos].value = (cdf[value] - min_cdf) * 255 / (total_pixels - min_cdf);
        }
    }

    return equalized_img;
}

// Função para transpor uma imagem em escala de cinza
// Function to transpose a grayscale image
void transpose_gray(const ImageGray *image, ImageGray *transposed_image)
{
    // Verifica se a imagem é nula, se a matriz de pixels é nula ou se a imagem transposta é nula.
    // Checks if the image is null, if the pixel matrix
    if (image == NULL || image->pixels == NULL || transposed_image == NULL)
    {
        fprintf(stderr, "Erro: Alguma das imagens é NULL.\n");
        return;
    }

    // Copio a largura e altura da imagem original
    // I copy the width and height of the original image
    int width = image->dim.largura;
    int height = image->dim.altura;

    // Transponho a largura e altura
    // I transpose the width and height
    transposed_image->dim.largura = height; // height em português é altura
    transposed_image->dim.altura = width; // width em português é largura

    // Aloco a memória necessária para a matriz de pixels da imagem transposta
    // I allocate the necessary memory for the pixel matrix of the transposed image
    alocarGray(height, width, &(transposed_image->pixels));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            // Para cada pixel na posição (i, j) na imagem original, seu valor é atribuído à posição (j, i) na imagem transposta.
            // To each pixel at position (i, j) in the original image, its value is assigned to position (j, i) in the transposed image.
            transposed_image->pixels[j * height + i].value = image->pixels[i * width + j].value;
        }
    }
}



void transpose_rgb(const ImageRGB *image, ImageRGB *transposed_image)
{
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



ImageHistoryNode *retornaInicioRGB(ImageHistoryNode *l){
    if (!l) return NULL;
    while(l->next != NULL)
        l = l->next;
    return l;
}

// Função add_image_to_history_rgb adiciona uma imagem RGB ao histórico de imagens, ou seja a cada alteração feita na imagem, uma cópia da imagem é salva no histórico.
// The add_image_to_history_rgb function adds an RGB image to the image history, that is, each change made to the image, a copy of the image is saved in the history.
void add_image_to_history_rgb(ImageHistory *history, ImageRGB *image)
{
    // Aloca memória para um novo nó do histórico de imagens
    // Allocates memory for a new node in the image history
    ImageHistoryNode *new_node = (ImageHistoryNode *)malloc(sizeof(ImageHistoryNode));

    history->current = retornaInicioRGB(history->current);
    // Cria uma nova imagem RGB com as mesmas dimensões da imagem fornecida
    // Creates a new RGB image with the same dimensions as the provided image
    new_node->image = create_image_rgb(image->dim.largura, image->dim.altura);

    // Copia a imagem fornecida para a nova imagem criada
    // Copies the provided image to the newly created image
    *new_node->image = *image;
    // Como os nós são inseridos no final da lista, o próximo nó é NULL
    // Since the nodes are inserted at the end of the list, the next node is NULL
    new_node->next = NULL;

    // O nó anterior ao novo nó é o nó atual do histórico
    // The node before the new node is the current node in the history
    new_node->prev = history->current;

    // Se o histórico já tiver um nó atual, atualiza o próximo nó para apontar para o novo nó
    // If the history already has a current node, update the next node to point to the new node
    if (history->current != NULL)
    {
        history->current->next = new_node;
    }

    // Atualiza o nó atual do histórico para o novo nó
    // Update the current node in the history to the new node
    history->current = new_node;
}

// Funciona de formula análoga a função add_image_to_history_rgb, porém para imagens em escala de cinza
// Works in an analogous formula to the add_image_to_history_rgb function, but for grayscale images
void add_image_to_history_gray(ImageHistoryGray *history, ImageGray *image)
{
    ImageHistoryNodeGray *new_node = (ImageHistoryNodeGray *)malloc(sizeof(ImageHistoryNodeGray));
    new_node->image = create_image_gray(image->dim.largura, image->dim.altura);
    *new_node->image = *image;
    new_node->next = NULL;
    new_node->prev = history->current;

    if (history->current != NULL) {
        history->current->next = new_node;
    }
    history->current = new_node;
}

// Função para desfazer a última alteração feita na imagem RGB
// Function to undo the last change made to the RGB image
void desfazer_rgb(ImageHistory *history, ImageRGB *imrgb)
{
    // Se o nó atual do histórico for NULL ou o nó anterior for NULL, não há nada para desfazer
    // If the current node in the history is NULL or the previous node is NULL, there is nothing to undo
    if (history->current == NULL || history->current->prev == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }
    // Caso contrário, o nó atual é atualizado para o nó anterior e a imagem é copiada para a imagem fornecida
    // Otherwise, the current node is updated to the previous node and the image is copied to the provided image
    history->current = history->current->prev;
    *imrgb = *history->current->image;
}

// Semelhante, porém no processo inverso
// Similar, but in the reverse process
void refazer_rgb(ImageHistory *history, ImageRGB *imrgb)
{
    if (history->current == NULL || history->current->next == NULL) {
        printf("Nada para refazer.\n");
        return;
    }
    // Caso contrário, o nó atual é atualizado para o próximo nó e a imagem é copiada para a imagem fornecida
    // Otherwise, the current node is updated to the next node and the image is copied to the provided image
    history->current = history->current->next;
    // Copia a imagem do nó atual para a imagem fornecida
    // Copies the image from the current node to the provided image
    *imrgb = *history->current->image;
}

void desfazer_gray(ImageHistoryGray *history, ImageGray *imgray)
{
    if (history->current == NULL || history->current->prev == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }
    history->current = history->current->prev;
    *imgray = *history->current->image;
}

void refazer_gray(ImageHistoryGray *history, ImageGray *imgray)
{
    if (history->current == NULL || history->current->next == NULL) {
        printf("Nada para refazer.\n");
        return;
    }
    history->current = history->current->next;
    *imgray = *history->current->image;
}


ImageHistory *create_image_history()
{
    ImageHistory *history = (ImageHistory *)malloc(sizeof(ImageHistory));
    history->current = NULL;
    return history;
}

ImageHistoryGray *create_image_history_gray()
{
    ImageHistoryGray *history = (ImageHistoryGray *)malloc(sizeof(ImageHistoryGray));
    history->current = NULL;
    return history;
}

void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, ImageHistory *history);
void aplicar_efeito_gray(ImageGray *imgray, int efeito, ImageHistoryGray *history);

// Função que sorteia um número entre 1 e 5 e aplica um efeito RGB aleatório à imagem
// Function that draws a number between 1 and 5 and applies a random RGB effect to the image
void sortear_efeito_rgb(ImageRGB *imrgb, ImageHistory *history)
{
    int efeito = (rand() % 5) + 1; 

    printf("Efeito sorteado: ");
    switch (efeito)
    {
    case 1:
        printf("Blur RGB\n");
        break;
    case 2:
        printf("CLAHE RGB\n");
        break;
    case 3:
        printf("Transpose RGB\n");
        break;
    case 4:
        printf("Flip Vertical RGB\n");
        break;
    case 5:
        printf("Flip Horizontal RGB\n");
        break;
    }
    aplicar_efeito_rgb(imrgb, efeito, history);
}

// Função que sorteia um número entre 1 e 5 e aplica um efeito em escala de cinza aleatório à imagem
// Function that draws a number between 1 and 5 and applies a random grayscale effect to the image
void sortear_efeito_gray(ImageGray *imgray,  ImageHistoryGray *history)
{
    int efeito = (rand() % 5) + 1;

    printf("Efeito sorteado: ");
    switch (efeito)
    {
    case 1:
        printf("Blur Gray\n");
        break;
    case 2:
        printf("CLAHE Gray\n");
        break;
    case 3:
        printf("Transpose Gray\n");
        break;
    case 4:
        printf("Flip Vertical Gray\n");
        break;
    case 5:
        printf("Flip Horizontal Gray\n");
        break;
    }
    aplicar_efeito_gray(imgray, efeito, history);
}

