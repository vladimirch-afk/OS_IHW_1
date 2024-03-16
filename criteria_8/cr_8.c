#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#if defined __USE_MISC || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
__THROW __nonnull ((1));
#endif

const char* first_fifo = "first.fifo";
const char* second_fifo = "second.fifo";
const int buf_size = 5000;
int main(int argc, char *argv[]) {
    int chanel1, chanel2;
    int size;
    char buf[buf_size];
    if(argc != 3){
        printf("Enter these args when starting program: <./program.out> <input.txt> <output.txt>\n");
        return 0;
    }
    mknod(first_fifo, S_IFIFO | 0666, 0);
    mknod(second_fifo, S_IFIFO | 0666, 0);
    if ((chanel1 = open(first_fifo, O_WRONLY)) < 0) {
        printf("Cant open FIFO for writing\n");
        exit(-1);
    }
    int file_r;
    if((file_r = open(argv[1], O_RDONLY , 0666)) < 0) {
        printf("Cant open file to read\n");
        exit(-1);
    }
    // Читаем содержимое файла
    size = read(file_r, buf, buf_size);
    if(close(file_r) < 0) {
        printf("Cant close input file\n");
    }
    // Передаем данные из первого процесса во второй
    int size_w = write(chanel1, buf, size);
    if(size_w != size){
        printf("Cant write to FIFO\n");
        exit(-1);
    }
    if (close(chanel1) < 0) {
        printf("Cant close FIFO");
        exit(-1);
    }

    if ((chanel2 = open(second_fifo, O_RDONLY)) < 0) {
        printf("Cant open FIFO for writing\n");
        exit(-1);
    }
    // Получаем данные из второго процесса
    size = read(chanel2, buf, buf_size);
    if(size < 0){
        printf(" 1st process can't read string from the pipe\n");
        exit(-1);
    }

    if(close(chanel2) < 0){
        printf("1st process can't close reading side of the pipe\n");
        exit(-1);
    }
    int file_w;
    // Открыть файл для записи ответа
    if((file_w = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) {
        printf("Cant open the output file\n");
        exit(-1);
    }
    printf("%s \n", buf);
    size_w = write(file_w, buf, size);
    if(size_w != size) {
        printf("Can't write string to file\n");
        exit(-1);
    }
    if(close(file_w) < 0) {
        printf("Cant close the output file\n");
    }
    return 0;
}

