ANNIE Event Display Libraries

The following repository contains libraries for viewing a 3D display of
the ANNIE detector.  Examples for utilizing these libraries are also
provided.

#### ROOT DEPENDENCIES ####

The Eve libraries rely on openGL, and ROOT must be built with the option
to use openGL.  To do this, run the command

root-config --enable-opengl

Then, go to ROOT's build directory and do:

make


