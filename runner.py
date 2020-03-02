import os
import sys
output = sys.argv[2] or "a.out"
os.system("gcc -Wall -Werror -O2  ./" + sys.argv[1] + " -lm -fopenmp  -o ./Binaries/" + output)
os.system("./Binaries/"+output)