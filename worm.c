#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int count = (argc > 1) ? atoi(argv[1]) : 10;
    if (count <= 0)
    {
        printf("Generation limit reached. Stopping.%c", 10);
        return (0);
    }

    char *s = \
    "#define _GNU_SOURCE%c#include <stdlib.h>%c#include <stdio.h>%c#include <unistd.h>%c"\
    "int main(int argc, char *argv[]){"\
    "int count = (argc > 1) ? atoi(argv[1]) : 10;"\
    "if (count <= 0) { printf(%cGeneration limit reached. Stopping.%%c%c, 10);return (0);}"\
    "char *s = %c%s%c;"\
    "char fn[] = %c./worm_XXXXXX.c%c; int fd = mkstemps(fn, 2); FILE *fp = fdopen(fd, %cw%c);"\
    "fprintf(fp, s, 10, 10, 10, 10, 34, 34, 34, s, 34, 34, 34, 34, 34, 34, 34, 34, 34);"\
    "fclose(fp); char cmd[256];"\
    "sprintf(cmd, %ccc %%s -o %%s.out && ./%%s.out %%d%c, fn, fn, fn, count - 1); system(cmd);"\
    "printf(%cwarm has been born (Gen: %%d)%%c%c, count, 10); return 0;}";

    char fn[] = "./worm_XXXXXX.c";
    int fd = mkstemps(fn, 2);
    FILE *fp = fdopen(fd, "w");

    /* fprintfの引数の順番をs内の%cと完全に一致させています */
    fprintf(fp, s, 
        10, 10, 10, 10,     /* header */
        34, 34,             /* count ベースケース*/
        34, s, 34,          /* char *s = (...) */
        34, 34, 34, 34,     /* fn, fd, fp difinition */
        34, 34,             /* cmd, sprintf*/
        34, 34
    );
    fclose(fp);
    char cmd[256];
    sprintf(cmd, "cc %s -o %s.out && ./%s.out %d", fn, fn, fn, count - 1);
    system(cmd);
    printf("warm has been born (Gen: %d)\n", count);
    return 0;
}
