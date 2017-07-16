/*
 * Accepts raw binary code image as input.
 * Outputs image compatible with paper tape loader.
 */

/*
 * Paper tape format(bytes, not words):
 *   01
 *   00
 *   Low byte of packet length (binary length + 6 for header)
 *   High byte of packet length
 *   Low byte of address to load binary data at
 *   High byte of address
 *   DataBegin
 *    |
 *    |
 *   DataEnd
 *   Checksum
 * I am unsure of the checksum format and need to check the SIMH source.
 * In the meantime a zero checksum still functions, albeit with a warning.
 */

#include <stdio.h>
#include <stdint.h>

#define NUMWORDS 20000

void main( void ) {
    uint16_t size = 6;

    FILE * src = fopen("vehan.bin","r");
    FILE * dst = fopen("vehan.pdp11","w+");

    uint16_t header[] = {1,0,01000};
    fwrite(header,6,1,dst);

    uint8_t byte;
    int read;
    do {
        read = fread(&byte,1,1,src);
        if(read == 1) fwrite(&byte,1,1,dst);
        size += read;
    } while (read == 1);

    uint16_t footer[] = {0,1,6,01000,0};
    fwrite(footer,10,1,dst);

    fseek(dst,2,SEEK_SET);
    fwrite(&size,2,1,dst);

    fclose(src);
    fclose(dst);
}
