#include "Window.h"
class Test {
	vector<Vec2*> vecs;

public:
	Test() {
		vecs.push_back(new Vec2(5, 5));
	};
	~Test() {};

	vector<Vec2*> get() { return vecs; }
	void print() { 
		printf("X: %f | Y: %f \n", vecs.at(0)->x, vecs.at(0)->y);
		printf("Count: %i \n", vecs.size());
	}
};

void manipulate(const vector<Vec2*> v) {
	Vec2* vec = v.at(0);

	vec->x = 54;
	vec->y = 3;
}

int main(void) {
	Test test;
	vector<Vec2*> v = test.get();
	Vec2* vec = v.at(0);

	vec->x = 54;
	vec->y = 3;

	test.print();

	Window window = Window();
	window.loop();

	return 0;
}