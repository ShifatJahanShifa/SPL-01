#ifndef GIFENC_H
#define GIFENC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GIF {
    uint16_t widthOfScreen, heightOfScreen;     // width and height total 4 bytes, of the screen
    int depth;    // color depth
    int backgroundIndex;    // background color index
    int fd;         //
    int offset;     // image info
    int numberOfFrames;     // frames number
    uint8_t *frame, *back;    // starting of a frame and ending of a frame
    uint32_t partial;    //
    uint8_t buffer[0xFF];    // store
} GIF;

GIF *newGif(
    const char *filename, uint16_t width, uint16_t height,
    uint8_t *palette, int depth, int backgroundIndex, int loop
);
void addFrame(GIF *gif, uint16_t delay);
void closeGif(GIF* gif);

#ifdef __cplusplus
}
#endif
#endif /* GIFENC_H */


