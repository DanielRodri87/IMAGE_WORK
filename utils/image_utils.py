from PIL import Image
import os

def image_rgb_from_latest_txt(directory, output_path):
    # Lista todos os arquivos no diretório
    files = os.listdir(directory)

    # Filtra apenas os arquivos com o padrão 'imagem_finalN.txt'
    txt_files = [file for file in files if file.startswith('imagem_final') and file.endswith('.txt')]

    # Se houver pelo menos um arquivo txt, pega o último
    if txt_files:
        latest_txt = max(txt_files)

        # Constrói o caminho completo para o arquivo txt mais recente
        txt_path = os.path.join(directory, latest_txt)

        # Abre o arquivo txt e converte em imagem RGB
        with open(txt_path, 'r') as file:
            lines = file.readlines()
            largura = int(lines[0].strip())
            altura = int(lines[1].strip())

            nova_imagem = Image.new('RGB', (largura, altura))

            for y in range(altura):
                for x in range(largura):
                    pixel = tuple(map(int, lines[2 + y].split(',')[x].strip().split()))
                    nova_imagem.putpixel((x, y), pixel)

            # Salva a imagem resultante
            nova_imagem.save(output_path)
    else:
        print("Nenhum arquivo 'imagem_finalN.txt' encontrado.")

def main():
    # Chama a função para converter o arquivo de texto mais recente em imagem RGB
    image_rgb_from_latest_txt("utils", "image_rgb.png")

if __name__ == "__main__":
    main()
