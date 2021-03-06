/*
 * physics.h
 *
 *  Created on: Jun 6, 2019
 *      Author: Manu Jayadahran
 *      This is the modification of the physics.h file made by ELdar for Elasticity.
 *      FUncion to fetch permeability is also added.
 */

#ifndef INC_PHYSICS_H_
#define INC_PHYSICS_H_

#include <fstream>
#include <deal.II/fe/fe_dgq.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/numerics/data_out.h>
#include <deal.II/numerics/fe_field_function.h>

namespace dd_biot
{
    using namespace dealii;

//    template< class T, class... ARGS >
//       std::unique_ptr<T> make_unique( ARGS&&... my_args )
//       {
//          return std::unique_ptr<T>(new T(std::forward<ARGS>(my_args)...));
//       }

    template<int dim>
    class YoungModulus
    {
    public:
        YoungModulus(const std::string &s, const std::vector<unsigned int> &reps, const std::vector<Point<dim>> &pts);
        double get_value(const Point<dim> &p) const;
        void output_field();
        void output_porosity_field();

    private:
        YoungModulus(const YoungModulus<dim> &ym) = delete;

        Triangulation<dim> tria;
        DoFHandler<dim> dof;
        FE_DGQ<dim> fe;

        std::string filename;
        std::vector<unsigned int> subs;
        std::vector<Point<dim>> corners;

        Vector<double> youngs;
        Vector<double> porosity;
        std::unique_ptr<typename Functions::FEFieldFunction<dim>> func_ptr;
    };

    template <int dim>
    YoungModulus<dim>::YoungModulus(const std::string &s, const std::vector<unsigned int> &reps, const std::vector<Point<dim>> &pts)
            :
            dof(tria),
            fe(0),
            filename(s),
            subs(reps),
            corners(pts)
    {
        GridGenerator::subdivided_hyper_rectangle(tria, subs, corners[0], corners[1]);
        dof.distribute_dofs(fe);

        youngs.reinit(dof.n_dofs());
        porosity.reinit(dof.n_dofs());
        std::ifstream data (filename);

        unsigned int idx = 0, i = 0;
        std::string line;
        if (data.is_open())
        {
            while (getline(data, line))
            {
                if (idx % 2 != 0)
                {
                    youngs[i] = 1e2*( pow(1-stod(line),2.1) );
                    porosity[i]= stod(line);
                    i++;
                }

                idx++;
            }

            data.close();
        }
        else
            Assert(false, ExcFileNotOpen("Porosity"));


//        func_ptr = std::make_unique<typename Functions::FEFieldFunction<dim>> (dof, youngs);
        func_ptr = std::unique_ptr<typename Functions::FEFieldFunction<dim>>(new Functions::FEFieldFunction<dim> (dof, youngs));
    }


    template <int dim>
    double
    YoungModulus<dim>::get_value(const Point<dim> &p) const
    {
        //return 1e7*pow((1-func_ptr->value(p)),2.1);
        return func_ptr->value(p);
    }

    template <int dim>
    void
    YoungModulus<dim>::output_field()
    {
        DataOut<dim> data_out;
        data_out.attach_dof_handler(dof);
        data_out.add_data_vector(youngs, "youngs_modulus", DataOut<dim>::type_dof_data);

        data_out.build_patches();

        std::ofstream out("youngs_modulus.vtk");
        data_out.write_vtk(out);
    }
    template <int dim>
    void
    YoungModulus<dim>::output_porosity_field()
    {
        DataOut<dim> data_out;
        data_out.attach_dof_handler(dof);
        data_out.add_data_vector(porosity, "porosity", DataOut<dim>::type_dof_data);

        data_out.build_patches();

        std::ofstream out("porosity_field.vtk");
        data_out.write_vtk(out);
    }

    //-------------------------------------------------------------------------------

    template<int dim>
    class Permeability
    {
    public:
        Permeability(const std::string &s, const std::vector<unsigned int> &reps, const std::vector<Point<dim>> &pts);
        double get_value(const Point<dim> &p) const;
        void output_field();

    private:
        Permeability(const Permeability<dim> &prmblty) = delete;

        Triangulation<dim> tria;
        DoFHandler<dim> dof;
        FE_DGQ<dim> fe;

        std::string filename;
        std::vector<unsigned int> subs;
        std::vector<Point<dim>> corners;

        Vector<double> K_value;
        std::unique_ptr<typename Functions::FEFieldFunction<dim>> func_ptr;
    };

    template <int dim>
    Permeability<dim>::Permeability(const std::string &s, const std::vector<unsigned int> &reps, const std::vector<Point<dim>> &pts)
            :
            dof(tria),
            fe(0),
            filename(s),
            subs(reps),
            corners(pts)
    {
        GridGenerator::subdivided_hyper_rectangle(tria, subs, corners[0], corners[1]);
        dof.distribute_dofs(fe);

        K_value.reinit(dof.n_dofs());
        std::ifstream data (filename);

        unsigned int idx = 0, i = 0;
        std::string line;
        if (data.is_open())
        {
            while (getline(data, line))
            {
                if (idx % 2 != 0)
                {
                    K_value[i] = stod(line);
                    i++;
                }

                idx++;
            }

            data.close();
        }
        else
            Assert(false, ExcFileNotOpen("Permeability"));

//        func_ptr = std::make_unique<typename Functions::FEFieldFunction<dim>> (dof, K_value);
        func_ptr = std::unique_ptr<typename Functions::FEFieldFunction<dim>>(new Functions::FEFieldFunction<dim> (dof, K_value));
    }

    template <int dim>
    double
    Permeability<dim>::get_value(const Point<dim> &p) const
    {
        //return 1e7*pow((1-func_ptr->value(p)),2.1);
        return func_ptr->value(p);
    }

    template <int dim>
    void
    Permeability<dim>::output_field()
    {
        DataOut<dim> data_out;
        data_out.attach_dof_handler(dof);
        data_out.add_data_vector(K_value, "Permeabiity", DataOut<dim>::type_dof_data);

        data_out.build_patches();

        std::ofstream out("permeability_field.vtk");
        data_out.write_vtk(out);
    }
}





#endif /* INC_PHYSICS_H_ */
