#include"compute.h"

int global_baslangic_stok;
uint8_t tedarik=0;
uint8_t state=1;
uint8_t counter=0;
/*
   This array will content the sum of the total cost of each table*/ 
double final_array_contenair[MAX_REORDER_POINT*MAX_ORDER]={};

int array_index=0; //is the index of final_array_contenair .Ww'll increment this index index after
float minExpense=0;// is
//-----------------------------//

struct table* cons_table(){
	struct table* temp=malloc(sizeof(*temp));
	if(state>MAX_SIMULATION){             //Reset the number if max benzetim of each table was reach
							           //
		state=1;

	}
	temp->nextTable=NULL;
	temp->open_order=0;
	temp->supply_time=0;
	temp->order_quantity=0;
	temp->reorder_point=0;
	temp->simulation_time=state;


	return temp;
}

void newRow(struct table** headRow,const int reorder_point,const int order_quantity){


	struct table* newTable=cons_table();
	newTable->reorder_point=reorder_point;
	newTable->order_quantity=order_quantity;
	state++;
	struct table* i=*headRow;   //To add the new struct in end for the list we need this temp tempt struct to iterate until reach the end


	if(*headRow==NULL){

		newTable->initial_stock=order_quantity;
		newTable->demand=RandomNum(80,130);
		newTable->items_in_stock=(newTable->initial_stock-newTable->demand); //Just for verification
		newTable->position_of_stock=(newTable->items_in_stock+newTable->open_order);
		global_baslangic_stok=newTable->items_in_stock;

		Lose(newTable);//Verify if there areb lost or not
		OrderNew(newTable,reorder_point,order_quantity); //Verify if we to make new order or not

		newTable->total_cost=(newTable->items_in_stok_value+newTable->lost_cost+newTable->order_cost); //

			*headRow=newTable;

	}else{

		newTable->initial_stock=global_baslangic_stok;
		newTable->demand=RandomNum(80,130);
		newTable->items_in_stock=(newTable->initial_stock-newTable->demand);
		//Just for verification
		Lose(newTable);


		if(comingOrder()){
			newTable->position_of_stock=(newTable->items_in_stock+order_quantity);
			newTable->open_order=0;
			newTable->supply_time=0;
			newTable->order_cost=0;
			global_baslangic_stok=newTable->items_in_stock;
		}else{
			global_baslangic_stok=order_quantity;
			OrderNew(newTable,order_quantity,reorder_point);
			newTable->position_of_stock=(newTable->items_in_stock);
		}

		newTable->total_cost=(newTable->items_in_stok_value+newTable->lost_cost+newTable->order_cost);

		while(i->nextTable!=NULL){
			i=i->nextTable;
		}

		i->nextTable=newTable;
	}


}

void OrderNew(struct table* newTable,const int order_quantity,const int reorder_point){
	if(newTable->items_in_stock<=reorder_point){
			//We need to make a new order
			newTable->open_order=order_quantity;
			newTable->supply_time=(uint8_t)RandomNum(2,3);
			counter=(newTable->supply_time+state);//Set counter to remainde when the order will be ok
			newTable->order_cost=order_expenses;
			newTable->items_in_stok_value=value_of_items_in_stok*newTable->items_in_stock;
			tedarik=newTable->supply_time;

		}else{
			newTable->open_order=0;
			newTable->supply_time=0;
			newTable->order_cost=0;
			tedarik=newTable->supply_time;
			global_baslangic_stok=newTable->position_of_stock;
		}
}

int comingOrder(){

	if(state< counter){
		return TRUE;
	}else{
		return FALSE;
	}

}



void Lose(struct table* newTable){
	if( newTable->items_in_stock<0){
			newTable->lost=(uint8_t)(abs(newTable->items_in_stock));
			newTable->lost_cost=(value_of_items_lost*newTable->lost);
			newTable->items_in_stock=0;
		}else{
			newTable->lost=0;
			newTable->lost_cost=0;
			newTable->items_in_stok_value=(value_of_items_in_stok*newTable->items_in_stock);
		}
}


int RandomNum(int lower,int upper){
	return (rand()%(upper-lower+1))+lower;


}
/*
ST:Simualtion Time
IS:Initial stok
OD: Oder
IT:Stok Item
LO:Lose
PS:Position of Stok
RO:Reorder
ST:Supply Time
SIC:Stock Item Cost
OC: Order Cost
LC:lost Cost
OC:Order Cost
TC: Total Cost
*/

void tablePrint(struct table* table){
	struct table* i=table;
	printf("Order :%d  $$$$$ ReorderPoint :%d\n",i->order_quantity,i->reorder_point);
	printf("ST---|--IS--|--OD--|----SI--|--LO--|----PS--|----RO--|--ST--|----SIC--|---LC--|--OC---|---TC--|\n");
	while(i !=NULL){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.02f\t%.02f\t%.02f\t%.02f\n",i->simulation_time,i->initial_stock,i->demand,i->items_in_stock,i->lost,i->position_of_stock,i->open_order,i->supply_time,i->items_in_stok_value,i->lost_cost,i->order_cost,i->total_cost);
		final_array_contenair[array_index]=final_array_contenair[array_index]+ i->total_cost;
		i=i->nextTable;
	}
	array_index++;
	printf("\n\n");
}


void MinExpense(double *array){
	minExpense=FLT_MAX;

	for(int i=0;i<MAX_REORDER_POINT*MAX_ORDER;i++){
		if(array[i]<minExpense){
			minExpense=array[i];
		}
	}



}

//Turn one Dimension array to 2D
void FTable(int siparis[],int yeniden[]){
    int optimumQ,optimumR;
	MinExpense(final_array_contenair);
    printf("R   | Q");  //R is for reoder and Q for reoder point
	for(int i=0;i<MAX_ORDER;i++){
		printf("\t   %d  ",siparis[i]);
	}
	printf("\n------------------------------------------------------------------------\n");
	for(int i=0;i<MAX_REORDER_POINT;i++){
		printf("\033[0;34m%d   |",yeniden[i]);
		for(int j=0;j<MAX_ORDER;j++){
			if( round(minExpense)==round(final_array_contenair[MAX_ORDER*i+j])){
        optimumQ=siparis[j];
        optimumR=yeniden[i];
				printf("\033[0;32m %0.2f \t  ",final_array_contenair[MAX_ORDER*i+j]);
			}else{
				printf("\033[0;31m %0.2f \t ",final_array_contenair[MAX_ORDER*i+j]);
			}
		}
		printf("\n\n");
	}
	printf("\033[0m");
	printf("Min Maliyeti[%.02f] elde etmek icin Q=%d ve R=%d olmaldir\n",minExpense,optimumQ,optimumR);

}

//gcc -o simulation benzetin.c compute.c -lm
// ./simulation 
