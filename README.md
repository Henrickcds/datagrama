# 📦 Ordenação de Pacotes UDP — Poxim Tech

Este projeto simula o funcionamento de um **sistema de comunicação baseado no protocolo UDP**, desenvolvido como parte da disciplina de **Programação e Análise de Algoritmos**.

O objetivo é **ordenar pacotes recebidos fora de ordem** utilizando o **Heapsort (min-heap)** para reconstituir a sequência correta e permitir o processamento parcial dos dados.

---

## 🎯 Problema

A empresa fictícia **Poxim Tech** está construindo um sistema de comunicação para redes TCP/IP.
O sistema deve lidar com pacotes que podem chegar **fora de ordem**, exigindo uma lógica de **reorganização e impressão condicional**.

### 📜 Regras do problema

* Os dados são organizados em pacotes de **até 512 bytes**.
* Cada pacote contém:

  * Um **número de sequência**
  * O **tamanho** (quantidade de bytes)
  * Os **dados propriamente ditos**
* Os pacotes são analisados em **duplas**:

  * Se forem **sequenciais**, são impressos juntos.
  * Se apenas um for da sequência, é impresso sozinho.
  * Se nenhum for da sequência, são armazenados em um **heap**.
* O heap é ordenado via **Heapsort**, para identificar quando novos pacotes completam uma sequência contínua.

---

## 🗂️ Estrutura do Projeto

```
├── datagrama.c         # Código-fonte principal em C
├── entrada.txt         # Exemplo de arquivo de entrada
└── (gerado após execução) saida.txt   # Saída esperada com pacotes ordenados
```

---

## ⚙️ Como Executar

### 1️⃣ Compilar o programa

```bash
gcc datagrama.c -o datagrama
```

### 2️⃣ Executar o simulador

```bash
./datagrama
```

O programa utiliza por padrão os arquivos:

* `entrada.txt` → dados de entrada
* `saida.txt` → resultado com pacotes ordenados

---

## 📥 Exemplo de Entrada

Arquivo: `entrada.txt`

```text
6 3
0 3 01 02 03
1 2 04 05
2 4 06 07 08 09
4 2 0F 10
3 5 0A 0B 0C 0D 0E
5 6 11 12 13 14 15 16
```

**Significado:**

* O primeiro número (`6`) indica o total de pacotes.
* O segundo número (`3`) indica a quantidade de pacotes recebidos antes de processar um lote.
* Cada linha seguinte representa um pacote com:

  * Número do pacote
  * Tamanho do pacote (quantidade de bytes)
  * Bytes em hexadecimal

---

## 📤 Exemplo de Saída (saida.txt)

```text
|01,02,03|04,05|06,07,08,09|
|0A,0B,0C,0D,0E|0F,10|11,12,13,14,15,16|
```

Cada linha corresponde a uma sequência de pacotes recebidos **em ordem**, delimitados por `|`.

---

## 🧮 Estruturas e Algoritmos Utilizados

* **Heap mínimo** para ordenação de pacotes pendentes
* **Heapsort** para garantir a ordem crescente de número de pacote
* **Processamento incremental** com impressão a cada lote de pacotes
* **Alocação dinâmica de memória** (`malloc`, `realloc`, `free`)
* **Strings formatadas** (`snprintf`) para montagem da saída

---

## 🧠 Conceitos Envolvidos

* Estruturas de dados: **Heap (Min-Heap)**
* Algoritmos de ordenação: **Heapsort**
* Manipulação de **arquivos** (`fopen`, `fscanf`, `fprintf`)
* Controle de fluxo e lógica condicional
* Processamento **parcial e incremental** de dados

---

## 👨‍💻 Autor

**Henrick Cardoso**

Projeto desenvolvido na disciplina de **Programação e Análise de Algoritmos** — 2025.
