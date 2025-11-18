/**
 * Copyright (c) 2025 Matthieu Castet<castet.matthieu@free.fr>. All rights reserved.
 *
**/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    unsigned long    xd;
    unsigned long    yd;
    unsigned long    l0;
    unsigned int     mx;
    unsigned int     my;
    int              order;
    int              planes;
    int              dl;
    int              d;
    int              options;
} HPLJZjsJbgEncSt;

typedef struct
{
    unsigned char *pszCompressedData;
    unsigned long dwTotalSize;
} HPLJZjcBuff;


int hp_encode_bits_to_jbig(int iWidth, int iHeight, unsigned char **pBuff,
                        HPLJZjcBuff *pOutBuff, HPLJZjsJbgEncSt *pJbgEncSt);
int hp_init_lib(int iFlag);


  unsigned char bitmap[15] = {
    /* 23 x 5 pixels, "JBIG" */
    0x7c, 0xe2, 0x38, 0x04, 0x92, 0x40, 0x04, 0xe2,
    0x5c, 0x44, 0x92, 0x44, 0x38, 0xe2, 0x38
  };


int main()
{

    int ret = hp_init_lib(1);
    if (!ret) {
        printf("init error\n");
        return 1;
    }

    HPLJZjsJbgEncSt se;
    memset(&se, 0xDE, sizeof(se));
    HPLJZjcBuff myBuffer;
    unsigned char *p = bitmap;

    myBuffer.pszCompressedData = malloc(1024);
    myBuffer.dwTotalSize = 0;

    ret = hp_encode_bits_to_jbig(23, 5, &p, &myBuffer, &se);

    printf("total size %d\n", myBuffer.dwTotalSize);
    printf("se xd=%d yd=%d\n", se.xd, se.yd);
    printf("se l0=%d mx=%d my=%d\n", se.l0, se.mx, se.my);
    printf("se l0=%d mx=%d my=%d d=%d options=0x%x\n", se.order, se.planes, se.dl, se.d, se.options);

    for (int i = 0; i < myBuffer.dwTotalSize; i++) {
        printf("0x%x ", myBuffer.pszCompressedData[i]);
    }
    printf("\n");
    free(myBuffer.pszCompressedData);

    return 0;
}
