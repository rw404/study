N = int(input())

trees = []
for i in range(N):
    cur_t = input()
    trees.append(cur_t)

def treemaker(tree_el):
    tree = {'left': None, 'right': None, 'up': None, 'type': 'root'}
    cur_node = tree
    for i in tree_el:
        if i == 'D':
            new_node = {'left': None, 'right': None, 'up': cur_node, 'type': 'left'}
            cur_node['left'] = new_node
            cur_node = new_node
        elif i == 'U':
            while cur_node['type'] == 'right':
                cur_node = cur_node['up']
            cur_node = cur_node['up']
            new_node = {'left': None, 'right': None, 'up': cur_node, 'type': 'right'}
            cur_node['right'] = new_node
            cur_node = new_node
    return tree

to_print = []
def tree_cnt(root, prefix):
    if root['left'] is None or root['right'] is None:
        to_print.append(''.join(prefix))
        return [''.join(prefix)]
    prefix.append('0')
    ans = tree_cnt(root['left'], prefix)
    prefix.pop()
    prefix.append('1')
    
    ans.extend(tree_cnt(root['right'], prefix))
    prefix.pop()
    return ans

for i in range(N):
    root = treemaker(trees[i]) 
    to_print = []
    tree_cnt(root, [])
    print(len(to_print))
    for j in range(len(to_print)):
        print(to_print[j])
