#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 1024
typedef struct {
    uint8_t red;
    uint8_t blue;
    uint8_t green;
} color24bit;

#pragma pack(1)
typedef struct {             // Total: 54 bytes
  uint16_t  type;             // Magic identifier: 0x4d42
  uint32_t  size;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors  
  uint32_t  important_colors; // Important colors 
} BMPHeader;
#pragma pack(1)

int main(int argc, char** argv){
    // read file passed by argv
    FILE* f = fopen(argv[1], "r");
    BMPHeader header;
    header.type = 0x4d42;
    // use lstat to get size of raw file + 54 bytes for header
    uint32_t imgSize = 24 * 192 * 256;
    header.size = imgSize + 54;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offset = 54;
    header.dib_header_size = 40;
    header.width_px = 256;
    header.height_px = 192;
    header.num_planes = 1;
    header.bits_per_pixel = 24;
    header.compression = 0;
    header.image_size_bytes = imgSize;
    header.x_resolution_ppm = 10;
    header.y_resolution_ppm = 10;
    header.num_colors = 0;
    header.important_colors = 0;

    FILE* output = fopen("out.bmp", "w+");
    fwrite(&header, 54, 1, output);
    uint16_t imageBuffer[BUFFER_SIZE] = {0};
    color24bit imageBuffer24bit[BUFFER_SIZE] = {0};

    while(1){
        fread(imageBuffer, sizeof(unsigned short), BUFFER_SIZE, f);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            color24bit pixel;
            pixel.red = ((uint8_t) (imageBuffer[i] >> 10)) << 3;
            pixel.green = ((uint8_t) (imageBuffer[i] >> 5)) << 3;
            pixel.blue = ((uint8_t) (imageBuffer[i])) << 3;
            imageBuffer24bit[i] = pixel;
        }
        fwrite(imageBuffer24bit, sizeof(color24bit), BUFFER_SIZE, output);
        int next = getc(f);
        if(next != EOF){
            ungetc(next, f);
        } else {
            break;
        }
    }

    fclose(f);
    fclose(output);
    // add header
    // rearrage colors?
    // prob convert from 16-bit to 24-bit depth
    // write to new file
}