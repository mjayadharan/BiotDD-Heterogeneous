# BiotDD-Heterogeneous medium simulator
__Multiscale Mortar Mixed Finite Element Method (MMMFE) simulator for Biot system of poroelasticity with heterogeneous medium from SPE dataset.__
DD repository for heterogeneous BC. 
# Latest branch is rectangular_SPE which has the following features: 
- This branch is the one used in the publication/thesis. 
- Derived poros.txt and permx.dat files from the following (https://www.spe.org/web/csp/datasets/set02.htm) . The top layer is used. 
- The jupyter notebook usued for extraction can be found in the folder por_perm_case2a/.
- The poros.txt file is further normalized to get value between 1 and 1.0e+5.
- __220x60__ rectangular subdomain is used. Necessary changes are made in inc/utilities and src/biot_dd.cc files. 
