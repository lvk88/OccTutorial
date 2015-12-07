# OccTutorial
[![Build Status](https://travis-ci.org/lvk88/OccTutorial.svg?branch=master)](https://travis-ci.org/lvk88/OccTutorial)
This repository contains a set of tutorials for OpenCASCADE, the open source geometry kernel.
You can read more about OpenCASCADE at http://www.opencascade.org. This series consists of chapters,
each chapter demonstrating a small set of features offered by OpenCASCADE. Make sure you also follow
the [blog](https://occtutorials.wordpress.com) where the discussions of each example is published.

## Where to start.
If you are familiar with using CMAKE, GIT, and generally with building and compiling, proceed to the "Quick start" section. If you need a detailed explanation
on how to check out the code, set up an IDE and build the first example, please go to [the setup section](https://github.com/lvk88/OccTutorial/wiki/Setup) in the Wiki.

## Quick start
The tutorials are being written and tested in Ubuntu 15.10. For the quickest start, it is therefore recommended to follow the tutorials using Ubuntu. 

### What if I am a Windows user?
The quick and easy way would be to install an Ubuntu OS inside a Virtualbox on your Windows, e.g. following [this guide.](http://www.psychocats.net/ubuntu/virtualbox) This would give you access to a fully functioning Ubuntu operating system. Make sure you also [install the guest additions](http://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm), so that you will have access to 3D acceleration.

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
This will create ~/occtutorial/sources/OccTutorial.

##Build the tutorial
The build system is based on CMAKE, and we are aiming for an out-of-source build. Therefore, we make a build folder:
<pre>
mkdir ~/occtutorial/build
</pre>
Next, we run CMAKE to generate us the Makefiles:
<pre>
cd ~/occtutorial/build/
cmake ~/occtutorial/sources/OccTutorial
</pre>
If everything went without error, we can build the tutorials:
<pre>
cd ~/occtutorial/build
make
</pre>
This will build the tutorials into build/bin directory. Each executable represents a small example of OpenCASCADE functionality.
##Run the first demonstrative example
Now that the tutorials are built, you can run the first demonstrative example.
<pre>
cd ~/occtutorial/build/bin
./chapter0
</pre>
This will create a simple box with a cylindrical hole, and print out some of its physical properties. The source of this can be found in
source/OccTutorial/Chapter0_Test/chapter0.cpp. It also creates an output file of the geometry in STEP format. You can open and examine it
using FreeCad for example. The file is located in build/bin/boxWitHole.stp

##How are the tutorials organized
The series is organized into Chapters, with each chapter focusing on one or two packages of OpenCASCADE. With the exception of Chapter0, every chapter
consists of an "inc", "src", and "runners" folder. Obviously, inc contains the headers for the given chapter, src the source files. Runners is a special
folder, which contains a set of driver files, each having its own main function. When building OccTutorials, the executable output will be compiled into 
@build/bin@

## Where to go now?
The tutorials are strongly under construction right now, but a detailed explanation of each source will be available at the [blog](https://occtutorials.wordpress.com)
soon. Until then, the comments in the files explain more or less what each example is doing.
