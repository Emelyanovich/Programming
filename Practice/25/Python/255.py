from random import randint, shuffle
x = input()
s = x.split()
Q = [int(y) for y in s]

def isSorted(Q):
    for i in range(1, len(Q)):
        if(Q[i - 1] > Q[i]):
            return False
    return True
sortList = Q
while not isSorted(sortList):
    rand1 = randint(0, len(sortList) - 1)
    rand2 = randint(0, len(sortList) - 1)
    swap = sortList[rand1]
    sortList[rand1] = sortList[rand2]
    sortList[rand2] = swap
print(sortList)
def isSorted(Q):
    for i in range(1, len(Q)):
        if(Q[i - 1] < Q[i]):
            return False
    return True
sortList = Q
while not isSorted(sortList):
    rand1 = randint(0, len(sortList) - 1)
    rand2 = randint(0, len(sortList) - 1)
    swap = sortList[rand1]
    sortList[rand1] = sortList[rand2]
    sortList[rand2] = swap
print(sortList)

B=[Q[1],Q[2],Q[3]]
def isSorted(B):
    for i in range(1, len(B)):
        if(B[i - 1] > B[i]):
            return False
    return True

sortList = B
while not isSorted(sortList):
    rand1 = randint(0, len(sortList) - 1)
    rand2 = randint(0, len(sortList) - 1)
    swap = sortList[rand1]
    sortList[rand1] = sortList[rand2]
    sortList[rand2] = swap
print(sortList)

B=[Q[1],Q[2],Q[3]]
def isSorted(B):
    for i in range(1, len(B)):
        if(B[i - 1] < B[i]):
            return False
    return True
sortList = B
while not isSorted(sortList):
    rand1 = randint(0, len(sortList) - 1)
    rand2 = randint(0, len(sortList) - 1)
    swap = sortList[rand1]
    sortList[rand1] = sortList[rand2]
    sortList[rand2] = swap
    
print(sortList)
