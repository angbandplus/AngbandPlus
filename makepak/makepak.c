/*
 * Copyright (c) 2001 Hansj�rg Malthaner
 *
 * This software may not be sold or used in other projects 
 * than Iso-Angband without written permission by the author
 *
 */

/* makepak.c
 * 
 * daten.pak generator for Simugraph
 * Hj. Malthaner, Aug. 1997
 *                                     
 */

/*
 * 18.11.97 lineare Speicherung fuer Images -> hoehere Performance
 * 22.03.00 modifiziert f�r run-l�ngen speicherung -> hoehere Performance
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dr_rdppm.h"

static int IMG_SIZE=64;

//#define TRANSPARENT 255
#define TRANSPARENT 0x808088


typedef unsigned char  PIXEL;
typedef unsigned short PIXVAL;
typedef unsigned int   PIXRGB;

// number of special colors
#define SPECIAL 8

static PIXRGB rgbtab[SPECIAL] =
{
  0x001C1C,
  0x003838,
  0x005555,
  0x007171,

  0x008D8D,
  0x00AAAA,
  0x00C6C6,
  0x00E2E2
};


struct dimension {
    int xmin,xmax,ymin,ymax;
};


struct imd {
    int y;
    int h;
    int len;
    PIXVAL * data;
}; 
                                 


#define NUM_IMAGES   320

static struct imd images[NUM_IMAGES];


static unsigned char *block;


static int block_getpix(x,y) 
{
    if(IMG_SIZE == 32) {
      x += x;
      y += y;
    }        

    return ((block[((y)*512*3)+(x)*3] << 16) + (block[((y)*512*3)+(x)*3+1] << 8) + (block[((y)*512*3)+(x)*3+2]));
}


static PIXVAL pixrgb_to_pixval(int rgb)
{                                       
  const int r = rgb >> 16;
  const int g = (rgb >> 8) & 0xFF;
  const int b = rgb & 0xFF;
  

  PIXVAL result = 0;
  int standard = 1;
  int i;

  for(i=0; i<SPECIAL; i++) {
    if(rgbtab[i] == rgb) {
      result = 0x8000 + i;

      standard = 0;
      break;
    }
  }

  if(standard) {
    result = ((r & 0xF8) << 7) | ((g & 0xF8) << 2) | ((b & 0xF8) >> 3);
  }
  
  return result;
}


void
getline(char *str, int max, FILE *f)
{
     fgets(str, max, f);
     str[strlen(str)-1]=0;
}


void
init_dim(PIXRGB *image, struct dimension *dim)
{
    int x,y;                       

    dim->ymin = dim->xmin = IMG_SIZE;
    dim->ymax = dim->xmax = 0;

    for(y=0; y<IMG_SIZE; y++) {
	for(x=0; x<IMG_SIZE; x++) {
	    if(image[x+y*IMG_SIZE] != TRANSPARENT) {
		if(x<dim->xmin)
		    dim->xmin = x;
		if(y<dim->ymin)
		    dim->ymin = y;
		if(x>dim->xmax)
		    dim->xmax = x;
		if(y>dim->ymax)
		    dim->ymax = y;
	    }
	}
    }


/*    dim[n].ymin = dim[n].xmin = 32;
    dim[n].ymax = dim[n].xmax = 63;
*/
/*    printf("Dim[%d] %d %d %d %d\n",n,dim[n].xmin,dim[n].ymin,dim[n].xmax,dim[n].ymax);
*/
}

static PIXVAL* encode_image(int x, int y, struct dimension *dim, int *len)
{    
    int line;
    PIXVAL *dest;
    PIXVAL *dest_base = malloc(64*64*2*sizeof(PIXVAL));
    PIXVAL *run_counter;

    y += dim->ymin;
    dest = dest_base;

    for(line=0; line<(dim->ymax-dim->ymin+1); line++) {
	int   row = 0;
	PIXRGB pix = block_getpix(x, (y+line));
	char count = 0;

	do {
	    count = 0;
	    while(pix == TRANSPARENT && row < IMG_SIZE) {
		count ++;
		row ++;
		pix = block_getpix((x+row), (y+line));
	    }            

//	    printf("-%d ", count);

	    *dest++ = count;

	    if(row < IMG_SIZE) {
                 
		run_counter = dest++;
		count = 0;

		while(pix != TRANSPARENT && row < IMG_SIZE) {
		    *dest++ = pixrgb_to_pixval(pix);
		    
		    count ++;
		    row ++;
		    pix = block_getpix((x+row), (y+line));
		}            
		*run_counter = count;

//		printf("+%d ", count);

	    }

	} while(row < IMG_SIZE);

//	printf("\n");
        
	*dest++ = 0;
    }

    *len = (dest - dest_base);

    return dest_base;
}


