#include "paleta.h"

const pixel_t colores_pasto[10] = {0x089, 0x099, 0x099, 0x0a9, 0x0a9, 0x0a9, 0x0b9, 0x0b9, 0x0c9, 0x0c9};


const pixel_t colores_ruta[4][4] = {
    // columnas: Asfalto, líneas laterales, color lateral, franja del medio
    {0x666, 0xfff, 0xb00, 0xfff},
    {0x666, 0xfff, 0xfff, 0xfff},
    {0x566, 0xfff, 0xb00, 0x566},
    {0x566, 0xfff, 0xfff, 0x566}
};

const pixel_t paleta_3[][8] = {
    {0x000, 0x00f, 0x0f0, 0x0ff, 0xf00, 0xf0f, 0xff0, 0xfff},
    {0x000, 0x89c, 0xabe, 0x0ff, 0xbcf, 0x78b, 0x9ad, 0xf0f},
    {0x000, 0x289, 0x6d9, 0xf00, 0x7f9, 0x069, 0x4b9, 0xfff},
    {0x000, 0x59c, 0xcde, 0xff4, 0xfff, 0x28a, 0x9bd, 0xf00},
    {0x000, 0xc82, 0xfcc, 0x4b9, 0xfed, 0x6d9, 0xdaa, 0x289},
    {0x000, 0xfff, 0xff0, 0xff0, 0x000, 0xf00, 0xfff, 0x0f0},
    {0x000, 0x00f, 0xfff, 0x0ff, 0x000, 0xf0f, 0xff0, 0xfff},
    {0x000, 0x00f, 0x0f0, 0x0ff, 0x000, 0xf0f, 0x0f0, 0xfff},
    {0x000, 0x00f, 0xf40, 0x0ff, 0x000, 0xf0f, 0xf40, 0xfff},
};

