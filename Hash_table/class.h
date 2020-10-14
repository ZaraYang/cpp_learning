#pragma once
#include "include.h"



// ֱ��Ѱַ��
// �ڹؼ���ȫ��Ƚ�Сʱ�����ã�ֱ��Ѱַ�����飩�е�index��ȫ���еĹؼ���һһ��Ӧ
// ֱ��Ѱַ���ڹؼ���ȫ��Ƚϴ�ʱ�������ã�������˷��ڴ� 

// Slot���ۣ� Ϊֱ��Ѱַ�������еĻ���Ԫ��
struct Slot {
private:
	int key_word;
	string* data_ptr;
public:
	Slot()
		:data_ptr(nullptr) {}

	Slot(int key) 
		:key_word(key),data_ptr(nullptr){}

	// ���ò��е�����
	virtual void Set_context(string* ptr){
		data_ptr = ptr;
	}

	// �Ƴ����е�����
	void Remove_context() {
		if (data_ptr == nullptr) {
			throw "Slot already empty!";
		}
		else {
			data_ptr = nullptr;
		}
	}

	// ���ز��е�����
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

	// ������£�Slot��keywordΪ���������е�index
	virtual void Table_init() {
		for (int i = 0; i < Scope_size; i++) {
			address_table[i] = Slot(i);
		}
	}

	// �ڱ��и���key��ѯ
	virtual string* Direct_address_search(int key) const {
		return address_table[key].Context();
	}

	// �������Ӽ�ֵ��
	virtual void Direct_address_insert(int& key, string* context) {
		if (address_table[key].Context() != nullptr) {
			throw "Key already used!";
		}
		else {
			address_table[key].Set_context(context);
		}
	}

	// �޸ı��еļ�ֵ��
	void Direct_address_change(int& key, string* context) {
		if (address_table[key].Context() == nullptr) {
			throw "Key is empty!";
		}
		else {
			address_table[key].Set_context(context);
		}
	}

	// ɾ�����еļ�ֵ��
	void Direct_address_delete(int& key) {
		address_table[key].Remove_context();
	}

	// �������Ѱַ�������еļ�ֵ��
	void Direct_address_show() {
		for (int i = 0; i < Scope_size; i++) {
			if (address_table[i].Context() != nullptr) {
				cout << i << "  --  " << *address_table[i].Context() << endl;
			}
		}
	}
};

// ɢ�б� Hash table
// ��ֱ��Ѱַ����Ҫ���ٵĴ洢�ռ䣬ͬʱ���ֿ��ٲ���Ԫ�ص�����
// ͨ��ɢ�к���h(k)��������۵�λ��
// ���ؼ���ȫ��ӳ�䵽ɢ�к�����ȫ���ϣ�������˾�һ�����г�ͻ������
// Ϊ�˾����ܵر����ͻ������ʹh�����ܵء�����������߾������ɢ�к����������ͻ

// ���ӷ����ɢ�б��еĳ�ͻ
// ��ɢ�б���ͬһ���۵�Ԫ�ط���һ����˫�������У�˫��������Ը����ɾ��
// ��Ч��ȡ����ɢ�к������ؼ��ַ����ڲ�λ�ϵľ��ȳ̶ȣ����е�key���ֲ���ͬһ������ʱ��������� �����򵥾���ɢ�С�

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

	// �������в����ֵ�ԣ�����һ��search�Ա�֤û���ظ���key
	// ��˻�����Ч��
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

	// Delete����д�� ����keyɾ�������еļ�ֵ��
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
	// Hash ����
	int Hash_func(int& key) {
		return floor(key/2);
		
		// ����ɢ�з�
		// int m = 3;
		// return key % m;

		// �˷�ɢ�з�
		// int m = 3;
		// int A = 0.618;
		// return floor(m * ((key * A) % 1));

	}
	// ȫ��ɢ�з� ��һ����ƺõ�ɢ�к��������ѡ��һ��
	// �кܺõ�ƽ������
	int Universal_hashing(int key) {
		// ����û���� ��
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


// ����Ѱַ��
// δ������ȷ�ԣ�
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

	// ����̽��
	// ���ݸ���ɢ�к�������ֵһ����һ����̽��
	// ����ɢ�б�������Խ��Խ������ ��һ��Ⱥ����
	int Linear_probe(int& key,int& i) {
		int m = 3;
		int index = (Auxiliary_hash_func(key) + i) % m;
		return index;
	}

	// ����̽�� c1 c2 Ϊ����������index������ֵ�ǹ���c1,c2�Ķ��κ���
	// Ϊ�˳������ɢ�б�c1 c2��ֵҪ�ܵ�����
	// �����С��ģ�Ķ���Ⱥ������Ϊ������̽��һ������ʼ̽���λ�þ���������̽������
	int Quadratic_probe(int& key,int& i){
		int c1 = 1, c2 = 1, m = 3;
		int index = (Auxiliary_hash_func(key) + c1 * i + c2 * pow(i, 2));
		index = index % m;
		return (index);
	}

	// ˫��ɢ��
	// ����Ѱַ����õķ���֮һ
	// Ϊ���ܹ���������ɢ�б�m���ȡ2���ݣ������һ���ܲ���������h2
	// ����ȡmΪ�����������һ������ֵ�ܱ�mС��h2
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

