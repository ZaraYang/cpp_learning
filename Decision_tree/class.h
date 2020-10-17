#pragma once
#include "include.h"

struct DT_data {
private:
	vector<vector<double>*>* Data;
public:
	DT_data()
		:Data(new vector<vector<double>*>){}
	// 根节点构造函数，从文件导入数据
	DT_data(string& addr)
		:Data(Import_from_file(addr)){}
	// 其他节点构造函数，直接输入分割后的数据指针
	DT_data(vector<vector<double>*>* ptr)
		:Data(ptr){}
	// 从文件导入数据
	vector<vector<double>*>* Import_from_file(string& addr) {
		vector<vector<double>*>* data = new vector<vector<double>*>;
		ifstream input_file(addr, ios::in);
		string buffer;
		getline(input_file, buffer);
		while (getline(input_file, buffer)) {
			data->push_back(Split_data(buffer));
		}
		return data;
	}
	// 字符串数据分割
	vector<double>* Split_data(string& e) {
		vector<double>* result = new vector<double>;
		for (int i = 0; i < int(e.size()); i++) {
			if (e[i] == ',') { e[i] = ' '; };
		}
		istringstream out(e);
		string buffer;
		while (out >> buffer) {
			result->push_back(atof(buffer.c_str()));
		}
		return result;
	}
	// 返回样本数量
	int Size() { return Data->size(); }
	// 插入数据
	void Insert_data(vector<double>* data) {
		Data->push_back(data);
	}
	vector<vector<double>*>& Show_data() { return *Data; }
	// 根据数据决定类别
	int Generate_label() const {
		map<int, int> label_map;
		for (vector<vector<double>*>::iterator iter = (*Data).begin(); iter != (*Data).end(); ++iter) {
			int temp_label = (int)(*iter)->back();
			if (label_map.count(temp_label) > 0) {
				label_map[temp_label]++;
			}
			else {
				label_map[temp_label] = 1;
			}
		}
		int max_num = 0, max_label = 0;
		for (map<int, int>::iterator iter = label_map.begin(); iter != label_map.end(); ++iter) {
			if (iter->second > max_num) {
				max_num = iter->second;
				max_label = iter->first;
			}
		}
		return max_label;
	}

	int Data_identity() {
		vector<vector<double>*>& data_ref = *Data;
		int temp_label = (int)data_ref[0]->back();
		for (vector<vector<double>*>::iterator iter = data_ref.begin()+1; iter != data_ref.end(); ++iter) {
			if ((*iter)->back() != temp_label) { return -1; }
		}
		return temp_label;
	}

};

// 决策树的节点
class Node{
private:
	int node_class;
	int feature = -1;
	double threshold;
	Node* father;
	map<int, Node*>* son_nodes = new map<int,Node*>;
public:
	Node()
		:father(nullptr){};
	Node(Node* ptr)
		:father(ptr){}
	//设定子节点
	void Set_son_node(int feature_value, Node* son) {
		(*son_nodes)[feature_value] = son;
	}
	//设定节点类别
	void Set_class(int label) {
		node_class = label;
	}
	// 设定划分特征
	void Set_feature(int f) {
		feature = f;
	}
	// 设定连续特征以及阈值
	void Set_feature(int f, double t) {
		feature = f;
		threshold = t;
	}
	// 返回属性
	int Node_feature() { return feature; }
	//返回 子节点
	map<int, Node*>& Node_sons() { return *son_nodes; }
	// 返回标签
	int Node_class() { return node_class; }
};

struct Stack_element {
	Node* Father_node;
	DT_data* Data;
	set<int>* Features;

	Stack_element(Node* a, DT_data* b, set<int>* c)
		:Father_node(a), Data(b), Features(c) {}
};

