/**
 * @file This file is part of EDGE.
 *
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section LICENSE
 * Copyright (c) 2020, Friedrich Schiller University Jena
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 * Expression-based velocity model using an input grid.
 **/
#ifndef EDGE_V_MODELS_GRID_EXPRESSION_H
#define EDGE_V_MODELS_GRID_EXPRESSION_H

#include "../io/Grid.h"
#include "Model.h"

namespace edge_v {
  namespace models {
    class GridExpression;
  }
}

/**
 * Velocity model using grid data for the evaluation of a runtime velocity expression.
 **/
class edge_v::models::GridExpression: public Model {
  private:
    //! grid
    io::Grid const * m_grid = nullptr;

    //! expression which is evaluated for the speed-computation
    struct {
      std::string str = "0==0;";
      std::string xName = "x";
      std::string yName = "y";
      std::string zName = "z";
      std::string dataName = "data";
      std::string minSpeedName = "min_speed";
      std::string maxSpeedName = "max_speed";
    } m_expr;

    //! minimum wave speeds
    double * m_speedsMin = nullptr;

    //! maximum wave speeds
    double * m_speedsMax = nullptr;

    /**
     * Frees allocated memory.
     **/
    void free();

  public:
    /**
     * Constructor.
     *
     * @param i_grid grid which is used for the expression evaluation.
     * @param i_expr expression which is evaluated.
     */
    GridExpression( io::Grid    const * i_grid,
                    std::string const & i_expr = "" );

    /**
     * Destructor.
     **/
    ~GridExpression();
   
    /**
     * Inits the velocity model at the given points.
     *
     * @param i_nPts number of points.
     * @param i_pts coordinates of the points.
     **/
    void init( t_idx           i_nPts,
               double const (* i_pts)[3] );

    /**
     * Gets the minimum wave speed at a point.
     *
     * @param i_pt point at which the minimum wave speed is derived.
     **/
    double getMinSpeed( t_idx i_pt ) const;

    /**
     * Gets the maximum wave speed at a point.
     *
     * @param i_pt point at which the maximum wave speed is derived.
     **/
    double getMaxSpeed( t_idx i_pt ) const;
};

#endif