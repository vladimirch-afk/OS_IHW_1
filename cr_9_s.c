#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#if defined __USE_MISC || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
__THROW __nonnull ((1));
#endif

// Переписать строку
char* rewrite(char string[], int size) {
    int alph_len = 20;
    char alph1[] = "bcdfghjklmnpqrstvwxz";
    char alph2[] = "BCDFGHJKLMNPQRSTVWXZ";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < alph_len; ++j) {
            if (string[i] == alph1[j]) {
                string[i] = alph2[j];
                break;
            }
        }
    }
    return string;
}

const char* first_fifo = "first.fifo";
const char* second_fifo = "second.fifo";
const int buf_size = 16;
int main(int argc, char *argv[]) {
    int chanel1, chanel2;
    int size;
    char buf[buf_size];
    printf("Second program is working and waiting for data\n");
    mknod(first_fifo, S_IFIFO | 0666, 0);
    mknod(second_fifo, S_IFIFO | 0666, 0);

    if ((chanel1 = open(first_fifo, O_RDONLY)) < 0) {
        printf("Cant open FIFO for reading\n");
        exit(-1);
    }
    if ((chanel2 = open(second_fifo, O_WRONLY)) < 0) {
        printf("Cant open FIFO for writing\n");
        exit(-1);
    }
    // Получаем данные из первого процесса во втором
    while ((size = read(chanel1, buf, buf_size)) > 0) {
        // Заменяем согласные буквы в строке на заглавные
        char *answer = rewrite(buf, size);

        // Передаем данные в первый процесс
        int size_w = write(chanel2, answer, size);

        if (size_w != size) {
            printf("Can't write string to FIFO\n ");
            exit(-1);
        }
    }
    if (size < 0) {
        printf("Cant read from FIFO\n");
        exit(-1);
    }
    if(close(chanel2) < 0) {
        printf("2nd process can't close FIFO for writing\n");
        exit(-1);
    }
    if (close(chanel1) < 0) {
        printf("2nd process can't close FIFO for reading\n");
        exit(-1);
    }
    return 0;
}
