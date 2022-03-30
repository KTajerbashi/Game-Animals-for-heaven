//////////////////////////////////////////////////////
//	Library include
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<ctime>
////////////////////////////////////////////////////////
//	Costant var or Define
const int maxsatr = 20, maxsotun = 20, maxheyvan = 100, maxghaza = 100;
const int Boud2 = 20;
const int Size = 20;

//////////////////////////////////////////////////////
//	Structs
struct heyvan {
    char noe;
    int  satr;
    int  sotun;
    int  energy;
    int  oneMove;
    int  maxJahesh;
    int  tolidMesl;
    int  attack;
    int  deffend;
    int  energyAvalie;
};

//////////////////////////////////////////////////////
//	Function
void gotoxy(int x, int y);	// Get X,Y and Change up cursor on Console
void clearScreen();			//	Clear Screen Console
void mysleep(unsigned int mseconds);
void setTextColor(int textColor, int backColor = 0) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
void GetPrintf(FILE *file,char A[][Boud2], int size);	// Get a Array and Print
void GetWorld(char A[][Boud2], int size);	// Make a news World with .
void GetBlock(char A[][Boud2], FILE *map, int blockHa[][2], int &size);				// Get Bloked size Cell and Coordinate
void GetHeaven(char A[][Boud2],int B[][2], int &size, FILE *map);			// Get Heaven size Cell And Cooedinate
void GetFood(int A[][3],char Chart[][Boud2], FILE *map, int &i);				// Get Food Energy and Coordinate
void PrintLine(FILE *file,int a);
void ACTION(FILE *file,int &x,int &y,char &C);
void peidaKardanNazdikTarinBehesht(int beheshtHa[][2], int tedadBeheshtHa, int satrheyvan, int sotunheyvan, int& satrnb, int& sotunnb);
int harkatHeyvan(FILE *file,char jahan[][20], int satrb, int sotunb, int& satrh, int& sotunh, int AbAdjahan, int beheshtHa[][2], int tedadbeheshtha, char noe, int maxJahesh, int &energy, int OneMove);
int checkDashtanGhaza(int ghaza[][3], int &tedadGhaza, int satr, int sotun);
int SHomareHamsar(int satr, int sotun, struct heyvan listHeyvanat[], int tedadKolHeyvanat);
int CheckDashtanGuneMovafeghDarAtraf(char jahan[][20], int satrh, int sotunh, char noe, struct heyvan listHeyvanat[100], int tedadKolHeyvanat,int &XM,int &YM);
void PeidaKardanNazdikTarinMakanKhali(char jahan[][20], int satrh, int sotunh, int satrHamsar, int sotunHamsar, int &satrBache, int &sotunBache);
void EzafeKardanBacheBeList(struct heyvan listHeyvanat[], int &tedadKolHeyvanat, int satrBache, int sotunBache, char noe, int energy,int &E,int &M,int &J,int &T,int &A,int &D);
int checkDashtanGuneMokhalefDarAtraf(char jahan[][20], int satrh, int sotunh, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, char noeh,int &XE,int &YE);
int ShomarandeDoshman(int satr, int sotun, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat);
int DustBarayeEhda(struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, int i);
void Save(int AbAdJahan, int tedadBonBast, int bonbastha[][2], int tedadBeheshtHa, int BeheshtHa[][2], int tedadGhazaHa, int GhazaHa[][3], struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, char GuneMoredNazar);
void PrintAbAdJahanDarFile(FILE *saveFILE, int AbAdJahan);
void PrintBonBastHaDarFile(FILE *saveFILE, int bonbastHa[][2], int tedadBonBastHa);
void printBeheshtHaDarFile(FILE *saveFILE, int beheshtHa[][2], int tedadBeheshtHa);
void PrintGhazaHaDarFile(FILE *saveFILE, int GhazaHa[][3], int tedadGhazaHa);
void PrintHeyvanatDarFile(FILE *saveFILE, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat);
void PrintGuneKarbarDarFile(FILE *saveFILE, char GuneMoredNazar);
void KhandanAzFileSaveShode(FILE *saveFILE, char jahan[][20], int &AbAdJahan, int blockHa[][2], int &tedadBlockHa, int beheshtHa[][2], int &tedadBeheshtHa, int ghazaHa[][3], int &tedadGhazaHa, int &tedadKolHeyvanat, struct heyvan listKolHeyvanat[], char &guneMoredNazar);
void GereftanListHeyvanat(FILE *saveFILE, struct heyvan listKolHeyvanat[], int &i, char jahan[][20]);
void Attack(FILE *file,struct heyvan listHeyvanha[],char jahan[][20],int size,int &i,int &tedadKolHeyvanha,int &SW);
void GAMEOVER(FILE *file,char A[][Boud2], int size){
	printf("\n\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|");
	printf("\n\t|%%%%%%%%%%%%%%%|      GAME OVER      |%%%%%%%%%%%%%%%|");
	printf("\n\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|\n");
	
    fprintf(file,"\n\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|");
	fprintf(file,"\n\t|%%%%%%%%%%%%%%%|      GAME OVER      |%%%%%%%%%%%%%%%|");
	fprintf(file,"\n\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|\n");
    
    GetPrintf(file, A, size);
}

