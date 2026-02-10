#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	char *s = \
	"#define _GNU_SOURCE%c"\
	"#include <stdlib.h>%c"\
	"#include <stdio.h>%c"\
	"#include <unistd.h>%c"\
	"int main()%c"\
	"{%c"\
	"char *s = %c%s%c;%c"\
	"char fn[] = %c./quine_XXXXXX.c%c;%c"\
	"int fd = mkstemps(fn, 2);%c"\
	"FILE *fp = fdopen(fd, %cw%c);%c"\
	"fprintf(fp, s, 10, 10, 10, 10, 10, 10, 34, s, 34, 10, 34, 34, 10, 10, 34, 34, 10, 10, 10, 10, 10);%c"\
	"fclose(fp);%c"\
	"return 0;%c"\
	"}%c";
    char fn[] = "./quine_XXXXXX.c";
    int fd = mkstemps(fn, 2);
    FILE *fp = fdopen(fd, "w");

    fprintf(fp, s, 
        10, 10, 10, 10,  /* header */
		10, 10,          /* main */
        34, s, 34, 10,   /* char *s = (...) */
        34, 34, 10,      /* char fn[] =  */
		10,              /* int fd, */
		34, 34, 10,      /* FILE *fp */
		10,              /* fprintf */
		10,              /* fclose */
		10,              /* return 0;*/
		10               /* } */
    );
    fclose(fp);
    return 0;
}