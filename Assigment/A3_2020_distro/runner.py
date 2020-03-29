import os
import sys
print("NOT USING WERROR")
os.system("gcc  -Wall  -g   " + sys.argv[1] + " -lm -o" + sys.argv[2])
os.system("./"+sys.argv[2])