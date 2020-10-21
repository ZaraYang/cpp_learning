#include <string>
#include"class.h"


string Generate_space(int space_num) {
	string space = "";
	for (int i = 0; i < space_num; i++) { space += " "; }
	return space;
}
string Generate_arrow() {
	return (" ----> ");
}
string Draw_limb(Node* ptr) {
	if (ptr->Father_node->Father_node == nullptr) {
		return("Root_Node:" + to_string(ptr->Key_word));
	}
	else if (ptr->Father_node == nullptr) {
		return("Sentinel");
	}
	else if (ptr->Node_color == Red) {
		return("Red_Node:"+ to_string(ptr->Key_word));
	}
	else{
		
		return("Black_Node:" + to_string(ptr->Key_word));
	}

}

int Draw_tree(Node* ptr, int* line_index, int pos_index, vector<string>& cout_list) {
	if (ptr->Father_node == nullptr) { return NULL; }
	if (*line_index < cout_list.size()) {
		if (cout_list[*line_index].size() < pos_index) {
			cout_list[*line_index] += Generate_space(cout_list[*line_index].size() - pos_index);
		}

		cout_list[*line_index] += Generate_arrow();
		cout_list[*line_index] += Draw_limb(ptr);
	}
	else {
		cout_list.push_back(Generate_space(pos_index) + "|");
		for (int i = (*line_index) - 1; i > 0; i--) {
			if (cout_list[i].size() < pos_index) { continue; }
			if (cout_list[i][pos_index] == ' ') { cout_list[i][pos_index] = '|'; }
			else { break; }
		}

		(*line_index)++;
		cout_list.push_back(Generate_space(pos_index));
		if (ptr->Father_node->Father_node != nullptr) {
			cout_list[*line_index] += Generate_arrow();
		}
		cout_list[*line_index] += (Draw_limb(ptr));
	}

	int curr_pos = cout_list[*line_index].size();
	curr_pos -= (Draw_limb(ptr).size() / 2);
	if (ptr->Son_nodes[Left]->Father_node != nullptr) {
		Draw_tree(ptr->Son_nodes[Left], line_index, curr_pos, cout_list);
	}
	if (ptr->Son_nodes[Right]->Father_node != nullptr) {
		(*line_index) += 1;
		Draw_tree(ptr->Son_nodes[Right], line_index, curr_pos, cout_list);
	}
}
//树结构可视化
void Show_me_the_fucking_tree(Node* root) {
	vector<string> cout_list;
	int* start_line = new int(0);
	int start_pos = 0;
	Draw_tree(root, start_line, start_pos, cout_list);
	for (vector<string>::iterator iter = cout_list.begin(); iter != cout_list.end(); ++iter) {
		cout << *iter << endl;
	}
}