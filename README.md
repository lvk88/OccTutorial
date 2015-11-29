# OccTutorial
This repository contains a set of tutorials for OpenCASCADE, the open source geometry kernel.
You can read more about OpenCASCADE at http://www.opencascade.org

## Quick start
The tutorials are being written and tested in Ubuntu 15.10. For the quickest start, it is therefore recommended to follow the tutorials using Ubuntu. 

### What if I am using Windows?
The easiest way is to install Ubuntu as a VirtualBox guest on your Windows machine, which will give you access to a fully
functioning Ubuntu operating system. Make sure you also install the guest additions, to have 3D acceleration enabled.

## Install OpenCASCADE
Install OpenCASCADE using your the package manager of your Linux distribution. For example, on Ubuntu:
<pre>
sudo apt-get install liboce-*
</pre>
To be able to visualize the geometric models in the earlier chapters, it is also recommended to install FreeCAD:
<pre>
sudo apt-get install freecad
</pre>

## Download the tutorial sources
Make a folder for the tutorial sources, e.g. in your home folder
<pre>
cd ~
mkdir occtutorial
mkdir occtutorial/sources
</pre>
Then, clone the repository from GIT:
<pre>
cd ~/occtutorial/sources
git clone https://github.com/lvk88/OccTutorial.git
</pre>
This will create @~/occtutorial/sources/OccTutorial@.

##Build the tutorial
The build system is based on CMAKE, and we are aiming for an out-of-source build. Therefore, we make a build folder:
<pre>
mkdir ~/occtutorial/build
</pre>
Next, we run CMAKE to generate us the Makefiles:
<pre>
cd ~occtutorial/build/
cmake ~/occtutorial/sources/OccTutorial
</pre>
If everything went without error, we can build the tutorials:
<pre>
cd ~/occtutorial/build
make
</pre>
This will build the tutorials into build/bin directory. Each executable represents a small example of OpenCASCADE functionality.
##Run the first demonstrative example
Now that the tutorials

##How are the tutorials organized
The series is organized into Chapters, with each chapter focusing on one or two packages of OpenCASCADE. With the exception of Chapter0, every chapter
consists of an "inc", "src", and "runners" folder. Obviously, inc contains the headers for the given chapter, src the source files. Runners is a special
folder, which contains a set of driver files, each having its own main function. When building OccTutorials, the executable output will be compiled into 
@build/bin@


