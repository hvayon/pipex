# __PIPEX__
Pipex is a project that reproduces the behaviour of the shell pipe | command in C

## __How to use__

    git clone https://github.com/hvayon/pipex.git

Go to pipex folder for the mandatory part

    $> cd pipex

or for folder the bonus part

    $> cd pipex_bonus

Build by make

    $> make

## __Mandatory part__

We read from file1, execute cmd1 with file1 as input, send the file2 to cmd2, which will write to cmd2

Program execution

    $> ./pipex file1 cmd1 cmd2 file2

is equivalent to

    $> < file1 cmd1 | cmd2 > file2

## __Bonus part__

Bonus part's program handles __multiple commands__. Program execution

    $> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

is equivalent to

    $> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

I also implemented __heredoc syntax__. It works as follows:

    $> cmd << LIMITER | cmd1 >> file | cmd2 | cmd3 ...


    

