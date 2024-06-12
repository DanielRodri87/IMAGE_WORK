#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

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
void exibir_resultado_rgb(int efeito);
void aplicar_efeito_gray(ImageGray *imgray, int efeito, int contagem);
void mostrar_menu();
void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, int contagem);
void abrir_imagem(const char *image_path);

void chamar_python(const char *script, const char *func, const char *input_path, const char *output_path);

int main()
{
    FILE *arq = fopen("utils/input_image_example_RGB.txt", "r");
    ImageRGB imrgb;
    ImageGray imgray;
    int opcao, efeito;
    int contagem_efeitos_rgb = 0;
    int contagem_efeitos_gray = 0;

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    criar_imagem_rgb(arq, &imrgb);

    while (1)
    {
        mostrar_menu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                while (1)
                {
                    printf("Selecione o efeito que deseja aplicar:\n");
                    printf("1 - Blur RGB\n2 - CLAHE RGB\n3 - Transpose RGB\n4 - Flip Vertical RGB\n5 - Flip Horizontal RGB\n6 - Concluir Aplicacao de Efeitos\n");
                    printf("Digite a opcao desejada: ");
                    scanf("%d", &efeito);

                    if (efeito == 6) {
                        printf("Aplicacao de efeitos concluída.\n");
                        break;
                    }

                    contagem_efeitos_rgb++;
                    aplicar_efeito_rgb(&imrgb, efeito, contagem_efeitos_rgb);
                }
                break;
            case 2:
                converter_para_gray(&imrgb, &imgray);
                FILE *GrayExample;
                GrayExample = fopen("utils/input_example_GRAY.txt", "w");
                salvar_imagem_arkv(&imgray, GrayExample);
                fclose(GrayExample);
                chamar_python("utils/image_utils.py", "image_gray_from_txt", "utils/input_example_GRAY.txt", "utils/output_example_GRAY.png");
                break;
            case 3:
                while (1)
                {
                    printf("Selecione o efeito que deseja aplicar:\n");
                    printf("1 - Blur Gray\n2 - CLAHE Gray\n3 - Transpose Gray\n4 - Flip Vertical Gray\n5 - Flip Horizontal Gray\n6 - Concluir Aplicacao de Efeitos\n");
                    printf("Digite a opcao desejada: ");
                    scanf("%d", &efeito);

                    if (efeito == 6) {
                        printf("Aplicacao de efeitos concluída.\n");
                        break;
                    }

                    contagem_efeitos_gray++;
                    aplicar_efeito_gray(&imgray, efeito, contagem_efeitos_gray);
                }
                break;
            case 4:
                printf("Quantos efeitos você aplicou: ");
                scanf("%d", &efeito);
                exibir_resultado_rgb(efeito);
                abrir_imagem("image_rgb.png");
                break;
            case 5:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opcao inválida\n");
                break;
        }
    }

    return 0;
}

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb)
{
    ler_imagem_arkv(arq, imrgb);
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", "utils/input_image_example_RGB.txt", "utils/output_image_example_RGB.png");
    abrir_imagem("image_rgb.png");
}

