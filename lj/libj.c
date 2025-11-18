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

#include <string.h>
#include <jbig.h>

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

static long JbgOptions[5] =
{
    /* Order */
    JBG_ILEAVE | JBG_SMID,
    /* Options */
    JBG_DELAY_AT | JBG_LRLTWO | JBG_TPDON | JBG_TPBON | JBG_DPON, //XXX remove JBG_DELAY_AT
    /* L0 */
    128,
    /* MX */
    16, //XXX set to 0 ?
    /* MY */
    0
};

int hp_init_lib(int iFlag)
{
    return !!iFlag;
}

static void output_jbig(unsigned char *start, size_t len, void *cbarg)
{
    HPLJZjcBuff *pOutBuff = cbarg;
    memcpy(pOutBuff->pszCompressedData + pOutBuff->dwTotalSize, start, len);
    pOutBuff->dwTotalSize += len;
}

int hp_encode_bits_to_jbig(int iWidth, int iHeight, unsigned char **pBuff,
                        HPLJZjcBuff *pOutBuff, HPLJZjsJbgEncSt *pJbgEncSt)
{
    struct jbg_enc_state se;
    jbg_enc_init(&se, iWidth, iHeight, 1, pBuff, output_jbig, pOutBuff);
    jbg_enc_options(&se, JbgOptions[0], JbgOptions[1],
            JbgOptions[2], JbgOptions[3], JbgOptions[4]);
    jbg_enc_out(&se);
    jbg_enc_free(&se);

    pJbgEncSt->xd = iWidth;
    pJbgEncSt->yd = iHeight;
    pJbgEncSt->order = JbgOptions[0];
    pJbgEncSt->options = JbgOptions[1];
    pJbgEncSt->l0 = JbgOptions[2];
    pJbgEncSt->mx = JbgOptions[3];
    pJbgEncSt->my = JbgOptions[4];
    pJbgEncSt->planes = 1;
    pJbgEncSt->d = 0;
    pJbgEncSt->dl = 0;


    return 0;
}


//TODO
#if 0
int HPJetReadyCompress(BYTE       *pbOutBuffer,
                       uint32_t   *outlen,
                       BYTE       *inmem,
                       const uint32_t iLogicalImageWidth,
                       const uint32_t iLogicalImageHeight);
/* hp always encode in color mode, event for gray image.
 * in case of gray mode plane 1 and 2 are 0
 *
 * param
 * pbOutBuffer : output buffer
 * outlen : in pbOutBuffer size, out compressed data size
 * inmem : input buffer
 * iLogicalImageWidth : Width / 3
 * iLogicalImageHeight : Height
 *
 * return < 0 in case of error
 */

see pxljr-1.4
i_compress_row code


}
 

#endif
