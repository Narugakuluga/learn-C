#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

// helped by Naruga-kun

float E_math(float lv,float multi); 
void bar(float x,float limit); 
float Dmg_math(char *name,float *hp,float atk,float def,float acc,float e_spd,float spd,float crt); 
void LVUP(float *LV,float *HP,float *ATK,float *DEF,float *ACC,float *SPD,float *EXP_LIMIT);
void wait_enter(void);
void cls_input_buffer(void);
float MfM(float M,float LV,float D);  //Math for Math
int Found_Weapon(float E_LV,char *name,int picked_up,float *Weapon_lv);

int main(void){
    srand(time(NULL)); // 起動時処理
    float HP = 20,HP_LIMIT = 20,LV = 1,EXP = 0,EXP_LIMIT = 25,ATK = 4,DEF = 4,ACC = 4,SPD = 4,CRT_multi; //プレイヤーステータスくん
    float M_ATK,M_DEF,M_ACC,M_SPD,Weapon_LV = 1;                                                   //装備含めたステータス
    float E_HP,E_HP_LIMIT,E_LV = 1,E_ATK,E_DEF,E_ACC,E_SPD;                                    //敵ステータスくん
    int E_NAME,EQUIP = 0,R;
    char input,name[40];
    char *E_list[] = {"SLIME","BAT","IMP","\e[1;32mGOBLIN\e[0m","\e[1;32mOGRE\e[0m","\e[1;32mRAIDER\e[0m","\e[1;34mGOLEM\e[0m","\e[1;34mSIREN\e[0m","\e[1;31mMANTIS\e[0m","\e[1;31mWYVERN\e[0m"};
    float E_atklist[] = {3,2,2,3,4,3,4,4,4,4};
    float E_deflist[] = {3,2,2,3,3,3,4,3,3,3};
    float E_acclist[] = {3,3,4,4,2,3,3,4,4,4};
    float E_spdlist[] = {3,4,3,4,2,5,2,3,4,4};
    float E_hplist[] = {8,7,7,8,9,9,10,9,9,10};
    float E_explist[] = {5,5,5,12,12,12,20,20,35,35};
    struct Weapon_base{
        char name[21];
        float M_atk,M_def,M_acc,M_spd,D_atk,D_def,D_acc,D_spd; //"M"ultiple & "D"elta
    };
    struct Weapon_base Weapons[] = {
        {"Sword",1.02,0.98,0.98,0.98,0.03,0.02,0.02,0.02},   //Dの基準は合計値が0.1になること
        {"Heavy Axe",1.08,0.99,0.94,0.89,0.07,0.01,0.01,0.01},  //ステータス倍率の与える影響は大きいため注意すること
        {"Spear",0.86,1.07,1.03,0.89,0.04,0.03,0.01,0.01},
        {"Dual Sword",0.84,0.89,1.16,1.16,0.01,0.01,0.04,0.04},
        {"Bow",0.87,0.79,1.25,0.79,0.03,0.01,0.05,0.01},
        {"Spellbook",0.79,0.79,0.94,1.23,0.01,0.01,0.01,0.07},
        {"Mjolnir",1.25,0.8,0.7,0.5,0.1,0,0,0}, //ゼロ除法対策はMfMにあるよ
        {"Fortune Dice",0.62,0.89,1.46,0.88,0.03,0.01,0.04,0.02},
        // ..まだ何かあるかな？
    };
 
    printf("NAME?\n"); 
    scanf("%39s",name);
    wait_enter();


    while(1){
        if (EXP >= EXP_LIMIT){ //LVUP処理
                LVUP(&LV,&HP_LIMIT,&ATK,&DEF,&ACC,&SPD,&EXP_LIMIT);
                HP = HP_LIMIT;
                EXP = 0;
                wait_enter();
            }
        
        M_ATK =  ATK * MfM(Weapons[EQUIP].M_atk,Weapon_LV,Weapons[EQUIP].D_atk);
        M_DEF =  DEF * MfM(Weapons[EQUIP].M_def,Weapon_LV,Weapons[EQUIP].D_def);
        M_ACC =  ACC * MfM(Weapons[EQUIP].M_acc,Weapon_LV,Weapons[EQUIP].D_acc);
        M_SPD =  SPD * MfM(Weapons[EQUIP].M_spd,Weapon_LV,Weapons[EQUIP].D_spd);
        
        E_NAME = rand() % ((int)floor(E_LV / 4) + 3);
        if (E_NAME > 10)
            E_NAME = E_NAME % 10;
        E_HP = E_math(E_LV,E_hplist[E_NAME]);
        E_HP_LIMIT = E_HP;
        E_ATK = E_math(E_LV,E_atklist[E_NAME]);
        E_DEF = E_math(E_LV,E_deflist[E_NAME]);
        E_ACC = E_math(E_LV,E_acclist[E_NAME]);
        E_SPD = E_math(E_LV,E_spdlist[E_NAME]);

        while(1){
            system("cls");  // メイン画面のプログラム
            printf("%s     HP %.0f/%.0f  ",name,HP,HP_LIMIT);
            bar(HP,HP_LIMIT);
            printf("     LV:%.0f EXP %.0f/%.0f  ",LV,EXP,EXP_LIMIT);
            bar(EXP,EXP_LIMIT);
            printf("\nATK:%.0f   DEF:%.0f       ACC_RATE:%.1f%%   DODGE_RATE:%.1f%%\nACC:%.0f   SPD:%.0f       CRT_RATE:%.1f%%   SPD_MULTI:%.1f%%\n",M_ATK,M_DEF,M_ACC - E_SPD + 90,100 - (E_ACC - M_SPD + 90),M_ACC,M_SPD,5 + (M_ACC - E_SPD) * 0.2,100 + M_SPD - E_SPD);
            printf("\e[1;33m[[  %s  %.0fLV  ATK:%.0f%%  DEF:%.0f%%  ACC:%.0f%%  SPD:%.0f%%  ]]\e[0m",Weapons[EQUIP].name,Weapon_LV,MfM(Weapons[EQUIP].M_atk,Weapon_LV,Weapons[EQUIP].D_atk)*100,MfM(Weapons[EQUIP].M_def,Weapon_LV,Weapons[EQUIP].D_def)*100,MfM(Weapons[EQUIP].M_acc,Weapon_LV,Weapons[EQUIP].D_acc)*100,MfM(Weapons[EQUIP].M_spd,Weapon_LV,Weapons[EQUIP].D_spd)*100);
            if (EQUIP == 7)
                printf("\e[1;36m + CRT_DAMAGE:500%%\e[0m");
            printf("\n-------------------------------------------------------------------------\n");
            printf("%s LV:%.0f    HP %.0f/%.0f   ",E_list[E_NAME],E_LV,E_HP,E_HP_LIMIT);
            bar(E_HP,E_HP_LIMIT);
            printf("\n"); 
            Sleep(50);
            wait_enter();
            
            CRT_multi = 2;
            if (EQUIP == 7)
                CRT_multi = 5;
            Dmg_math(E_list[E_NAME],&E_HP,M_ATK,E_DEF,M_ACC,E_SPD,M_SPD,CRT_multi);
            if (E_HP > 0){
                Dmg_math(name,&HP,E_ATK,M_DEF,E_ACC,M_SPD,E_SPD,2);
                if (!(HP > 0)){ //死亡時処理
                    printf("\n\e[1;34mYOU DIED...   LOST EXP:%.0f\e[0m\n",EXP - floor(EXP / 1.1));
                    if (E_LV > 1)
                        printf("DO YOU WANT TO BACK RETURN? [y/else]");
                    input = getchar();
                    if (input == 'y' && E_LV > 1){
                        E_LV -= 1;
                        cls_input_buffer();
                    }
                    else if (input != '\n')
                        cls_input_buffer();
                    HP = HP_LIMIT;
                    EXP = floor(EXP / 1.1);
                    break;
                }
            }
            else{ //撃破時処理
                EXP += E_LV * E_LV * E_explist[E_NAME];
                printf("\n\e[1;33mYOU DEFEATED ENEMY!  EXP:%.0f\e[0m",E_LV * E_LV * E_explist[E_NAME]);

                if (rand() % 100 < 8){
                    R = rand() % 8;
                    R = Found_Weapon(E_LV,Weapons[R].name,R,&Weapon_LV);
                    if (R != -1){
                        EQUIP = R;
                        cls_input_buffer();
                    }
                }

                printf("\nDO YOU WANT TO GO NEXT? [y/else]");
                input = getchar();
                if (input == 'y'){
                    E_LV += 1;  
                    cls_input_buffer();
                }
                else if (input != '\n')
                    cls_input_buffer();
                break;
            }

            wait_enter();
            
        }

    }
    return 0;
}

