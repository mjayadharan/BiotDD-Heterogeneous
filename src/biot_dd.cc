/* ---------------------------------------------------------------------
 This program implements DD for Biot problem with three different schemes:
 Monilithic(split_flag=0), Drained Split(split_flag=1), Fixed Stress(split_flag=2).
 This particular example refers to example 3 in the draft of the publications on the topic with Authors: Manu J, Eldar K, Ivan Yotov
 Here we use a  heterogeneous porosity and permeability field from the society of petroleum enginner's comparitive solution project.
 The  motor simulation functionality(From the original program written by Eldar for Elasticity) is redacted.
 * ---------------------------------------------------------------------
 *
 * Author: Manu Jayadharan, University of Pittsburgh 2019
 * Derived from code written  by: Eldar Khattatov, University of Pittsburgh, 2016 - 2017
 */

// Utilities, data, etc.
#include "../inc/biot_mfedd.h"

// Main function is simple here
int main (int argc, char *argv[])
{
    try
    {
        using namespace dealii;
        using namespace dd_biot;

        MultithreadInfo::set_thread_limit(4);
        Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv, 1);

        // Mortar mesh parameters   (non-matching checkerboard)
        unsigned int h_size;
        unsigned int mortar_h_size;
        h_size = 2*2; //gives h= 1/128 with 64 subdomains
        mortar_h_size = 2; //gives H = 1/16 with 64 subdomains

        std::vector<unsigned int> x_y_refinement(2);
        x_y_refinement = {h_size, h_size};
//        std::vector<std::vector<unsigned int>> mesh_m2d(17, x_y_refinement);
        std::vector<std::vector<unsigned int>> mesh_m2d(5);

        mesh_m2d[0] = {20, 44};
        mesh_m2d[1] = {h_size, h_size};
        mesh_m2d[2] = {h_size, h_size};
        mesh_m2d[3] = {h_size, h_size};
        mesh_m2d[4] = {1, 1};

//        mesh_m2d[mesh_m2d.size() - 1] = {mortar_h_size, mortar_h_size}; //mortar mesh (last elemtn)


        DataStruct<2> ds;
		ds.name = "poros.txt";
		ds.name2="permx.dat";
		ds.reps.push_back(60);
		ds.reps.push_back(220);
		ds.pts.push_back(Point<2>(0,0));
		ds.pts.push_back(Point<2>(60,220));
        double c0=1;
        double alpha=1;
        int num_cycle=1;
        int max_itr=4000;
        double tolerence = 1.e-6;
        BiotParameters bparam (0.01,100,c0,alpha);
//        MixedBiotProblemDD<2> drained_split(1,ds, bparam,0,0,1,1);
//        MixedBiotProblemDD<2> fixed_stress(1,ds,bparam,0,0,2,1);
//        MixedBiotProblemDD<2> monolithic(1,ds,bparam,0,0,0,1);

//        drained_split.run (num_cycle, mesh_m2d, tolerence, max_itr);
//        fixed_stress.run(num_cycle, mesh_m2d, tolerence, max_itr);
//        monolithic.run (num_cycle, mesh_m2d, tolerence, max_itr);

        //BiotDD with mortar
//	   MixedBiotProblemDD<2> lin_mortar(1,ds,bparam,1,1,0,1);
        MixedBiotProblemDD<2> quad_mortar(1,ds,bparam,1,2,0,1);
//        MixedBiotProblemDD<2> cubic_mortar(1,ds,bparam,1,3,0,1);

//	   lin_mortar.run(num_cycle,mesh_m2d,tolerence,max_itr);
        quad_mortar.run(num_cycle,mesh_m2d,tolerence,max_itr);
//        cubic_mortar.run(num_cycle,mesh_m2d,tolerence,max_itr);

	   //Biot Mortar with multi-scale basis construction
//        MixedBiotProblemDD<2> lin_mortar_mscale(1,ds,bparam,2,1,0,1);
//        lin_mortar_mscale.run(num_cycle,mesh_m2d,tolerence,max_itr);
    }
    catch (std::exception &exc)
    {
        std::cerr << std::endl << std::endl
                  << "----------------------------------------------------"
                  << std::endl;
        std::cerr << "Exception on processing: " << std::endl
                  << exc.what() << std::endl
                  << "Aborting!" << std::endl
                  << "----------------------------------------------------"
                  << std::endl;

        return 1;
    }
    catch (...)
    {
        std::cerr << std::endl << std::endl
                  << "----------------------------------------------------"
                  << std::endl;
        std::cerr << "Unknown exception!" << std::endl
                  << "Aborting!" << std::endl
                  << "----------------------------------------------------"
                  << std::endl;

        return 1;
    }

    return 0;
}