int main() {
	int E,M,J,T,A,D;
    int i,j,k,l,q,x,y,X,Y,m,n,o,SW1=1,SW2,SW3,R , abAdJahan, satrbonbast, sotunbonbast, satrheaven, sotunheaven, tedadheyvan, satr, sotun, satrnb, sotunnb, vaziat , tedadKolHeyvanha = 0;
    char guneMoredNazar, f, noe,CC;
    char khune, pv,LE;   //pv: parantez va virgul.
    int tedadKhune, ghaza[maxghaza][3];
    char jahan[20][20];
    int beheshtHa[100][2], tedadBeheshtha;
    int tedadGuneHa,tedadGhazaHa = 0;
    int EnergyAvalie ,energyYekHarkat,jahesh,tolid,energyHamle,energyDefa;
    int Doshman,Dust,eghdam2,sw2;
    int sw,eghdam,Hamsar,EnergyM,EnergyF;
    int satrBache,sotunBache,XM=-3,YM=-3;
    int blockHa[100][2], tedadBlockHa;
    
    heyvan listHeyvanha[maxheyvan];

    FILE *Human_Readable_Log;
    Human_Readable_Log = fopen("Human_Readable_Log.txt","w");
    if(!Human_Readable_Log){
        printf("can't open the human readable log!\n");
    }
    
    FILE *saveFILE;
    saveFILE = fopen("SaveAndLoad.txt","r");
    if(saveFILE){
        KhandanAzFileSaveShode(saveFILE, jahan, abAdJahan, blockHa, tedadBlockHa, beheshtHa, tedadBeheshtha, ghaza, tedadGhazaHa, tedadKolHeyvanha, listHeyvanha, guneMoredNazar);
    }else{
        printf("There isn't any savad file! the game satarts from the begining!\n");
        FILE *map;
        map=fopen("map_phase1.txt","r");
        if(!map){
            printf("can't open the file!");
            return 0;
        }
    
	    setTextColor(12);
        puts("\n==================\n");
        puts("    Input Mode");
        puts("\n==================\n");

        fprintf(Human_Readable_Log,"\n==================\n");
        fprintf(Human_Readable_Log,"    Input Mode");
        fprintf(Human_Readable_Log,"\n==================\n");

    //	LINE 1
    	setTextColor(9);
        fscanf(map ,"%d", &abAdJahan);
    //	get the size of world 
        GetWorld(jahan, abAdJahan);
    //	
        srand(time(NULL));
    //	LINE 2	#
	    setTextColor(0,12);
	    GetBlock(jahan, map, blockHa, tedadBlockHa);
    //	LINE 3	H
	    setTextColor(10,1);
	    GetHeaven(jahan,beheshtHa,tedadBeheshtha, map);
    //	LINE 4	===
	    setTextColor(10);
        fscanf(map, " %c%c%c",&LE,&LE,&LE);	if(LE != 61){ return 0;	}
    //	LINE 5	F
	    setTextColor(9,7);
	    GetFood(ghaza,jahan, map, tedadGhazaHa);
    //	LINE 6 ===
	    setTextColor(10);
	    fscanf(map, " %c%c",&LE,&LE);	if(LE != 61){ return 0;	}
    //	LINE 7	Animals
    //	baraye heyvanha chon noe anha ham mohem hast yek struct tarif shode.
	    i = 0;
	    setTextColor(13);
        fscanf(map, " %c", &listHeyvanha[i].noe);
        tedadGuneHa=1;
        do {
            fscanf(map, "%d", &tedadheyvan);
            tedadKolHeyvanha += tedadheyvan;
            for (j = 0; j < tedadheyvan; j++) {
                fscanf(map, " %c", &pv);  //(
                fscanf(map, "%d", &listHeyvanha[i].satr);
                fscanf(map, " %c", &pv);  //,
                fscanf(map, "%d", &listHeyvanha[i].sotun);
                fscanf(map, " %c", &pv);  //)
                jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = listHeyvanha[i].noe;
                listHeyvanha[i + 1].noe = listHeyvanha[i].noe;
                i++;
            }
            fscanf(map, " %c", &listHeyvanha[i].noe);
            tedadGuneHa++;
        } while (listHeyvanha[i].noe != 61);                       // anjam bede ta zamani ke mosavi vared shavad.

    //	LINE	8	==
	    setTextColor(10);
	    fscanf(map, " %c%c",&LE,&LE);	if(LE != 61){ return 0;	}
    //	LINE	9	My Animal	
	    setTextColor(11);
        fscanf(map, " %c", &guneMoredNazar);
    //	LINE	10	===
        setTextColor(10);
	    fscanf(map, " %c%c%c",&LE,&LE,&LE);	if(LE != 61){ return 0;	}
    //	LINE 	11 information of Animals
        tedadGuneHa--;
        setTextColor(14);
        for(i=0;i<tedadGuneHa;i++){
            fscanf(map, " %c",&noe);
            fscanf(map, "%d",&EnergyAvalie);
            fscanf(map, "%d",&energyYekHarkat);
            fscanf(map, " %c",&pv);	//	$
            fscanf(map, "%d",&jahesh);
            fscanf(map, " %c",&pv);	//	$
            fscanf(map, "%d",&tolid);
            fscanf(map, " %c",&pv);	//	$
            fscanf(map, "%d",&energyHamle);
            fscanf(map, " %c",&pv);	//	$
            fscanf(map, "%d",&energyDefa);

            for(j=0;j<tedadKolHeyvanha;j++){
                if(listHeyvanha[j].noe==noe){
                    listHeyvanha[j].energy=EnergyAvalie;
                    listHeyvanha[j].energyAvalie=EnergyAvalie;
                    listHeyvanha[j].oneMove=energyYekHarkat;
                    listHeyvanha[j].maxJahesh=jahesh;
                    listHeyvanha[j].tolidMesl=tolid;
                    listHeyvanha[j].attack=energyHamle;
                    listHeyvanha[j].deffend=energyDefa;
                }
            }
        }
    }

    setTextColor(15,4);
    printf("\n\t\t============================");
    printf("\n\t\t[[[[[    Start Game    ]]]]]\n");
    printf("\t\t============================\n");

    fprintf(Human_Readable_Log,"\n\t\t============================");
    fprintf(Human_Readable_Log,"\n\t\t[[[[[    Start Game    ]]]]]\n");
    fprintf(Human_Readable_Log,"\t\t============================\n");

    setTextColor(10);
    GetPrintf(Human_Readable_Log,jahan, abAdJahan);
    while (1) {
        for (i = 0; i < tedadKolHeyvanha; i++) {
            // agar gune karbar bud:
            if (listHeyvanha[i].noe == guneMoredNazar ) {
            	XM=YM=-3;
                satr=listHeyvanha[i].satr;
                sotun=listHeyvanha[i].sotun;
                EnergyAvalie=listHeyvanha[i].energy;
                energyYekHarkat=listHeyvanha[i].oneMove;
                jahesh=listHeyvanha[i].maxJahesh;
                printf("\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
                printf("[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);

                fprintf(Human_Readable_Log,"\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
                fprintf(Human_Readable_Log,"[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                //	START FAZ 4 Gift Energy
                    SW2 = 1;
                    R = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha, XM, YM);
                    if (R != -1)
                    {
                        printf("Your Energy is Now : %d\n", listHeyvanha[i].energy);
                        printf("Do you want Gift Energ ? (Y/N) : ");

                        fprintf(Human_Readable_Log,"Your Energy is Now : %d\n", listHeyvanha[i].energy);
                        fprintf(Human_Readable_Log,"Do you want Gift Energ ? (Y/N) : ");

                        scanf(" %c", &CC);
                        if (CC == 'y' || CC == 'Y')
                        {
                            fprintf(Human_Readable_Log,"You entered Y\n");
                            SW2 = 0;
                            for (m = 0; m < tedadKolHeyvanha && SW1; m++)
                            {
                                if (XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun)
                                {
                                    listHeyvanha[m].energy += listHeyvanha[i].oneMove;
                                    listHeyvanha[i].energy -= listHeyvanha[i].oneMove;
                                    SW1 = 0;
                                }
                            }
                        }
                    }
                //  End Faz 4 Gift Step
				// HArakat FAZ 2
                if( jahesh==1 && listHeyvanha[i].energy >= energyYekHarkat && SW2 == 1 ){
                	//	1-MOVE 1
                	//	FAZ 3 Tolid Mesl
                	SW3=1;
                	Attack(Human_Readable_Log,listHeyvanha,jahan,abAdJahan,i,tedadKolHeyvanha,SW3);
            		if(SW3 == 1){
            			Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
                		SW1=1;
                		if(Hamsar != -1){
                		    for(m=0;m<tedadKolHeyvanha && SW1;m++){
                		        if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
                                    //printf("FORD : %c : %d\n",listHeyvanha[m].noe,listHeyvanha[m].energy);
                			        EnergyM=listHeyvanha[m].energy;
							        SW1=0;
						        }
						    }
						    m--;
						    SW1=1;
						    EnergyF=listHeyvanha[i].energy;
					        printf("M : %d\nF : %d\n",EnergyM,EnergyF);
                	        fprintf(Human_Readable_Log,"M : %d\nF : %d\n",EnergyM,EnergyF);
                	        if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		        printf("Do you Want Make Child ? (Y/N) : ");
                                fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		        scanf(" %c",&CC);
                		        if(CC == 'Y' || CC == 'y'){
                			        SW1=0;
                                    fprintf(Human_Readable_Log,"You enetered Y\n");
                			        listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			        listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			        PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			        EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			        jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
                			
    			                    printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			        printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							        printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

    		        	            fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
    			                    fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							        fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
						        }
					        }
                	        EnergyAvalie=listHeyvanha[i].energyAvalie;
            
				        }				
                        //	End Tolid Mesl
                	    if(SW1 == 1){
                		    ACTION(Human_Readable_Log,satr,sotun,CC);
                		    if(jahan[satr][sotun] == 'F'){
                			    R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                			    listHeyvanha[i].energy+=R;
						    }
                		    if(CC != 13){
                		        listHeyvanha[i].energy-=listHeyvanha[i].oneMove;
                		
                		        jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
                		        listHeyvanha[i].satr = satr;
                		        listHeyvanha[i].sotun = sotun;
                		        if (jahan[satr][sotun]=='H'){
                			        setTextColor(4,3);
                			        printf("\n***************************\n");
                		            printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		            printf("\n***************************\n");

                                    fprintf(Human_Readable_Log,"\n***************************\n");
                		            fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		            fprintf(Human_Readable_Log,"\n***************************\n");

                		            setTextColor(1,0);
                		            GAMEOVER(Human_Readable_Log,jahan,Size);
                		            return 0;
                		        }
                		
                		        jahan[satr][sotun] = listHeyvanha[i].noe;
					        }                		
				
					    }
                	
					}
				}
                else if(jahesh == 2 && listHeyvanha[i].energy >= energyYekHarkat && SW2 == 1 ){
					//	2-MOVE 1
					//	FAZ 3 Tolid Mesl
					SW3=1;
                	Attack(Human_Readable_Log,listHeyvanha,jahan,abAdJahan,i,tedadKolHeyvanha,SW3);
                	if(SW3 == 1){
                		Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
                		SW1=1;
                	    if(Hamsar != -1){
                		    for(m=0;m<tedadKolHeyvanha && SW1;m++){
                			    if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
	                			    EnergyM=listHeyvanha[m].energy;
								    SW1=0;
							    }
						    }
					        m--;
					        SW1=1;
					        EnergyF=listHeyvanha[i].energy;
                	        if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		        printf("Do you Want Make Child ? (Y/N) : ");
                                fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		        scanf(" %c",&CC);
                		        if(CC == 'Y' || CC == 'y'){
                			        SW1=0;
                                    fprintf(Human_Readable_Log,"You have entered Y\n");
                			        listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			        listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			        PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			        EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			        jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
                			        printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			        printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							        printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

                                    fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			        fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							        fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
						        }
					        }
                	        EnergyAvalie=listHeyvanha[i].energyAvalie;
            
				        }				
                        //	End Tolid Mesl
                
                		if(SW1 == 1){
                			ACTION(Human_Readable_Log,satr,sotun,CC);
                			if(jahan[satr][sotun] == 'F'){
                				R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                				listHeyvanha[i].energy+=R;
							}
                			if(CC != 13){
                				listHeyvanha[i].energy-=listHeyvanha[i].oneMove;           
                				jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
            	    			listHeyvanha[i].satr = satr;
                				listHeyvanha[i].sotun = sotun;
                				if (jahan[satr][sotun]=='H'){
                			        setTextColor(4,3);
                			        printf("\n***************************\n");
                		            printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		            printf("\n***************************\n");

                                    fprintf(Human_Readable_Log,"\n***************************\n");
                		            fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		            fprintf(Human_Readable_Log,"\n***************************\n");

                		            setTextColor(1,0);
                		            GAMEOVER(Human_Readable_Log,jahan,Size);
                		            return 0;
                	            }
                				jahan[satr][sotun] = listHeyvanha[i].noe;
							}
                		
						}
						if(listHeyvanha[i].energy >=listHeyvanha[i].oneMove){
							//	2-MOVE 2
							printf("\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
            			    printf("[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);

                            fprintf(Human_Readable_Log,"\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
            			    fprintf(Human_Readable_Log,"[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
							//	FAZ 3 Tolid Mesl
                            Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
                            //    printf("HAMSAR : %d %d:%d\n",Hamsar,XM,YM);
                            SW1=1;
                            if(Hamsar != -1){
                	            for(m=0;m<tedadKolHeyvanha && SW1;m++){
                		            if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
                			            EnergyM=listHeyvanha[m].energy;
							            SW1=0;
						            }
					            }
				                m--;
				                SW1=1;
				                EnergyF=listHeyvanha[i].energy;
			                    //	printf("M : %d\nF : %d\n",EnergyM,EnergyF);
                                if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		            printf("Do you Want Make Child ? (Y/N) : ");
                                    fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		            scanf(" %c",&CC);
                		            if(CC == 'Y' || CC == 'y'){
                			            SW1=0;
                                        fprintf(Human_Readable_Log,"You Have entered Y\n");
                			            listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			            listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			            PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			            EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			            jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
    						            printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
            			                printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							            printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

                                        fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                                        fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
			             	            fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
							        }
				                }
                                EnergyAvalie=listHeyvanha[i].energyAvalie;           
				            }				
                            //	End Tolid Mesl
                			if(SW1 == 1){
                				ACTION(Human_Readable_Log,satr,sotun,CC);
                				if(jahan[satr][sotun] == 'F'){
                					R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                					listHeyvanha[i].energy+=R;
								}
                				if(CC != 13){
                					listHeyvanha[i].energy-=listHeyvanha[i].oneMove;           
                					jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
            	    				listHeyvanha[i].satr = satr;
                					listHeyvanha[i].sotun = sotun;
                					if (jahan[satr][sotun]=='H'){
                			            setTextColor(4,3);
                			            printf("\n***************************\n");
                		                printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                printf("\n***************************\n");

                                        fprintf(Human_Readable_Log,"\n***************************\n");
                		                fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                fprintf(Human_Readable_Log,"\n***************************\n");

                		                setTextColor(1,0);
                		                GAMEOVER(Human_Readable_Log,jahan,Size);
                		                return 0;
                		            }
                					jahan[satr][sotun] = listHeyvanha[i].noe;
								}
								
							}
                
						}
                        //else marbut be harkat 2 az jahesh 2.
                        else if(listHeyvanha[i].energy < energyYekHarkat){
					        //	Food
					        //	Died
						    printf("The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						    fprintf(Human_Readable_Log,"The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						    ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
               		        ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                		    ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                    	    tedadGhazaHa++;
						    if(listHeyvanha[i].energy > 0){
							    jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
						    }else{
							    jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
						    }
                    	    for(j = i; j < tedadKolHeyvanha; j++){
                    	        listHeyvanha[j] = listHeyvanha[j + 1];
                   		    }
                    		tedadKolHeyvanha--;
                    		i--;
				        }
				
					}
				}
                else if(jahesh == 3 && listHeyvanha[i].energy >= energyYekHarkat && SW2 == 1){
					SW3=1;
                	Attack(Human_Readable_Log,listHeyvanha,jahan,abAdJahan,i,tedadKolHeyvanha,SW3);
                	if(SW3 == 1){
                		
					    if(listHeyvanha[i].energy >=listHeyvanha[i].oneMove){
						    //	3-MOVE 1
						    //	FAZ 3 Tolid Mesl
                		    Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
            			    //	printf("HAMSAR : %d %d:%d\n",Hamsar,XM,YM);
                		    SW1=1;
                	        if(Hamsar != -1){
                		        for(m=0;m<tedadKolHeyvanha && SW1;m++){
                			        if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
                			            EnergyM=listHeyvanha[m].energy;
							            SW1=0;
						            }
					            }
				                m--;
				                SW1=1;
				                EnergyF=listHeyvanha[i].energy;
                                if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		            printf("Do you Want Make Child ? (Y/N) : ");
                                    fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		            scanf(" %c",&CC);
                		            if(CC == 'Y' || CC == 'y'){
                			            SW1=0;
                                        fprintf(Human_Readable_Log,"You have entered Y\n");
                			            listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			            listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			            PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			            EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			            jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
                			
							            printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			            printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							            printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

                                        fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			            fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							            fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
						            }   
				                }
                                EnergyAvalie=listHeyvanha[i].energyAvalie;
            
				            }				
                            //	End Tolid Mesl
						
						    if(SW1 == 1){
							    ACTION(Human_Readable_Log,satr,sotun,CC);
							    if(jahan[satr][sotun] == 'F'){
                				    R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                				    listHeyvanha[i].energy+=R;
							    }
                				if(CC != 13){
                					listHeyvanha[i].energy-=listHeyvanha[i].oneMove;           
                					jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
            	    				listHeyvanha[i].satr = satr;
                					listHeyvanha[i].sotun = sotun;
                					if (jahan[satr][sotun]=='H'){
                			            setTextColor(4,3);
                			            printf("\n***************************\n");
                		                printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                printf("\n***************************\n");

                                        fprintf(Human_Readable_Log,"\n***************************\n");
                		                fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                fprintf(Human_Readable_Log,"\n***************************\n");

                		                setTextColor(1,0);
                		                GAMEOVER(Human_Readable_Log,jahan,Size);
                		                return 0;
                		            }
                					jahan[satr][sotun] = listHeyvanha[i].noe;
								}
                			
						    }
                			if(listHeyvanha[i].energy >=listHeyvanha[i].oneMove){
								//	3-MOVE 2
								printf("\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
            				    printf("[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);

                                fprintf(Human_Readable_Log,"\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
            				    fprintf(Human_Readable_Log,"[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
								//	FAZ 3 Tolid Mesl
                				Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
               					SW1=1;
                				if(Hamsar != -1){
                					for(m=0;m<tedadKolHeyvanha && SW1;m++){
                					    if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
                						   EnergyM=listHeyvanha[m].energy;
										   SW1=0;
									    }
								    }
				                    m--;
				                    SW1=1;
				                    EnergyF=listHeyvanha[i].energy;
                                    if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		                printf("Do you Want Make Child ? (Y/N) : ");
                                        fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		                scanf(" %c",&CC);
                		                if(CC == 'Y' || CC == 'y'){
                			                SW1=0;
                                            fprintf(Human_Readable_Log,"you have entered Y\n");
                			                listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			                listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			                PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			                EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			                jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
                			                printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			                printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							                printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

                                            fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			                fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							                fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
							            }
				                    }
                                    EnergyAvalie=listHeyvanha[i].energyAvalie;
				                }				
                                //	End Tolid Mesl
								if(SW1 == 1){
									ACTION(Human_Readable_Log,satr,sotun,CC);
									if(jahan[satr][sotun] == 'F'){
                						R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                						listHeyvanha[i].energy+=R;
									}
                				    if(CC != 13){
                					    listHeyvanha[i].energy-=listHeyvanha[i].oneMove;           
                					    jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
            	    				    listHeyvanha[i].satr = satr;
                					    listHeyvanha[i].sotun = sotun;
                					    if (jahan[satr][sotun]=='H'){
                			                setTextColor(4,3);
                			                printf("\n***************************\n");
                		                    printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                    printf("\n***************************\n");

                                            fprintf(Human_Readable_Log,"\n***************************\n");
                		                    fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                    fprintf(Human_Readable_Log,"\n***************************\n");

                		                    setTextColor(1,0);
                		                    GAMEOVER(Human_Readable_Log,jahan,Size);
                		                    return 0;
                		                }
                					    jahan[satr][sotun] = listHeyvanha[i].noe;
								    }
							
								}
								if(listHeyvanha[i].energy >=listHeyvanha[i].oneMove){
									//	3-MOVE 3
									printf("\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
                					printf("[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);

                                    fprintf(Human_Readable_Log,"\n[  Your Animal is  %d : %d  ]\n",listHeyvanha[i].satr,listHeyvanha[i].sotun);
                					fprintf(Human_Readable_Log,"[Information {%d} = (E : %d) : ( M = %d ) : ( J = %d ) : ( T = %d ) : ( A = %d ) : ( D = %d ) ]\n",listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].oneMove,listHeyvanha[i].maxJahesh,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
									//	FAZ 3 Tolid Mesl
                					Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha,XM,YM);
                                    //    printf("HAMSAR : %d %d:%d\n",Hamsar,XM,YM);
                                    SW1=1;
                                    if(Hamsar != -1){
                	                    for(m=0;m<tedadKolHeyvanha && SW1;m++){
                		                    if(XM == listHeyvanha[m].satr && YM == listHeyvanha[m].sotun){
                                                //printf("FORD : %c : %d\n",listHeyvanha[m].noe,listHeyvanha[m].energy);
                			                    EnergyM=listHeyvanha[m].energy;
							                    SW1=0;
						                    }
					                    }
				                        m--;
				                        SW1=1;
				                        EnergyF=listHeyvanha[i].energy;
			                            //	printf("M : %d\nF : %d\n",EnergyM,EnergyF);
			                            printf("\nFather information = %d : %d : %d : %c : %d : %d : %d\n",tedadKolHeyvanha,tedadGhazaHa,tedadGuneHa,listHeyvanha[i].noe,listHeyvanha[i].energy,listHeyvanha[i].energyAvalie,listHeyvanha[i].tolidMesl);
                                        fprintf(Human_Readable_Log,"\nFather information = %d : %d : %d : %c : %d : %d : %d\n",tedadKolHeyvanha,tedadGhazaHa,tedadGuneHa,listHeyvanha[i].noe,listHeyvanha[i].energy,listHeyvanha[i].energyAvalie,listHeyvanha[i].tolidMesl);
                                        if(EnergyF >= listHeyvanha[i].tolidMesl && EnergyM >= listHeyvanha[i].tolidMesl){
                		                    printf("Do you Want Make Child ? (Y/N) : ");
                                            fprintf(Human_Readable_Log,"Do you Want Make Child ? (Y/N) : ");
                		                    scanf(" %c",&CC);
                		                    if(CC == 'Y' || CC == 'y'){
                			                    SW1=0;
                                                fprintf(Human_Readable_Log,"You have entered Y\n");
                			                    listHeyvanha[i].energy-=listHeyvanha[i].tolidMesl/2;
                			                    listHeyvanha[m].energy-=listHeyvanha[i].tolidMesl/2;
                			                    PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[m].satr,listHeyvanha[m].sotun, satrBache, sotunBache);
                			                    EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);
                			                    jahan[satrBache][sotunBache] = listHeyvanha[i].noe;
                			                    printf("\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			                    printf("\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							                    printf("\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);

                                                fprintf(Human_Readable_Log,"\n Father information = %c : %d : %d : %d : %d : %d",listHeyvanha[i].noe,listHeyvanha[i].energyAvalie,listHeyvanha[i].energy,listHeyvanha[i].tolidMesl,listHeyvanha[i].attack,listHeyvanha[i].deffend);
                			                    fprintf(Human_Readable_Log,"\n Mother information = %c : %d : %d : %d : %d : %d",listHeyvanha[m].noe,listHeyvanha[m].energyAvalie,listHeyvanha[m].energy,listHeyvanha[m].tolidMesl,listHeyvanha[m].attack,listHeyvanha[m].deffend);
							                    fprintf(Human_Readable_Log,"\n Child information ( %c : %d ) = (%d) : (%d) : (%d) : (%d) : (%d)\n",listHeyvanha[i].noe,E,M,J,T,A,D);
						                    }
				
				                        }
                                        EnergyAvalie=listHeyvanha[i].energyAvalie;
                                        //   	printf("Energy : %d\n",EnergyAvalie);
                                        //   	printf("| Tolid : %d |\n",listHeyvanha[i].tolidMesl);
				                    }				
                                    //	End Tolid Mesl
									
								    if(SW1==1){
										ACTION(Human_Readable_Log,satr,sotun,CC);
										if(jahan[satr][sotun] == 'F'){
                							R=checkDashtanGhaza(ghaza,tedadGhazaHa,satr,sotun);
                							listHeyvanha[i].energy+=R;
										}
				           				if(CC != 13){
            		    					listHeyvanha[i].energy-=listHeyvanha[i].oneMove;           
            		    					jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
            	    						listHeyvanha[i].satr = satr;
                							listHeyvanha[i].sotun = sotun;
                							if (jahan[satr][sotun]=='H'){
                			                    setTextColor(4,3);
                			                    printf("\n***************************\n");
                		                        printf("***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                        printf("\n***************************\n");

                                                fprintf(Human_Readable_Log,"\n***************************\n");
                		                        fprintf(Human_Readable_Log,"***\t%c Won!\t\t***", listHeyvanha[i].noe);
                		                        fprintf(Human_Readable_Log,"\n***************************\n");

                		                        setTextColor(1,0);
                		                        GAMEOVER(Human_Readable_Log,jahan,Size);
                		                        return 0;
                		                    }
                							jahan[satr][sotun] = listHeyvanha[i].noe;
										}
                				
								    }
								}
                                // else marbut be harkat 3 az jahesh 3.
                                else if(listHeyvanha[i].energy < energyYekHarkat){
					                //	Food
					                //	Died
						            printf("The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						            fprintf(Human_Readable_Log,"The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						            ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
               		                ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                		            ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                    	            tedadGhazaHa++;
						            if(listHeyvanha[i].energy > 0){
							            jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
						            }else{
							            jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
						            }
                    	            for(j = i; j < tedadKolHeyvanha; j++){
                    	                listHeyvanha[j] = listHeyvanha[j + 1];
                   		            }
                    		        tedadKolHeyvanha--;
                    		        i--;
				                }
							}
                            // else marbut be harkat 2 az jahesh 3.
                            else if(listHeyvanha[i].energy < energyYekHarkat){
					            //	Food
					            //	Died
					        	printf("The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						        fprintf(Human_Readable_Log,"The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						        ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
               		            ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                		        ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                    	        tedadGhazaHa++;
						        if(listHeyvanha[i].energy > 0){
							        jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
						        }else{
							        jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
						        }
                    	        for(j = i; j < tedadKolHeyvanha; j++){
                    	            listHeyvanha[j] = listHeyvanha[j + 1];
                   		        }
                    		    tedadKolHeyvanha--;
                    		    i--;
				            }
					    }
                        //else marbut be harkat 1 az jahesh 3.
                        else if(listHeyvanha[i].energy < energyYekHarkat){
					        //	Food
					        //	Died
						    printf("The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						    fprintf(Human_Readable_Log,"The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
						    ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
               		        ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                		    ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                    	    tedadGhazaHa++;
						    if(listHeyvanha[i].energy > 0){
							    jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
						    }else{
							    jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
						    }
                    	    for(j = i; j < tedadKolHeyvanha; j++){
                    	        listHeyvanha[j] = listHeyvanha[j + 1];
                   	    	}
                     		tedadKolHeyvanha--;
                    		i--;
				        }
					
					}
				}
                //else marbut be jahesh 1.
                else if(listHeyvanha[i].energy < energyYekHarkat){
					//	Food
					//	Died
					printf("The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
					fprintf(Human_Readable_Log,"The ( %c ) is Died in ( %d ,%d ) \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun);
					ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
               		ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                	ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                    tedadGhazaHa++;
					if(listHeyvanha[i].energy > 0){
						jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
					}else{
						jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
					}
                    for(j = i; j < tedadKolHeyvanha; j++){
                    	listHeyvanha[j] = listHeyvanha[j + 1];
                   	}
                    tedadKolHeyvanha--;
                    i--;
				}


                XM = -3;
                YM = -3;

            
            // gune system.    
            }else {
                sw = 0;
                eghdam = rand() % 3 + 1;
                switch (eghdam){
                    case 1: {
                        printf("%c in (%d,%d) is deciding to attack or donate energy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        fprintf(Human_Readable_Log,"%c in (%d,%d) is deciding to attack or donate energy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        break;
                    }
                    case 2: {
                        printf("%c in (%d,%d) is prepared to give life...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        fprintf(Human_Readable_Log,"%c in (%d,%d) is prepared to give life...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        break;
                    }
                }
                
                if(eghdam == 1){

                    eghdam2 = rand() % 2 + 1;
                    sw2 = 0;

                    if(eghdam2 == 1){

                        printf("%c in (%d,%d) decided to attack...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        fprintf(Human_Readable_Log,"%c in (%d,%d) decided to attack...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        Doshman = checkDashtanGuneMokhalefDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha, tedadKolHeyvanha, listHeyvanha[i].noe,X,Y);
                        
                        if(listHeyvanha[i].energy > 3 * listHeyvanha[i].oneMove && Doshman != -1){

                            printf("%c in (%d,%d) considered %c in (%d,%d) as an enemy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                            printf("%c in (%d,%d) attacked %c in (%d,%d)...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);

                            fprintf(Human_Readable_Log,"%c in (%d,%d) considered %c in (%d,%d) as an enemy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                            fprintf(Human_Readable_Log,"%c in (%d,%d) attacked %c in (%d,%d)...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                            listHeyvanha[i].energy -= 3 * listHeyvanha[i].oneMove;
                            
                            // agar energy hamle heyvan bishtar az energy defa doshman bashad:
                            if(listHeyvanha[i].attack > listHeyvanha[Doshman].deffend){
                                listHeyvanha[i].energy += listHeyvanha[Doshman].energy;
                                jahan[listHeyvanha[Doshman].satr][listHeyvanha[Doshman].sotun] = '.';
                                
                                printf("%c in (%d,%d) won the war with %c in (%d,%d)\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                                printf("%c in (%d,%d) gets the %c's energy.\nNow %c's energy is %d.\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[i].noe, listHeyvanha[i].energy);

                                fprintf(Human_Readable_Log,"%c in (%d,%d) won the war with %c in (%d,%d)\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                                fprintf(Human_Readable_Log,"%c in (%d,%d) gets the %c's energy.\nNow %c's energy is %d.\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[i].noe, listHeyvanha[i].energy);

                                j = Doshman;
                                for(; j < tedadKolHeyvanha; j++){
                                    listHeyvanha[j] = listHeyvanha[j + 1];
                                }
                                tedadKolHeyvanha--;
                                if(i>Doshman) i--;
                                
                            }
                            // agar energy defa doshman bishtar az energy hamle heyvan bashad:
                            else if(listHeyvanha[Doshman].deffend > listHeyvanha[i].attack){
                                listHeyvanha[Doshman].energy += listHeyvanha[i].energy;
                                jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
                                
                                
                                printf("%c in (%d,%d) lost the war and get killed by %c in (%d,%d).\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                                printf("%c in (%d,%d) gets the %c's energy\nNow %c's energy is %d.\n", listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun, listHeyvanha[i].noe, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].energy);

                                fprintf(Human_Readable_Log,"%c in (%d,%d) lost the war and get killed by %c in (%d,%d).\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun);
                                fprintf(Human_Readable_Log,"%c in (%d,%d) gets the %c's energy\nNow %c's energy is %d.\n", listHeyvanha[Doshman].noe, listHeyvanha[Doshman].satr, listHeyvanha[Doshman].sotun, listHeyvanha[i].noe, listHeyvanha[Doshman].noe, listHeyvanha[Doshman].energy);
                                
                                j = i;
                                for(; j < tedadKolHeyvanha; j++){
                                    listHeyvanha[j] = listHeyvanha[j + 1];
                                }
                                tedadKolHeyvanha--;
                                i--;

                            }
                        }
                        else {
                            sw2 = 1;
                            printf("The attack failed!\n");
                            fprintf(Human_Readable_Log,"The attack failed!\n");
                        }

                    }

                    if(eghdam2 == 2 || sw2 == 1){
                        printf("%c in (%d,%d) decided to donate energy...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        fprintf(Human_Readable_Log,"%c in (%d,%d) decided to donate energy...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        Dust = DustBarayeEhda(listHeyvanha, tedadKolHeyvanha, i);

                        if(Dust == -1){
                            sw = 1;
                        }
                        else{
                            printf("%c in (%d,%d) considered %c in (%d,%d) as a friend to donate energy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Dust].noe, listHeyvanha[Dust].satr, listHeyvanha[Dust].sotun);
                            fprintf(Human_Readable_Log,"%c in (%d,%d) considered %c in (%d,%d) as a friend to donate energy...\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Dust].noe, listHeyvanha[Dust].satr, listHeyvanha[Dust].sotun);
                        }

                        if(listHeyvanha[i].energy > listHeyvanha[i].oneMove && sw == 0){

                            listHeyvanha[i].energy -= listHeyvanha[i].oneMove;
                            listHeyvanha[Dust].energy += listHeyvanha[i].oneMove;

                            printf("energy for One move passed frome %c in (%d,%d) to %c in (%d,%d).\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Dust].noe, listHeyvanha[Dust].satr, listHeyvanha[Dust].sotun);
                            fprintf(Human_Readable_Log,"energy for One move passed frome %c in (%d,%d) to %c in (%d,%d).\n",listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Dust].noe, listHeyvanha[Dust].satr, listHeyvanha[Dust].sotun);
                        }

                        else{
                            sw = 1;
                        }
                    }
                }

                // tolid mesl mikonad.
                if(eghdam == 2 || sw == 1){

                    if(sw == 1){
                        printf("Donating failed!\n");
                        fprintf(Human_Readable_Log,"Donating failed!\n");
                    }

                    Hamsar = CheckDashtanGuneMovafeghDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[i].noe, listHeyvanha, tedadKolHeyvanha, XM, YM);

                    if(Hamsar == -1){
                        sw = 2;
                    }

                    if(listHeyvanha[i].energy >= listHeyvanha[i].tolidMesl && listHeyvanha[Hamsar].energy >= listHeyvanha[Hamsar].tolidMesl && (sw == 0 || sw == 1)){
                        PeidaKardanNazdikTarinMakanKhali(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Hamsar].satr,listHeyvanha[Hamsar].sotun, satrBache, sotunBache);
                        EzafeKardanBacheBeList(listHeyvanha, tedadKolHeyvanha, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].energyAvalie,E,M,J,T,A,D);

                        jahan[satrBache][sotunBache] = listHeyvanha[i].noe;

                        listHeyvanha[i].energy -= listHeyvanha[i].tolidMesl / 2;
                        listHeyvanha[Hamsar].energy -= listHeyvanha[Hamsar].tolidMesl / 2;

                        printf("%c in (%d,%d) created by %c in (%d,%d) and %c in (%d,%d).\n",listHeyvanha[i].noe, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Hamsar].noe, listHeyvanha[Hamsar].satr, listHeyvanha[Hamsar].sotun);
                        fprintf(Human_Readable_Log,"%c in (%d,%d) created by %c in (%d,%d) and %c in (%d,%d).\n",listHeyvanha[i].noe, satrBache, sotunBache, listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha[Hamsar].noe, listHeyvanha[Hamsar].satr, listHeyvanha[Hamsar].sotun);
                    }

                    else{
                        sw = 2;
                    }

                }
                
                // harkat mikonad.
                if(eghdam == 3 || sw == 2){

                    if(sw == 2){
                        printf("giving birth failed!\n");
                        fprintf(Human_Readable_Log,"giving birth failed!\n");
                    }
                    
                    printf("%c in (%d,%d) decided to move...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                    fprintf(Human_Readable_Log,"%c in (%d,%d) decided to move...\n", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);

                    peidaKardanNazdikTarinBehesht(beheshtHa, tedadBeheshtha, listHeyvanha[i].satr, listHeyvanha[i].sotun, satrnb, sotunnb); //nb:nazdiktarin behesht.
                    vaziat = harkatHeyvan(Human_Readable_Log,jahan, satrnb, sotunnb, listHeyvanha[i].satr, listHeyvanha[i].sotun, abAdJahan, beheshtHa, tedadBeheshtha, listHeyvanha[i].noe, listHeyvanha[i].maxJahesh, listHeyvanha[i].energy, listHeyvanha[i].oneMove);
                    if (vaziat == 1) {

                        printf("%c Won!", listHeyvanha[i].noe);
                        fprintf(Human_Readable_Log,"%c Won!", listHeyvanha[i].noe);
                        GAMEOVER(Human_Readable_Log,jahan,Size);
                        return 0;

                    }else if(vaziat == 2){

                        printf("%c diad in (%d,%d). ", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        fprintf(Human_Readable_Log,"%c diad in (%d,%d). ", listHeyvanha[i].noe, listHeyvanha[i].satr, listHeyvanha[i].sotun);
                        jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';

                        ghaza[tedadGhazaHa][0] = listHeyvanha[i].energy;
                        ghaza[tedadGhazaHa][1] = listHeyvanha[i].satr;
                        ghaza[tedadGhazaHa][2] = listHeyvanha[i].sotun;
                        tedadGhazaHa++;
                        jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = 'F';
                    
                        j = i;
                        for(; j < tedadKolHeyvanha; j++){
                            listHeyvanha[j] = listHeyvanha[j + 1];
                        }
                        tedadKolHeyvanha--;
                        i--;

                    }else {
                        listHeyvanha[i].energy += checkDashtanGhaza(ghaza,tedadGhazaHa,listHeyvanha[i].satr,listHeyvanha[i].sotun);
                    } 
            	}

                mysleep(2000);
                
            }
            
			if(tedadKolHeyvanha == 0){
            	GAMEOVER(Human_Readable_Log,jahan,abAdJahan);
                return 0;
			}else{
				GetPrintf(Human_Readable_Log,jahan, abAdJahan);
			}
            
            Save(abAdJahan, tedadBlockHa, blockHa, tedadBeheshtha, beheshtHa, tedadGhazaHa, ghaza, listHeyvanha, tedadKolHeyvanha, guneMoredNazar);
        }
        mysleep(3000);
    }
	return 0;
}

void gotoxy(int x, int y){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = y;
    cursorCoord.Y = x;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
void clearScreen() {
    system("cls");
}
void mysleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void PrintLine(FILE *file,int a) {
    int i;
    printf("\n");
    fprintf(file,"\n");
    for (i = 0; i <= a; i++) {
        printf("----");
        fprintf(file,"----");
    }
    printf("\n");
    fprintf(file,"\n");
}
void GetPrintf(FILE *file,char A[][Boud2], int size) {
    int i=0, j=0,k=0;
    PrintLine(file ,size);
    printf("      ");
    fprintf(file,"      ");
    setTextColor(14);
    for(i=0;i<size;i++){
    	if(i<10){
    		printf(" %d ",i);
            fprintf(file," %d ",i);
		}else{
			printf(" %d",i);
            fprintf(file," %d",i);
		}
	}
	printf("\n      ");
    fprintf(file,"\n      ");
	for(i=0;i<size;i++){
		printf("---");
        fprintf(file,"---");
	}
	printf("\n");
    fprintf(file,"\n");
    for (i = 0; i < size; i++) {
    	setTextColor(14);
    	if(i<10){
    		printf("   %d |",i);
            fprintf(file,"   %d |",i);
		}else{
			printf("  %d |",i);
            fprintf(file,"  %d |",i);
		}
        for (j = 0; j < size; j++) {
        	if(A[i][j] == 72 ){
        		setTextColor(7,2);
        		printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 35 ){
				setTextColor(0,4);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 46 ){
				setTextColor(6);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 70 ){
				setTextColor(4,11);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 65 ){
				setTextColor(3);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 66 ){
				setTextColor(10);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 67 ){
				setTextColor(14);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 68 ){
				setTextColor(6);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}else
			if(A[i][j] == 69 ){
				setTextColor(12);
				printf(" %c ", A[i][j]);
                fprintf(file," %c ", A[i][j]);
			}
			else{
                setTextColor(6);
                printf(" . ");
                fprintf(file," . ");
            }
            
        }
        setTextColor(14);
    	if(i<10){
    		printf("| %d\t",i);
            fprintf(file,"| %d\t",i);
		}else{
			printf("| %d\t",i);
            fprintf(file,"| %d\t",i);
		}
        if(i != size-1){
        	printf("\n     |");
            fprintf(file,"\n     |");
       		for(k=0;k<size;k++){
        		printf("   ");
                fprintf(file,"   ");
			}
			printf("|\n");
            fprintf(file,"|\n");
		}
    }
    printf("\n      ");
    fprintf(file,"\n      ");
    setTextColor(14);
	for(i=0;i<size;i++){
		printf("---");
        fprintf(file,"---");
	}
	printf("\n      ");
    fprintf(file,"\n      ");
    for(i=0;i<size;i++){
    	if(i<10){
    		printf(" %d ",i);
            fprintf(file," %d ",i);
		}else{
			printf(" %d",i);
            fprintf(file," %d",i);
		}
	}
	setTextColor(10);
    PrintLine(file,size);
    printf("\n\n");
    fprintf(file,"\n\n");
    
};
void GetWorld(char A[][Boud2], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            A[i][j] = 46;
            //	printf("%c ",A[i][j]);
        }
        //	printf("\n\n");
    }
};
void GetBlock(char A[][Boud2], FILE *map, int blockHa[][2], int &size) {
    int i;
    char C;
    fscanf(map, " %c", &C);
    fscanf(map, "%d", &size);
    for (i = 0; i < size; i++) {
        fscanf(map, " %c", &C);
        fscanf(map, "%d%c%d", &blockHa[i][0], &C, &blockHa[i][1]);
        fscanf(map, " %c", &C);
        A[blockHa[i][0]][blockHa[i][1]] = 35;
    }
};
void GetHeaven(char A[][Boud2],int B[][2],int &size, FILE *map) {
    int i, j, x, y;
    char C;
    fscanf(map, " %c", &C);
    fscanf(map, "%d", &size);
    for (i = 0; i < size; i++) {
        fscanf(map, " %c", &C);
        fscanf(map, "%d%c%d", &x, &C, &y);
        fscanf(map, " %c", &C);
        B[i][0]=x;
        B[i][1]=y;
        A[x][y] = 72;
    }
};
void GetFood(int A[][3],char Chart[][Boud2], FILE *map, int &i) {
    int j, x, y, Energy;
    char C;
    i = 0;
    fscanf(map, " %c", &C);
    do {
    	fscanf(map, "%d", &Energy);
        fscanf(map, " %c %d %c %d %c", &C, &x, &C, &y, &C);
        Chart[x][y]='F';
        A[i][0]=Energy;
        A[i][1]=x;
		A[i][2]=y;
        i++;
        fscanf(map, " %c", &C);
    } while (C != 61);
};
void ACTION(FILE *file,int &x,int &y,char &C){
	char CC;
	setTextColor(7);
	printf("\n\t\tW=UP\t\tS=DOWN\t\tA=LEFT\t\tD=RIGHT\n\t\tQ=LeftTop\tE=RightTop\tZ=DownLeft\tC=DownRight\n");
    fprintf(file,"\n\t\tW=UP\t\tS=DOWN\t\tA=LEFT\t\tD=RIGHT\n\t\tQ=LeftTop\tE=RightTop\tZ=DownLeft\tC=DownRight\n");

	setTextColor(13);
	printf("\t\n Enter Your Key : ");
    fprintf(file,"\t\n Enter Your Key : ");

	CC=getch();
	C=CC;
//	scanf(" %c",&CC);
	printf("%c",CC);
    fprintf(file,"%c",CC);
	if(CC != 13){
		switch(CC){
		case 'a':
			case 'A': {
				y--;
				break;
			}
		case 'd':
			case 'D': {
				y++;
				break;
			}
		case 'w':
			case 'W': {
				x--;
				break;
			}
		case 's':
			case 'S': {
				x++;
				break;
			}
		case 'q':
			case 'Q': {
				x--;
				y--;
				break;
			}
		case 'e':
			case 'E': {
				x--;
				y++;
				break;
			}
		case 'z':
			case 'Z': {
				x++;
				y--;
				break;
			}
		case 'c':
			case 'C': {
				x++;
				y++;
				break;
			}
		}
	}
};
void Attack(FILE *file,struct heyvan listHeyvanha[],char jahan[][20],int size,int &i,int &tedadKolHeyvanha,int &SW){
	int Doshman,icount,j,k,XE,YE;
	char CC;
	SW=1;
	Doshman = checkDashtanGuneMokhalefDarAtraf(jahan, listHeyvanha[i].satr, listHeyvanha[i].sotun, listHeyvanha, tedadKolHeyvanha, listHeyvanha[i].noe,XE,YE);
	if(Doshman != -1){
		printf("Your Animal is (%c) (%d,%d) : E %d : A %d : D %d \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun,listHeyvanha[i].energy,listHeyvanha[i].attack,listHeyvanha[i].deffend);
		printf("Enemy Animal is (%d,%d) : ",XE,YE);
		printf("Do You Want to Attack ? (Y/N) : ");

        fprintf(file,"Your Animal is (%c) (%d,%d) : E %d : A %d : D %d \n",listHeyvanha[i].noe,listHeyvanha[i].satr,listHeyvanha[i].sotun,listHeyvanha[i].energy,listHeyvanha[i].attack,listHeyvanha[i].deffend);
		fprintf(file,"Enemy Animal is (%d,%d) : ",XE,YE);
		fprintf(file,"Do You Want to Attack ? (Y/N) : ");
		
		scanf(" %c",&CC);
		if(CC == 'Y' || CC == 'y'){
            fprintf(file,"You Have entered Y\n");
			
			for(icount=0;icount<tedadKolHeyvanha;icount++){
				if(listHeyvanha[icount].satr == XE && listHeyvanha[icount].sotun == YE){
					if( listHeyvanha[i].energy >= (listHeyvanha[i].oneMove*3) ){
						listHeyvanha[i].energy -= (listHeyvanha[i].oneMove*3);
						printf("Enemy Animal is (%c) (%d,%d) : E %d : A %d : D %d \n",listHeyvanha[icount].noe,XE,YE,listHeyvanha[icount].energy,listHeyvanha[icount].attack,listHeyvanha[icount].deffend);
                    	fprintf(file,"Enemy Animal is (%c) (%d,%d) : E %d : A %d : D %d \n",listHeyvanha[icount].noe,XE,YE,listHeyvanha[icount].energy,listHeyvanha[icount].attack,listHeyvanha[icount].deffend);
					SW=0;
					if( listHeyvanha[i].attack > listHeyvanha[icount].deffend ){
						jahan[listHeyvanha[icount].satr][listHeyvanha[icount].sotun] = '.';
						listHeyvanha[i].energy += listHeyvanha[icount].energy;
                    	printf("The (%c) is Died by (%c)\n",listHeyvanha[icount].noe,listHeyvanha[i].noe);
                    	printf("(A : %d) : (E : %d) : (D : %d)\n",listHeyvanha[i].energy,listHeyvanha[icount].energy,i);

                        fprintf(file,"The (%c) is Died by (%c)\n",listHeyvanha[icount].noe,listHeyvanha[i].noe);
                    	fprintf(file,"(A : %d) : (E : %d) : (D : %d)\n",listHeyvanha[i].energy,listHeyvanha[icount].energy,i);

                    	for(j = icount; j < tedadKolHeyvanha; j++){
                    	    listHeyvanha[j] = listHeyvanha[j + 1];
                    	}
                    	tedadKolHeyvanha--;
                    	if(i>icount) i--;
                    	
					}else {
						jahan[listHeyvanha[i].satr][listHeyvanha[i].sotun] = '.';
						listHeyvanha[icount].energy += listHeyvanha[i].energy;
                    	printf("The (%c) is Died by (%c)\n",listHeyvanha[i].noe,listHeyvanha[icount].noe);
                    	printf("(A : %d) : (E : %d) : (D : %d)\n",listHeyvanha[i].energy,listHeyvanha[icount].energy,i);

                        fprintf(file,"The (%c) is Died by (%c)\n",listHeyvanha[i].noe,listHeyvanha[icount].noe);
                    	fprintf(file,"(A : %d) : (E : %d) : (D : %d)\n",listHeyvanha[i].energy,listHeyvanha[icount].energy,i);

                    	for(j = i; j < tedadKolHeyvanha; j++){
                    	    listHeyvanha[j] = listHeyvanha[j + 1];
                    	}
                    	tedadKolHeyvanha--;
                    	i--;
					}
				
					}else{
						SW=1;
						printf("You Don't Have Energy For Attack\n");
						fprintf(file,"You Don't Have Energy For Attack\n");
					}
					
				}
			}
		}
	}
	
};
// in tabe satr va sotun nazdiktarin behesht ra bar migardanad.
void peidaKardanNazdikTarinBehesht(int beheshtHa[][2], int tedadBeheshtHa, int satrheyvan, int sotunheyvan, int& satrnb, int& sotunnb) {
    int faselemin = 40;
    int i, faseleSatr, faseleSotun, fasele;
	
    for (i = 0; i < tedadBeheshtHa; i++) {
        faseleSatr = satrheyvan - beheshtHa[i][0];
        if (faseleSatr < 0) faseleSatr *= -1;

        faseleSotun = sotunheyvan - beheshtHa[i][1];
        if (faseleSotun < 0) faseleSotun *= -1;

        fasele = faseleSatr + faseleSotun;
        if (fasele < faselemin) {
            faselemin = fasele;
            satrnb = beheshtHa[i][0];
            sotunnb = beheshtHa[i][1];
        }
    }
}
// in tabe heyvan hayi ke dast ma nistand ra harkat midahad.
int harkatHeyvan(FILE *file,char jahan[][20], int satrb, int sotunb, int& satrh, int& sotunh, int AbAdjahan, int beheshtHa[][2], int tedadbeheshtha, char noe, int maxJahesh, int &energy, int OneMove) {
    int jahesh,i;
    if (satrh < satrb) {
        if (jahan[satrh + 1][sotunh] != 'H' && jahan[satrh + 1][sotunh] != '.' && jahan[satrh + 1][sotunh] != 'F') {
            if (sotunb > sotunh) {
                if(energy < OneMove){
                    return 2;
                }
                satrh++;
                sotunh++;
                energy -= OneMove;
                printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                if (jahan[satrh][sotunh]=='H') {
                    return 1;
                }
                jahan[satrh - 1][sotunh - 1] = '.';
                jahan[satrh][sotunh] = noe;
            }
            else if (sotunb < sotunh) {
                if(energy < OneMove){
                    return 2;
                }
                satrh++;
                sotunh--;
                energy -= OneMove;
                printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                if (jahan[satrh][sotunh]=='H') {
                    return 1;
                }
                jahan[satrh - 1][sotunh + 1] = '.';
                jahan[satrh][sotunh] = noe;
            }
            else {
                if (sotunh + 1 <= AbAdjahan) {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh++;
                    sotunh++;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh - 1][sotunh - 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
                else {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh++;
                    sotunh--;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh - 1][sotunh + 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
            }
        }
        else {
            jahesh=rand()%maxJahesh+1;
            for(i=satrh+1;i<=satrh+jahesh;i++){
                if(jahan[i][sotunh]=='#' || (jahan[i][sotunh]>64 && jahan[i][sotunh]<70) ||  (jahan[i][sotunh]>70 && jahan[i][sotunh]<91)){
                    jahesh=i-satrh-1;
                    break;
                }
                if(jahan[i][sotunh]=='H'){

                    if(energy > (i - satrh) * OneMove){
                        printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,i,sotunh);
                        fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,i,sotunh);
                        return 1;
                    } 
                    else {
                        jahesh = i - satrh -1;
                        break;
                    }

                }
                if(i==satrb){
                    jahesh=i-satrh;
                    break;
                }
            }

            while(energy < jahesh * OneMove){
                jahesh--;
            }
            if(jahesh < 1) return 2;
            energy -= jahesh * OneMove;

            satrh+=jahesh;
            printf("%c moved from (%d,%d) to (%d,%d)\n",noe,satrh-jahesh,sotunh,satrh,sotunh);
            fprintf(file,"%c moved from (%d,%d) to (%d,%d)\n",noe,satrh-jahesh,sotunh,satrh,sotunh);
            jahan[satrh-jahesh][sotunh]='.';
            jahan[satrh][sotunh]=noe;
        }
    }
    else if (satrh > satrb) {
        if (jahan[satrh - 1][sotunh] != 'H' && jahan[satrh - 1][sotunh] != '.' && jahan[satrh + 1][sotunh] != 'F') {
            if (sotunh < sotunb) {
                if(energy < OneMove){
                    return 2;
                }
                satrh--;
                sotunh++;
                energy -= OneMove;
                printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                if (jahan[satrh][sotunh]=='H') {
                    return 1;
                }
                jahan[satrh + 1][sotunh - 1] = '.';
                jahan[satrh][sotunh] = noe;
            }
            else if (sotunh > sotunb) {
                if(energy < OneMove){
                    return 2;
                }
                satrh--;
                sotunh--;
                energy -= OneMove;
                printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                if (jahan[satrh][sotunh]=='H') {
                    return 1;
                }
                jahan[satrh + 1][sotunh + 1] = '.';
                jahan[satrh][sotunh] = noe;
            }
            else {
                if (sotunh + 1 <= AbAdjahan) {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh--;
                    sotunh++;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh + 1][sotunh - 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
                else {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh--;
                    sotunh--;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh + 1][sotunh + 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
            }
        }
        else {
            jahesh=rand()%maxJahesh+1;
            for(i=satrh-1;i>=satrh-jahesh;i--){
                if(jahan[i][sotunh]=='#' || (jahan[i][sotunh] > 64 && jahan[i][sotunh] < 70) || (jahan[i][sotunh] > 70 && jahan[i][sotunh] < 91)){
                    jahesh=satrh-i-1;
                    break;
                }
                if(jahan[i][sotunh]=='H'){
                    if(energy > (satrh - i) * OneMove){
                        printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,i,sotunh);
                        fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,i,sotunh);
                        return 1;
                    }
                    else{
                        jahesh = satrh - i - 1;
                        break;
                    }
                }
                if(i==satrb){
                    jahesh=satrh-i;
                    break;
                }
            }

            while(energy < jahesh * OneMove){
                jahesh--;
            }
            if(jahesh < 1) return 2;
            energy -= jahesh * OneMove;

            satrh-=jahesh;
            printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh+jahesh,sotunh,satrh,sotunh);
            fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh+jahesh,sotunh,satrh,sotunh);
            jahan[satrh+jahesh][sotunh]='.';
            jahan[satrh][sotunh]=noe;
        }
    }
    else if (satrh == satrb) {
        if (sotunh < sotunb) {
            if (jahan[satrh][sotunh + 1] != 'H' && jahan[satrh][sotunh + 1] != '.' && jahan[satrh + 1][sotunh] != 'F') {
                if (satrh - 1 >= 0) {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh--;
                    sotunh++;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh - 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh + 1][sotunh - 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
                else {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh++;
                    sotunh++;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh - 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh - 1][sotunh - 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
            }
            else {
                jahesh=rand()%maxJahesh+1;
                for(i=sotunh+1;i<=sotunh+jahesh;i++){
                    if(jahan[satrh][i]=='#' || (jahan[satrh][i] > 64 && jahan[satrh][i] < 70) || (jahan[satrh][i] > 70 && jahan[satrh][i] < 91)){
                        jahesh=i-sotunh-1;
                        break;
                    }
                    if(jahan[satrh][i]=='H'){
                        if(energy > (i - sotunh) * OneMove){
                            printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,satrh,i);
                            fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,satrh,i);
                            return 1;
                        }
                        else{
                            jahesh = i - sotunh - 1;
                            break;
                        }
                    }
                }

                while(energy < jahesh * OneMove){
                    jahesh--;
                }
                if(jahesh < 1) return 2;
                energy -= jahesh * OneMove;

                sotunh+=jahesh;
                printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh-jahesh,satrh,sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh-jahesh,satrh,sotunh);
                jahan[satrh][sotunh-jahesh]='.';
                jahan[satrh][sotunh]=noe;
            }
        }
        else if (sotunh > sotunb) {
            if (jahan[satrh][sotunh - 1] != 'H' && jahan[satrh][sotunh - 1] != '.' && jahan[satrh + 1][sotunh] != 'F') {
                if (satrh - 1 >= 0) {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh--;
                    sotunh--;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh + 1, sotunh + 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh + 1][sotunh + 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
                else {
                    if(energy < OneMove){
                        return 2;
                    }
                    satrh++;
                    sotunh--;
                    energy -= OneMove;
                    printf("%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                    fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n", noe, satrh - 1, sotunh + 1, satrh, sotunh);
                    if (jahan[satrh][sotunh]=='H') {
                        return 1;
                    }
                    jahan[satrh - 1][sotunh + 1] = '.';
                    jahan[satrh][sotunh] = noe;
                }
            }
            else {
                jahesh=rand()%maxJahesh+1;
                for(i=sotunh-1;i>=sotunh-jahesh;i--){
                    if(jahan[satrh][i]=='#' || (jahan[satrh][i] > 64 && jahan[satrh][i] < 70) || (jahan[satrh][i] > 70 && jahan[satrh][i] < 91)){
                        jahesh=sotunh-i+1;
                        break;
                    }
                    if(jahan[satrh][i]=='H'){
                        if(energy > (sotunh - i) * OneMove){
                            printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,satrh,i);
                            fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh,satrh,i);
                            return 1;
                        }
                        else{
                            jahesh = sotunh - i + 1;
                            break;
                        }
                    }
                }

                while(energy < jahesh * OneMove){
                    jahesh--;
                }
                if(jahesh < 1) return 2;
                energy -= jahesh * OneMove;

                sotunh-=jahesh;
                printf("%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh+jahesh,satrh,sotunh);
                fprintf(file,"%c moved frome (%d,%d) to (%d,%d)\n",noe,satrh,sotunh+jahesh,satrh,sotunh);
                jahan[satrh][sotunh+jahesh]='.';
                jahan[satrh][sotunh]=noe;
            }
        }
    }

    return 0;
}

int checkDashtanGhaza(int ghaza[][3], int &tedadGhaza, int satr, int sotun){
    int i;
    for(i=0; i<tedadGhaza; i++){
        if(ghaza[i][1] == satr && ghaza[i][2] == sotun){
            return (ghaza[i][0]);
        }
    }
    for(;i<tedadGhaza;i++){
    	ghaza[i][0]=ghaza[i+1][0];
    	ghaza[i][1]=ghaza[i+1][1];
    	ghaza[i][2]=ghaza[i+1][2];
	}
	tedadGhaza--;
    return 0;
}

int CheckDashtanGuneMovafeghDarAtraf(char jahan[][20], int satrh, int sotunh, char noe, struct heyvan listHeyvanat[100], int tedadKolHeyvanat,int &XM,int &YM){
    int SH;
    if(jahan[satrh - 1][sotunh] == noe){
        SH = SHomareHamsar(satrh-1, sotunh,listHeyvanat,tedadKolHeyvanat);
        XM=satrh-1;
        YM=sotunh;
        return SH;
    }
    else if(jahan[satrh - 1][sotunh - 1] == noe){
        SH = SHomareHamsar(satrh - 1, sotunh - 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh-1;
        YM=sotunh-1;
        return SH;
    }
    else if(jahan[satrh][sotunh - 1] == noe){
        SH = SHomareHamsar(satrh, sotunh - 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh;
        YM=sotunh-1;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh - 1] == noe){
        SH = SHomareHamsar(satrh + 1, sotunh - 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh+1;
        YM=sotunh-1;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh] == noe){
        SH = SHomareHamsar(satrh + 1, sotunh,listHeyvanat,tedadKolHeyvanat);
        XM=satrh+1;
        YM=sotunh;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh + 1] == noe){
        SH = SHomareHamsar(satrh + 1, sotunh + 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh+1;
        YM=sotunh+1;
        return SH;
    }
    else if(jahan[satrh][sotunh + 1] == noe){
        SH = SHomareHamsar(satrh, sotunh + 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh;
        YM=sotunh+1;
        return SH;
    }
    else if(jahan[satrh - 1][sotunh + 1] == noe){
        SH = SHomareHamsar(satrh - 1, sotunh + 1,listHeyvanat,tedadKolHeyvanat);
        XM=satrh-1;
        YM=sotunh+1;
        return SH;
    }

        return -1;
}

int SHomareHamsar(int satr, int sotun, struct heyvan listHeyvanat[], int tedadKolHeyvanat){
    for(int i=0; i < tedadKolHeyvanat; i++){
        if(satr == listHeyvanat[i].satr && sotun == listHeyvanat[i].sotun){
            return i;
        }
    }

    return -1;
}

void PeidaKardanNazdikTarinMakanKhali(char jahan[][20], int satrh, int sotunh, int satrHamsar, int sotunHamsar, int &satrBache, int &sotunBache){
    int i = 1,sw = 0;
    if(jahan[satrh][sotunHamsar] == '.'){
        satrBache = satrh;
        sotunBache = sotunHamsar;
    }
    else if(jahan[satrHamsar][sotunh] == '.'){
        satrBache = satrHamsar;
        sotunBache = sotunh;
    }
    else{
        if(satrh == satrHamsar){
            while(1){
                if(jahan[satrh - i][sotunh] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh;
                    break;
                }
                if(jahan[satrh - i][sotunh - i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh - i;
                    break;
                }
                if(jahan[satrh][sotunh - i] == '.'){
                    satrBache = satrh;
                    sotunBache = sotunh - i;
                    break;
                }
                if(jahan[satrh + i][sotunh - i] == '.'){
                    satrBache = satrh + i;
                    sotunBache = sotunh - i;
                    break;
                }
                if(jahan[satrh + i][sotunh] == '.'){
                    satrBache = satrh + i;
                    sotunBache = sotunh;
                    break;
                }
                if(jahan[satrh - i][sotunh + i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh + i;
                    break;
                }
                if(jahan[satrh][sotunh + i] == '.'){
                    satrBache = satrh;
                    sotunBache = sotunh + i;
                    break;
                }
                if(jahan[satrh - i][sotunh + i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh + i;
                    break;
                }
            }
        }
        else{
            while(1){
                if(jahan[satrh][sotunh - i] == '.'){
                    satrBache = satrh;
                    sotunBache = sotunh - i;
                    break;
                }
                if(jahan[satrh + i][sotunh - i] == '.'){
                    satrBache = satrh + i;
                    sotunBache = sotunh - i;
                    break;
                }
                if(jahan[satrh + i][sotunh] == '.'){
                    satrBache = satrh + i;
                    sotunBache = sotunh;
                    break;
                }
                if(jahan[satrh - i][sotunh + i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh + i;
                    break;
                }
                if(jahan[satrh][sotunh + i] == '.'){
                    satrBache = satrh;
                    sotunBache = sotunh + i;
                    break;
                }
                if(jahan[satrh - i][sotunh + i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh + i;
                    break;
                }
                if(jahan[satrh - i][sotunh] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh;
                    break;
                }
                if(jahan[satrh - i][sotunh - i] == '.'){
                    satrBache = satrh - i;
                    sotunBache = sotunh - i;
                    break;
                }
            }
        }
    }
}

void EzafeKardanBacheBeList(struct heyvan listHeyvanat[], int &tedadKolHeyvanat, int satrBache, int sotunBache, char noe, int energy,int &E,int &M,int &J,int &T,int &A,int &D){
	listHeyvanat[tedadKolHeyvanat].noe = noe;
    listHeyvanat[tedadKolHeyvanat].satr = satrBache;
    listHeyvanat[tedadKolHeyvanat].sotun = sotunBache;
    listHeyvanat[tedadKolHeyvanat].energy =E= energy;
    listHeyvanat[tedadKolHeyvanat].oneMove =M= rand() % 181 + 20;
    listHeyvanat[tedadKolHeyvanat].maxJahesh =J= rand() % 3 + 1;
    listHeyvanat[tedadKolHeyvanat].tolidMesl =T= rand() % 541 + 60;
    listHeyvanat[tedadKolHeyvanat].attack =A= rand() % 481 + 20;
    listHeyvanat[tedadKolHeyvanat].deffend =D= rand() % 481 + 20;

    tedadKolHeyvanat++;
}

int checkDashtanGuneMokhalefDarAtraf(char jahan[][20], int satrh, int sotunh, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, char noeh,int &XE,int &YE){
    int SH;

    if(jahan[satrh - 1][sotunh] != '.' && jahan[satrh - 1][sotunh] != 'F' && jahan[satrh - 1][sotunh] != noeh && jahan[satrh - 1][sotunh] != 'H' && jahan[satrh - 1][sotunh] != '#'){
        SH = ShomarandeDoshman(satrh - 1, sotunh, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh - 1;
        YE=sotunh;
        return SH;
    }
    else if(jahan[satrh - 1][sotunh - 1] != '.' && jahan[satrh - 1][sotunh - 1] != 'F' && jahan[satrh - 1][sotunh - 1] != noeh && jahan[satrh - 1][sotunh - 1] != 'H' && jahan[satrh - 1][sotunh - 1] != '#'){
        SH = ShomarandeDoshman(satrh - 1, sotunh - 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh - 1;
        YE=sotunh - 1;
        return SH;
    }
    else if(jahan[satrh][sotunh - 1] != '.' && jahan[satrh][sotunh - 1] != 'F' && jahan[satrh][sotunh - 1] != noeh && jahan[satrh][sotunh - 1] != 'H' && jahan[satrh][sotunh - 1] != '#'){
        SH = ShomarandeDoshman(satrh, sotunh - 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh ;
        YE=sotunh -1 ;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh - 1] != '.' && jahan[satrh + 1][sotunh - 1] != 'F' && jahan[satrh + 1][sotunh - 1] != noeh && jahan[satrh + 1][sotunh - 1] != 'H' && jahan[satrh + 1][sotunh - 1] != '#'){
        SH = ShomarandeDoshman(satrh + 1, sotunh - 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh + 1;
        YE=sotunh -1;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh] != '.' && jahan[satrh + 1][sotunh] != 'F' && jahan[satrh + 1][sotunh] != noeh && jahan[satrh + 1][sotunh] != 'H' && jahan[satrh + 1][sotunh] != '#'){
        SH = ShomarandeDoshman(satrh + 1, sotunh, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh +1;
        YE=sotunh;
        return SH;
    }
    else if(jahan[satrh + 1][sotunh + 1] != '.' && jahan[satrh + 1][sotunh + 1] != 'F' && jahan[satrh + 1][sotunh + 1] != noeh && jahan[satrh + 1][sotunh + 1] != 'H' && jahan[satrh + 1][sotunh + 1] != '#'){
        SH = ShomarandeDoshman(satrh + 1, sotunh + 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh + 1;
        YE=sotunh + 1;
        return SH;
    }
    else if(jahan[satrh][sotunh + 1] != '.' && jahan[satrh][sotunh + 1] != 'F' && jahan[satrh][sotunh + 1] != noeh && jahan[satrh][sotunh + 1] != 'H' && jahan[satrh][sotunh + 1] != '#'){
        SH = ShomarandeDoshman(satrh, sotunh + 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh ;
        YE=sotunh+1;
        return SH;
    }
    else if(jahan[satrh - 1][sotunh + 1] != '.' && jahan[satrh - 1][sotunh + 1] != 'F' && jahan[satrh - 1][sotunh + 1] != noeh && jahan[satrh - 1][sotunh + 1] != 'H' && jahan[satrh - 1][sotunh + 1] != '#'){
        SH = ShomarandeDoshman(satrh - 1, sotunh + 1, listKolHeyvanat, tedadKolHeyvanat);
        XE=satrh - 1;
        YE=sotunh + 1;
        return SH;
    }
    else{
        return -1;
    }
}

int ShomarandeDoshman(int satr, int sotun, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat){
    int i;
    for(i = 0; i < tedadKolHeyvanat; i++){
        if(satr == listKolHeyvanat[i].satr && sotun == listKolHeyvanat[i].sotun){
            return i;
        }
    }

    return -1;
}

int DustBarayeEhda(struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, int i){
    int j;

    for(j = 0; j < tedadKolHeyvanat; j++){
        if(listKolHeyvanat[i].noe == listKolHeyvanat[j].noe && i != j){
            return j;
        }
    }

    return -1;
}

void Save(int AbAdJahan, int tedadBonBast, int bonbastha[][2], int tedadBeheshtHa, int BeheshtHa[][2], int tedadGhazaHa, int GhazaHa[][3], struct heyvan listKolHeyvanat[], int tedadKolHeyvanat, char GuneMoredNazar){
    FILE *saveFILE;
    saveFILE = fopen("SaveAndLoad.txt","w");

    PrintAbAdJahanDarFile(saveFILE, AbAdJahan);
    PrintBonBastHaDarFile(saveFILE, bonbastha, tedadBonBast);
    printBeheshtHaDarFile(saveFILE, BeheshtHa, tedadBeheshtHa);
    PrintGhazaHaDarFile(saveFILE, GhazaHa, tedadGhazaHa);
    PrintHeyvanatDarFile(saveFILE, listKolHeyvanat, tedadKolHeyvanat);
    PrintGuneKarbarDarFile(saveFILE, GuneMoredNazar);

    fclose(saveFILE);
}

void PrintAbAdJahanDarFile(FILE *saveFILE, int AbAdJahan){
    fprintf(saveFILE, "%d\n", AbAdJahan);
}

void PrintBonBastHaDarFile(FILE *saveFILE, int bonbastHa[][2], int tedadBonBastHa){
    int i;
    fprintf(saveFILE, "# %d ",tedadBonBastHa);

    for(i = 0; i < tedadBonBastHa; i++){
        fprintf(saveFILE, "(%d,%d)", bonbastHa[i][0], bonbastHa[i][1]);
    }

    fprintf(saveFILE, "\n");
}

void printBeheshtHaDarFile(FILE *saveFILE, int beheshtHa[][2], int tedadBeheshtHa){
    int i;
    fprintf(saveFILE, "H %d ", tedadBeheshtHa);

    for(i = 0; i < tedadBeheshtHa; i++){
        fprintf(saveFILE, "(%d,%d)", beheshtHa[i][0], beheshtHa[i][1]);
    }

    fprintf(saveFILE, "\n");
}

void PrintGhazaHaDarFile(FILE *saveFILE, int GhazaHa[][3], int tedadGhazaHa){
    int i;
    for(i = 0; i < tedadGhazaHa; i++){
        fprintf(saveFILE, "F %d (%d,%d)\n", GhazaHa[i][0], GhazaHa[i][1], GhazaHa[i][2]);
    }

    fprintf(saveFILE, "=\n");
}

void PrintHeyvanatDarFile(FILE *saveFILE, struct heyvan listKolHeyvanat[], int tedadKolHeyvanat){
    int i;
    
    for(i = 0; i < tedadKolHeyvanat; i++){
        fprintf(saveFILE, "%c %d %d %d %d %d %d %d %d %d\n", listKolHeyvanat[i].noe, listKolHeyvanat[i].satr, listKolHeyvanat[i].sotun, listKolHeyvanat[i].energy, listKolHeyvanat[i].oneMove, listKolHeyvanat[i].maxJahesh, listKolHeyvanat[i].tolidMesl, listKolHeyvanat[i].deffend, listKolHeyvanat[i].attack, listKolHeyvanat[i].energyAvalie);
    }

    fprintf(saveFILE, "=\n");
}

void PrintGuneKarbarDarFile(FILE *saveFILE, char GuneMoredNazar){
    fprintf(saveFILE,"%c", GuneMoredNazar);
}

void KhandanAzFileSaveShode(FILE *saveFILE, char jahan[][20], int &AbAdJahan, int blockHa[][2], int &tedadBlockHa, int beheshtHa[][2], int &tedadBeheshtHa, int ghazaHa[][3], int &tedadGhazaHa, int &tedadKolHeyvanat, struct heyvan listKolHeyvanat[], char &guneMoredNazar){


    fscanf(saveFILE,"%d",&AbAdJahan);
    GetWorld(jahan, AbAdJahan);

    GetBlock(jahan, saveFILE, blockHa, tedadBlockHa);
    GetHeaven(jahan, beheshtHa, tedadBeheshtHa, saveFILE);
    GetFood(ghazaHa, jahan, saveFILE, tedadGhazaHa);
    GereftanListHeyvanat(saveFILE, listKolHeyvanat, tedadKolHeyvanat, jahan);

    fscanf(saveFILE," %c",&guneMoredNazar);
}

void GereftanListHeyvanat(FILE *saveFILE, struct heyvan listKolHeyvanat[], int &i, char jahan[][20]){

    i = 0;
    fscanf(saveFILE," %c", &listKolHeyvanat[i].noe);
    do{
        fscanf(saveFILE,"%d %d %d %d %d %d %d %d %d",&listKolHeyvanat[i].satr, &listKolHeyvanat[i].sotun, &listKolHeyvanat[i].energy, &listKolHeyvanat[i].oneMove, &listKolHeyvanat[i].maxJahesh, &listKolHeyvanat[i].tolidMesl, &listKolHeyvanat[i].attack, &listKolHeyvanat[i].deffend, &listKolHeyvanat[i].energyAvalie);
        jahan[listKolHeyvanat[i].satr][listKolHeyvanat[i].sotun] = listKolHeyvanat[i].noe;
        i++;
        fscanf(saveFILE," %c",&listKolHeyvanat[i].noe);    
    } while(listKolHeyvanat[i].noe != 61);

}






