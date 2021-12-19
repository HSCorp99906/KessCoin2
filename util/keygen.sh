openssl ecparam -name secp256k1 -genkey -noout -out keys/private.pem
openssl ec -in keys/private.pem -pubout > keys/public.pem
