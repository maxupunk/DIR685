#!/bin/sh

 ./cryptotest -a des_cbc 1000 2048
sleep 1
 ./cryptotest -a des_ecb 1000 2048
sleep 1
 ./cryptotest -a 3des_cbc 1000 2048
sleep 1
 ./cryptotest -a 3des_ecb 1000 2048
sleep 1
 ./cryptotest -a aes128_cbc 1000 2048
sleep 1
 ./cryptotest -a aes128_ecb 1000 2048
sleep 1
 ./cryptotest -a aes192_cbc 1000 2048
sleep 1
 ./cryptotest -a aes192_ecb 1000 2048
sleep 1
 ./cryptotest -a aes256_cbc 1000 2048
sleep 1
 ./cryptotest -a aes256_ecb 1000 2048
sleep 1
 ./cryptotest -a md5 1000 2048
sleep 1
 ./cryptotest -a md5_hmac 1000 2048
sleep 1
 ./cryptotest -a sha1 1000 2048
sleep 1
 ./cryptotest -a sha1_hmac 1000 2048
sleep 1

