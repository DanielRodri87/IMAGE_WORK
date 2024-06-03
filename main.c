#include <stdio.h>
#include "image.h"

int main() {
    FILE *arq;
    arq = fopen("utils/input_image_example_RGB.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    ImageGray imgray;
    ImageRGB imrgb;
    ImageGray flip_gray_vertical;
    ImageRGB flip_rgb_vertical;
    ImageRGB blur_rgb;
    ImageGray blur_gray;
    ImageRGB clahe_rgb_img;
    ImageGray transpose_gray_var;
    ImageRGB transpose_rgb_var;


    system("pause");

    ler_imagem_arkv(arq, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");

    // #################################### INICIO - BLUR_RGB ###########################################

    // Inicializa blur_rgb
    ImageRGB img_saida_blur_rgb;

    blur_rgb.dim.altura = imrgb.dim.altura;
    blur_rgb.dim.largura = imrgb.dim.largura;
    alocarRGB(blur_rgb.dim.altura, blur_rgb.dim.largura, &(blur_rgb.pixels));

    // Chama a função ajustada
    blur_rgb = *median_blur_rgb(&imrgb, 15);

    FILE *RGBBlur;
    RGBBlur = fopen("utils/blur_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&blur_rgb, RGBBlur);

    RGBBlur = fopen("utils/blur_rgb.txt", "r");
    ler_imagem_arkv(RGBBlur, &img_saida_blur_rgb);
    printImageColor(&img_saida_blur_rgb);
    printf("\n\n\n");

    // #################################### FIM - BLUR_RGB ###########################################


    // #################################### INICIO - Clahe_RGB ##########################################

    // Inicializa clahe_rgb_img
    ImageRGB img_saida_clahe_rgb;

    clahe_rgb_img.dim.altura = imrgb.dim.altura;
    clahe_rgb_img.dim.largura = imrgb.dim.largura;
    alocarRGB(clahe_rgb_img.dim.altura, clahe_rgb_img.dim.largura, &(clahe_rgb_img.pixels));

    // Chama a função ajustada
    clahe_rgb_img = *clahe_rgb(&imrgb, 256, 40);

    FILE *RGBClahe;
    RGBClahe = fopen("utils/clahe_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&clahe_rgb_img, RGBClahe);

    RGBClahe = fopen("utils/clahe_rgb.txt", "r");
    ler_imagem_arkv(RGBClahe, &img_saida_clahe_rgb);
    printImageColor(&img_saida_clahe_rgb);
    printf("\n\n\n");

    // #################################### FIM - Clahe_RGB ###########################################

    // #################################### TRANPOSE RGB ###########################################

    ImageRGB img_saida_transpose_rgb;
    transpose_rgb_var.dim.altura = imrgb.dim.altura;
    transpose_rgb_var.dim.largura = imrgb.dim.largura;
    alocarRGB(transpose_rgb_var.dim.altura, transpose_rgb_var.dim.largura, &(transpose_rgb_var.pixels));

    transpose_rgb(&imrgb, &transpose_rgb_var);
    FILE *transporgb;
    transporgb = fopen("utils/transpose_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&transpose_rgb_var, transporgb);

    transporgb = fopen("utils/transpose_rgb.txt", "r");
    ler_imagem_arkv(transporgb, &img_saida_transpose_rgb);
    printImageColor(&img_saida_transpose_rgb);
    printf("\n\n\n");


    // #################################### INICIO - flip_vertical_RGB ###########################################
    
    ImageRGB flip_rgb_vertical_saida;
    // Inicializa flip_rgb_vertical
    flip_rgb_vertical.dim.altura = imrgb.dim.altura;
    flip_rgb_vertical.dim.largura = imrgb.dim.largura;
    alocarRGB(flip_rgb_vertical.dim.altura, flip_rgb_vertical.dim.largura, &(flip_rgb_vertical.pixels));

    // Chama a função ajustada
    flip_vertical_rgb(&imrgb, &flip_rgb_vertical);

    FILE *RGBFlip;
    RGBFlip = fopen("utils/flip_rgb_vertical.txt", "w");
    salvar_imagem_arkv_rgb(&flip_rgb_vertical, RGBFlip);

    RGBFlip = fopen("utils/flip_rgb_vertical.txt", "r");
    ler_imagem_arkv(RGBFlip, &flip_rgb_vertical_saida);
    printImageColor(&flip_rgb_vertical_saida);
    printf("\n\n\n");  

    // #################################### FIM - flip_vertical_RGB ###########################################
    converter_para_gray(&imrgb, &imgray);

    FILE *GrayExample;
    GrayExample = fopen("utils/example_GRAY.txt", "w");
    salvar_imagem_arkv(&imgray, GrayExample);

    GrayExample = fopen("utils/example_GRAY.txt", "r");
    ler_imagem_arkv(GrayExample, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");


    // #################################### INÍCIO - TRANSPOSE_GRAY ###########################################

    ImageRGB transpose_gray_saida;
    transpose_gray_var.dim.altura = imgray.dim.altura;
    transpose_gray_var.dim.largura = imgray.dim.largura;
    alocarGray(transpose_gray_var.dim.altura, transpose_gray_var.dim.largura, &(transpose_gray_var.pixels));

    transpose_gray(&imgray, &transpose_gray_var);
    FILE *transpogray;
    transpogray = fopen("utils/transpose_gray.txt", "w");
    salvar_imagem_arkv(&transpose_gray_var, transpogray);

    transpogray = fopen("utils/transpose_gray.txt", "r");
    ler_imagem_arkv(transpogray, &transpose_gray_saida);
    printImageColor(&transpose_gray_saida);
    printf("\n\n\n");

    // #################################### INICIO - BLUR_GRAY ###########################################
    ImageRGB img_blur_gray_saida;

    // Inicializa blur_gray
    blur_gray.dim.altura = imgray.dim.altura;
    blur_gray.dim.largura = imgray.dim.largura;
    alocarGray(blur_gray.dim.altura, blur_gray.dim.largura, &(blur_gray.pixels));

    // Chama a função ajustada
    blur_gray = *median_blur_gray(&imgray, 15);

    FILE *GrayBlur;
    GrayBlur = fopen("utils/blur_gray.txt", "w");
    salvar_imagem_arkv(&blur_gray, GrayBlur);

    GrayBlur = fopen("utils/blur_gray.txt", "r");
    ler_imagem_arkv(GrayBlur, &img_blur_gray_saida);
    printImageColor(&img_blur_gray_saida);
    printf("\n\n\n");

    // #################################### FIM - BLUR_GRAY ###########################################

    // #################################### INICIO - flip_vertical_gray ###########################################

    ImageRGB flip_gray_vertical_saida;
    // Inicializa flip_gray_vertical
    flip_gray_vertical.dim.altura = imgray.dim.altura;
    flip_gray_vertical.dim.largura = imgray.dim.largura;
    alocarGray(flip_gray_vertical.dim.altura, flip_gray_vertical.dim.largura, &(flip_gray_vertical.pixels));

    // Chama a função ajustada
    flip_vertical_gray(&imgray, &flip_gray_vertical);

    FILE *GrayFlip;
    GrayFlip = fopen("utils/flip_gray_vertical.txt", "w");
    salvar_imagem_arkv(&flip_gray_vertical, GrayFlip);

    GrayFlip = fopen("utils/flip_gray_vertical.txt", "r");
    ler_imagem_arkv(GrayFlip, &flip_gray_vertical_saida);
    printImageColor(&flip_gray_vertical_saida);
    printf("\n\n\n");

    // #################################### FIM - flip_vertical_gray ###########################################


    system("pause");
    // free_image_gray(&blur_gray);
    // free_image_rgb(&blur_rgb);
    // free_image_rgb(&flip_rgb_vertical);
    // free_image_gray(&imgray);
    // free_image_rgb(&imrgb);
    // free_image_gray(&flip_gray_vertical);
    // free_image_rgb(&transporgb);
    // free_image_gray(&transpogray);

    return 0;

}