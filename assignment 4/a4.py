import string
import copy

DEBUG=0

my_kb=[]# store atoms added from tell and infer_all
inferred_atoms=[]# store inferred atoms from infer_all
kb=[]# store input kb from load()
sentences=[]

# calling load again will delete the old one and replace it with the new one
def myInit():
    global my_kb
    global inferred_atoms
    global kb
    global sentences
    my_kb=[]
    inferred_atoms=[]
    kb=[]
    sentences=[]
    return True

def clear_atoms():
    global my_kb
    global inferred_atoms
    global sentences
    my_kb=[]
    inferred_atoms=[]
    sentences=[]
    return True

def print_kb():
    for i in sentences:
        print(i)
    print('\n')

    
def load(filename):
    global sentences
    myInit()
    # check input file exists or not
    try:
        myFile=open(filename,'r')
        all_sentences=myFile.read()
    except FileNotFoundError:
            print("Could not find ",filename)
            return False
    sentences=all_sentences.splitlines()
    '''
    if(DEBUG):
        print("sentences",sentences)
    '''
    for i in sentences:
        words=i.split('<--')
        # i contains head and other atoms
        if(len(words)!=2):
            print("Error: ",filename," is not a valid knowledge base")
            return False
        # first element in i is head
        temp=words[0].strip()
        #check if it is atom
        if(is_atom(temp)==False):
            print("Error: ",filename," is not a valid knowledge base")
        head=temp
        '''
        if(DEBUG):
            print("words",words)
        '''
        # translate a<--b&c into [a,[b,c]] and store it in kb
        atoms_list=words[1]
        temp_premises=atoms_list.split('&')
        # remove leading and trailing whitespaces
        premises=[]
        for j in temp_premises:
            #check if it is atom
            temp=j.strip()
            #remove empty entry
            if(temp==""):
                continue
            if(is_atom(temp)==False):
                print("Error: ",filename," is not a valid knowledge base")
                return False
            premises.append(temp)
        if(premises==[]):
            print("Error: ",filename," is not a valid knowledge base")
            return False
        kbInline=[head,premises]
        kb.append(kbInline)

    for i in sentences:
        print(i)
    print('\n')
    print(len(sentences)," new rule(s) added")
    print('\n')
        
    '''
    if(DEBUG):  
        print("kb",kb)
    '''

def tell(knowledge):
    global my_kb
    my_kb_temp=copy.deepcopy(my_kb)

    # split each atom
    temp=knowledge
    temp_premises=temp.split(' ')
    '''
    if(DEBUG):
        print("temp_premises in tell",temp_premises)
    '''
    # remove leading and trailing whitespaces
    premises=[] # store input atoms
    for j in temp_premises:
        #check if it is atom
        temp=j.strip()
        #remove empty entry
        if(temp==""):
            continue
        if(is_atom(temp)==False):
            print("Error: ",temp," is not a valid atom")
            return False
        premises.append(temp)
    if(premises==[]):
        print("Error: tell needs at least one atom")
        return False
    
    for atm in premises:
        inferred_list=infer_all(my_kb_temp)
        '''
        # if atm can be inferred by other atoms, atm can only be added if other atoms have been added
        for entry in kb:
            if(atm in my_kb):
                break
            elif(atm in entry[0]):
                for pre_req in entry[1]:
                    if not (pre_req in my_kb_temp or pre_req in inferred_list):
                        print(atm,"is aborted. Prerequisite atom has not been told")
                        return False
        
        inferred_list=infer_all(my_kb_temp)
        '''
        # check if atom has already added
        for entry in kb:
            if atm in inferred_list:
                print("atom ",atm," already known to be true")
                break
            elif (atm in entry[0] or atm in entry[1]) and not(atm in my_kb_temp or atm in inferred_list):
                print(atm," added to KB")
                my_kb_temp.append(atm)# add into my_kb_temp
                break
            
    print('\n')
    
    my_kb=copy.deepcopy(my_kb_temp)# add into my_kb if no error
    return True

def infer_all(input_kb):
    global inferred_atoms
    inferred_atoms=[]
    my_kb_before=copy.deepcopy(input_kb)# store atom already know to be true before infer_all
    my_kb_temp=copy.deepcopy(input_kb)
    inferred_comparison=['']
    # loop until no more inferred atom has been added
    while(inferred_atoms!=inferred_comparison):
        inferred_comparison=copy.deepcopy(inferred_atoms)
        for entry in kb:
            # if atoms in my_kb satisfy all prerequisite in one rule, then the corrsponding head could be inferred
            if (entry[0] in my_kb_temp) or (entry[0] in inferred_atoms):
                continue
            current_prereq=[]
            for atm in entry[1]:
                if atm in my_kb_temp:
                    current_prereq.append(atm)
            if current_prereq==entry[1]:
                inferred_atoms.append(entry[0])
                my_kb_temp.append(entry[0])
                
    return inferred_atoms
    #print("Newly inferred atoms:/n",inferred_atoms)
    #print("Atoms already known to be true:/n",my_kb_before)

def print_infer():
    my_kb_before=copy.deepcopy(my_kb)
    global inferred_atoms
    print("Newly inferred atoms:")
    if inferred_atoms==[]:
        print(" <none>")
    else:
        for atm in inferred_atoms:
            my_kb.append(atm)
            print(atm,end=" ")
        print('\n')
    print("Atoms already known to be true:")
    if my_kb_before==[]:
        print(" <none>")
        print('\n')
    else:
        for atm in my_kb_before:
            print(atm,end=" ")
        print('\n')
    return True

        
# returns True if, and only if, string s is a valid variable name
def is_atom(s):
    if not isinstance(s, str):
        return False
    if s == "":
        return False
    return is_letter(s[0]) and all(is_letter(c) or c.isdigit() for c in s[1:])

def is_letter(s):
    return len(s) == 1 and s.lower() in "_abcdefghijklmnopqrstuvwxyz"


def find_arg(cmd,func_name):
    arg=""
    for i in range(len(func_name)+1, len(cmd)):
        arg+=cmd[i]
    return arg
    
def myInterpreter():
    need_help=1
    while(True):
        if(need_help):
            print("Enter myhelp to get a list of commands.")
            need_help=0
        cmd=input("kb> ")
        if cmd.find("load")==0:
            myInit()
            load(find_arg(cmd,"load"))
        elif cmd.find("tell")==0:
            tell(find_arg(cmd,"tell"))
        elif cmd=="infer_all":
            infer_all(my_kb)
            print_infer()
        elif cmd=="quit" or cmd == "exit":
            break
        elif cmd=="clear_atoms":
            clear_atoms()
        elif cmd=="print_kb":
            print_kb()
        elif cmd=="myhelp":
            print("Command list: load (filename), infer_all, tell(atoms), quit, exit, clear_atoms, print_kb")
        else:
            print("Unknown Command: ",cmd)
    

if __name__ == '__main__':
    myInterpreter()
