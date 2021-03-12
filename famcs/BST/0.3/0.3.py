file = open('bst.txt', 'r')
V = []
i = 0

for line in file:
    if i < 2:
        if i == 0:
            n = int(line.rstrip('\n'))
        else:
            V.append([line.rstrip('\n'),0,'root'])
    else:
        S = line.rstrip('\n').split(' ')
        V.append([S[0],S[1],S[2]])
    i += 1

    levels = {k for k in range(1,n+1)}
    parents = {k for k in range(1,n)}




print(V)