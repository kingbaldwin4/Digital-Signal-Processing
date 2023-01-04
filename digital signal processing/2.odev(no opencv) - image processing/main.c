#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Big endian to little endian conversion of 32-bit number (if needed)
#define B2L_ENDIAN(num) (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000))

// Check if the machine uses little endian byte order
extern int is_little_endian();

// Read a binary file to buffer
extern uint8_t* read_file(const char*, size_t*);

// Write a binary file to buffer
extern void write_file(const uint8_t*, const char*, size_t);

// Calculate histogram, mean and variance of the pixel data
extern void histogram(const uint8_t*, size_t);

int main()
{
    uint8_t* buffer;
    uint32_t offset, width, height; // offset is the position that pixel data begin
    size_t size;

    buffer = read_file("gray.bmp", &size);

    if (is_little_endian()) {
        offset  = *((uint32_t*)(&buffer[10]));
        width   = *((uint32_t*)(&buffer[18]));
        height  = *((uint32_t*)(&buffer[22]));
    }
    else {
        offset  = B2L_ENDIAN(*((uint32_t*)(&buffer[10])));
        width   = B2L_ENDIAN(*((uint32_t*)(&buffer[18])));
        height  = B2L_ENDIAN(*((uint32_t*)(&buffer[22])));
    }
    
    histogram(&buffer[offset], width * height);

    return 0;
}

int is_little_endian() {
    uint16_t word = 0x0001;
    uint8_t* ptr = (uint8_t*)&word;
    return (ptr[0]) ? 1 : 0;
}

uint8_t* read_file(const char* file_path, size_t* size) {
    FILE* fp = fopen(file_path, "rb");

    if (!fp) {
        fprintf(stderr, "File couldn't found\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*)malloc(*size);

    if (!buffer) {
        fprintf(stderr, "Buffer is null\n");
        exit(1);
    }

    fread(buffer, *size, 1, fp);
    fclose(fp);
    return buffer;
}

void write_file(const uint8_t* buffer, const char* file_path, size_t size) {
    FILE* fp = fopen(file_path, "wb");

    if (!fp) {
        fprintf(stderr, "File couldn't created\n");
        exit(1);
    }

    fwrite(buffer, size, 1, fp);
    fclose(fp);
}

void histogram(const uint8_t* buffer, size_t size) {
    int i, bins[256] = { 0 };
    float mean, variance;

    for (i = 0; i < size; i++)
        bins[buffer[i]]++;

    printf("HISTOGRAM\n\n");
    for (i = 0; i < 256; i++)
        printf("H(%03d) = %d\n", i, bins[i]);

    mean = 0.0f;
    for (i = 0; i < 256; i++)
        mean += i * bins[i];
    mean = mean / size;

    printf("\nmean : %.2f\n", mean);

    variance = 0.0f;
    for (i = 0; i < 256; i++)
        variance += (i - mean) * (i - mean) * bins[i];
    variance = variance / (size - 1);

    printf("\nvariance : %.2f\n", variance);
}
