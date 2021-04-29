# BiotDD-Heterogeneous mediuam simulator
DD repository for heterogeneous BC. 
__Repository corresponding to BiotDD2 MMMFE method for Biot system of poroelasiticity__
- This branch is the one used in the publication/thesis. 
- Derived poros.txt and permx.dat files from the following (https://www.spe.org/web/csp/datasets/set02.htm) . The top layer is used. 
- The jupyter notebook usued for extraction can be found in the folder por_perm_case2a/.
- The poros.txt file is further normalized to get value between 1 and 1.0e+5.
- __220x60__ rectangular subdomain is used. Necessary changes are made in inc/utilities and src/biot_dd.cc files. 
