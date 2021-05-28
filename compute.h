#ifndef COMPUTE_H
#define COMPUTE_H

#include<stdint.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<float.h>

#ifndef MAX_SIMULATON
#define MAX_SIMULATION 5
#endif

#define MAX_ORDER 4
#define MAX_REORDER_POINT 5
#define TRUE 1
#define FALSE 0


static const int order_expenses=50;
static const float value_of_items_in_stok=0.2;
static const int value_of_items_lost=100;

 struct table{
	uint8_t simulation_time;
	int initial_stock;
	int demand;
	int items_in_stock;
	uint8_t lost;
	int position_of_stock;
	int open_order;
	uint8_t supply_time;
	float items_in_stok_value;
	float lost_cost;
	float order_cost;
	double total_cost;
	int order_quantity;
	int reorder_point;
	struct table*  nextTable;
};




struct table* cons_table();
void newRow(struct table** tab,const  int siparis_mik, const int yeniden_veren);
void OrderNew(struct table* table,const int siparis_mik, const int yeniden_veren);
int  RandomNum(int low,int upper);
void Lose(struct table* t);
int  comingOrder();
void tablePrint(struct table* table);
void MinExpense();
void FTable();

#endif


