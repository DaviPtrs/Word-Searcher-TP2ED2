from os import system
from sys import argv
from collections import defaultdict
import csv

with open(argv[1]) as csvfile:
    arq = csv.reader(csvfile, delimiter=',')
    infos = defaultdict(list)
    for row in arq:
        if '=-' in row[0]:
            key = row[0]
        else:
            infos[key].append(row)

    for keys, sets in infos.items():
        print(keys)
        print("Inserção, N, Busca")
        for linhas in sets:
            print("{},{},{},{}".format(linhas[0], linhas[1], linhas[2], linhas[3]))
