// hello_world.cpp
// This program prints "Hello World"
#include <stdio.h> //including files
#include <string>
int main(int argc, char *argv[]) //main function
{
	// braces delimit a code block
	std::string message = "Hello World!";
	printf("%s",message.c_str()); // casting
	return 0;
	// return value to shell
}
