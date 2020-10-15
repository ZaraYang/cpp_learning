#pragma once
#include "include.h"


class Decision_tree_data {
private:
	vector<vector<float>*>* Data;
	map<int, set<float>>* Feature_map_ptr;
public:
	Decision_tree_data(){}
	Decision_tree_data(map<int, set<float>>* ptr)
		:Data(new vector<vector<float>*>),Feature_map_ptr(ptr){}
	Decision_tree_data(string& addr) 
		:Data(Import_from_file(addr)),Feature_map_ptr(Data_feature_analysis()){}

	vector<vector<float>*>* Import_from_file(string& addr) {
		vector<vector<float>*>* data = new vector<vector<float>*>;
		ifstream input_file(addr,ios::in);
		string buffer;
		getline(input_file, buffer);
		while (getline(input_file, buffer)) {
			data->push_back(Split_data(buffer));
		}
		return data;
	}
	vector<float>* Split_data(string& e) {
		vector<float>* result = new vector<float>;
		for (int i = 0; i < e.size(); i++) {
			if (e[i] == ',') { e[i] = ' '; };
		}
		istringstream out(e);
		string buffer;
		while (out >> buffer) {
			result->push_back(atof(buffer.c_str()));
		}
		return result;
	}
	int Data_size() {return Data->size();}

	vector<vector<float>*>* Show_data() { return Data; }

	void Insert_data(vector<float>* data) {
		Data->push_back(data);
	}

	map<int, set<float>>* Data_feature_analysis() {
		map<int, set<float>>* features = new map<int, set<float>>;
		for (int i = 0; i < d_feature_count; i++) {
			set<float> buffer;
			for (int j = 0; j < (*Data).size(); j++) {
				buffer.insert((*(*Data)[j])[i]);
			}
			(*features)[i] = buffer;
		}
		return features;
	}

	vector<Decision_tree_data>* Divide_data(int feature) {
		if (feature >= d_feature_count) { throw "No threshold for continues feature!"; }
		vector<Decision_tree_data>* Result = new vector<Decision_tree_data>;
		for (int i = 0;i< (*Feature_map_ptr)[feature].size();i++){
			Result->push_back(*new Decision_tree_data(Feature_map_ptr));
		}
		for (int i = 0; i < (*Data).size(); i++) {
			(*Result)[(*(*Data)[i])[feature]].Insert_data((*Data)[i]);
		}
		return Result;
	}

	vector<Decision_tree_data>* Divide_data(int feature, float threshold) {
		vector<Decision_tree_data>* Result = new vector<Decision_tree_data>;
		for (int i = 0; i < 2; i++) {
			Result->push_back(*new Decision_tree_data(Feature_map_ptr));
		}
		for (int i = 0; i < (*Data).size(); i++) {
			int Insert_index = (*(*Data)[i])[feature] <= threshold ? 0 : 1;
			(*Result)[Insert_index].Insert_data((*Data)[i]);
		}
		return Result;
	}
	
	float* Decide_best_devide() {
		float max_information_gain = - 99;
		int max_feature = 0;
		float threshold = -1;
		for (int i = 0; i < d_feature_count; i++) {
			float temp_information_gain = Information_gain(i);
			if ( temp_information_gain > max_information_gain) {
				max_information_gain = temp_information_gain;
				max_feature = i;
			}
		}

		for (int i = d_feature_count; i < feature_count; i++) {
			vector<float> temp_vect;
			for (int j = 0; j < Data->size(); j++) {
				temp_vect.push_back((*(*Data)[j])[i]);
			}
			sort(temp_vect.begin(), temp_vect.end());
			for (int j = 1; j < temp_vect.size() - 1; j++) {
				float temp_information_gain = Information_gain(i,temp_vect[j]);
				if (temp_information_gain > max_information_gain) {
					max_information_gain = temp_information_gain;
					max_feature = i;
					threshold = temp_vect[j];
				}
			}
			
		}
		if (threshold == -1) {
			return new float[2]{ max_feature,NULL };
		}
		else {
			return new float[2]{ max_feature,threshold };
		}
	}

	float Information_entropy() const {
		float Entropy = 0;
		for (int i = 0; i < label_count; i++) {
			float count = 0;
			for (int j = 0; j < Data->size(); j++) {

				if (i == (*Data)[j]->back()) {
					count++;
				}
			}
			float p = count/Data->size();
			if (p == 0) { continue; }
			else {
				Entropy -= p * log2f(p);
			}
		}
		return Entropy;
	}

	float Information_entropy(vector<vector<float>*>* data) const {
		float Entropy = 0;
		for (int i = 0; i < label_count; i++) {
			float count = 0;
			for (int j = 0; j < data->size(); j++) {

				if (i == (*data)[j]->back()) {
					count++;
				}
			}
			float p = count / data->size();
			Entropy -= p * log2f(p);
		}
		return Entropy;
	}

	float Information_gain(int feature){
		if (feature >= d_feature_count) { throw "No threshold for continues feature!"; }
		float Ent = Information_entropy();
		vector<Decision_tree_data>* Divided_data_ptr = Divide_data(feature);
		float buffer= 0;
		for (int i = 0; i < Divided_data_ptr->size(); i++) {
			float partition = static_cast<float>((*Divided_data_ptr)[i].Data_size()) / Data->size();
			float temp_entropy = (*Divided_data_ptr)[i].Information_entropy();

			buffer += partition*temp_entropy;
		}
		return Ent - buffer;
	}

	float Information_gain(int feature, float threshold) {
		float Ent = Information_entropy(Data);
		vector<Decision_tree_data>* Divided_data_ptr = Divide_data(feature,threshold);
		float buffer = 0;
		for (int i = 0; i < Divided_data_ptr->size(); i++) {
			float partition = static_cast<float>((*Divided_data_ptr)[i].Data_size()) / Data->size();
			float temp_entropy = (*Divided_data_ptr)[i].Information_entropy();

			buffer += partition * temp_entropy;
		}
		return Ent - buffer;
	}

	int Label_identity() {
		int label = (*Data)[0]->back();
		for (int i = 1; i < (*Data).size(); i++) {
			if (label != (*Data)[i]->back()) {
				return NULL;
			}
		}
		return label;
	}
	// 由于连续特征的加入，不可能出现feature一样的情况
	bool Feature_identity() {}
	
	bool Out_of_data() {
		return (bool*)(*Data).size();
	}
};

class Feature_list {
private:
	set<int>* feature_list;
	void Feature_list_init() {
		for (int i = 0; i < feature_count; i++) {
			feature_list->insert(i);
		}
	}

public:
	Feature_list() :feature_list(new set<int>){
		Feature_list_init();}

	void Delete_feature(int feature) {
		feature_list->erase(feature);
	}

	bool Out_of_feature() {
		return (bool*)feature_list->size();
	}
};