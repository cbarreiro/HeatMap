#include "Session.h"

CSession::CSession() {	
	
}

CSession::~CSession() {
	EXIT_FLAG = true;
}

void CSession::initSession(void) {	
	// Initialize MySQL object
	sessionCon = mysql_init(NULL);
	
	// Check object status
	if (sessionCon == NULL) {
		std::cout << mysql_error(sessionCon);
		check = FAIL;
	}
	
	// Check connections status
	if (mysql_real_connect(sessionCon, "localhost", "root", "root-pswd", NULL, 0, NULL, 0) == NULL) {
		std::cout << mysql_error(sessionCon);
		mysql_close(sessionCon);
		check = FAIL;
	}
	
	if (check == PASS) {
		sessionStart = time(0);
	}
}

void CSession::termSession(void) {
	if (sessionCon != NULL) {
		mysql_close(sessionCon);
	}
}
