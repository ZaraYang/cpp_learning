#pragma once
#include "include.h"



// 直接寻址表
// 在关键字全域比较小时起作用，直接寻址表（数组）中的index和全域中的关键字一一对应
// 直接寻址表在关键字全域比较大时并不适用，会大量浪费内存 

// Slot（槽） 为直接寻址表数组中的基本元素
struct Slot {
private:
	int key_word;
	string* data_ptr;
public:
	Slot()
		:data_ptr(nullptr) {}

	Slot(int key) 
		:key_word(key),data_ptr(nullptr){}

	// 设置槽中的内容
	virtual void Set_context(string* ptr){
		data_ptr = ptr;
	}

	// 移除槽中的内容
	void Remove_context() {
		if (data_ptr == nullptr) {
			throw "Slot already empty!";
		}
		else {
			data_ptr = nullptr;
		}
	}

	// 返回槽中的内容
	virtual string* Context() {
		return data_ptr;
	}

	int Key() {
		return key_word;
	}

};

class Direct_address_table {
private:
	int Scope_size;
	Slot* address_table;
public:
	Direct_address_table(int& key_scope_size)
		:address_table(new Slot[key_scope_size]),Scope_size(key_scope_size){
		Table_init();
	}

	~Direct_address_table() {
		delete address_table;
		cout << "Direct-address-table Deleted." << endl;
	}

	// 简化情况下，Slot的keyword为其在数组中的index
	virtual void Table_init() {
		for (int i = 0; i < Scope_size; i++) {
			address_table[i] = Slot(i);
		}
	}

	// 在表中根据key查询
	virtual string* Direct_address_search(int key) const {
		return address_table[key].Context();
	}

	// 向表中添加键值对
	virtual void Direct_address_insert(int& key, string* context) {
		if (address_table[key].Context() != nullptr) {
			throw "Key already used!";
		}
		else {
			address_table[key].Set_context(context);
		}
	}

	// 修改表中的键值对
	void Direct_address_change(int& key, string* context) {
		if (address_table[key].Context() == nullptr) {
			throw "Key is empty!";
		}
		else {
			address_table[key].Set_context(context);
		}
	}

	// 删除表中的键值对
	void Direct_address_delete(int& key) {
		address_table[key].Remove_context();
	}

	// 迭代输出寻址表中所有的键值对
	void Direct_address_show() {
		for (int i = 0; i < Scope_size; i++) {
			if (address_table[i].Context() != nullptr) {
				cout << i << "  --  " << *address_table[i].Context() << endl;
			}
		}
	}
};

// 散列表 Hash table
// 比直接寻址表需要更少的存储空间，同时保持快速查找元素的优势
// 通过散列函数h(k)来计算出槽的位置
// 将关键字全域映射到散列函数的全域上，但是因此就一定会有冲突的问题
// 为了尽可能地避免冲突，可以使h尽可能地“随机”，或者精心设计散列函数来避免冲突

// 链接法解决散列表中的冲突
// 将散列表中同一个槽的元素放在一个（双向）链表中，双向链表可以更快的删除
// 其效率取决于散列函数将关键字分配在槽位上的均匀程度，所有的key都分布在同一个槽中时最慢的情况 ，“简单均匀散列”

class Hash_link_node :Link_Node {
private:
	Hash_link_node* header;
	Hash_link_node* tailer;
	string* context;
	int key_word;
public:
	Hash_link_node(Hash_link_node* front_node, Hash_link_node* rear_node, string* node_context ,int key)
		:header(front_node), tailer(rear_node), context(node_context),key_word(key){}

	~Hash_link_node() {
		cout << "Delete hash link node" << endl;
	}

	Hash_link_node* Front() const override {
		return header;
	}

	Hash_link_node* Rear() const override {
		return tailer;
	}

	void Set_front(Hash_link_node* ptr) {
		header = ptr;
	}

	void Set_rear(Hash_link_node* ptr) {
		tailer = ptr;
	}

	void Set_value(string* value) {
		context = value;
	}

	int Key() const{
		return key_word;
	}

	string* Value() const {
		return context;
	}
};

class Hash_linked_list :Linked_list {
private:
	Hash_link_node* Sentinel = new Hash_link_node(nullptr,nullptr,nullptr,NULL);
	Hash_link_node* Currently_ptr;
public:
	Hash_linked_list()
		:Currently_ptr(Sentinel) {
		Sentinel->Set_front(Sentinel);
		Sentinel->Set_rear(Sentinel);
//		cout << "Hash link list init!";
	}

	// 向链表中插入键值对，调用一次search以保证没有重复的key
	// 因此会拖慢效率
	void Insert(int key,string* context) {
		if (Search(key) != nullptr) {
			throw "Key already used!";
		}
		Hash_link_node* temp_node = new Hash_link_node(Sentinel, nullptr,context,key);

		if (Sentinel->Rear() != Sentinel) {
			temp_node->Set_rear(Sentinel->Rear());
			Sentinel->Rear()->Set_front(temp_node);
		}
		else {
			Currently_ptr = temp_node;
			temp_node->Set_rear(Sentinel);
			Sentinel->Set_front(temp_node);
		}
		Sentinel->Set_rear(temp_node);
	}

	Hash_link_node* Search(int& key) {
		Hash_link_node* temp_node = Sentinel;
		while (temp_node->Rear() != Sentinel) {
			temp_node = temp_node->Rear();
			if (temp_node->Key() == key) {
				return temp_node;
			}
		}
		return nullptr;
	}

