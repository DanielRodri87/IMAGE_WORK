**Descrição do Trabalho: Implementação de Operações de Manipulação de Imagens com Histórico de Reversão**

**Instrucoes para Controle de versão**
- clonar o repositorio
- criar um novo repositorio com os integrantes da equipe e o monitor (adrianorodriguesdsousa@ufpi.edu.br or certainlyWrong)
- 


**Orientações:**
- O trabalho será realizado por até três alunos (não serão permitidos mais que três).
- O trabalho deverá ser enviado via SIGAA.
- A pontuação máxima será de 10 pontos.
- Utilize apenas a linguagem C para implementação. O uso de auxiliares em Python disponibilizados no repositório também é permitido.

**Objetivo:**
O objetivo deste projeto é desenvolver uma solução para manipulação de imagens que permita a aplicação de várias operações, como rotação, inversão e filtros, em imagens em escala de cinza e em cores. Além disso, o sistema deve fornecer um histórico reversível das operações realizadas, permitindo ao usuário voltar para versões anteriores da imagem, ou caso necessário, ir novamente para a versão mais adiante, afinal é uma lista dupla.

**Implementação:**
1. **Estrutura de Dados:**
   - Utilização de uma lista duplamente encadeada para armazenar o histórico de imagens. Cada nó da lista conterá uma referência para a imagem resultante de uma operação e ponteiros para o próximo e o anterior nós na lista.

2. **Operações de Manipulação de Imagem:**
   - Implementação de uma variedade de operações, como rotação, inversão (vertical e horizontal), aplicação de filtros (como o filtro de média), equalização de histograma e outras técnicas de processamento de imagem.
   - Cada operação deve retornar uma nova imagem processada, preservando a imagem original no histórico, esta sempre será a imagem inicial da lista.

3. **Interface do Usuário:**
   - Desenvolvimento de uma interface com as opcoes de menu indicada para cada tipo de imagem, i.e., RBG ou Gray, 
   - Visualize o histórico de operações (usar os cod python para gerar as imagens).
   - A interface deve fornecer controles para aplicar novas operações, desfazer operações e navegar pelo histórico (ou seja, pelas posicoes da lista).

4. **Operações randomicas:**
   - Nesta abordagem, o usuário seleciona um tipo de imagem para o qual deseja aplicar operações de processamento. O sistema, então, escolhe aleatoriamente quais operações serão aplicadas a essa imagem. Após a conclusão das operações, o resultado final é apresentado em uma lista encadeada simples. Cada entrada na lista corresponde a uma operação realizada, permitindo ao usuário visualizar o processo passo a passo e o resultado final da manipulação da imagem.

5. **Observações:**
   - Muitas funções do sistema podem não estar mapeadas, deixando espaço para que o desenvolvedor as implemente conforme necessário.
   - É importante observar atentamente os requisitos mencionados anteriormente para garantir que o sistema atenda às expectativas e funcione conforme o esperado.


