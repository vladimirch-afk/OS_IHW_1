#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

const int buf_size = 5000;
int main(int argc, char *argv[]) {
    int chanel2[2], chanel1[2], res;
    int size;
    char buf[buf_size];
    if(argc != 3){
        printf("Enter these args when starting program: <./program.out> <input.txt> <output.txt>\n");
        return 0;
    }

    // Создаем канал передачи данных во второй процесс
    if(pipe(chanel1) < 0) {
        printf("Can't open pipe\n");
        exit(-1);
    }
    // Создаем канал передачи данных во третий процесс
    if(pipe(chanel2) < 0) {
        printf("Can't open pipe\n");
        exit(-1);
    }

    // Создаем сами процессы
    res = fork();
    if(res < 0) {
        printf("Cant create new process\n");
        exit(-1);
    } else if (res > 0) { // Действия для первого процесса
        if(close(chanel1[0]) < 0){
            printf("Parent process can't close the reading end of the pipe\n");
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
        int size_w = write(chanel1[1], buf, size);
        if(size_w != size){
            printf("Cant write to pipe\n");
            exit(-1);
        }
        if(close(chanel1[1]) < 0) {
            printf("Parent can't close the writing end of the pipe\n");
            exit(-1);
        }
    } else {  // Действия для второго процесса
        // Создаем третий процесс
        int res_p_2 = fork();
        if(res_p_2 < 0) {
            printf("The 2nd process can't create child\n");
            exit(-1);
        } else if(res_p_2 > 0){ // Действия для второго процесса
            if(close(chanel1[1]) < 0){
                printf("2nd process can't close the writing nd of the pipe\n");
                exit(-1);
            }
            // Получаем данные из первого процесса во втором
            size = read(chanel1[0], buf, buf_size);
            if(size < 0){
                printf("Cant read from pipe\n");
                exit(-1);
            }
            // Заменяем согласные буквы в строке на заглавные
            char* answer = rewrite(buf, size);
            if(close(chanel1[0]) < 0){
                printf("2nd process can't close reading end of the pipe\n");
                exit(-1);
            }

            // Передаем данные в третий канал
            int size_w = write(chanel2[1], answer, size);

            if(size_w != size){
                printf("Can't write string to pipe\n ");
                exit(-1);
            }
            if(close(chanel2[1]) < 0) {
                printf("2nd process can't close writing end of pipe\n");
                exit(-1);
            }
        } else{ // Действия для третьего процесса
            if(close(chanel2[1]) < 0){
                printf("3rd process can't close writing ens of the pipe\n");
                exit(-1);
            }
            // Получаем данные из второго канала
            size = read(chanel2[0], buf, buf_size);
            if(size < 0){
                printf("3rd process can't read string from the pipe\n");
                exit(-1);
            }

            if(close(chanel2[0]) < 0){
                printf("3rd process can't close reading side of the pipe\n");
                exit(-1);
            }
            int file_w;
            // Открыть файл для записи ответа
            if((file_w = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) {
                printf("Cant open the output file\n");
                exit(-1);
            }
            printf("%s \n", buf);
            int size_w = write(file_w, buf, size);
            if(size_w != size) {
                printf("Can't write string to file\n");
                exit(-1);
            }
            if(close(file_w) < 0) {
                printf("Cant close the output file\n");
            }
        }
    }
    return 0;
}
