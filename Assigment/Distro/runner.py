import os
import sys
print("NOT USING WERROR")
os.system("gcc -Wall  " + sys.argv[1] + " -o" + sys.argv[2])
os.system("./"+sys.argv[2])