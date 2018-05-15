#pragma once
#include <vector>
#include <string>
#include "Settings.h"
#include "Keys.h"

enum class state { CONNECTING, SENDING, CONNECTED, CONNECTIONERROR };
enum buttons { UP, DOWN, LEFT, RIGHT, START, SELECT, A, B, X, Y, L1, L2 };
extern Settings set;