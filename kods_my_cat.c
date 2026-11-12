#include <stdio.h>
// Для printf (вывод ошибок)
#include <fcntl.h>
// Для open()
#include <unistd.h>
// Для read(), write(), close()
#include <errno.h>
// Для errno и perror()
#include <string.h>
int main (int argc, char *argv[]) {
// argc - это количество слов которе пользователь запишет  в терминале .Если будет записано: my_cat vr_file_1.txt . То argc = 2
// а argv - это массив самих слов.
// argv[0] = my_cat (название проги)
// argv[1] = vr_file_1.txt (полное название файла с которым будет работать прога)
    if (argc == 1) {
        printf("Вы не ввели название файла которое хотите запускить.\nПожалуйсто перезапутите программу :)");
        return 0;

}
    int perm_adres = open(argv[1], O_RDONLY);
    if (perm_adres == -1 ){
        perror("Такого файла нет.\nПожалуйсто перезапутите программу :)\n");
        return 1;
    }
    // Создаём переменную perm_adres с типом данных (int обезательно) и присваиваем ей в качестве значения дискриптор (номерок) файла которыйпользователь указал как argv[1] .
    char keis[1024];
    // делаем как бы заготовку:создаём массив keis с типом данных char на 1024 символа (это 1 килобайт потомучто 1 символ = 1 байт).В нём в дальнейшем будет хранится содержимое файла.
    ssize_t ch_zapis_simvol_v_massive ;
    ssize_t ch_simvol_v_file = 0;
    while ((ch_zapis_simvol_v_massive = read(perm_adres, keis, 1024)) > 0) {
        write(1,keis , ch_zapis_simvol_v_massive);
        // мы как бы говорим ядру: выведи на херню под номерком 1 массив с именем keis такое  количество символов которое указано в переменной ch_zapis_simvol_v_massive.
        ch_simvol_v_file = ch_simvol_v_file + ch_zapis_simvol_v_massive;
    }
    close(perm_adres);
    // (закрываем файл с номереком который хранится в perm_adres )
    printf("Было выведено:\n %zd", ch_simvol_v_file);
}
