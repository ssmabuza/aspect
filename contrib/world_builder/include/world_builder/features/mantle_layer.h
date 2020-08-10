/*
  Copyright (C) 2018 - 2020 by the authors of the World Builder code.

  This file is part of the World Builder.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _world_feature_features_mantle_layer_h
#define _world_feature_features_mantle_layer_h

#include <world_builder/features/interface.h>
#include <world_builder/world.h>

#include <world_builder/features/mantle_layer_models/temperature/interface.h>
#include <world_builder/features/mantle_layer_models/composition/interface.h>
#include <world_builder/features/mantle_layer_models/grains/interface.h>


namespace WorldBuilder
{
  namespace Features
  {
    /**
     * This class represents a mantle layer and can implement submodules
     * for temperature and composition. These submodules determine what
     * the returned temperature or composition of the temperature and composition
     * functions of this class will be.
     */
    class MantleLayer : public Interface
    {
      public:
        /**
         * constructor
         */
        MantleLayer(WorldBuilder::World *world);

        /**
         * Destructor
         */
        ~MantleLayer();

        /**
         * declare and read in the world builder file into the parameters class
         */
        static
        void declare_entries(Parameters &prm,
                             const std::string &parent_name = "",
                             const std::vector<std::string> &required_entries = {});

        /**
         * declare and read in the world builder file into the parameters class
         */
        void parse_entries(Parameters &prm) override final;



        /**
         * Returns a temperature based on the given position, depth in the model,
         * gravity and current temperature.
         */
        double temperature(const Point<3> &position,
                           const double depth,
                           const double gravity,
                           double temperature) const override final;


        /**
         * Returns a value for the requests composition (0 is not present,
         * 1 is present) based on the given position, depth in the model,
         * the composition which is being requested and the current value
         * of that composition at this location and depth.
         */
        double composition(const Point<3> &position,
                           const double depth,
                           const unsigned int composition_number,
                           double value) const override final;


        /**
         * Returns a grains (rotation matrix and grain size)
         * based on the given position, depth in the model,
         * the composition which is being requested and the current value
         * of that composition at this location and depth.
         */
        virtual
        WorldBuilder::grains
        grains(const Point<3> &position,
               const double depth,
               const unsigned int composition_number,
               WorldBuilder::grains value) const override final;



      private:
        /**
         * A vector containing all the pointers to the temperature models. This vector is
         * responsible for the features and has ownership over them. Therefore
         * unique pointers are used.
         * @see Features
         */
        std::vector<std::unique_ptr<Features::MantleLayerModels::Temperature::Interface> > temperature_models;

        /**
         * A vector containing all the pointers to the composition models. This vector is
         * responsible for the features and has ownership over them. Therefore
         * unique pointers are used.
         * @see Features
         */
        std::vector<std::unique_ptr<Features::MantleLayerModels::Composition::Interface> > composition_models;

        /**
         * A vector containing all the pointers to the grains models. This vector is
         * responsible for the features and has ownership over them. Therefore
         * unique pointers are used.
         * @see Features
         */
        std::vector<std::unique_ptr<Features::MantleLayerModels::Grains::Interface> > grains_models;

        double min_depth;
        double max_depth;

    };


  }
}

#endif