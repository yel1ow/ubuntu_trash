#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

int (*f)(int);

bool init_library(const char *lib, const char *name)
{
	void *hdl = dlopen(lib, RTLD_LAZY);
	if(hdl == NULL)
		return false;
	f = (int (*)(int))dlsym(hdl, name);
	if(f == NULL)
		return false;
	return true;
}


int main(int argc, char *argv[])
{
	if(init_library(argv[1], argv[2]))
	{
		int a = atoi(argv[3]);
		printf("%d\n", f(a));
	}
	return 0;
}
