#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *strlower(char *s)
{
    char *p = s;

    while(*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p += 0x20; // Convert to lower case.
        }

        p++;
    }

    return s;
}


unsigned long long extract_size(char *size_str, unsigned long long default_value)
{
    unsigned long long size = default_value;

    if (!size_str || !*size_str)
    {
        return default_value;
    }

    char *temp = malloc(strlen(size_str) + 1);

    if (temp)
    {
        strcpy(temp, size_str);

        strlower(temp);

        char *ep = 0;

        size = strtoul(temp, &ep, 10);

        if (ep)
        {
            if (strstr(ep, "kb"))
            {
                size *= 1024;
            }
            else if (strstr(ep, "mb"))
            {
                size *= 1024 * 1024;
            }
            else if (strstr(ep, "gb"))
            {
                size *= 1024 * 1024 * 1024;
            }
            else if (strstr(ep, "tb"))
            {
                size *= 1024llu * 1024llu * 1024llu * 1024llu;
            }
        }

        free(temp);
    }
    else
    {
        fprintf(stderr, "ERROR: Couldn't allocate memory.\n");
    }

    return size;
}



int main(int argc, char *argv[])
{
    int result = 0;

    if (argc > 2)
    {
        unsigned long long size = extract_size(argv[2], 10 * 1024 * 1024);

        printf("size = %llu\n", size);

        FILE *fp = fopen(argv[1], "w");

        if (fp)
        {
            unsigned long long v = 0;
            unsigned long long cur_size = 0;

            while (cur_size < size)
            {
                fwrite(&v, sizeof(unsigned long long), 1, fp); 

                v += 1;

                cur_size += sizeof(unsigned long long);
            }

            fclose(fp);
        }
        else
        {
            fprintf(stderr, "ERROR: Couldn't open file %s\n", argv[1]);
            result = -3;
        }
    }
    else
    {
        fprintf(stderr, "ERROR: You must provide a size. You can use kb, mb, gb and tb\n");
        result = -1;
    }


    return result;
}

