#include "stdafx.h"
#include "Session.h"

int main() {
	CSession test;
	test.initSession();

	while(1);
	test.~CSession();
}
