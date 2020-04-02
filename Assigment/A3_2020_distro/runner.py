import os
import sys
#print("NOT USING WERROR")
os.system("gcc  -Werror  -Wall  -g   " + sys.argv[1] + " -lm -fopenmp -o" + sys.argv[2])
os.system("./"+sys.argv[2])