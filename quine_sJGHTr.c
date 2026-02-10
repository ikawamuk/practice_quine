#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
char *s = "#define _GNU_SOURCE%c#include <stdlib.h>%c#include <stdio.h>%c#include <unistd.h>%cint main()%c{%cchar *s = %c%s%c;%cchar fn[] = %c./quine_XXXXXX.c%c;%cint fd = mkstemps(fn, 2);%cFILE *fp = fdopen(fd, %cw%c);%cfprintf(fp, s, 10, 10, 10, 10, 10, 10, 34, s, 34, 10, 34, 34, 10, 10, 34, 34, 10, 10, 10, 10, 10);%cfclose(fp);%creturn 0;%c}%c";
char fn[] = "./quine_XXXXXX.c";
int fd = mkstemps(fn, 2);
FILE *fp = fdopen(fd, "w");
fprintf(fp, s, 10, 10, 10, 10, 10, 10, 34, s, 34, 10, 34, 34, 10, 10, 34, 34, 10, 10, 10, 10, 10);
fclose(fp);
return 0;
}
