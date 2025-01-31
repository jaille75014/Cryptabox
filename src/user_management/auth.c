#include <stdio.h>
#include <string.h>
//      #include <openssl/sha.h>
#include <mysql.h>
#include "auth.h"
#include "users.h"

#define MAX_USERNAME = 50
#define MAX_PASSWORD = 30
#define HASH_SIZE = 65

