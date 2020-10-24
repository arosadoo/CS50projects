#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Checks for correct usage
    if(argc !=2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }


    //Opens memory card file
    FILE *memCard = fopen(argv[1],"r");
    if(memCard == NULL){
        return 1;
    }


    //Data variables for iterating through memory card
    char *jpegN = malloc(sizeof(char *));
    int picCount = 0, size = 0;
    BYTE buffer[512];
    FILE *img = NULL;

    //Looping through memory card
    do
    {
        //Reads memory card in chunks of 512 BYTES
        size = fread(buffer,sizeof(BYTE),512,memCard);

        //Checks if first bytes of the block signal the start of a JPEG
        if(buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 240) == 224)
        {
            //Initializes first JPEG
            if(picCount == 0)
            {
                //Creation of jpg file
                sprintf(jpegN, "%03i.jpg", picCount);
                picCount++;
                img = fopen(jpegN, "w");
                if(img == NULL)
                {
                    return 1;
                }
                
                //Writing data into image
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            else
            {
                //Close previous jpeg
                fclose(img);
                
                //Creation of jpg file
                sprintf(jpegN, "%03i.jpg", picCount);
                picCount++;
                img = fopen(jpegN, "w");
                if(img == NULL)
                {
                    return 1;
                }
                
                //Writing data into image
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
           

        }
        else if(picCount >= 1)
        {
            //Wrties rest of image to file
            fwrite(buffer, sizeof(BYTE), size, img);
        }
    }while(size == 512);


    //Closes file pointers and free's dyanmic memory
    free(jpegN);
    fclose(img);
    fclose(memCard);
}
