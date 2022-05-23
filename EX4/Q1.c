#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *source;
    source = fopen("src.txt", "a+");
    if (source == NULL)
    {
        printf("打开要读取的文件失败\n");
        return -1;
    }

    FILE *target;
    target = fopen("tar.txt", "w+"); //创建新的文件
    if (target == NULL)
    {
        printf("新建要创建的文件失败\n");
        return -1;
    }

    // 获取source.txt 的内容长度
    int length;
    fseek(source, 0, SEEK_END); // 指针指向末尾，用于统计内容长度
    length = ftell(source);
    fseek(source, 0, SEEK_SET); // 恢复指针

    char stream[length];                              // 创建一个流用于暂存txt的内容
    fread(stream, length * sizeof(char), 1, source);  // 读取src.txt文件的内容到stream
    fwrite(stream, length * sizeof(char), 1, target); // 将stream的内容写入到tar.txt
    printf("复制完成！\n");

    // 关闭连接
    fclose(source);
    fclose(target);
    return 0;
}