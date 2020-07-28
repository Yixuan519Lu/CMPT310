Those atoms are the requirement for me to assemble my desktop PC. The desktop PC may not work without any of the atom.
Also, I can use those rules to help me to change any parts of computer.

As I mention in q1, enter myhelp will get a list of valid commands including load (filename), infer_all, tell(atoms), quit, exit, clear_atoms, print_kb.

1. kb> load a4_q2_kb.txt will output all rules in 4_q2_kb.txt and total number of rules added.
When load a new KB file, old KB and all atoms told before will delete.

Example:
kb> tell water_cooling_fans rbg_ram will output: 
water_cooling_fans  added to KB
rbg_ram  added to KB

2. When tell atom that is already in the KB due to a previous tell command, or because it was inferred by the rules will output atom X already known to be true.

Example:
kb> tell fans 
atom  fans  already known to be true

Any invalid input of tell command will output corresponding error as requirement in A4.

Example:
kb> tell 4396
Error:  4396  is not a valid atom

3. Infer_all will print all the atoms that can currently be inferred by the rules in the KB.
If no newly atoms inferred or no atoms already know to be true then <none> will be printed.

Example:
(before load a4_q2_kb.txt) 
kb> infer_all
Newly inferred atoms:
 <none>
Atoms already known to be true:
 <none>

kb> load a4_q2_kb.txt
......
kb> tell water_cooling_fans rbg_ram
......
kb> infer_all 
Newly inferred atoms:
fans ram 

Atoms already known to be true:
water_cooling_fans rbg_ram 

4. clear_atoms will removes all atoms.

Example:
kb> infer_all
Newly inferred atoms:
 <none>
Atoms already known to be true:
water_cooling_fans rbg_ram fans ram 

kb> clear_atoms
kb> infer_all
Newly inferred atoms:
 <none>
Atoms already known to be true:
 <none>

5. print_kb will print current KB.

6. Enter quit or exit to terminate program.