// 决策树 
class Decision_tree {
private:
	Node* Root;
	set<int>* Feature_list;
public:
	Decision_tree()
		:Root(new Node()), Feature_list(new set<int>) {
		for (int i = 0; i < feature_count; i++) { Feature_list->insert(i); }
	}
	// 对离散特征划分数据集，返回堆内存指针
	map<int, DT_data>* Divide_data(DT_data& data_ptr, int& feature) const {
		if (feature >= d_feature_count) { throw "No threshold for continues feature!"; }
		map<int, DT_data>* result = new map<int, DT_data>;

		for (int i = 0; i < data_ptr.Size(); i++) {
			int feature_value = (int)(*((data_ptr.Show_data())[i]))[feature];
			if (result-> find(feature_value)!= result->end()){
				(*result)[feature_value].Insert_data((data_ptr.Show_data())[i]);
			}
			else {
				(*result)[feature_value] = *(new DT_data());
				(*result)[feature_value].Insert_data((data_ptr.Show_data())[i]);
			}
		}
		return result;
	}
	// 对连续特征划分数据集，返回堆内存指针
	map<int, DT_data>* Divide_data(DT_data& data_ptr, int& feature, double& threshold) const {
		if (feature < d_feature_count) { throw "No threshold for continues feature!"; }
		map<int, DT_data>* result = new map<int, DT_data>;
		for (int i = 0; i < 2; i++) {
			(*result)[i] = *(new DT_data());
		}
		for (int i = 0; i < data_ptr.Size(); i++) {
			int feature_value = (*((data_ptr.Show_data())[i]))[feature] > threshold ? 1 : 0;
			(*result)[feature_value].Insert_data((data_ptr.Show_data())[i]);
		}
		return result;
	}
	// 计算信息熵
	double Information_entropy(DT_data& data) const {
		double Entropy = 0;
		for (int i = 0; i < label_count; i++) {
			double count = 0;
			for (int j = 0; j < data.Size(); j++) {
				if (i == data.Show_data()[j]->back()) {
					count++;
				}
			}
			double p = count / data.Size();
			if (p == 0) { continue; }
			else {
				Entropy -= p * log2l(p);
			}
		}
		return Entropy;
	}
	//计算离散特征的信息增益,计算后释放堆内存
	double Information_gain(DT_data& data, int& feature) const {
		if (feature >= d_feature_count) { throw "No threshold for continues feature!"; }
		double Ent = Information_entropy(data);
		map<int, DT_data>* Divided_data_ptr = Divide_data(data, feature);
		double buffer = 0;
		for (map<int, DT_data>::iterator iter = Divided_data_ptr->begin(); iter != Divided_data_ptr->end(); ++iter) {
			DT_data& data_ref = iter->second;
			double partition = double(data_ref.Size()) / double(data.Size());
			double temp_entropy = Information_entropy(data_ref);
			buffer += partition * temp_entropy;
		}
		delete Divided_data_ptr;
		return Ent - buffer;
	}
	// 计算连续特征的信息增益，计算后释放堆内存
	double Information_gain(DT_data& data, int& feature, double threshold) const  {
		if (feature < d_feature_count) { throw "No threshold for continues feature!"; }
		double Ent = Information_entropy(data);
		map<int, DT_data>* Divided_data_ptr = Divide_data(data, feature, threshold);
		double buffer = 0;
		for (map<int, DT_data>::iterator iter = Divided_data_ptr->begin(); iter != Divided_data_ptr->end(); ++iter) {
			DT_data& data_ref = iter->second;
			double partition = double(data_ref.Size()) / double(data.Size());
			double temp_entropy = Information_entropy(data_ref);
			buffer += partition * temp_entropy;
		}
		delete Divided_data_ptr;
		return Ent - buffer;
	}
	// 选择最优的数据划分特征
	double* Choice_best_feature(set<int>& features_ref, DT_data& data) {
		double max_info_gain = -99;
		int best_feature = 0;
		double best_threshold = -1;
		for (set<int>::iterator iter = features_ref.begin(); iter != features_ref.end(); ++iter) {
			int temp_feature = *iter;
			if (temp_feature < d_feature_count) {
				double temp_info_gain = Information_gain(data,temp_feature);
				if (temp_info_gain > max_info_gain) {
					max_info_gain = temp_info_gain;
					best_feature = temp_feature;
				}
			}
			else {
				vector<double> temp_datas;
				{
					vector<vector<double>*>::iterator iter = data.Show_data().begin();
					for (; iter != data.Show_data().end(); ++iter) {
						temp_datas.push_back((*(*iter))[temp_feature]);
					}
				}
				sort(temp_datas.begin(), temp_datas.end());
				vector<double>::iterator iter = temp_datas.begin();
				for (; iter != temp_datas.end()-1;++iter){
					double temp_threshold = (*iter + *(iter + 1)) / 2;
					double temp_info_gain = Information_gain(data, temp_feature, temp_threshold);
					if (temp_info_gain > max_info_gain) {
						max_info_gain = temp_info_gain;
						best_feature = temp_feature;
						best_threshold = temp_threshold;
					}
				}
			}
		}
		if (best_feature >= d_feature_count) {
			return new double[2]{ double(best_feature),best_threshold };
		}
		else {
			return new double[2]{ double(best_feature),-1 };
		}
	}
	// 递归建树
	int Build_tree(Node* node_ptr, set<int> features, DT_data* data) {
		int temp_label = data->Data_identity();
		if (temp_label != -1) { node_ptr->Set_class(temp_label); return NULL; }
		if (features.size() == 0) { node_ptr->Set_class(data->Generate_label()); return NULL; }
		double* devided_result = Choice_best_feature(features, *data);
		int best_feature_ref = (int)devided_result[0];
		double best_threshold_ref = devided_result[1];
		node_ptr->Set_feature(best_feature_ref);
		map<int, DT_data>* devided_datas_ptr;
		if (devided_result[1] == -1) { devided_datas_ptr = Divide_data(*data,best_feature_ref); }
		else { devided_datas_ptr = Divide_data(*data, best_feature_ref, best_threshold_ref); }
		if (best_feature_ref < d_feature_count) {
			features.erase(best_feature_ref);
		}
		for (map<int, DT_data>::iterator iter = devided_datas_ptr->begin(); iter != devided_datas_ptr->end(); ++iter) {
			Node* son_node = new Node(node_ptr);
			node_ptr->Set_son_node(iter->first, son_node);
			if (iter->second.Size() == 0) { 
				son_node->Set_class(data->Generate_label());
				return NULL;
			}
			else {
				Build_tree(son_node, features,&iter->second);
			}
		}
	}
	// 非递归建树
	void Build_tree_without_recursion(Node* node_ptr, set<int> features, DT_data* data) {
		stack<Stack_element> task_stack;
		task_stack.push(Stack_element(node_ptr,data,&features));
		while (task_stack.size() != 0) {
			Stack_element temp = task_stack.top();
			set<int>* temp_features = new set<int>;
			temp_features = temp.Features;
			DT_data* temp_data = temp.Data;
			Node* father_node = temp.Father_node;
			task_stack.pop();

			int temp_label = temp_data->Data_identity();
			if (temp_label != -1) { father_node->Set_class(temp_label); continue; }
			if (temp_features->size() == 0) { father_node->Set_class(temp_data->Generate_label());continue; }

			double* devided_result = Choice_best_feature(*temp_features, *temp_data);
			int best_feature_ref = (int)devided_result[0];
			double best_threshold_ref = devided_result[1];
			father_node->Set_feature(best_feature_ref);
			if (best_feature_ref < d_feature_count) {
				temp_features->erase(best_feature_ref);
			}
			map<int, DT_data>* devided_datas_ptr;
			if (devided_result[1] == -1) { devided_datas_ptr = Divide_data(*temp_data, best_feature_ref); }
			else { devided_datas_ptr = Divide_data(*temp_data, best_feature_ref, best_threshold_ref); }
			for (map<int, DT_data>::iterator iter = devided_datas_ptr->begin(); iter != devided_datas_ptr->end();++iter) {
				Node* son_node = new Node(father_node);
				father_node->Set_son_node(iter->first, son_node);
				if (iter->second.Size() == 0) {
					son_node->Set_feature(iter->second.Generate_label());
					continue;
				}
				task_stack.push(Stack_element(son_node, &iter->second, temp_features));
			}
		}
	
	}
	// 递归建树 主程序
	void Main_build_tree(DT_data* data) {
		Build_tree_without_recursion(Root, *Feature_list, data);
		//Build_tree(Root, *Feature_list, data);
	}
	// 以下代码为可视化部分
	string Generate_space(int space_num) {
		string space = "";
		for (int i = 0; i < space_num; i++) { space += " "; }
		return space;
	}
	string Generate_arrow() {
		return (" ---> ");
	}
	string Draw_limb(Node* ptr) {
		if ((ptr->Node_sons()).size() == 0) {
			return("Leaf:" + to_string(ptr->Node_class()));
		}
		else{
			return("Node:" + to_string(ptr->Node_feature())+ " ---> ");
		}
	}
	void Draw_branch(int space_num) {
	}
	int Draw_tree(Node* ptr,int* line_index,int pos_index,vector<string>& cout_list) {
		if (*line_index < cout_list.size()){
			if (cout_list[*line_index].size() < pos_index) {
				cout_list[*line_index] += Generate_space(cout_list[*line_index].size() - pos_index);
			}
			cout_list[*line_index] += Generate_arrow();
			cout_list[*line_index] += Draw_limb(ptr);
		}
		else {
			cout_list.push_back(Generate_space(pos_index) + "|");
			for (int i = (*line_index)-1; i > 0; i--) {
				if (cout_list[i].size() < pos_index) { continue; }
				if (cout_list[i][pos_index] == ' ') { cout_list[i][pos_index] = '|'; }
				else { break; }
			}

			(*line_index)++;
			cout_list.push_back(Generate_space(pos_index));

			cout_list[*line_index] += Generate_arrow();
			cout_list[*line_index]+=(Draw_limb(ptr));
		}

		if ((ptr->Node_sons()).size() == 0) {
			return NULL;
		}
		int curr_pos = cout_list[*line_index].size();
		map<int, Node*>::iterator iter = (ptr->Node_sons()).begin();
		for (;iter != (ptr->Node_sons()).end(); ++iter) {
			if (iter == (ptr->Node_sons()).begin()) {
				Draw_tree(iter->second, line_index, curr_pos,cout_list);
			}
			else {
				*line_index += 1;
 				Draw_tree(iter->second, line_index, curr_pos, cout_list);
			}
		}
	}
	//树结构可视化
	void Show_me_the_fucking_tree() {
		vector<string> cout_list;
		int* start_line = new int(0);
		int start_pos = 0;
		Draw_tree(Root, start_line, start_pos,cout_list);
		for (vector<string>::iterator iter = cout_list.begin(); iter != cout_list.end(); ++iter) {
			cout << *iter << endl;
		}
	}
};

