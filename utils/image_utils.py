from PIL import Image
import os

# Essa função converte uma imagem para um arquivo de texto
# This function converts an image to a text file
def txt_from_image_gray(image_path, output_path, gray=True):
    try:
        img = Image.open(image_path)

        if gray:
            img = img.convert('L')
        
        largura, altura = img.size
        pixels = list(img.getdata())
        
        with open(output_path, 'w') as file:
            file.write(f"{largura}\n")
            file.write(f"{altura}\n")
            for y in range(altura):
                for x in range(largura):
                    pixel = str(pixels[y * largura + x]).replace(",", "").replace("(", "").replace(")", "")
                    file.write(f"{pixel},")
                file.write("\n")
        print(f"Arquivo texto salvo em {output_path}")
    except Exception as e:
        print(f"Erro ao converter imagem para texto: {e}")

# Converte uma imagem GRAY para um arquivo de texto
# Converts an GRAY image to a text file
def image_gray_from_txt(txt_path, output_path):
    try:
        with open(txt_path, 'r') as file:
            lines = file.readlines()

            largura = int(lines[0].strip())
            altura = int(lines[1].strip())

            nova_imagem = Image.new('L', (largura, altura))

            for y in range(altura):
                for x in range(largura):
                    gray_value = int(lines[2 + y].split(',')[x].strip())
                    nova_imagem.putpixel((x, y), gray_value)

            nova_imagem.save(output_path)
        print(f"Imagem cinza salva em {output_path}")
    except Exception as e:
        print(f"Erro ao converter texto para imagem cinza: {e}")

# Converte uma imagem RGB para um arquivo de texto
# Converts an RGB image to a text file
def image_rgb_from_txt(txt_path, output_path):
    try:
        with open(txt_path, 'r') as file:
            lines = file.readlines()

            largura = int(lines[0].strip())
            altura = int(lines[1].strip())

            nova_imagem = Image.new('RGB', (largura, altura))

            for y in range(altura):
                for x in range(largura):
                    pixel = tuple(map(int, lines[2 + y].split(',')[x].strip().split()))
                    nova_imagem.putpixel((x, y), pixel)

            nova_imagem.save(output_path)
        print(f"Imagem RGB salva em {output_path}")
    except Exception as e:
        print(f"Erro ao converter texto para imagem RGB: {e}")


# Essa função converte o último arquivo de texto em uma imagem cinza. Essa função adicional, não foi solicitada no trabalho, porém foi necessária para o controle de arquivos na lógica do programa.
# This function converts the last text file to a gray image. This additional function was not requested in the work, however it was necessary for file control in the program logic.
def image_rgb_from_latest_txt(directory, output_path):
    try:
        files = os.listdir(directory)

        txt_files = [file for file in files if file.startswith('input') and file.endswith('.txt')]

        if txt_files:
            latest_txt = max(txt_files)

            txt_path = os.path.join(directory, latest_txt)

            with open(txt_path, 'r') as file:
                lines = file.readlines()
                largura = int(lines[0].strip())
                altura = int(lines[1].strip())

                nova_imagem = Image.new('RGB', (largura, altura))

                for y in range(altura):
                    for x in range(largura):
                        pixel = tuple(map(int, lines[2 + y].split(',')[x].strip().split()))
                        nova_imagem.putpixel((x, y), pixel)

                nova_imagem.save(output_path)
            print(f"Imagem RGB salva em {output_path}")
        else:
            print("Imagem nao encontrada")
    except Exception as e:
        print(f"Erro ao processar o último arquivo de texto RGB: {e}")

def main():
    image_rgb_from_latest_txt("utils", "out_image.png")

if __name__ == "__main__":
    main()
    
    