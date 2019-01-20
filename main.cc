#include "grid.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main(){
 Grid g;
 string s;
 int n;
 while (cin >> s){
	if (s == "new") {
		cin >> s;
		istringstream iss{s};
		if(!(iss >> n)) continue;
		g.init(n);
	} else if (s == "init") {
		int x, y;
		while(cin >> x >> y) {
			if (x == -1 || y == -1) break;
			g.turnOn(x,y);
		}
	} else if (s == "step") {
		g.tick();
	} else if (s == "steps") {
		istringstream iss{s};
		if (!(iss >> n)) continue;
		for (int i = 0; i < n; ++i){
			g.tick();
		}
	} else if (s == "print") {
		cout << g;
	} else {
		continue;
	}
 }
}
