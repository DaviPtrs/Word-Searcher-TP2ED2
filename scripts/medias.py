from os import system
from sys import argv
from collections import defaultdict
import csv

testFiles = ["3-19disc", "anti-mib", "asyoulik", "the_strings_of_pearls", "infinity_bible"]
numBuscas = [10, 100, 1000]


if len(argv) != 1:
    if argv[-1].isdigit():
        testFiles = argv[1:-1]
        n = int(argv[-1]) 
        if n in numBuscas:
            numBuscas = [n]
    else:
        testFiles = argv[1:]
        
for file in testFiles:
    for n in numBuscas:
        fileName = "output/{}_{}.csv".format(file, n)
        with open(fileName) as csvfile:
            arq = csv.reader(csvfile, delimiter=',')
            line = 1
            avgTempIns = 0
            avgTempBusca = 0
            infos = defaultdict(list)
            for row in arq:
                if line < 2:
                    line += 1
                elif '=-' in row[0]:
                    key = row[0]
                elif not 'I' in row[0]:
                    data = [float(row[0]), float(row[2])]
                    infos[key].append(data)

            for keys, sets in infos.items():
                print(keys)
                for nums in sets:
                    avgTempIns += nums[0]
                    avgTempBusca += nums[1]
                tam = len(sets)
                avgTempIns = float (float(avgTempIns) / float(tam))
                avgTempBusca = float (float(avgTempBusca) / float(tam))
                print("{},{:.6f},{},{:.6f}".format(file, avgTempIns, int(n), avgTempBusca))
