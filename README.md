# ASP-Based Implementations for Inconsistency Measurement in LTL
### Setup
Simply clone and build the project:
* ```git clone git@github.com:aig-hagen/inconsistency-measurement-LTL.git``` 
* ```cd inconsistency-measurement-LTL```
* ```mkdir build```
* ```cd build```
* ```cmake ..```
* ```make```

### Notes
* To generate a Makefile using cmake the packages bison and re2c need
to be installed, otherwise the clingo library cannot be compiled
* The directory ```data``` contains some example knowledge bases in the correct input format
* The directory ```declare_data``` contains the same knowledge bases as ```data```, but in Declare format. 

### Usage
```./im_app <path_to_file> <im> <m>```
* ```<path_to_file>```: path to knowledge base
* ```<im>```: inconsistency measure (```contension-ltl``` or ```drastic-ltl```)
* ```<m>```: number of final state

Example: ```./im_app ../data/bpi_2012_75_12-5_12-5LTL.txt contension-ltl 5```