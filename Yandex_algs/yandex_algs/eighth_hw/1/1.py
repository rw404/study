tree = []

def add(el):
    if len(tree) == 0:
        tree.append(el)
        tree.append([])
        tree.append([])
        print("DONE")
    else:
        tree_el = tree
        prev_el = tree
        in_tree = False
        while len(tree_el) != 0:
            if el < tree_el[0]:
                prev_el = tree_el
                tree_el = tree_el[1]
            elif el == tree_el[0]:
                print("ALREADY")
                in_tree = True
                break
            else:
                prev_el = tree_el
                tree_el = tree_el[2] 
        if not in_tree:
            if prev_el[0] > el:
                prev_el[1] = [el, [], []]
            else:
                prev_el[2] = [el, [], []]
            print("DONE")

def search(el):
    if len(tree) == 0:
        print("NO")
    else:
        tree_el = tree
        while len(tree_el) != 0:
            if el < tree_el[0]:
                tree_el = tree_el[1]
            elif el == tree_el[0]:
                print("YES")
                return
            else:
                tree_el = tree_el[2]
        print("NO")

def printt(mas, h):
    tree_el = mas
    if len(tree_el) == 0:
        return
    else:    
        printt(tree_el[1], h+1)
        for i in range(h):
            print(".", end='') 
        print(tree_el[0])
        printt(tree_el[2], h+1)

while True:
    try:
        inp = input()
    except EOFError:
        break
    if inp == "PRINTTREE":
        printt(tree, 0)
    else:
        cmd, val = inp.split()[0], int(inp.split()[1])
        if cmd == "ADD":
            add(val)
        elif cmd == "SEARCH":
            search(val) 
