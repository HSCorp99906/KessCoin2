#ifndef RSA_UTIL_H
#define RSA_UTIL_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <stdbool.h>


bool gen_private_key(const char* filename);

bool gen_public_key(const char* filename);
 

#endif  // RSA_UTIL_H
