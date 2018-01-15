# Frequent Subgraph Mining

### Description
The program implements FFSM algorithm from paper [1]. Basically, it finds 
frequent patterns that occur in given graph database and send it out 
to standard output.

Input: It accepts an integer as a minsup and a database of graphs from 
standard input. 

Output: It prints out frequent graphs to standard output.

## Note
In the program, frequency of a pattern is defined as total number of its 
instance in all the graphs. That means one graph may contain multiple 
number of the same pattern. And one node in an instance of a subgraph 
could form another instance of the same subgraph as well. That is to say, 
two instances of a same pattern in a graph may have overlapping nodes 
and edges. Subgraphs whose frequency is larger or equal to minsup is 
considered as frequent pattern.

There is also another widely accepted technology that counts frequency as 
the number of graphs that contain certain subgraph. The method is included 
in the source code of this project as well. Please contact me if need 
further detail.

The frequent patterns is send to standard output in the form of both matrix 
and canonical label. 


[1]: Huan, Jun, Wei Wang, and Jan Prins. "Efficient mining of frequent subgraphs in the presence of isomorphism." Data Mining, 2003. ICDM 2003. Third IEEE International Conference on. IEEE, 2003. ([pdf](http://www.cs.unc.edu/techreports/03-021.pdf))









