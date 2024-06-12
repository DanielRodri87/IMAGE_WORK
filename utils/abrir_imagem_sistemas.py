import subprocess
import sys
import os

def abrir_imagem(image_path):
    try:
        if sys.platform.startswith('darwin'):
            subprocess.call(('open', image_path))
        elif os.name == 'nt':
            subprocess.call(('explorer', image_path))
        elif os.name == 'posix':
            subprocess.call(('xdg-open', image_path))
    except Exception as e:
        print("Erro ao abrir a imagem:", e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python abrir_imagem_sistemas.py <caminho_da_imagem>")
    else:
        imagem = sys.argv[1]
        abrir_imagem(imagem)
