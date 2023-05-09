User Guide:
Installation
Linux (C++):
The Linux version of the maze solver uses SDL to handle all graphical elements.  The SDL library can be installed with the provided “install_sdl.sh” script.
To compile, simply use the provided Makefile with the “make” command.
To execute the solver, use the standard “./maze” command.

Windows (Python):
The Windows version of the maze solver uses the PyGame library. PyGame can be installed either with the provided install script, or with the command “python3 -m pip install -U pygame –user”.  There is a rare issue where PyGame will not install using the previous command. In that case, you may have to use “py -m pip install -U pygame –user”.
Once PyGame is installed, the solver can be executed with the “./maze.py” or “python3 maze.py” command.

Running the Program
Regardless of which version is installed, using the solver is the same.  Upon running the program, the user is presented with a simple UI. Here, a maze size can be chosen. Each number (5, 10, 25, 50) refers to the dimension size of the matrix, i.e. selecting 10 will result in a 10x10 maze. Once a maze size is selected, a randomly generated maze is drawn, and a new set of options appears. These allow the user to select a path finding algorithm.  After selecting an algorithm, the solver provides a visual representation of the execution of the algorithm and draws the optimal path. At this point a new algorithm or a new maze size can be chosen. At any point, the solver can be exited by clicking the red “Quit” button at the top of the UI.

Bugs
Linux version occasionally doesn’t draw maze size buttons
