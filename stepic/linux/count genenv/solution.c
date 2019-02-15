#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

static char *itoa_helper(char *dest, int i) {
  if (i <= -10) {
    dest = itoa_helper(dest, i/10);
  }
  *dest++ = '0' - i%10;
  return dest;
}

char *itoa(char *dest, int i) {
  char *s = dest;
  if (i < 0) {
    *s++ = '-';
  } else {
    i = -i;
  }
  *itoa_helper(s, i) = '\0';
  return dest;
}

int main()
{
	char *p_name = "genenv";
	int k = 0;
	DIR *dir = opendir("/proc");
	struct dirent *entry;
	while((entry = readdir(dir)) != 0)
	{
		if (entry->d_type && DT_DIR)
		{
			if(entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
			{
				char path[100] = "/proc/";
				char tmp[50];
				strcat(path, entry->d_name);
				strcat(path, "/stat");
				FILE *f = fopen(path, "r");
				long long x;
				fscanf(f, "%lld ", &x);
				char buf[100];
				fscanf(f, "%s ", buf);
				if(strstr(buf, p_name))
					k++;
				//printf("name = %s\n", buf);
			}
		}
	}
	printf("%d\n", k);
	return 0;
}