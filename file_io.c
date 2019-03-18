#include <stdio.h>


int main() {
    FILE* fp;
    // open
    if ((fp = fopen("test.dat", "w+")) == NULL) {
        printf("can't open file");
    }

    // close
    fclose(fp);

    // char io
    char c;
    c = fgetc(fp);
    fputc(c, fp);

    // string io
    char (*p)[10];
    fgets(p, 10, fp); // 输入长度可以小于10， 提前结束
    fputs(p, fp);

    // format string io
    int d;
    char p[10];
    fprintf(fp, "%d %s", 10, "yes");
    fscanf(fp, "%d %s", &d, p);

    // binary io
    fread(p, 1, 10, fp);
    fwrite(p, 1, 10, fp);

    // random access
    rewind(fp);
    fseek(fp, 100L, 0);

    // error
    int any_error = ferror(fp); // 0 okay, otherwise error
    clearerr(fp);
}
