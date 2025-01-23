#include <stdio.h>

int main(void){
    float dps,atk,cooldown,crit,crit_dmg;
    int multi_atk;
    char flag;
    while(1){
        printf("ATK:");
        scanf("%f",&atk);
        printf("CD[s]:");
        scanf("%f",&cooldown);
        printf("CRT[%%]:");
        scanf("%f",&crit);
        printf("CRT_DMG[%%]:");
        scanf("%f",&crit_dmg);
        printf("N of ATK:");
        scanf("%d",&multi_atk);

        crit *= 0.01;
        crit_dmg *= 0.01;
        if (crit > 1)
            crit = 1;
        if (cooldown <= 0){
            cooldown = 1;
            printf("!! ZERO DIVISION ERROR !!\n");
        }

        dps = atk / cooldown;
        dps *= 1 + crit * (crit_dmg - 1);
        dps *= multi_atk;
        printf("DPS:%.1f\n",dps);

        printf("CONTINUE? y/n\n");
        getchar();
        scanf(" %c",&flag);
        
        if (flag == 'n')
            break;
        printf("\n");
    }
    return 0;
}