// 敵のステータス処理 [lv,multi]
float E_math(float lv,float multi){
    return round(lv * multi);
}

// プログレスバーくん [x,limit]
void bar(float x,float limit){
float i;
printf("[");
    for (i = 0;i < 10;i++){
        if (x / limit * 10 > i)
            printf("x");
        else
            printf("-");
    }
printf("]");
}

// ダメージアレコレ [e_name,&e_hp,atk,e_def,acc,e_spd]
float Dmg_math(char *name,float *hp,float atk,float def,float acc,float e_spd,float spd,float crt){
    float dmg = 0;
    if ((acc - e_spd + 90) * 10 > (rand() % 1000 + 1)){
        dmg = atk * (1 - def / (def + 50)) * ((100 + spd - e_spd) / 100);
        if ((5 + (acc - e_spd) * 0.2) * 10 > (rand() % 1000 + 1)){
            dmg *= crt;
            printf("\e[1;33m!! CRITICAL !!\e[0m\n");
            Sleep(150);
        }
    }
    else{
        dmg = 0;
        printf("\e[1;33m!! DODGED !!\e[0m\n");
        Sleep(150);
    }
    dmg = round(dmg);
    *hp -= dmg;
    printf("%.0f DAMAGE -> %s\n",dmg,name);
    Sleep(150);

}

