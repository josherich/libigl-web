// g++ -O3 -DNDEBUG -DMATSIZE=<x> benchmark.cpp -o benchmark && time ./benchmark

#include <iostream>

#include <Eigen/Core>

#ifdef __EMSCRIPTEN__
    #include <GLES2/gl2.h>
    #include <emscripten.h>
    #include <emscripten/threading.h>
    #include <emscripten/html5.h>
#endif

#include <igl/readOFF.h>
#include <igl/readCSV.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/opengl/glfw/Viewer.h>

#include "hard_nrosy.h"

#ifndef MATSIZE
#define MATSIZE 3
#endif

using namespace std;
using namespace Eigen;

#ifndef REPEAT
#define REPEAT 4
#endif

#ifndef SCALAR
#define SCALAR double
#endif

#ifdef __EMSCRIPTEN__
static void create_webgl_context()
{
       EmscriptenWebGLContextAttributes attr;
       emscripten_webgl_init_context_attributes(&attr);
       attr.majorVersion = 2; attr.minorVersion = 0;
       EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(0, &attr);
       emscripten_webgl_make_context_current(ctx);
       printf("created webgl context\n");
}
#endif

Eigen::MatrixXd V;
Eigen::MatrixXi F;

Eigen::MatrixXi TT;
Eigen::MatrixXi TTi;

// constraint points
Eigen::MatrixXd VC;
Eigen::VectorXi IC;

// vector field
Eigen::MatrixXd R;

// Constrained faces id
Eigen::VectorXi b;

// Cosntrained faces representative vector
Eigen::MatrixXd bc;

igl::opengl::glfw::Viewer viewer;

int N;

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
    return true;
}

bool mouse_down(igl::opengl::glfw::Viewer& viewer, int, int)
{
    return false;
}

int main(int argc, char *argv[])
{
    #ifdef __EMSCRIPTEN__
        create_webgl_context();
    #endif
    N = 1;
    std::string shape = "data/hand.off";
    std::string constraints = "data/irr4-cyl2.constraints";

    igl::readOFF(shape, V, F);
    igl::readCSV(constraints, VC);

    igl::triangle_triangle_adjacency(F,TT,TTi);

    b.resize(VC.rows());
    b = VC.transpose().row(0).cast<int>();

    bc.resize(VC.rows(), 3);
    bc.col(0) = VC.col(1);
    bc.col(1) = VC.col(2);
    bc.col(2) = VC.col(3);

    R = hard_nrosy(V,F,TT,b,bc,N);

    viewer.data().set_mesh(V, F);

    viewer.callback_key_down = &key_down;
    viewer.callback_mouse_down = &mouse_down;
    viewer.data().show_lines = true;

    viewer.launch();

    return 0;
}
