#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
using namespace std;


enum label_set { 好瓜, 坏瓜, label_count };
enum discontinue_feature_set { 色泽, 根蒂, 敲声, 纹理, 脐部, 触感, d_feature_count };
enum continue_feature_set { 硬度 = d_feature_count, 含糖率, feature_count };