static void 
init_image_block(char *filename, int start)
{
    struct dimension dim;
    PIXRGB image[IMG_SIZE*IMG_SIZE];
    int nr = start;

    int z,n;
    int x,y;


    if(load_block(block, filename) == 0) {
	exit(1);
    }  


    for(z=0; z<5; z++) {
	for(n=0; n<8; n++) {
	    for(x=0; x<IMG_SIZE; x++) {
		for(y=0; y<IMG_SIZE; y++) {
		    image[x+y*IMG_SIZE] = block_getpix(x+n*IMG_SIZE, y+z*IMG_SIZE);
		}                          
	    }   
	    init_dim(image, &dim);

//	    images[nr].x = dim.xmin;
	    images[nr].y = dim.ymin;

//	    images[nr].w = dim.xmax - dim.xmin + 1;
	    images[nr].h = dim.ymax - dim.ymin + 1;

	    if(images[nr].h > 0) {
		int len;
		images[nr].data = encode_image(n*IMG_SIZE, z*IMG_SIZE, &dim, &len);
		images[nr].len = len;
//		printf("Image %d length %d\n", nr, len); 
	    } else {
		images[nr].data = NULL;
		images[nr].len = 0;
	    }

	    nr ++;
	}
    }
}

void
fwrite_int(int *p, FILE *f)
{
    const int i = *p;
    fputc(i & 255,f);
    fputc((i >> 8) & 255,f);
    fputc((i >> 16) & 255,f);
    fputc((i >> 24) & 255,f);
}

void
init_images()
{                                                   
    init_image_block("./images/000.ppm", 0);  
    init_image_block("./images/040.ppm", 40);  
    init_image_block("./images/080.ppm", 80);  
    init_image_block("./images/120.ppm", 120);  
    init_image_block("./images/160.ppm", 160);  
    init_image_block("./images/200.ppm", 200);  
    init_image_block("./images/240.ppm", 240);  
    init_image_block("./images/280.ppm", 280);  


    {
        const char * filename = IMG_SIZE == 32 ? "daten2.pak" : "daten.pak";
	FILE *f = fopen(filename,"wb");

	if(f != NULL) {
	    int i;

	    i = NUM_IMAGES;
	    fwrite_int(&i, f);

            for(i=0; i<NUM_IMAGES; i++) {

		fwrite_int(&(images[i].y), f);
		fwrite_int(&(images[i].h), f);
		fwrite_int(&(images[i].len), f);

		if(images[i].h > 0) {
		    fwrite(images[i].data, images[i].len*sizeof(PIXVAL), 1, f);
		}                                               
	    }


	    fclose(f);
	} else {
	    printf("Can't open '%s' for writing.\n", filename);
	    exit(1);
	}
    }
}

int
simgraph_init()
{
    block = (unsigned char*) malloc(512*360*3);

    if(block != NULL) {                
        init_images();

	return 1;
    } else {
	puts("Error: not enough memory!");
	return 0;
    }
}


void
simgraph_exit()
{
    free(block);
}


int
main(int argc, char *argv[])
{
    if(argc == 2) {
	IMG_SIZE = 32;
    } else {
	IMG_SIZE = 64;
    }

    puts("  \nIso-Makepak v1.02 by Hj. Malthaner  (c) 1998-2003\n");
    puts("  This program creates the 'daten.pak' file used");
    puts("  by Iso-Angband from a bundle of ppm images.");
    puts("  The images must be stored in a subfolder");
    puts("  called 'images'.\n");
    puts("  If you have questions about Makepak");
    puts("  contact the author at:");
    puts("    hansjoerg.malthaner@gmx.de");


    printf("\ncreating %dx%d tiles\n", IMG_SIZE, IMG_SIZE);


    simgraph_init();


    simgraph_exit();

    puts("  >>>> Wrote daten.pak successfully.\n");

#ifdef COUNT_COLORS
    for(i=0; i<256; i++) {
	printf("%3d %8d\n", i, histogramm[i]);
    }
#endif

    return 0;
}
