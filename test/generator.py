import networkx as nx
import random

samples = [(2 ** (i + 1), random.randint(int(2 ** i), int(2 ** (i + 2)))) for i in range(10)]

for i in range(len(samples)):
    fPath = f"input/test-{i}.txt"

    # Gere um grafo aleatório
    G = nx.gnm_random_graph(samples[i][0], samples[i][1])

    # Adicione pesos aleatórios às arestas
    for edge in G.edges():
        weight = random.uniform(0.1, 1.0)  # Peso aleatório entre 0.1 e 1
        G[edge[0]][edge[1]]['weight'] = weight

    nx.write_edgelist(G, fPath)

    # Leia o conteúdo do arquivo
    with open(fPath, "r") as file:
        content = file.read()

    # Adicione o comentário ao início do conteúdo
    content = f"# {samples[i][0]}\n" + content

    # Reescreva o arquivo com o comentário
    with open(fPath, "w") as file:
        file.write(content)