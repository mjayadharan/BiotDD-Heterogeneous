# BiotDD-Heterogeneous medium simulator
__Multiscale Mortar Mixed Finite Element Method (MMMFE) simulator for Biot system of poroelasticity with heterogeneous medium from SPE dataset.__  
  
__Note that the latest branch is rectangular_SPE which has the following features:__
- This branch is the one used in the publication/thesis. 
- Derived poros.txt and permx.dat files from the following (https://www.spe.org/web/csp/datasets/set02.htm) . The top layer is used. 
- The jupyter notebook usued for extraction can be found in the folder por_perm_case2a/.
- The poros.txt file is further normalized to get value between 1 and 1.0e+5.
- __220x60__ rectangular subdomain is used. Necessary changes are made in inc/utilities and src/biot_dd.cc files. 

### Note from previous version:
- The simulator is written using deal.ii FE package which is based on C++.  
-  All instructions are with respect to a terminal in linux/mac. Please use the ubuntu sub-system if you are using windows 10. A good installation guide for the linux sub-system can be found [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
- Image/animation processing and visualization can be done using paraview. Installation guide can be found [here.](https://www.paraview.org/Wiki/ParaView:Build_And_Install)

## Author
-----------
Manu Jayadharan, Department of Mathematics at University of Pittsburgh, 2021.

email: [manu.jayadharan@gmail.com](mailto:manu.jayadharan@gmail.com), [manu.jayadharan@pitt.edu](mailto:manu.jayadharan@pitt.edu)  
[reserachgate link](https://www.researchgate.net/profile/Manu_Jayadharan)  
[linkedin profile](https://www.linkedin.com/in/manu-jayadharan/)  

## deal.ii 9.1 requirement (latest at the time)
---------------------------------------
Need deal.ii configured with mpi  to compile and run the simulations. Latest version of dealii can be found at : [https://www.dealii.org/download.html](https://www.dealii.org/download.html)

**deal.ii installation instruction:** Follow readme file to install latest version of deal.ii with `-DDEAL_II_WITH_MPI=ON` flag to cmake. 


## Compilation instructions.
-------------------------------------------
`cmake -DDEAL_II_DIR=/path to dealii installation folder/ .` from the main directory

`make release` for faster compilations

`make debug` for more careful compilations with warnings

`mpirun -n 'j' BiotDD` where j is the number of subdomains(processses)

**Please contact the author for further instructions.**

## Quick start guide for the simulator.
-------------------------------------
* Most of the parameters including number of refinements, mortar_degree, max_number of gmres iterations, final_time, subdomain mesh size
ratio etc are fed to the executable file DarcyVT using parameter.txt in the main folder. This file can simply be modified
without recompiling the program.  
