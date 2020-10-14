#include "include.h"
#include"class.h"

// Hash table
// ¹þÏ£±í£¬É¢ÁÐ±í


void main() {
//	int direct_address_table_size = 10;
//	Direct_address_table e(direct_address_table_size);
//
	string Names[5] = { "He.Y","Cao.XY","He.SS","Lai.X","Chen.BX" };
//	for (int i = 0; i < 5; i++) {
//		e.Direct_address_insert(i, &Names[i]);
//	}
//	e.Direct_address_show();
	
	int a = 5;
	Hash_table e(a);
	for (int i = 0; i < 5; i++) {
		e.Insert(i, &Names[i]);
	}
	e.Show_hash_table();

}