	void Delete(Hash_link_node* ptr) {
		ptr->Front()->Set_rear(ptr->Rear());
		ptr->Rear()->Set_front(ptr->Front());
		if (ptr->Rear() == Sentinel) {
			Currently_ptr = ptr->Front();
		}
		delete ptr;
	}

	// Delete的重写， 根据key删除链表中的键值对
	void Delete(int& key) override {
		Hash_link_node* search_result = Search(key);
		if (search_result == nullptr) {
			cout << "NO SUCN NODE IN LINK LIST !" << endl;
		}
		else {
			Delete(search_result);
		}
	}

	void Change(int& key, string* value) {
		Hash_link_node* ptr = Search(key);
		ptr->Set_value(value);
	}

	void Show_link_list() const override{
		Hash_link_node* temp_ptr = Sentinel;
		cout << "Start <-> ";
		while (temp_ptr->Rear() != Sentinel) {
			temp_ptr = temp_ptr->Rear();
			cout << "[ "<<temp_ptr->Key()<< " : " << *temp_ptr->Value() << " ]" << " <-> ";
		}
		cout << "Nullptr" << endl;
	}

};


class Hash_slot :public Slot {
private:
	Hash_linked_list* link_list; 
	int Hash_key_word;
public:
	Hash_slot(){}

	Hash_slot(int k)
		:Hash_key_word(k),link_list(new Hash_linked_list()){}

	void Set_context(int key_word,string* ptr) {
		link_list->Insert(key_word, ptr);
	}

	void Remove_context(int& key) {
		link_list->Delete(key);
	}

	void Change_context(int& key,string* value){
		link_list->Change(key, value);
	}

	string* Context(int key) {
		return link_list->Search(key)->Value();
	}

	void Show_slot() {
		link_list->Show_link_list();
	}
};

class Hash_table  {
private:
	int Scope_size;
	Hash_slot* address_table;
public:
	Hash_table(int& key_scope_size)
		:address_table(new Hash_slot[key_scope_size]), Scope_size(key_scope_size) {
		Table_init();
	}

	void Table_init(){
		for (int i = 0; i < Scope_size; i++) {
			address_table[i] = Hash_slot(i);
		}
	}
	// Hash 函数
	int Hash_func(int& key) {
		return floor(key/2);
		
		// 除法散列法
		// int m = 3;
		// return key % m;

		// 乘法散列法
		// int m = 3;
		// int A = 0.618;
		// return floor(m * ((key * A) % 1));

	}
	// 全域散列法 从一组设计好的散列函数中随机选择一个
	// 有很好的平均性能
	int Universal_hashing(int key) {
		// 这里没看懂 ？
	}

	string* Search(int& key){
		return address_table[Hash_func(key)].Context(key);
	}

	void Insert(int& key, string* context){
		address_table[Hash_func(key)].Set_context(key, context);
	}

	void Delete(int& key) {
		address_table[Hash_func(key)].Remove_context(key);
	}

	void Change(int& key, string* value) {
		address_table[Hash_func(key)].Change_context(key, value);
	}

	void Show_hash_table() {
		for (int i = 0; i < Scope_size; i++) {
			cout << "[Slot " << i << "]";
			address_table[i].Show_slot();
		}
	}
};


// 开放寻址法
// 未测试正确性！
class Open_address_table {
private:
	int Scope_size;
	Slot* address_table;
public:
	Open_address_table(int& key_scope_size)
		:address_table(new Slot[key_scope_size]), Scope_size(key_scope_size) {}

	int	Auxiliary_hash_func(int& key) {
		int m = 3;
		return key % m;
	}
	
	int Auxiliary_hash_func_2(int& key) {
		int m = 2;
		return (key % m) + 1;
	}

	// 线性探查
	// 根据辅助散列函数的数值一个挨一个的探查
	// 随着散列表内数据越来越多会变慢 （一次群集）
	int Linear_probe(int& key,int& i) {
		int m = 3;
		int index = (Auxiliary_hash_func(key) + i) % m;
		return index;
	}

	// 二次探查 c1 c2 为辅助常数，index的增加值是关于c1,c2的二次函数
	// 为了充分利用散列表，c1 c2的值要受到限制
	// 会出现小规模的二次群集，因为和线性探查一样，初始探查的位置决定了整个探查序列
	int Quadratic_probe(int& key,int& i){
		int c1 = 1, c2 = 1, m = 3;
		int index = (Auxiliary_hash_func(key) + c1 * i + c2 * pow(i, 2));
		index = index % m;
		return (index);
	}

	// 双重散列
	// 开放寻址法最好的方法之一
	// 为了能够查找整个散列表，m最好取2的幂，并设计一个总产生奇数的h2
	// 或者取m为素数，并设计一个返回值总比m小的h2
	int Double_hash(int& key, int& i) {
		int m = 3;
		int index = Auxiliary_hash_func(key) + i * Auxiliary_hash_func_2(key);
		index = index % m;
		return index;
	}

	int Probe(int& key,int& i) {
		return Linear_probe(key,i);
	}

	void Hash_insert(int& key, string* Value){
		int add_index = 0;
		while(1) {
			if (add_index == Scope_size) {
				throw "Hash table overflow!";
			}

			int index = Probe(key,add_index);
			if (address_table[index].Context() == nullptr) {
				address_table[index].Set_context(Value);
			}
			else {
				add_index++;
			}
		}
		
	}

	string* Hash_search(int& key) {
		int add_index = 0;
		while (1) {
			int index = Probe(key,add_index);
			if (address_table[index].Key() == key) {
				return address_table[index].Context();
			}
			if (address_table[index].Context() == nullptr || add_index == Scope_size) {
				return nullptr;
			}
			add_index++;
		}
	}






};

