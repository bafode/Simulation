#include"compute.h"




int main(void){
	int siparis_list[MAX_ORDER]={224,275,325,400};
	int yeniden_siparis_verme_noktasi[MAX_REORDER_POINT]={200,225,250,275,300};
	srand(time(NULL));
	register int new_table=0;
	struct table * t[100];

	for(int i=0;i<100;i++) {
		t[i]=NULL;
	}

	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<MAX_SIMULATION;k++){
				newRow(&t[new_table],yeniden_siparis_verme_noktasi[i],siparis_list[j]);

			}


			new_table++;
		}
	}



	for(int i=0;i<new_table;i++){
		tablePrint(t[i]);
	}

	printf("\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////\n");
	FTable(siparis_list,yeniden_siparis_verme_noktasi);

	return 0;
}

