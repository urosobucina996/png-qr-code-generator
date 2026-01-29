#include <stdio.h>
#include <stdlib.h>
#include "qrcodegen.h"
#include "TinyPngOut.h"

#define SCALE 10
#define MARGIN 4 
#define QR_MAX_INPUT_BUFFER 2980

int main(){

    char input[QR_MAX_INPUT_BUFFER];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error, no input.\n");
        return 1;
    }

    FILE *file = fopen("image.png", "wb");
    if (file == NULL) {
        printf("Couldnt generate picture");
        exit(-1);
    }

    uint8_t qr[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

    bool ok = qrcodegen_encodeText(input,
        tempBuffer, qr, qrcodegen_Ecc_MEDIUM,
        qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,
        qrcodegen_Mask_AUTO, true);
    if (!ok){
        fclose(file);
        return 0;
    }
        
    int size = qrcodegen_getSize(qr);
    int imgSize = (size + MARGIN * 2) * SCALE;
    struct TinyPngOut writer;
    enum TinyPngOut_Status status = TinyPngOut_init(&writer, imgSize, imgSize, file);
    if(status != TINYPNGOUT_OK) {
        printf("Status of generate picture is not ok.");
        fclose(file);
        exit(-1);
    }


    uint8_t rgb_white[] = {255, 255, 255};
    uint8_t rgb_black[] = {0, 0, 0};
    for (int y = 0; y < imgSize; y++) {
        for (int x = 0; x < imgSize; x++) {
            int qrX = (x / SCALE) - MARGIN;
            int qrY = (y / SCALE) - MARGIN;

            bool dark = false;

            if (qrX >= 0 && qrX < size && qrY >= 0 && qrY < size) {
                dark = qrcodegen_getModule(qr, qrX, qrY);
            }

            TinyPngOut_write(&writer, dark ? rgb_black : rgb_white, 1);
        }
    }
    fclose(file);
    return 0;
}