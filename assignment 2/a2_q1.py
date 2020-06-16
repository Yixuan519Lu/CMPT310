import random

def rand_graph(pb,num_nodes):
    graph={}
    for i in range(num_nodes):
        graph.setdefault(i , [])

    for i in range(num_nodes-1):
        for j in range(i+1,num_nodes):
            if pb>=random.random():
                graph.setdefault(i , []).append(j)
                graph.setdefault(j , []).append(i)
    return graph

'''
graph=rand_graph(0.5,10)
print(graph)
'''
