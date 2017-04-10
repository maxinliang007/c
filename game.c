//简化版，去掉无用code
//测试版file.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GET_ELEMENT_NUMS(s) (sizeof(s) / sizeof(*s));

int main()
{
	// 1. 文件创建

	// 打开文件指针
	FILE *file_addr = fopen("text_list.log", "a+");
	if (file_addr == NULL)
	{
		printf("%s", "Open file failed\n");
		return 1000;
	}
	
	// 创建字符串列表
	char *text_list[] = {"hello", "world"};
	
	// 获取数组长度 && 循环写入文件
	int element_nums = GET_ELEMENT_NUMS(text_list);
	int i = 0;
	for (i = 0; i < element_nums; i++)
	{
		fputs(text_list[i], file_addr);
		fputs("\n", file_addr);	
	}	

	fclose(file_addr);


	// 2. 读取文件 && 替换为* && 查找
	
	// 打开文件指针
	FILE *ofile_addr = fopen("text_list.log", "r");
	if (ofile_addr == NULL)
        {
                printf("%s", "Open file failed\n");
                return 1000;
        }	

	// 单行读取文件内容
	char line[100];
	while (fgets(line, 100, ofile_addr) != NULL)
	{
		// 去掉字符串末尾的\n，替换为字符串结束符\0
		line[strlen(line) - 1] = '\0';
		
		// 复制单个字符串
		char str_cpy[100];
		strcpy(str_cpy, line);

		// 将原字符串替换为*
		char *p = line;
		while (*p != '\0')
		{
			*p = '*';
			p++;
		}
		
		// 循环用户输入字符，直到全部猜中为止
		while (strchr(line, '*') != NULL)
		{
		// 用户输入单个字符
		int character = fgetc(stdin);
	
		// 判断字符是否在str_cpy中 && 获取索引数组			
		int i = 0, j = 0, z = 0;

		// 获取索引数量
		for (; i < strlen(str_cpy); i++)
		{
			if (str_cpy[i] == (char)character)
                        {
				z++;
			}
		}
		
		// 动态分配内存
                int *position = NULL;
                position = (int*)malloc(z * sizeof(int));
		if (position == NULL)
		{
			printf("Assign memory failed\n");
			return 2000;
		}

		i = 0;
		for (; i < strlen(str_cpy); i++)
		{
			if (str_cpy[i] == (char)character)
			{
				position[j] = i;
				j++;	
			}
		}				

		//替换line中*为输入字符
		int jj = 0;
                if (z != 0)
                {
                        for (; jj < z; jj++)
                        {
                                int pos = *(position + jj);
                                line[pos] = character;
                        }      
                }

                // 输出替换后的line
               	printf("%s\n", line);
	
		free(position);
		}
		
		break;
	}

	fclose(ofile_addr);
}
