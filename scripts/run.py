from os import system
from sys import argv
import csv

testFiles = ["3-19disc.txt", "anti-mib.txt", "asyoulik.txt", "the_strings_of_pearls.txt", "infinity_bible.txt"]
numBuscas = [10, 100, 1000]


if len(argv) != 1:
    if argv[-1].isdigit():
        testFiles = argv[1:-1]
        n = int(argv[-1]) 
        if n in numBuscas:
            numBuscas = [n]
    else:
        testFiles = argv[1:]
        


system("mkdir output")

for file in testFiles:
    for n in numBuscas:
        inputName = "input/{}.txt".format(n)
        if "tests/" in file:
            file = file[6:]
        textFile = "tests/{}".format(file)
        cmd = "./main {} 5 {} < {}".format(textFile, n, inputName)

        fileOut = file
        if ".txt" in file:
            fileOut = fileOut[:-4]
        fileName = "output/{}_{}.csv".format(fileOut, n)
        print("Criando arquivo " + fileName)
        system("rm output/{}".format(fileName))
        system("touch "+ fileName)
        system("echo '{}' >>  {}".format(fileName, fileName))
        print(cmd)
        print("\n")
        for c in range(0,5):
            system(cmd + " >> " + fileName)
