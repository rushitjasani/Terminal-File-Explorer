@author - Rushitkumar Jasani   @rollno - 2018201034

Compilation steps : run makefile in the directory where source file are present.
to run project :./term

Aim of the project is to implement terminal based file explorer
which gives user navigation facility, search facility many more
file operations e.g. create, delete, move, rename etc.
To exit from command mode : ESC
To exit from normal mode(project): press 'q' only.
(No control signals will work in termination)

Assumptions :
-> for files containing space in name, use '\' as escape seq.
   eg to create folder named "Rushit Jasani" in Home dir, type :
   create_dir Rushit\ Jasani ~
-> preferable to open in full size terminal. if one record spans
   over more than one line then navigation won't work correctly.
-> if path length is more than 115 to 120 char then navigation
   may not work properly.
-> in command mode, to edit the command, use backspace only.
-> if ENTER is pressed on some file and if there is no default
   application found then there will be no movement.
