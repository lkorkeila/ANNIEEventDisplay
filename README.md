ANNIE Event Display Libraries

The following repository contains libraries for viewing a 3D display of
the ANNIE detector.  Examples for utilizing these libraries are also
provided.

The current working version of these libraries was written by Matt
Wetstein's research group at Iowa State University. 

#### ROOT DEPENDENCIES ####

The Eve libraries rely on openGL, and ROOT must be built with the option
to use openGL.  To do this, you must first install the following dependencies
with your favorite package manager:

lib-mesaGL-devel
lib-mesaGLU-devel

Then, go to your root build's directory and run the command

./configure --enable-opengl

Then, go to ROOT's build directory and do:

make

If you're running this in the docker, then it's likely that you'll have some
issue reported regarding exporting your display.  For a linux system, you can add the following flags to your docker run command:

-e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix

Then, adjust your x server permissions using the xhost command.  The simplest option is to run a command like (where $containerId is your running container's ID):

$ xhost local:$containerId
