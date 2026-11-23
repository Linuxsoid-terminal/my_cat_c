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
    int flag_status = 0;
    if (argc == 1) {
        printf("Вы не ввели название файла которое хотите запускить.\nПожалуйсто перезапутите программу :)");
        return 1;
    }
    if (argc == 3){
        if (strcmp(argv[2], "-n") == 0){
            flag_status = 1;
            printf("Номерация строк включена :)\n");}
        else {
                printf("Программа не поддерживает флаг:\n %s", argv[2]);
                return 1 ;
            }
    }
    char keis[1024];
    ssize_t ch_zapis_simvol_v_massive ;
    ssize_t ch_simvol_v_file = 0;
    long long nomer_stroky = 1;
    int perm_adres = open(argv[1], O_RDONLY);
    if (perm_adres == -1 ){
        perror("Такого файла нет.\nПожалуйсто перезапутите программу :)\n");
        return 1;}
        if (flag_status == 1) {
            printf("%lld ", nomer_stroky);
            fflush(stdout);
            // приказываем проге незамедлительно выводит nomer_stroky.Если мы это не сделаем то printf сработает только после write хотя если смотреть на код такого не должно быть.Но вот такие приколы у системного программирования :)
        }
    while ((ch_zapis_simvol_v_massive = read(perm_adres, keis, 1024)) > 0) {
        if (flag_status == 1) {
            int index = 0;
            // index это посути номер сивола.
            // И да если что напоминаю машина(компютер) щетает символы от 0 а не от 1.Например в слове 'Tere' нулевой символ это 'T' а первый символ 'e' и тагдалее.
            while (index < ch_zapis_simvol_v_massive) {
                write(1,&keis[index],1);
                // Выводим на консоль содержимое массива keis по одному символу.
                if (keis[index] == '\n') {
                    nomer_stroky ++;
                    printf("%lld ", nomer_stroky);
                    fflush(stdout);
                    // приказываем проге незамедлительно выводит nomer_stroky.Если мы это не сделаем то printf сработает только после write хотя если смотреть на код такого не должно быть.Но вот такие приколы у системного рограммирования :)
                }
                index ++;
            }
        }
        if (flag_status == 0){
            write(1,keis , ch_zapis_simvol_v_massive);
            // мы как бы говорим ядру: выведи на херню под номерком 1 массив с именем keis
            // количество символов которое указано в переменной ch_zapis_simvol_v_massive.
        }

        ch_simvol_v_file = ch_simvol_v_file + ch_zapis_simvol_v_massive;
    }
    close(perm_adres);
    printf("Было выведено:\n %zd", ch_simvol_v_file);

}