// レベルアップ画面の処理 [LV,HP,ATK,DEF,ACC,SPD,EXP_LIMIT]
void LVUP(float *LV,float *HP,float *ATK,float *DEF,float *ACC,float *SPD,float *EXP_LIMIT){
    int flag = 0;
    char k;
    *LV += 1;
    *HP += 3;
    *ATK += 2;
    *DEF += 2;
    *ACC += 2;
    *SPD += 2;
    *EXP_LIMIT = *LV * *LV * 25;  //雑な計算、増加幅は後で考える
    while(1){
        system("cls");
        printf("\e[1;36m    !! LEVEL UP !!\n");
        printf("      %.0fLV -> %.0fLV\n",*LV-1,*LV);
        printf("-- CHOISE BONUS POINT --\e[0m\n1:HP          2:ATK\n3:DEF         4:ACC\n5:SPD         ENTER THE NUMBER\n");
        k = getchar();
        switch(k){
            case '1':
            *HP += 3;
            flag = 1;
            break;
            
            case '2':
            *ATK += 1;
            flag = 1;
            break;
            
            case '3':
            *DEF += 2;
            flag = 1;
            break;

            case '4':
            *ACC += 2;
            flag = 1;
            break;

            case '5':
            *SPD += 2;
            flag = 1;
            break;

            default:
            flag = 0;
        }
        if (flag == 1)
            break;
    }
}

// ENTERの入力を待つ
void wait_enter(void){
char txt;
    while(1){
        txt = getchar();
        if (txt == '\n')
            break;
    }
}

// バッファをクリアするッス
void cls_input_buffer(void){
    int a;
    while((a = getchar()) != '\n' && a != EOF){
        // なにもしない
    }
}

// Math for Math
float MfM(float M,float LV,float D){
    float X;
    X = M + LV * D;
    if (X < 0)
        X = 0;
    return X;
}

//お宝お宝なんじゃらほい
int Found_Weapon(float E_LV,char *name,int picked_up,float *Weapon_lv){
    float LV;
    LV = round(E_LV * (rand() % 60 + 76) / 200);
    if (LV < 1)
        LV = 1;
    Sleep(150);
    printf("\n\e[1;36mYOU FOUND %s [LV:%.0f] !!\e[0m\n",name,LV);
    Sleep(150);
    printf("EQUIP?  [y/else]");
    if (getchar() == 'y'){
        *Weapon_lv = LV;
        return picked_up;
    }
    else{
        printf("...EQUIP?  [y/else]");
        if (getchar() == 'y'){
            *Weapon_lv = LV;
            return picked_up;
        }
        else
            return -1;
    }
}
