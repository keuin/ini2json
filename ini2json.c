#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX 1024



int main()
{
    char line_buffer[LINE_MAX];
    int first_valid_line = 1;
    int line_counter = 0;
    int error_counter = 0;
    printf("{\n"); // JSON text start
    while(fgets(line_buffer,LINE_MAX,stdin))
    {
        line_buffer[strcspn(line_buffer,"\n")] = '\0';
        ++line_counter;
        if(line_buffer[0] == '#' || line_buffer[0] == '\0')
            continue; // A comment line or a blank line, skip.
        
        int valid_chars = 0;
        for(int i=0;line_buffer[i] != '\0';++i)
        {
            if(!isspace(line_buffer[i]) && isprint(line_buffer[i]) && line_buffer[i] != '\n')
                ++valid_chars;
            if(line_buffer[i] == '=')
            {
                if(!first_valid_line)
                    printf(",\n");
                else
                    first_valid_line = 0;

                printf("    ");

                // Output key name
                printf("\"");

                char *pname = line_buffer;
                char *pvalue = line_buffer + i;

                while(pname != pvalue)
                {
                    switch(*pname)
                    {
                        case '"':
                            printf("\\\"");
                            break;
                        case '\\':
                            printf("\\\\");
                        default:
                            putchar(*pname);
                    }
                    ++pname;
                }
                printf("\"");

                putchar(':');

                // Output key value
                printf("\"");

                ++pvalue; // Move foward to skip '='
                while(*pvalue != '\0')
                {
                    if(*pvalue == '"')
                        printf("\\\"");
                    else
                        putchar(*pvalue);
                    ++pvalue;
                }
                printf("\"");

                break; // Skip error detecting.
            }
            if(line_buffer[i+1] == '\0' && valid_chars)
            {
                +error_counter;
                fprintf(stderr,"[Error] Invalid line %d: \"%s\", no equal sign was found. This line was skipped.\n",line_counter,line_buffer);
            }
        }
    }
    printf("\n}");
    if(error_counter)
        fprintf(stderr,"%d error(s) occured.\n",error_counter);
    return 0;
}


