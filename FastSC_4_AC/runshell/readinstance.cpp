#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *ent;
    char path[1024];

    // 检查参数个数
    if (argc != 3) {
        printf("Usage: %s <path> <Executable file>\n", argv[0]);
        return 1;
    }

    // 获取输入路径
    strcpy(path, argv[1]);

    // 尝试打开目录
    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // 读取目录中的每个条目
    while ((ent = readdir(dir)) != NULL) {
        // 打印文件名
        
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
        if (strstr(ent->d_name, ".bin") != NULL) { //strstr 函数来检查 ent->d_name 中是否包含子字符串 .clq
            continue; 
        }

        for (int i = 1; i <= 10; i++) {
            // printf("%s -f %s/%s -s 2 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 3 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 4 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 5 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 10 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 15 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 20 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 25 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);
            // printf("%s -f %s/%s -s 30 -t 1000 -o 999999 -c %d >> Nuklpex_classical.txt\n", argv[2], argv[1], ent->d_name, i);

            printf("%s %s/%s 1000 %d 1 >> res.txt\n",argv[2], argv[1], ent->d_name, i);
            

        }

        // printf("%s -f %s/%s -s 2 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 3 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 4 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 5 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 10 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 15 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 20 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 25 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
        // printf("%s -f %s/%s -s 30 -t 1000 -o 999999 -c 1 >> PNuklpex_classicB.txt\n", argv[2], argv[1], ent->d_name);
            

        
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s2.txt -C 1800 %s %s/%s -x 2\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s3.txt -C 1800 %s %s/%s -x 3\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s4.txt -C 1800 %s %s/%s -x 4\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s5.txt -C 1800 %s %s/%s -x 5\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s10.txt -C 1800 %s %s/%s -x 10\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s15.txt -C 1800 %s %s/%s -x 15\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s20.txt -C 1800 %s %s/%s -x 20\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s25.txt -C 1800 %s %s/%s -x 25\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_DIMACS/%s30.txt -C 1800 %s %s/%s -x 30\n", ent->d_name, argv[2], argv[1], ent->d_name);
        
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s2.txt -C 1800 %s %s/%s -x 2\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s3.txt -C 1800 %s %s/%s -x 3\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s4.txt -C 1800 %s %s/%s -x 4\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s5.txt -C 1800 %s %s/%s -x 5\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s10.txt -C 1800 %s %s/%s -x 10\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s15.txt -C 1800 %s %s/%s -x 15\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s20.txt -C 1800 %s %s/%s -x 20\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s25.txt -C 1800 %s %s/%s -x 25\n", ent->d_name, argv[2], argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_BHOSLIB/%s30.txt -C 1800 %s %s/%s -x 30\n", ent->d_name, argv[2], argv[1], ent->d_name);
        

        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s2.txt -C 1800 ./kPEX %s/%s 2\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s3.txt -C 1800 ./kPEX %s/%s 3\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s4.txt -C 1800 ./kPEX %s/%s 4\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s5.txt -C 1800 ./kPEX %s/%s 5\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s10.txt -C 1800 ./kPEX %s/%s 10\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s15.txt -C 1800 ./kPEX %s/%s 15\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s20.txt -C 1800 ./kPEX %s/%s 20\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s25.txt -C 1800 ./kPEX %s/%s 25\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_SNAP/%s30.txt -C 1800 ./kPEX %s/%s 30\n", ent->d_name, argv[1], ent->d_name);
        
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s2.txt -C 1800 ./kPEX %s/%s 2\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s3.txt -C 1800 ./kPEX %s/%s 3\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s4.txt -C 1800 ./kPEX %s/%s 4\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s5.txt -C 1800 ./kPEX %s/%s 5\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s10.txt -C 1800 ./kPEX %s/%s 10\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s15.txt -C 1800 ./kPEX %s/%s 15\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s20.txt -C 1800 ./kPEX %s/%s 20\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s25.txt -C 1800 ./kPEX %s/%s 25\n", ent->d_name, argv[1], ent->d_name);
        // printf("./runsolver0 --timestamp --use-pty -o ./output_graph/%s30.txt -C 1800 ./kPEX %s/%s 30\n", ent->d_name, argv[1], ent->d_name);
        
        //printf("./jiexi %s/%s >> SNAP.txt\n", argv[1], ent->d_name);

        //printf("./jiexi %s/%s >> DIMACE10.txt\n", argv[1], ent->d_name);

        //printf("./jiexi %s/%s >> Network_Repository.txt\n", argv[1], ent->d_name);

        //printf("./jiexi %s/%s >> graph.txt\n", argv[1], ent->d_name);

        
        //printf("./toBin %s/%s\n", argv[1], ent->d_name);


    }

    // 关闭目录
    closedir(dir);

    return 0;
}

