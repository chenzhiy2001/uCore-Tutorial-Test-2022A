#include <unistd.h>
#include <bpf.h>
int main()
{
	sys_bpf(0, NULL, 0);
	// while (1) ;
	return 0;
}
