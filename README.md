
# Terminal Based File Explorer
A file explorer for linux systems that runs on terminal

## Compiling
* run make in the source code directory to compile.

## Running
```
* run ./term
```
It will open explorer in current folder
```
* run ./term <path_to_directory>
```
It will open explorer in specified folder

## Commands
* up, down, left, right, backspace, h keys work as described in assignment. Also 'q' can be used to quit the program.
* : can be used to get into command mode. Bottom line would be available to right command.
* After running one command, the bottom line gets cleared and is ready to accept more commands.
* To exit from command mode : ESC
* To exit from normal mode(project): press 'q' only(No control signals will work in termination).

## Assumptions
* for files containing space in name, use \\ as escape seq. eg to create folder named "Rushit Jasani" in Home dir, 
type : ``` create_dir Rushit\ Jasani ~ ```
* preferable to open in full size terminal. if one record spans over more than one line then navigation won't work correctly.
* if path length is more than 115 to 120 char then navigation may not work properly.
* in command mode, to edit the command, use backspace only.
* if ENTER is pressed on some file and if there is no default application found then there will be no movement.