const pixel_t paleta_4[][16] = {
    {0xaaa, 0xaba, 0x08f, 0xf30, 0xfff, 0x00a, 0xc00, 0xddd, 0xf90, 0xaba, 0x444, 0x222, 0x888, 0x800, 0xf30, 0xaf0},
    {0xaaa, 0xaba, 0x08f, 0xf30, 0xfff, 0x00a, 0xc00, 0xddd, 0xf90, 0x888, 0x444, 0x222, 0xaba, 0x800, 0xf30, 0xaf0},
    {0xaaa, 0xaba, 0x08f, 0xf30, 0xfff, 0x00a, 0xc00, 0xddd, 0xf90, 0xaba, 0x444, 0x222, 0x888, 0xf00, 0xf30, 0xaf0},
    {0xaaa, 0xaba, 0x08f, 0xf30, 0xfff, 0x00a, 0xc00, 0xddd, 0xf90, 0x888, 0x444, 0x222, 0xaba, 0xf00, 0xf30, 0xaf0},
    {0xaaa, 0xaba, 0x02a, 0x0df, 0xfff, 0x006, 0x09f, 0xddd, 0x9ff, 0xaba, 0x444, 0x222, 0x888, 0x800, 0x0bf, 0xaf0},
    {0xaaa, 0xaba, 0x02a, 0x0df, 0xfff, 0x006, 0x09f, 0xddd, 0x9ff, 0x888, 0x444, 0x222, 0xaba, 0x800, 0x0bf, 0xaf0},
    {0xaaa, 0xaba, 0x02a, 0x0df, 0xfff, 0x006, 0x09f, 0xddd, 0x9ff, 0xaba, 0x444, 0x222, 0x888, 0xf00, 0x0bf, 0xaf0},
    {0xaaa, 0xaba, 0x02a, 0x0df, 0xfff, 0x006, 0x09f, 0xddd, 0x9ff, 0x888, 0x444, 0x222, 0xaba, 0xf00, 0x0bf, 0xaf0},
    {0xaaa, 0xaba, 0x084, 0xf90, 0xfff, 0x064, 0x0c0, 0xddd, 0xfb0, 0xaba, 0x444, 0x222, 0x888, 0x800, 0x0f0, 0xaf0},
    {0xaaa, 0xaba, 0x084, 0xf90, 0xfff, 0x064, 0x0c0, 0xddd, 0xfb0, 0x888, 0x444, 0x222, 0xaba, 0x800, 0x0f0, 0xaf0},
    {0xaaa, 0xaba, 0x084, 0xf90, 0xfff, 0x064, 0x0c0, 0xddd, 0xfb0, 0xaba, 0x444, 0x222, 0x888, 0xf00, 0x0f0, 0xaf0},
    {0xaaa, 0xaba, 0x084, 0xf90, 0xfff, 0x064, 0x0c0, 0xddd, 0xfb0, 0x888, 0x444, 0x222, 0xaba, 0xf00, 0x0f0, 0xaf0},
    {0xaaa, 0xaba, 0xa00, 0xff0, 0xfff, 0x600, 0xca0, 0xddd, 0xff8, 0xaba, 0x444, 0x222, 0x888, 0x800, 0xfc0, 0xaf0},
    {0xaaa, 0xaba, 0xa00, 0xff0, 0xfff, 0x600, 0xca0, 0xddd, 0xff8, 0x888, 0x444, 0x222, 0xaba, 0x800, 0xfc0, 0xaf0},
    {0xaaa, 0xaba, 0xa00, 0xff0, 0xfff, 0x600, 0xca0, 0xddd, 0xff8, 0xaba, 0x444, 0x222, 0x888, 0xf00, 0xfc0, 0xaf0},
    {0xaaa, 0xaba, 0xa00, 0xff0, 0xfff, 0x600, 0xca0, 0xddd, 0xff8, 0x888, 0x444, 0x222, 0xaba, 0xf00, 0xfc0, 0xaf0},
    {0xaaa, 0xaba, 0xc00, 0x666, 0xfff, 0x800, 0x444, 0xddd, 0x888, 0xaba, 0x444, 0x222, 0x888, 0x800, 0x666, 0xaf0},
    {0xaaa, 0xaba, 0xc00, 0x666, 0xfff, 0x800, 0x444, 0xddd, 0x888, 0x888, 0x444, 0x222, 0xaba, 0x800, 0x666, 0xaf0},
    {0xaaa, 0xaba, 0xc00, 0x666, 0xfff, 0x800, 0x444, 0xddd, 0x888, 0xaba, 0x444, 0x222, 0x888, 0xf00, 0x666, 0xaf0},
    {0xaaa, 0xaba, 0xc00, 0x666, 0xfff, 0x800, 0x444, 0xddd, 0x888, 0x888, 0x444, 0x222, 0xaba, 0xf00, 0x666, 0xaf0},
    {0x000, 0xaaa, 0x222, 0xfff, 0xfff, 0xf00, 0xf00, 0xfff, 0xfff, 0xfff, 0xfff, 0xf00, 0xf00, 0xf00, 0xf00, 0x000},
    {0x000, 0x0ef, 0x222, 0xf00, 0xf00, 0xf00, 0xf00, 0xfff, 0xfff, 0x000, 0x000, 0x000, 0x000, 0xfff, 0xfff, 0x000},
    {0x000, 0xbbb, 0x222, 0xf00, 0xff0, 0xf00, 0xff0, 0xff0, 0xf00, 0xf00, 0xff0, 0xf00, 0xff0, 0xf00, 0xff0, 0x000},
    {0x09f, 0xbf7, 0x0f2, 0x0e6, 0x0c1, 0x0a0, 0x080, 0xdfa, 0xc70, 0x860, 0xda0, 0x050, 0x070, 0xf00, 0x000, 0xfaa},
    {0x99a, 0xfff, 0xff0, 0xfd0, 0xfb0, 0xf90, 0xf60, 0xf40, 0xf00, 0xd00, 0xb00, 0x900, 0x600, 0x400, 0x200, 0x0df},
    {0x99a, 0xff0, 0xfff, 0xff0, 0xff0, 0xfc0, 0xf90, 0xf50, 0xf30, 0xf00, 0xc00, 0xa00, 0x800, 0xfe0, 0x400, 0x0df},
    {0x000, 0xfff, 0xeee, 0xddd, 0xccc, 0xbbb, 0xaaa, 0x999, 0x888, 0x00a, 0x777, 0x050, 0x070, 0x000, 0x000, 0x000},
    {0xfc0, 0x4f0, 0x0c0, 0x4b0, 0x080, 0x060, 0xf8f, 0xcba, 0xa75, 0x640, 0x888, 0xba8, 0x986, 0x776, 0x000, 0x000},
    {0x000, 0x060, 0x172, 0x284, 0x395, 0x4a6, 0x5b7, 0x6c8, 0x7d9, 0x8ea, 0x9fb, 0xafc, 0xafd, 0xff0, 0x000, 0x000},
    {0xbbb, 0xfc0, 0xfb0, 0xe90, 0xfff, 0x0cf, 0x0af, 0x08f, 0xc72, 0x0ef, 0x888, 0x000, 0x000, 0xf00, 0xfff, 0xfff},
    {0xbbb, 0xfc0, 0xfb0, 0xe90, 0xfff, 0xdd0, 0xbb0, 0x880, 0xc72, 0xff0, 0x888, 0x000, 0x000, 0xf00, 0xfff, 0xfff},
    {0xfd9, 0xaf3, 0x0f0, 0x0e0, 0x0c0, 0x0a0, 0x080, 0xaf8, 0xff9, 0xca0, 0x980, 0x050, 0x070, 0xb70, 0x980, 0x0aa},
    {0xfd9, 0xaf3, 0x0f0, 0x0e0, 0x0c0, 0x0a0, 0x080, 0xaf8, 0xff9, 0x0d0, 0x0a0, 0x050, 0x070, 0xff0, 0x000, 0x0aa},
    {0x000, 0xfff, 0xeff, 0xdff, 0xcff, 0xbfe, 0xaed, 0x9dc, 0x8cb, 0x7ba, 0x6a9, 0x598, 0x487, 0x376, 0xfff, 0x000},
    {0x0cf, 0xbbb, 0x999, 0x09f, 0x0f0, 0x00c, 0xfff, 0xddd, 0xff0, 0xfa0, 0xf00, 0x000, 0xf0e, 0x0f0, 0x0f0, 0x000},
    {0x000, 0xfff, 0xf0f, 0xb97, 0xf00, 0xf90, 0xfb0, 0xfe0, 0xdff, 0x000, 0x0f0, 0xfff, 0xccf, 0x000, 0x000, 0x000},
    {0x0cf, 0xbbb, 0x999, 0x09f, 0x0f0, 0x00c, 0xfff, 0xddd, 0xff0, 0xfa0, 0xf00, 0x000, 0x000, 0x0f0, 0x0f0, 0x000},
    {0x09f, 0xfff, 0xfff, 0xfff, 0xfff, 0xb00, 0xa00, 0xfff, 0x860, 0xfff, 0xc70, 0x700, 0x070, 0xf00, 0x000, 0xfaa},
    {0x09f, 0xff0, 0xee0, 0xd00, 0xcc0, 0xbb0, 0xaa0, 0xff0, 0xc70, 0x860, 0xda0, 0x880, 0x770, 0xf00, 0x000, 0xfaa},
    {0x09f, 0xfb0, 0xe90, 0xd90, 0xc00, 0xb00, 0xa00, 0xfc0, 0xc70, 0x860, 0xda0, 0x700, 0x070, 0xf00, 0x000, 0xfaa},
    {0xfff, 0xffc, 0xff0, 0xfd0, 0xfb0, 0xf90, 0xf60, 0xd00, 0xfee, 0xedd, 0xccc, 0xaaa, 0x888, 0x000, 0x000, 0x000},
    {0x0ff, 0x600, 0x800, 0xa00, 0x000, 0xfff, 0x999, 0xbbb, 0x006, 0x008, 0x007, 0x600, 0x800, 0xa00, 0x000, 0x000},
    {0x0ff, 0xf00, 0xff9, 0xfb3, 0x000, 0xfff, 0x999, 0xbbb, 0x006, 0x008, 0x007, 0x600, 0x800, 0xa00, 0x000, 0x000},
    {0x0ff, 0x600, 0x800, 0xa00, 0x000, 0xfff, 0x999, 0xbbb, 0x006, 0x008, 0x007, 0xf00, 0xff9, 0xfb3, 0x000, 0x000},
    {0x0ff, 0x600, 0x800, 0xa00, 0x000, 0xfff, 0x999, 0xbbb, 0x00f, 0xfff, 0x0ff, 0x600, 0x800, 0xa00, 0x000, 0x000},
    {0x0ff, 0xff0, 0xff0, 0xfff, 0xf00, 0xff0, 0xf00, 0xf00, 0xaaa, 0x000, 0xddd, 0x999, 0xf00, 0xff0, 0x000, 0x000},
    {0x0ff, 0xf00, 0xf00, 0xfff, 0xf00, 0xff0, 0xff0, 0xff0, 0xaaa, 0x000, 0xddd, 0x999, 0xf00, 0xff0, 0x000, 0x000},
    {0x0ff, 0xf00, 0xff0, 0xfff, 0xff0, 0xf00, 0xf00, 0xff0, 0xaaa, 0x000, 0xddd, 0x999, 0xf00, 0xff0, 0x000, 0x000},
    {0x000, 0x000, 0x885, 0x000, 0xf00, 0x00a, 0xfff, 0x880, 0xfff, 0xf00, 0x0f0, 0xff0, 0x00f, 0xf0f, 0x00f, 0x000},
    {0x111, 0xddd, 0xaaa, 0xaaa, 0xdee, 0xdee, 0xbcc, 0xbcc, 0xccc, 0x078, 0x9bf, 0x9bf, 0x999, 0x999, 0x888, 0x888},
    {0x000, 0xfff, 0xdff, 0xcef, 0xbdf, 0xace, 0x9be, 0x8ad, 0x79c, 0x68b, 0x57a, 0x468, 0x354, 0xfff, 0xfff, 0x888},
    {0x000, 0xfff, 0xdff, 0xcef, 0xbdf, 0xace, 0x9be, 0x8ad, 0x79c, 0x68b, 0x57a, 0x468, 0x354, 0xcef, 0xdff, 0x888},
    {0x000, 0xff0, 0x885, 0x000, 0xff0, 0x00a, 0xbf0, 0x880, 0x000, 0x000, 0x0f0, 0x0ff, 0x000, 0xf0f, 0xff0, 0x000},
    {0x000, 0xfff, 0xfff, 0x000, 0x000, 0x000, 0xfff, 0x000, 0x000, 0xccc, 0x222, 0xfff, 0xfff, 0xfff, 0x000, 0x000},
    {0x000, 0x000, 0x000, 0xfff, 0x000, 0xfff, 0xfff, 0x000, 0xfff, 0xf00, 0xfff, 0xfff, 0xfff, 0xfff, 0xe00, 0x000},
    {0x000, 0xfff, 0x00f, 0xfff, 0xfff, 0x00f, 0xfff, 0x00f, 0xfff, 0x00e, 0x00f, 0x00f, 0x00f, 0xfff, 0xff0, 0x000},
    {0x6b7, 0xfff, 0xffd, 0xdf0, 0xff0, 0xaf8, 0x2d2, 0x5c6, 0x8b7, 0x0a0, 0x090, 0x080, 0xfd7, 0xcf8, 0x9f8, 0xefe},
    {0xcdd, 0xfff, 0xeff, 0xefe, 0xeee, 0xdee, 0xcde, 0xccc, 0xded, 0xbcc, 0xabc, 0x99a, 0x89a, 0x178, 0x168, 0xefb},
    {0x00d, 0xfff, 0xeff, 0xdff, 0xcff, 0xbff, 0x0ff, 0x0ef, 0x0df, 0x0cf, 0x0bf, 0x0af, 0x00f, 0x00c, 0x00b, 0xefb},
    {0xeda, 0x896, 0xca7, 0xffb, 0xfeb, 0xfea, 0xdc9, 0xdca, 0xeca, 0xdb9, 0xec9, 0xfc9, 0xb96, 0xa86, 0x986, 0xefe},
};
