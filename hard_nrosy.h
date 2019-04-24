// Copyright (C) 2016 Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef HARD_NROSY
#define HARD_NROSY

#include <Eigen/Core>

Eigen::MatrixXd hard_nrosy
        (
        const Eigen::MatrixXd& V,          // Vertices of the mesh
        const Eigen::MatrixXi& F,          // Faces
        const Eigen::MatrixXi& TT,         // Adjacency triangle-triangle
        const Eigen::VectorXi& hard_id,        //  constraints face ids
        const Eigen::MatrixXd& hard_value,     //  constraints 3d vectors
        const int n                        // Degree of the n-rosy field
        );

#endif
