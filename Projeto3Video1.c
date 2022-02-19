#include <stdio.h>
#include <string.h>
#include <math.h>  //190x105 //320X240
#define width 190 
#define height 105
#define channels 3

int CompareFrames(int Frame1[width][height][channels], int Frame2[width][height][channels]) {
    int i,j,k,sum=0;

    for(i=0;i<height;i++) {
        for(j=0;j<width;j++) {
            for(k=0;k<channels;k++) 
                sum += abs(Frame1[i][j][k] - Frame2[i][j][k]);   
        }
    }
    printf("%d ",sum);
    return sum;
}

int main() {
    FILE *fp;
    int Frame1[height][width][channels];
    int Frame2[height][width][channels];
    char ch,str[50];
    int i,j,k,l,dif,n=591;

    fp = fopen("./video1/001.rgb","r");
    fseek(fp,0,SEEK_SET);
    fseek(fp,129600,SEEK_SET);
    
    for(i=0;i<height;i++) {
        for(j=0;j<width;j++) {
            for(k=0;k<channels;k++) {
                if((ftell(fp) - 129600)%190 == 0)
                    fseek(fp,390,SEEK_CUR);
                fread(&ch,sizeof(char),1,fp);
                Frame1[i][j][k] = (int)ch;
            }
        }
    }
    fclose(fp); 

    for(l=1;l<n;l++) {
        sprintf(str,"./video1/%03d.rgb",l+1);   

        fp = fopen(str,"r");
        fseek(fp,0,SEEK_SET);
        fseek(fp,129600,SEEK_SET);

        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                for(k=0;k<channels;k++) {
                    if((ftell(fp) - 129600)%190 == 0)
                        fseek(fp,390,SEEK_CUR);
                    fread(&ch,sizeof(char),1,fp);
                    Frame2[i][j][k] = (int)ch;
                }
            }
        }
        fclose(fp);

        dif = CompareFrames(Frame1,Frame2);

        if(dif > 2500000)
        printf("Anomalia no frame %d!\n",l+1);
        else printf("Frame %d OK!\n",l+1); 
    }
}