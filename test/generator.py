import networkx as nx
import random

def generateSamples(sizes, title):
    for i in range(len(sizes)):
        fPath = f"input/{title}-{i}.txt"
        
        G = nx.gnm_random_graph(sizes[i][0], sizes[i][1])

        for edge in G.edges():
            weight = random.uniform(0.1, 1.0)
            G[edge[0]][edge[1]]['weight'] = weight

        nx.write_edgelist(G, fPath)

        with open(fPath, "r") as file:
            content = file.read()

        content = f"# {sizes[i][0]}\n" + content

        with open(fPath, "w") as file:
            file.write(content)

validation_samples = [(2 ** (i + 1), random.randint(int(2 ** i), int(2 ** (i + 2)))) for i in range(10)]

generateSamples(validation_samples, "validate")

evaluation_samples = [(100, 300), (500, 500), (1000, 1500), (2000, 3000)]

generateSamples(evaluation_samples, "evaluate")