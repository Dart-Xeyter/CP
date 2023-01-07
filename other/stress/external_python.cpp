import os
from random import *


def gen_test():
    with open("test.txt", 'w') as test:
        pass


q2 = 0
while True:
    print(q2)
    gen_test()
    easy = 'easy.py'
    hard = 'C:\\testing\\testing\\Windows\\b.exe'
    os.system(f'python3 {easy} < test.txt > easy.txt')
    os.system(f'{hard} < test.txt > hard.txt')
    ans1 = open("easy.txt").read()
    ans2 = open("hard.txt").read()
    if ans1 != ans2:
        exit(179)
    q2 += 1
