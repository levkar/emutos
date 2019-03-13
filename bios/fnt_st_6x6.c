/*
 * fnt_st_6x6.c - 6x6 font for Atari ST encoding
 *
 * Copyright (C) 2001-2018 The EmuTOS development team
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#include "config.h"
#include "portab.h"
#include "fonthdr.h"

extern const UWORD off_6x6_table[];

static const UWORD dat_table[576] =
{
    0x0082, 0x0421, 0xCFB6, 0x0DE3, 0x04E3, 0x8150, 0xF987, 0xBCC3,
    0xCC3E, 0x73E0, 0x381F, 0x8442, 0x00CD, 0x947B, 0x260C, 0x3184,
    0x8800, 0x0006, 0x704F, 0x3C33, 0xC73E, 0x71C3, 0x0C18, 0x061C,
    0x71CF, 0x1EF3, 0xEF9E, 0x89C0, 0x9242, 0x289C, 0xF1CF, 0x1EFA,
    0x28A2, 0x8A2F, 0x9EC1, 0xE200, 0x6008, 0x0008, 0x0180, 0x8001,
    0x2060, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0E31, 0xC400,
    0x7941, 0x0851, 0x0200, 0x2144, 0x1421, 0x0508, 0x2007, 0x8851,
    0x0210, 0x5145, 0x041A, 0x2F06, 0x1041, 0x04F1, 0xE71C, 0x6000,
    0x30C0, 0xC36C, 0x69A3, 0x4201, 0xE41A, 0x6941, 0x0869, 0xE7BD,
    0x4BA9, 0xBC7B, 0xFF1C, 0x7BFC, 0x1EF3, 0x0D8E, 0xF9BF, 0xB6F9,
    0xCD5E, 0x3BE0, 0x3ED8, 0xC000, 0x01CF, 0xC0F8, 0xE000, 0x71C7,
    0x0C18, 0x838C, 0x7886, 0x060C, 0xC21A, 0x30C0, 0x0071, 0xC73E,
    0x01C2, 0x0662, 0xAF2A, 0x1A17, 0x8682, 0x0150, 0xC880, 0x84C2,
    0x0C02, 0x5367, 0x203F, 0x42F4, 0x00CD, 0xBEA3, 0x4D0C, 0x60C3,
    0x0800, 0x000C, 0x98C0, 0x8252, 0x0802, 0x8A23, 0x0C31, 0xE326,
    0x8A28, 0xA08A, 0x0820, 0x8880, 0x9443, 0x6CA2, 0x8A28, 0xA022,
    0x28A2, 0x5221, 0x1860, 0x6700, 0x61CF, 0x1C79, 0xC21E, 0xB181,
    0x2421, 0x4F1C, 0xF1E7, 0x0E72, 0x28A2, 0x4A27, 0x8C30, 0xCE88,
    0x8002, 0x1400, 0x801E, 0x5002, 0x0050, 0x8000, 0xFBCA, 0x1400,
    0x8508, 0x0000, 0x0E23, 0x6D88, 0x2082, 0x0800, 0x00A2, 0x0000,
    0x30C0, 0x06F6, 0xB2C4, 0x8C72, 0xC22C, 0xB002, 0x1CEB, 0x38D7,
    0x012D, 0x8C08, 0x618C, 0x31BD, 0x861B, 0xE7C6, 0xD9B9, 0xB618,
    0x6D56, 0x186F, 0xE6D8, 0xA216, 0x6B66, 0xFE61, 0xC6BE, 0x736D,
    0x9A21, 0xC412, 0x03E1, 0x9810, 0xC02C, 0x49E0, 0x0768, 0x6300,
    0x0362, 0x3BDF, 0x6E1C, 0xB297, 0x84DE, 0xE150, 0xC88F, 0xBEC3,
    0xEF8E, 0x7320, 0xB760, 0x6294, 0x00C9, 0x1470, 0x8618, 0x60C7,
    0xBE01, 0xE018, 0xA847, 0x1C93, 0xCF04, 0x71E0, 0x0060, 0x018C,
    0xBBEF, 0x208B, 0xCF26, 0xF880, 0x9842, 0xAAA2, 0xF22F, 0x1C22,
    0x28AA, 0x2142, 0x1830, 0x6D80, 0x3028, 0xA08B, 0xE7A2, 0xC881,
    0x3823, 0xE8A2, 0x8A24, 0x9822, 0x28AA, 0x3221, 0x1830, 0x6B9C,
    0x8227, 0x1C71, 0xC720, 0x71C7, 0x1821, 0x871C, 0x80EF, 0x9C71,
    0xC8A2, 0x89C8, 0x9871, 0xCF1E, 0x7187, 0x22F1, 0x2FA2, 0x61E7,
    0xB6CC, 0xCD9B, 0x71C5, 0x96BA, 0xE71C, 0x7000, 0x08EA, 0xDB55,
    0x4927, 0x0C18, 0x6D8C, 0x19BD, 0x8618, 0x6646, 0xD9BD, 0x9CD8,
    0x6F56, 0x1866, 0xF671, 0xC72D, 0xD3C6, 0x5433, 0x668C, 0xABED,
    0x9C72, 0xA792, 0x7886, 0x0630, 0xCF80, 0x30C3, 0x0468, 0xC100,
    0x008D, 0x8662, 0xACAA, 0xE2DF, 0xDC93, 0xA358, 0xD9CC, 0x06D8,
    0x698C, 0xDBEF, 0xA440, 0x2168, 0x00C0, 0x3E29, 0x6E80, 0x60C3,
    0x0830, 0x0330, 0xC848, 0x02F8, 0x2888, 0x8823, 0x0C31, 0xE30C,
    0xB228, 0xA08A, 0x0822, 0x8888, 0x9442, 0x29A2, 0x822A, 0x0222,
    0x2536, 0x5084, 0x1818, 0x6000, 0x03E8, 0xA08A, 0x021E, 0x8881,
    0x2422, 0xA8A2, 0x8A24, 0x0622, 0x252A, 0x31E2, 0x0C30, 0xC132,
    0x822F, 0x8208, 0x20A0, 0xFBEF, 0x8820, 0x88A2, 0xF38A, 0x228A,
    0x28A2, 0x7A28, 0x8E20, 0x8D88, 0x0888, 0xA289, 0xA79C, 0x6100,
    0x8B14, 0xC6F6, 0x0A26, 0x9AA2, 0xC8A2, 0x8800, 0x086A, 0xF8C0,
    0x4BAD, 0x8C38, 0x6D8C, 0x19BD, 0x8018, 0x6646, 0xD9B1, 0x8ED0,
    0x6C56, 0x1866, 0xC631, 0xCDAD, 0xD366, 0x1463, 0x668C, 0xAB65,
    0x36AA, 0xA412, 0x0000, 0x0030, 0xC01A, 0x0003, 0x3469, 0xE700,
    0x0087, 0x0421, 0xC9B6, 0x4210, 0x3C18, 0xE75C, 0xD9CC, 0x06F8,
    0x6D8C, 0xD867, 0x3C71, 0xEEF0, 0x0000, 0x14F2, 0x6D00, 0x3184,
    0x8830, 0x0320, 0x704F, 0xBC13, 0xC708, 0x71C3, 0x0418, 0x0600,
    0x822F, 0x1EF3, 0xE81E, 0x89C7, 0x127A, 0x289C, 0x81C9, 0xBC21,
    0xE222, 0x888F, 0x9E09, 0xE000, 0x01EF, 0x1C79, 0xC202, 0x89C1,
    0x2272, 0x289C, 0xF1E4, 0x1C11, 0xE236, 0x4827, 0x8E31, 0xC03E,
    0x7A28, 0x3EFB, 0xEF9E, 0x8208, 0x0820, 0x8FBE, 0x81EB, 0xA28A,
    0x28A2, 0x0A28, 0x8479, 0xCF08, 0xF888, 0xA289, 0x6000, 0xC900,
    0x863C, 0xC36C, 0xFA24, 0x8C79, 0xEFBE, 0x8800, 0x082B, 0x1A40,
    0x482C, 0xBE68, 0x6D8C, 0x19BF, 0x80F1, 0xE6DE, 0x73FF, 0xBEC0,
    0x6FF6, 0x1867, 0xC632, 0x889A, 0x6BC6, 0x14C1, 0xC7CC, 0x71CD,
    0xB671, 0xC392, 0x7BE7, 0x9E30, 0x822C, 0x0000, 0x1C00, 0x0000,
    0x0082, 0x0000, 0x0000, 0x01E3, 0x1810, 0xB64C, 0xF9CF, 0xBE1B,
    0xEF8C, 0xF860, 0x0758, 0xAC00, 0x00C0, 0x0020, 0x0680, 0x0000,
    0x0060, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0x000C,
    0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0060, 0x0000,
    0x0000, 0x0000, 0x0000, 0x003E, 0x0000, 0x0000, 0x003C, 0x000E,
    0x0000, 0x0000, 0x8020, 0x0000, 0x0000, 0x03C0, 0x0030, 0x0000,
    0xC1E7, 0x1E79, 0xE7B8, 0x71C7, 0x1C71, 0xC8A2, 0xF800, 0x1C71,
    0xC79E, 0xF1C7, 0x8000, 0x8C30, 0x79C7, 0x1E89, 0x2FBE, 0x7000,
    0x0F04, 0xC000, 0x79CB, 0x1000, 0x08A2, 0x7000, 0x0029, 0xE780,
    0x10C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00C0,
    0x0000, 0x0000, 0x0001, 0x8000, 0x0306, 0x00F8, 0x0C08, 0x7000,
    0x1CC0, 0x8000, 0x0000, 0x0033, 0x0000, 0x0000, 0x0800, 0x0000
};

const Fonthead fnt_st_6x6 = {
    1,                  /*   WORD font_id       */
    8,                  /*   WORD point         */
    "6x6 system font",  /*   char name[32]      */
    0,                  /*   UWORD first_ade    */
    255,                /*   UWORD last_ade     */
    4,                  /*   UWORD top          */
    4,                  /*   UWORD ascent       */
    3,                  /*   UWORD half         */
    1,                  /*   UWORD descent      */
    1,                  /*   UWORD bottom       */
    5,                  /*   UWORD max_char_width*/
    6,                  /*   UWORD max_cell_width*/
    0,                  /*   UWORD left_offset  */
    3,                  /*   UWORD right_offset */
    1,                  /*   UWORD thicken      */
    1,                  /*   UWORD ul_size      */
    0x5555,             /*   UWORD lighten      */
    0xAAAA,             /*   UWORD skew         */
    F_STDFORM | F_MONOSPACE,/*   UWORD flags        */

    0,                  /*   UBYTE *hor_table   */
    off_6x6_table,      /*   UWORD *off_table   */
    dat_table,          /*   UWORD *dat_table   */
    192,                /*   UWORD form_width   */
    6,                  /*   UWORD form_height  */

    0                   /*   Fonthead * next_font    */
};
