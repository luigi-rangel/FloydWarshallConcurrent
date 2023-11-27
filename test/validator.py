import networkx as nx
import subprocess

def load_matrix(input_file):
    matrix = []

    with open(input_file, 'r') as file:
        lines = file.readlines()

        for line in lines:
            if line[0] == "#": continue
            # Remove espaços em branco e caracteres especiais
            clean_line = line.strip('{}\n').split()

            # Converte os elementos da linha para inteiros ou float, conforme necessário
            matrix_line = [float(x) for x in clean_line]

            matrix.append(matrix_line)

    return matrix

num_tests = 10
max_threads = 10

solution_path = "main.exe"

error = False

for i in range(num_tests):
    input_file_path = f"input/validate-{i}.txt"
    output_file_path = f"output/validate-{i}.txt"

    print(f"Processando o arquivo {input_file_path}")

    input_matrix = nx.read_edgelist(input_file_path)
    nx_solution = nx.floyd_warshall(input_matrix, weight='weight')

    validator = {a: dict(b) for a, b in nx_solution.items()}

    for nthreads in range(1, max_threads + 1):
        if subprocess.call([solution_path, str(nthreads), input_file_path, output_file_path]) != 0:
            print(f"O programa falhou com o arquivo {input_file_path} :(")
        
        output_matrix = load_matrix(output_file_path)

        for i in validator:
            for j in validator[i]:
                if validator[i][j] - output_matrix[int(i)][int(j)] > 1e-10: 
                    print(f"ERRO: {output_file_path}")
                    error = True

if not error: print("\nAlgoritmo executado corretamente em todos os arquivos")