void aplicar_efeito_rgb(ImageRGB *imrgb, int efeito, int contagem)
{
    char txt_filename[50];
    char output_filename[50];
    snprintf(txt_filename, sizeof(txt_filename), "utils/input_imagem_final%d.txt", contagem); // Modificado para iniciar com "input_"
    snprintf(output_filename, sizeof(output_filename), "utils/imagem_final%d.png", contagem);

    switch (efeito) {
        case 1:
            printf("Aplicando Blur RGB\n");
            aplicar_blur_rgb(imrgb);

            break;
        case 2:
            printf("Aplicando CLAHE RGB\n");
            aplicar_clahe_rgb(imrgb);

            break;
        case 3:
            printf("Aplicando Transpose RGB\n");
            aplicar_transpose_rgb(imrgb);
            break;
        case 4:
            printf("Aplicando Flip Vertical RGB\n");
            aplicar_flip_vertical_rgb(imrgb);
            break;
        case 5:
            printf("Aplicando Flip Horizontal RGB\n");
            aplicar_flip_horizontal_rgb(imrgb);
            break;
        default:
            printf("Opcao de efeito inválida\n");
            return;
    }

    FILE *imagemFinal = fopen(txt_filename, "w");
    if (imagemFinal == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }
    salvar_imagem_arkv_rgb(imrgb, imagemFinal);
    fclose(imagemFinal);
    printf("Imagem salva em '%s'\n", txt_filename);

    // Chamar o Python para converter o arquivo txt em imagem apenas quando necessário
    if (efeito != 6) {
        chamar_python("utils/image_utils.py", "image_rgb_from_txt", txt_filename, output_filename);
    }
}


void aplicar_efeito_gray(ImageGray *imgray, int efeito, int contagem)
{
    char txt_filename[50];
    char output_filename[50];
    snprintf(txt_filename, sizeof(txt_filename), "utils/input_imagem_final%d.txt", contagem); // Modificado para iniciar com "input_"
    snprintf(output_filename, sizeof(output_filename), "utils/imagem_final%d.png", contagem);

    switch (efeito) {
        case 1:
            printf("Aplicando Blur Gray\n");
            aplicar_blur_gray(imgray);
            break;
        case 2:
            printf("Aplicando CLAHE Gray\n");
            aplicar_clahe_gray(imgray);
            break;
        case 3:
            printf("Aplicando Transpose Gray\n");
            aplicar_transpose_gray(imgray);
            break;
        case 4:
            printf("Aplicando Flip Vertical Gray\n");
            aplicar_flip_vertical_gray(imgray);
            break;
        case 5:
            printf("Aplicando Flip Horizontal Gray\n");
            aplicar_flip_horizontal_gray(imgray);
            break;
        default:
            printf("Opcao de efeito inválida\n");
            return;
    }

    FILE *imagemFinal = fopen(txt_filename, "w");
    if (imagemFinal == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }
    salvar_imagem_arkv(imgray, imagemFinal);
    fclose(imagemFinal);
    printf("Imagem salva em '%s'\n", txt_filename);

    chamar_python("utils/image_utils.py", "image_rgb_from_txt", txt_filename, output_filename);
}

void mostrar_menu()
{
    printf("========================================\n");
    printf("          EDITOR DE IMAGENS UFHOTOPI    \n");
    printf("========================================\n");
    printf("1 - Aplicar Efeitos RGB\n");
    printf("2 - Converter para Preto e Branco\n");
    printf("3 - Aplicar Efeitos Preto e Branco\n");
    printf("4 - Exibir Resultado\n");
    printf("5 - Sair\n");
    printf("========================================\n");
}

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

void exibir_resultado_rgb(int efeito)
{
    char filename[50];
    char output_filename[50];
    snprintf(filename, sizeof(filename), "utils/imagem_final%d.txt", efeito);
    snprintf(output_filename, sizeof(output_filename), "utils/imagem_final%d.png", efeito);

    FILE *imagemFinal = fopen(filename, "r");
    if (imagemFinal == NULL) {
        printf("Erro ao abrir o arquivo da imagem final.\n");
        return;
    }
    ImageRGB img_final;
    ler_imagem_arkv(imagemFinal, &img_final);
    fclose(imagemFinal);
    chamar_python("utils/image_utils.py", "image_rgb_from_txt", filename, output_filename);
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


// Aqui irei fazer uma função que vai abrir fotos no windows
void abrir_imagem(const char *image_path)
{
    char command[256];
    snprintf(command, sizeof(command), "python utils/abrir_imagem_sistemas.py %s", image_path);
    int ret = system(command);
    if (ret != 0) {
        printf("Erro ao abrir a imagem. Código de retorno: %d\n", ret);
    }
}
