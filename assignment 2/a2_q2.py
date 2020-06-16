
def check_teams(graph , csp_sol):
    if len(graph)!=len(csp_sol):
        print("length of graph and csp_sol are not equal")
        exit()
    num_nodes=len(csp_sol)
    
    for i in range(num_nodes):
        for j in range(i+1,num_nodes):
            if csp_sol[i]==csp_sol[j] and i in graph[j]:
                return False
    return True



'''
graph={0:[1,2,5],1:[0,4,5],2:[0,5],3:[5],4:[1,5],5:[0,1,2,3,4]}#{0: [1, 2], 1: [0], 2: [0], 3: []}
csp_sol={0:0,1:1,2:2,3:0,4:2,5:3}
print(check_teams(graph,csp_sol))

'''
