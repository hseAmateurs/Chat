#pragma once
#include <iostream>
#include "serverClass.h"


using namespace std;
string dataTime();
pair<string, string> splitString(const string& input);
void onlineNotifier(const SERVER& server, int userId);