#include <stdio.h>
#include <string.h>
#include <math.h>

#define width 320
#define height 240
#define channels 3

int CompareFrames(int Frame1[width][height][channels], int Frame2[width][height][channels]) {
    int i,j,k,sum=0;

    for(i=0;i<height;i++) {
        for(j=0;j<width;j++) {
            for(k=0;k<channels;k++) 
                sum += abs(Frame1[i][j][k] - Frame2[i][j][k]);   
        }
    }
    return sum;
}

int main() {
    FILE *fp;
    int Frame1[height][width][channels];
    int Frame2[height][width][channels];
    char ch,str[50];
    int i,j,k,l,dif,n=31;

    fp = fopen("./video2/001.rgb","r");
    
    for(i=0;i<height;i++) {
        for(j=0;j<width;j++) {
            for(k=0;k<channels;k++) {
                fread(&ch,sizeof(char),1,fp);
                Frame1[i][j][k] = (int)ch;
            }
        }
    }
    fclose(fp); 

    for(l=1;l<n;l++) {
    sprintf(str,"./video2/%03d.rgb",l+1);   
        fp = fopen(str,"r");

        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                for(k=0;k<channels;k++) {
                    fread(&ch,sizeof(char),1,fp);
                    Frame2[i][j][k] = (int)ch;
                }
            }
        }
        fclose(fp);

        dif = CompareFrames(Frame1,Frame2);

        if(dif > 5900000)
        printf("Anomalia no frame %d!\n",l+1);
        else printf("Frame %d OK!\n",l+1); 
    }
}