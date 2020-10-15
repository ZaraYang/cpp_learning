#pragma once
#include "include.h"
#include "Data_struct.h"

class Node {
private:
	bool Leaf_node;
	int node_class;
	int choice_feature;
	float threshold;
	Decision_tree_data* data_ptr;
	Feature_list features;
	map<int,Node*> Son_nodes;
public:
	Node(Decision_tree_data* ptr,Feature_list f)
		:data_ptr(ptr),features(f){}
	Node(Decision_tree_data* ptr)
		:data_ptr(ptr), features(Feature_list()){}

	Feature_list return_features() { return features; }

	void Set_class(int c) {
		node_class = c;
	}

	void Set_son_node(int& feature,Node* ptr) {
		if (Son_nodes.find(feature) != Son_nodes.end()){
			throw "Feature already exist !";
		}
		Son_nodes[feature] = ptr;
	}

	bool Lable_identity() {
		int label = data_ptr->Label_identity();
		if (label != NULL) {
			Set_class(label);
			Leaf_node = true;
			return true;
		}
		else {
			return false;
		}
	}
	
	bool Out_of_feature() {
		return features.Out_of_feature();
	}
	
	vector<Decision_tree_data>* Best_divided(){
		vector<Decision_tree_data>* result;
		float* best_choice = data_ptr->Decide_best_devide();
		if (best_choice[1] != NULL) {
			result = data_ptr->Divide_data(best_choice[0], best_choice[1]);
		}
		else {
			result = data_ptr->Divide_data(best_choice[0]);
		}
		features.Delete_feature(best_choice[0]);
		delete best_choice;
		return result;
	}

};


class Basic_decision_tree {
private:
	Node* Root_node_ptr;

public:
	Basic_decision_tree(Decision_tree_data* data_ptr)
		:Root_node_ptr(new Node(data_ptr)){}
	int Build_tree(Node* ptr) {
		if (ptr->Lable_identity()){
			return 0;
		}
		if (ptr->Out_of_feature()){}

		vector<Decision_tree_data>* devided_data_ptr = ptr->Best_divided();
		for (int i = 0; i < devided_data_ptr->size(); i++) {
			Node* sub_node_ptr = new Node(&(*devided_data_ptr)[i], ptr->return_features());
			if ((*devided_data_ptr)[i].Data_size() == 0) {
				// 
			}
			else {
				Build_tree(sub_node_ptr);
			}
		}

	}
};
