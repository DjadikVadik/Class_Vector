#include "Vector.h"




int main()
{
	system("chcp 1251 > 0");

	Vector<int> v;
	v.push_beck(14);
	v.push_beck(67);
	v.push_beck(35);
	v.push_front(11);
	v.push_beck(14);
	v.push_beck(1);
	v.print();
	
}