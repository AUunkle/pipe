PIPE - project
Pipe containe two console projects: Server and Client.

This projects were build in MSVC 2017

Curently all options of pipes are hardcoded. 

For the demonstration projects you have to 
 - build them in MSVC or any other IDE/compilers which are suported  C++17.
 - put the "taskList.dat" from the repo in the same folder with Client.exe,
       or create it manualy.
 - Server should be run first, in other case Client will be closed by exeption.

Transmition of the data doing in two modes sync and async.
Every time when Server or Client resived any message, or define error, they logged about it in console 



Description of "taskList.dat" file
format of the "taskList.dat" must be the next one
 - every task should be placed in one line,
 - all params should be separate with space symbol 
 - struct of the task is
         <MODE> <TYPE> <DATA> 
   MODE - can be "sync" or "async",
   TYPE - "Char", "Int32", "Double"
   DATA - should be symbol or digits any amount, but all data in one line should be the one type. 

Yuo can use like example "taskList.dat" file from the repo.


 

