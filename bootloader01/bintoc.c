
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

unsigned int data[2048];
char postfix[16];

int main ( int argc, char *argv[] )
{
    unsigned int ra;
    unsigned int rb;

    if(argc<3)
    {
        printf("bintoc input output\n");
        return(1);
    }
    postfix[0]=0;
    if(argc>3)
    {
        strcpy(postfix,argv[3]);
    }
    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("Error opening file [%s]\n",argv[1]);
        return(1);
    }
    rb=fread(data,1,sizeof(data),fp);
    fclose(fp);
    printf("%u bytes read\n",rb);
    if(rb>4096)
    {
        printf("Error more than a sector\n");
        return(1);
    }
    fp=fopen(argv[2],"wt");
    if(fp==NULL)
    {
        printf("Error opening file [%s]\n",argv[2]);
        return(1);
    }

    rb+=3;
    rb>>=1;
    fprintf(fp,"\n");
    fprintf(fp,"const unsigned int flash_data_words%s=0x%08X;\n",postfix,rb);
    fprintf(fp,"const unsigned int flash_data%s[]=\n",postfix);
    fprintf(fp,"{\n");
    for(ra=0;ra<rb;ra++)
    {
        fprintf(fp,"0x%08X, // 0x%04X\n",data[ra],ra<<2);
    }
    fprintf(fp,"};\n");
    fprintf(fp,"\n");
    fclose(fp);

    return(0);
}

//-------------------------------------------------------------------------
// Copyright (c) 2018 David Welch dwelch@dwelch.com
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-------------------------------------------------------------------------
