#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
char* _Asm(const char* asm_code)
{
    char* Result = (char*)malloc(6000);
    if (strncmp(asm_code, "mov ", 4) == 0)
    {
        if (asm_code[4] == '$') //立即数
        {
            char temp[30] = { 0 };
            int i = 0;
            for (i = 5; i < strlen(asm_code) - 4; i++)
            {
                temp[i - 5] = asm_code[i];
            }
            temp[i - 5] = '\0';
            if (strlen(temp) == 2) //这是一个byte
            {
                //判断寄存器
                char temp2[30] = { 0 };
                int j = 0;
                for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
                {
                    temp2[j - 5 - strlen(temp)] = asm_code[j];
                }
                temp2[j - 5 - strlen(temp)] = '\0';
                if (strcmp(temp2, ",eax") == 0)
                {
                    sprintf(Result, "b8 %s 00 00 00", temp);
                }
                if (strcmp(temp2, ",ebx") == 0)
                {
                    sprintf(Result, "bb %s 00 00 00", temp);
                }
                if (strcmp(temp2, ",ecx") == 0)
                {
                    sprintf(Result, "b9 %s 00 00 00", temp);
                }
                if (strcmp(temp2, ",edx") == 0)
                {
                    sprintf(Result, "ba %s 00 00 00", temp);
                }
                if (strcmp(temp2, ",esi") == 0)
                {
                    sprintf(Result, "be %s 00 00 00", temp);
                }
                if (strcmp(temp2, ",edi") == 0)
                {
                    sprintf(Result, "bf %s 00 00 00", temp);
                }
            }
            else if (strlen(temp) == 1)
            {
                char bmp3[] = { '0', temp[0], '\0' };
                char temp2[30];
                int j = 0;
                for (j = 5 + strlen(bmp3); j < strlen(asm_code); j++)
                {
                    temp2[j - 5 - strlen(bmp3)] = asm_code[j];
                }
                temp2[j - 5 - strlen(bmp3)] = '\0';
                if (strcmp(temp2, "eax") == 0)
                {
                    sprintf(Result, "b8 %s 00 00 00", bmp3);
                }
                else if (strcmp(temp2, "ebx") == 0)
                {
                    sprintf(Result, "bb %s 00 00 00", bmp3);
                }
                else if (strcmp(temp2, "edx") == 0)
                {
                    sprintf(Result, "ba %s 00 00 00", bmp3);
                }
                else if (strcmp(temp2, "ecx") == 0)
                {
                    sprintf(Result, "b9 %s 00 00 00", bmp3);
                }
                else if (strcmp(temp2, "esi") == 0)
                {
                    sprintf(Result, "be %s 00 00 00", bmp3);
                }
                else if (strcmp(temp2, "edi") == 0)
                {
                    sprintf(Result, "bf %s 00 00 00", bmp3);
                }
            }
            else if (strlen(temp) == 4) //a word
            {
                char num1[] = { temp[0], temp[1], 0 };
                char num2[] = { temp[2], temp[3], 0 };
                char temp2[30] = { 0 };
                int j = 0;
                for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
                {
                    temp2[j - 5 - strlen(temp)] = asm_code[j];
                }
                temp2[j - 5 - strlen(temp)] = '\0';
                if (strcmp(temp2, ",eax") == 0)
                {
                    sprintf(Result, "b8 %s %s 00 00", num2, num1);
                }
                else if (strcmp(temp2, ",ebx") == 0)
                {
                    sprintf(Result, "bb %s %s 00 00", num2, num1);
                }
                else if (strcmp(temp2, ",edx") == 0)
                {
                    sprintf(Result, "ba %s %s 00 00", num2, num1);
                }
                else if (strcmp(temp2, ",ecx") == 0)
                {
                    sprintf(Result, "b9 %s %s 00 00", num2, num1);
                }
                else if (strcmp(temp2, ",esi") == 0)
                {
                    sprintf(Result, "be %s %s 00 00", num2, num1);
                }
                else if (strcmp(temp2, ",edi") == 0)
                {
                    sprintf(Result, "bf %s %s 00 00", num2, num1);
                }
            }
            // double world
            else if (strlen(temp) == 8)
            {
                printf("[debug:]size=8\n");
                char num1[] = { temp[0], temp[1], 0 };
                char num2[] = { temp[2], temp[3], 0 };
                char num3[] = { temp[4], temp[5], 0 };
                char num4[] = { temp[6], temp[7], 0 };
                char temp2[30] = { 0 };
                int j = 0;
                for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
                {
                    temp2[j - 5 - strlen(temp)] = asm_code[j];
                }
                temp2[j - 5 - strlen(temp)] = '\0';
                if (strcmp(temp2, ",eax") == 0)
                {
                    sprintf(Result, "b8 %s %s %s %s", num4, num3, num2, num1);
                }
                else if (strcmp(temp2, ",ebx") == 0)
                {
                    sprintf(Result, "bb %s %s %s %s", num4, num3, num2, num1);
                }
                else if (strcmp(temp2, ",edx") == 0)
                {
                    sprintf(Result, "ba %s %s %s %s", num4, num3, num2, num1);
                }
                else if (strcmp(temp2, ",ecx") == 0)
                {
                    sprintf(Result, "b9 %s %s %s %s", num4, num3, num2, num1);
                }
                else if (strcmp(temp2, ",esi") == 0)
                {
                    sprintf(Result, "be %s %s %s %s", num4, num3, num2, num1);
                }
                else if (strcmp(temp2, ",edi") == 0)
                {
                    sprintf(Result, "bf %s %s %s %s", num4, num3, num2, num1);
                }
            }
            else
            {
                printf("Error!\n");
            }
        }
        else if (asm_code[4] == '%') //寄存器
        {
            char temp[30] = { 0 };
            int i = 0;
            for (i = 5; i < strlen(asm_code) - 4; i++)
            {
                temp[i - 5] = asm_code[i];
            }
            temp[i - 5] = '\0';
            char temp2[30] = { 0 };
            int j = 0;
            for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
            {
                temp2[j - 5 - strlen(temp)] = asm_code[j];
            }
            temp2[j - 5 - strlen(temp)] = '\0';

            if (strcmp("eax", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c0");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c3");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c1");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c2");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c6");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c7");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",eax", temp2) == 0)
            {
                sprintf(Result, "8b c5");
            }
            //ebx
            if (strcmp("eax", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b d8");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b db");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b d9");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b da");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b de");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b df");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",ebx", temp2) == 0)
            {
                sprintf(Result, "8b dd");
            }

            //ecx
            if (strcmp("eax", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b c8");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b cb");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b c9");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b ca");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b ce");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b cf");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",ecx", temp2) == 0)
            {
                sprintf(Result, "8b cd");
            }
            //edx
            if (strcmp("eax", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d0");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d3");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d1");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d2");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d6");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d7");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",edx", temp2) == 0)
            {
                sprintf(Result, "8b d5");
            }
            //ebp
            if (strcmp("eax", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b e8");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b eb");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b e9");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b ea");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b ee");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b ef");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b ed");
            }
            else if (strcmp("esp", temp) == 0 && strcmp(",ebp", temp2) == 0)
            {
                sprintf(Result, "8b ec");
            }
            //esi
            if (strcmp("eax", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f0");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f3");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f1");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f2");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f6");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f7");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f5");
            }
            else if (strcmp("esp", temp) == 0 && strcmp(",esi", temp2) == 0)
            {
                sprintf(Result, "8b f4");
            }
            //edi
            if (strcmp("eax", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b f8");
            }
            else if (strcmp("ebx", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b fb");
            }
            else if (strcmp("ecx", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b f9");
            }
            else if (strcmp("edx", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b fa");
            }
            else if (strcmp("esi", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b fe");
            }
            else if (strcmp("edi", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b ff");
            }
            else if (strcmp("ebp", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b fd");
            }
            else if (strcmp("esp", temp) == 0 && strcmp(",edi", temp2) == 0)
            {
                sprintf(Result, "8b fc");
            }
        }
        else if (asm_code[4] == '&') //指针
        {
            //立即数
            if (asm_code[5] == '$') //说明是立即数
            {
                char temp[30] = { 0 };
                int i = 0;
                for (i = 6; i < strlen(asm_code) - 4; i++)
                {
                    temp[i - 6] = asm_code[i];
                }
                temp[i - 6] = '\0';
                if (strlen(temp) == 2) //这是一个byte
                {
                    //判断寄存器
                    char temp2[30] = { 0 };
                    int j = 0;
                    for (j = 6 + strlen(temp); j < strlen(asm_code); j++)
                    {
                        temp2[j - 6 - strlen(temp)] = asm_code[j];
                    }
                    temp2[j - 6 - strlen(temp)] = '\0';
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "a1 %s 00 00 00", temp);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "8b 1d %s 00 00 00", temp);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "8b 0d %s 00 00 00", temp);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "8b 15 %s 00 00 00", temp);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "8b 35 %s 00 00 00", temp);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "8b 3d %s 00 00 00", temp);
                    }
                }
                else if (strlen(temp) == 1)
                {
                    char bmp3[] = { '0', temp[0], '\0' };
                    char temp2[30];
                    int j = 0;
                    for (j = 6 + strlen(bmp3); j < strlen(asm_code); j++)
                    {
                        temp2[j - 6 - strlen(bmp3)] = asm_code[j];
                    }
                    temp2[j - 6 - strlen(bmp3)] = '\0';
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "a1 %s 00 00 00", bmp3);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "8b 1d %s 00 00 00", bmp3);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "8b 0d %s 00 00 00", bmp3);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "8b 15 %s 00 00 00", bmp3);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "8b 35 %s 00 00 00", bmp3);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "8b 3d %s 00 00 00", bmp3);
                    }
                }
                else if (strlen(temp) == 4) //a word
                {
                    char num2[] = { temp[0], temp[1], 0 };
                    char num1[] = { temp[2], temp[3], 0 };
                    char temp2[30] = { 0 };
                    int j = 0;
                    for (j = 6 + strlen(temp); j < strlen(asm_code); j++)
                    {
                        temp2[j - 6 - strlen(temp)] = asm_code[j];
                    }
                    temp2[j - 6 - strlen(temp)] = '\0';
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "a1 %s %s 00 00", num1, num2);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "8b 1d %s %s 00 00", num1, num2);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "8b 0d %s %s 00 00", num1, num2);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "8b 15 %s %s 00 00", num1, num2);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "8b 35 %s %s 00 00", num1, num2);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "8b 3d %s %s 00 00", num1, num2);
                    }
                }
                // double world
                else if (strlen(temp) == 8)
                {
                    printf("[debug:]size=8\n");
                    char num4[] = { temp[0], temp[1], 0 };
                    char num3[] = { temp[2], temp[3], 0 };
                    char num2[] = { temp[4], temp[5], 0 };
                    char num1[] = { temp[6], temp[7], 0 };
                    char temp2[30] = { 0 };
                    int j = 0;
                    for (j = 6 + strlen(temp); j < strlen(asm_code); j++)
                    {
                        temp2[j - 6 - strlen(temp)] = asm_code[j];
                    }
                    temp2[j - 6 - strlen(temp)] = '\0';
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "a1 %s %s %s %s", num1, num2, num3, num4);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "8b 1d %s %s %s %s", num1, num2, num3, num4);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "8b 0d %s %s %s %s", num1, num2, num3, num4);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "8b 15 %s %s %s %s", num1, num2, num3, num4);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "8b 35 %s %s %s %s", num1, num2, num3, num4);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "8b 3d %s %s %s %s", num1, num2, num3, num4);
                    }
                }
                else
                {
                    printf("Error!\n");
                }
            }
        }
        else
        {
            printf("SyntaxError-->%c", asm_code[4]);
        }
    }
    else if (strncmp(asm_code, "push ", 5) == 0)
    {
        /*获取将要压入栈的寄存器（32位）*/
        char temp[30] = { 0 };
        int i = 0;
        for (i = 6; i < strlen(asm_code); i++)
        {
            temp[i - 6] = asm_code[i];
        }
        temp[i - 6] = '\0';
        if (strcmp(temp, "eax") == 0)
        {
            sprintf(Result, "50");
        }
        if (strcmp(temp, "ebx") == 0)
        {
            sprintf(Result, "53");
        }
        if (strcmp(temp, "ecx") == 0)
        {
            sprintf(Result, "51");
        }
        if (strcmp(temp, "edx") == 0)
        {
            sprintf(Result, "52");
        }
        if (strcmp(temp, "esi") == 0)
        {
            sprintf(Result, "56");
        }
        if (strcmp(temp, "edi") == 0)
        {
            sprintf(Result, "57");
        }
        if (strcmp(temp, "ebp") == 0)
        {
            sprintf(Result, "55");
        }
        if (strcmp(temp, "esp") == 0)
        {
            sprintf(Result, "54");
        }
    }
    else if (strncmp(asm_code, "pop ", 4) == 0)
    {
        //获取将要取出栈的寄存器（32位）
        char temp[30] = { 0 };
        int i = 0;
        for (i = 5; i < strlen(asm_code); i++)
        {
            temp[i - 5] = asm_code[i];
        }
        temp[i - 5] = '\0';
        if (strcmp(temp, "eax") == 0)
        {
            sprintf(Result, "58");
        }
        if (strcmp(temp, "ebx") == 0)
        {
            sprintf(Result, "5b");
        }
        if (strcmp(temp, "ecx") == 0)
        {
            sprintf(Result, "59");
        }
        if (strcmp(temp, "edx") == 0)
        {
            sprintf(Result, "5a");
        }
        if (strcmp(temp, "esi") == 0)
        {
            sprintf(Result, "5e");
        }
        if (strcmp(temp, "edi") == 0)
        {
            sprintf(Result, "5f");
        }
        if (strcmp(temp, "ebp") == 0)
        {
            sprintf(Result, "5d");
        }
        if (strcmp(temp, "esp") == 0)
        {
            sprintf(Result, "5c");
        }
    }
    else if (strncmp(asm_code, "cmp ", 4) == 0 && asm_code[4] == '$') //立即数
    {
        //寄存器与数字比较
        //先数字 再寄存器
        //获取数字
        char temp[30] = { 0 };
        int i = 0;
        for (i = 5; i < strlen(asm_code) - 4; i++)
        {
            temp[i - 5] = asm_code[i];
        }
        temp[i - 5] = '\0';
        //获取寄存器
        char temp2[30] = { 0 };
        int j = 0;
        for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
        {
            temp2[j - 5 - strlen(temp)] = asm_code[j];
        }
        temp2[j - 5 - strlen(temp)] = '\0';

        if (strlen(temp) == 2) //byte
        {

            if (strcmp(temp2, ",eax") == 0)
            {
                sprintf(Result, "83 f8 %s", temp);
            }
            if (strcmp(temp2, ",ebx") == 0)
            {
                sprintf(Result, "83 fb %s", temp);
            }
            if (strcmp(temp2, ",ecx") == 0)
            {
                sprintf(Result, "83 f9 %s", temp);
            }
            if (strcmp(temp2, ",edx") == 0)
            {
                sprintf(Result, "83 fa %s", temp);
            }
            if (strcmp(temp2, ",esi") == 0)
            {
                sprintf(Result, "83 fe %s", temp);
            }
            if (strcmp(temp2, ",edi") == 0)
            {
                sprintf(Result, "83 ff %s", temp);
            }
        }
        if (strlen(temp) == 4) //word
        {
            //拆分数字
            char num1[30] = { temp[0], temp[1], 0 };
            char num2[30] = { temp[2], temp[3], 0 };
            if (strcmp(temp2, ",eax") == 0)
            {
                sprintf(Result, "81 f8 %s %s", num2, num1);
            }
            if (strcmp(temp2, ",ebx") == 0)
            {
                sprintf(Result, "81 fb %s %s", num2, num1);
            }
            if (strcmp(temp2, ",ecx") == 0)
            {
                sprintf(Result, "81 f9 %s %s", num2, num1);
            }
            if (strcmp(temp2, ",edx") == 0)
            {
                sprintf(Result, "81 fa %s %s", num2, num1);
            }
            if (strcmp(temp2, ",esi") == 0)
            {
                sprintf(Result, "81 fe %s %s", num2, num1);
            }
            if (strcmp(temp2, ",edi") == 0)
            {
                sprintf(Result, "81 ff %s %s", num2, num1);
            }
        }
        else if (strlen(temp) == 8) //dowrd
        {
            //拆分数字
            char num1[30] = { temp[0], temp[1], 0 };
            char num2[30] = { temp[2], temp[3], 0 };
            char num3[30] = { temp[4], temp[5], 0 };
            char num4[30] = { temp[6], temp[7], 0 };
            if (strcmp(temp2, ",eax") == 0)
            {
                sprintf(Result, "81 f8 %s %s %s %s", num4, num3, num2, num1);
            }
            if (strcmp(temp2, ",ebx") == 0)
            {
                sprintf(Result, "81 fb %s %s %s %s", num4, num3, num2, num1);
            }
            if (strcmp(temp2, ",ecx") == 0)
            {
                sprintf(Result, "81 f9 %s %s %s %s", num4, num3, num2, num1);
            }
            if (strcmp(temp2, ",edx") == 0)
            {
                sprintf(Result, "81 fa %s %s %s %s", num4, num3, num2, num1);
            }
            if (strcmp(temp2, ",esi") == 0)
            {
                sprintf(Result, "81 fe %s %s %s %s", num4, num3, num2, num1);
            }
            if (strcmp(temp2, ",edi") == 0)
            {
                sprintf(Result, "81 ff %s %s %s %s", num4, num3, num2, num1);
            }
        }
    }
    else if (strncmp(asm_code, "cmp ", 4) == 0 && asm_code[4] == '%') //寄存器
    {
        //获取寄存器
        char temp[30] = { 0 };
        int i = 0;
        for (i = 5; i < strlen(asm_code) - 4; i++)
        {
            temp[i - 5] = asm_code[i];
        }
        temp[i - 5] = '\0';
        //获取寄存器
        char temp2[30] = { 0 };
        int j = 0;
        for (j = 5 + strlen(temp); j < strlen(asm_code); j++)
        {
            temp2[j - 5 - strlen(temp)] = asm_code[j];
        }
        temp2[j - 5 - strlen(temp)] = '\0';
        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b d8", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b db", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b cb", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b d3", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b f3", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "ebx"))
        {
            sprintf(Result, "3b fb", temp);
        }

        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c0", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c3", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c1", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c2", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c6", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "eax"))
        {
            sprintf(Result, "3b c7", temp);
        }

        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b c8", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b cb", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b c9", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b ca", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b ce", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "ecx"))
        {
            sprintf(Result, "3b cf", temp);
        }

        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d0", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d3", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d1", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d2", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d6", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "edx"))
        {
            sprintf(Result, "3b d7", temp);
        }

        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f0", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f3", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f1", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f2", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f6", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "esi"))
        {
            sprintf(Result, "3b f7", temp);
        }

        if (strcmp(temp2, ",eax") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b f8", temp);
        }
        if (strcmp(temp2, ",ebx") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b fb", temp);
        }
        if (strcmp(temp2, ",ecx") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b f9", temp);
        }
        if (strcmp(temp2, ",edx") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b fa", temp);
        }
        if (strcmp(temp2, ",esi") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b fe", temp);
        }
        if (strcmp(temp2, ",edi") == 0 && strcmp(temp, "edi"))
        {
            sprintf(Result, "3b ff", temp);
        }
    }
    else if (strncmp(asm_code, "int ", 4) == 0)
    {
        char temp[30] = { 0 };
        int i = 0;
        for (i = 4; i < strlen(asm_code) + 1; i++)
        {
            temp[i - 4] = asm_code[i];
        }
        temp[i - 4] = '\0';
        sprintf(Result, "cd %s", temp);
    }
    else if (strcmp(asm_code, "retf") == 0)
    {
        sprintf(Result, "cb");
    }
    else if (strcmp(asm_code, "ret") == 0)
    {
        sprintf(Result, "c3");
    }
    else if (strncmp(asm_code, "jmp ", 4) == 0)
    {
        if (asm_code[4] == '%') //寄存器
        {
            char temp[30] = { 0 };
            //获取寄存器名
            int i = 0;
            for (i = 5; i < strlen(asm_code) + 1; i++)
            {
                temp[i - 5] = asm_code[i];
            }
            temp[i - 5] = '\0';
            if (strcmp(temp, "eax") == 0)
            {
                sprintf(Result, "ff e0");
            }
            else if (strcmp(temp, "ebx") == 0)
            {
                sprintf(Result, "ff e3");
            }
            else if (strcmp(temp, "ecx") == 0)
            {
                sprintf(Result, "ff e1");
            }
            else if (strcmp(temp, "edx") == 0)
            {
                sprintf(Result, "ff e2");
            }
            else if (strcmp(temp, "esi") == 0)
            {
                sprintf(Result, "ff e6");
            }
            else if (strcmp(temp, "edi") == 0)
            {
                sprintf(Result, "ff e7");
            }
        }
    }
    else if (strncmp(asm_code, "add ", 4) == 0)
    {

        if (asm_code[4] == '$') //这是个立即数
        {
            //获取立即数
            char temp[30] = { 0 };
            int i = 0;
            for (i = 5; i < strlen(asm_code) - 4; i++)
            {
                temp[i - 5] = asm_code[i];
            }
            temp[i - 5] = '\0';
            //获取寄存器名
            char temp2[30] = { 0 };
            int j = 0;
            for (j = 5+strlen(temp); j < strlen(asm_code); j++)
            {
                temp2[j - 5 - strlen(temp)] = asm_code[j];
            }
            temp2[j - 5 - strlen(temp)] = '\0';
            //cout << "Ok!\n" << temp << endl << temp2 << endl;
            if (1)
            {
                if (strlen(temp) == 2)//byte
                {
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "83 c0 %s", temp);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "83 c3 %s", temp);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "83 c1 %s", temp);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "83 c2 %s", temp);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "83 c6 %s", temp);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "83 c7 %s", temp);
                    }


                }
                else if (strlen(temp) == 4) //word
                {
                    char num1[30] = { temp[0],temp[1],0 };
                    char num2[30] = { temp[2],temp[3],0 };
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "83 c0 %s %s", num2, num1);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "83 c3 %s %s", num2, num1);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "83 c1 %s %s", num2, num1);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "83 c2 %s %s", num2, num1);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "83 c6 %s %s", num2, num1);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "83 c7 %s %s", num2, num1);
                    }
                }
                if (strlen(temp) == 8) //dword
                {
                    char num1[30] = { temp[0],temp[1],0 };
                    char num2[30] = { temp[2],temp[3],0 };
                    char num3[30] = { temp[4],temp[5],0 };
                    char num4[30] = { temp[6],temp[7],0 };
                    if (strcmp(temp2, ",eax") == 0)
                    {
                        sprintf(Result, "83 c0 %s %s %s %s", num4, num3, num2, num1);
                    }
                    if (strcmp(temp2, ",ebx") == 0)
                    {
                        sprintf(Result, "83 c3 %s %s %s %s", num4, num3, num2, num1);
                    }
                    if (strcmp(temp2, ",ecx") == 0)
                    {
                        sprintf(Result, "83 c1 %s %s %s %s", num4, num3, num2, num1);
                    }
                    if (strcmp(temp2, ",edx") == 0)
                    {
                        sprintf(Result, "83 c2 %s %s %s %s", num4, num3, num2, num1);
                    }
                    if (strcmp(temp2, ",esi") == 0)
                    {
                        sprintf(Result, "83 c6 %s %s %s %s", num4, num3, num2, num1);
                    }
                    if (strcmp(temp2, ",edi") == 0)
                    {
                        sprintf(Result, "83 c7 %s %s %s %s", num4, num3, num2, num1);
                    }
                }
            }
        }
        else if (asm_code[4] == '%') //这是一个寄存器
        {
            //获取寄存器1名
            char temp[30] = { 0 };
            int i = 0;
            for (i = 5; i < strlen(asm_code) - 4; i++)
            {
                temp[i - 5] = asm_code[i];
            }
            temp[i - 5] = '\0';
            //获取寄存器2名
            char temp2[30] = { 0 };
            int j = 0;
            for (j = strlen(temp) + 5; j < strlen(asm_code); j++)
            {
                temp2[j - strlen(temp) - 5] = asm_code[j];
            }
            temp2[j - (strlen(asm_code) - 5)] = '\0';
            if (strcmp(temp2, ",eax") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 c0");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 c3");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 c1");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 c2");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 c6");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "03 c7");
                }
            }
            if (strcmp(temp2, ",ebx") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 d8");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 db");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 d9");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 da");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 de");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "13 df");
                }
            }
            if (strcmp(temp2, ",ecx") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 c8");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 cb");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 c9");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 ca");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 ce");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "03 cf");
                }
            }
            if (strcmp(temp2, ",edx") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 d0");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 d3");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 d1");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 d2");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 d6");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "03 d7");
                }
            }
            if (strcmp(temp2, ",esi") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 f0");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 f3");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 f1");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 f2");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 f6");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "03 f7");
                }
            }
            if (strcmp(temp2, ",edi") == 0)
            {
                if (strcmp(temp, "eax") == 0)
                {
                    sprintf(Result, "03 f8");
                }
                if (strcmp(temp, "ebx") == 0)
                {
                    sprintf(Result, "03 fb");
                }
                if (strcmp(temp, "ecx") == 0)
                {
                    sprintf(Result, "03 f9");
                }
                if (strcmp(temp, "edx") == 0)
                {
                    sprintf(Result, "03 fa");
                }
                if (strcmp(temp, "esi") == 0)
                {
                    sprintf(Result, "03 fe");
                }
                if (strcmp(temp, "edi") == 0)
                {
                    sprintf(Result, "03 ff");
                }
            }
        }

    }
    else if (strncmp(asm_code, "sub ",4) == 0)
    {

    }
    else if (strcmp(asm_code, "pusha") == 0)
    {
        sprintf(Result, "60");
    }
    else if (strcmp(asm_code, "popa") == 0)
    {
        sprintf(Result, "61");
    }
    else
    {
        printf("error by %s", asm_code);
    }
    return Result;
}
int main(int argv, char** argc)
{
    if (argv == 1) //debug
    {
        cout << "Please input asm code:";
        string co;
        getline(cin, co);
        cout << _Asm(co.c_str()) << endl;

        return 0;
    }
    fstream fl;
    fl.open(argc[1], ios::in);
    fstream fl2;
    fl2.open(argc[2], ios::out);
    string code;
    fl2 << "POWERINTHEAD";
    while (getline(fl, code))
    {
        string cd;
        string cd1 = "";
        cd = _Asm(code.c_str());
        if (cd == "")
        {
            cout << "The Code Have any problem!";
            return 1;
        }
        for (int i = 0; i < cd.length(); i++)
        {
            if (cd[i] != ' ')
            {
                string bmp = "A";
                bmp[0] = cd[i];
                cd1 += bmp;
            }
        }
        char rl[3];
        rl[2] = 0;
        for (int i = 0, b = 0; i < cd1.length(); i++, b++)
        {
            rl[b % 2] = cd1[i];
            if (i % 2 == 1)
            {
                int rs = strtol(rl, NULL, 16);
                string rl1 = "A";
                rl1[0] = rs;
                fl2 << rl1;
            }
        }
    }
    return 0;
}
