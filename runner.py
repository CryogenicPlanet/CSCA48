import os
import sys
output = sys.argv[2] or "a.out"
os.system("g++ -Wall -Werror ./" + sys.argv[1] + " -o " + output)
os.system("./"+output)