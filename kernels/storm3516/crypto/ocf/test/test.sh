#!/bin/sh

echo "test aes-128-cbc*******************"
./openssl enc -in a.txt -out aes128e -e -engine cryptodev -aes-128-cbc -pass pass:mi1d2d3le
./openssl enc -in aes128e -out aes128d -d -engine cryptodev -aes-128-cbc -pass pass:mi1d2d3le
cmp a.txt aes128d
rm -f aes128d aes128e

echo "test aes-128-ecb*******************"
./openssl enc -in a.txt -out aes128e -e -engine cryptodev -aes-128-ecb -pass pass:mi1d2d3le
./openssl enc -in aes128e -out aes128d -d -engine cryptodev -aes-128-ecb -pass pass:mi1d2d3le
cmp a.txt aes128d
rm -f aes128d aes128e

echo "test -aes-192-cbc*******************"
./openssl enc -in a.txt -out aes192e -e -engine cryptodev -aes-192-cbc -pass pass:mi1d2d3le
./openssl enc -in aes192e -out aes192d -d -engine cryptodev -aes-192-cbc -pass pass:mi1d2d3le
cmp a.txt aes192d
rm -f aes192d aes192e

echo "test -aes-192-ecb*******************"
./openssl enc -in a.txt -out aes192e -e -engine cryptodev -aes-192-ecb -pass pass:mi1d2d3le
./openssl enc -in aes192e -out aes192d -d -engine cryptodev -aes-192-ecb -pass pass:mi1d2d3le
cmp a.txt aes192d
rm -f aes192d aes192e

echo "test -aes-256-cbc*******************"
./openssl enc -in a.txt -out aes256e -e -engine cryptodev -aes-256-cbc -pass pass:mi1d2d3le
./openssl enc -in aes256e -out aes256d -d -engine cryptodev -aes-256-cbc -pass pass:mi1d2d3le
cmp a.txt aes256d
rm -f aes256d aes256e

echo "test -aes-256-ecb*******************"
./openssl enc -in a.txt -out aes256e -e -engine cryptodev -aes-256-ecb -pass pass:mi1d2d3le
./openssl enc -in aes256e -out aes256d -d -engine cryptodev -aes-256-ecb -pass pass:mi1d2d3le
cmp a.txt aes256d
rm -f aes256d aes256e

echo "test aes128*******************"
./openssl enc -in a.txt -out aes128e.txt -e -engine cryptodev -aes128 -pass pass:mi1d2d3le
./openssl enc -in aes128e.txt -out aes128d.txt -d -engine cryptodev -aes128 -pass pass:mi1d2d3le
cmp a.txt aes128d.txt
rm -f aes128d.txt aes128e.txt

echo "test aes192*******************"
./openssl enc -in a.txt -out aes192e.txt -e -engine cryptodev -aes192 -pass pass:mi1d2d3le
./openssl enc -in aes192e.txt -out aes192d.txt -d -engine cryptodev -aes192 -pass pass:mi1d2d3le
cmp a.txt aes192d.txt
rm -f aes192d.txt aes192e.txt

echo "test aes256*******************"
./openssl enc -in a.txt -out aes256e.txt -e -engine cryptodev -aes256 -pass pass:mi1d2d3le
./openssl enc -in aes256e.txt -out aes256d.txt -d -engine cryptodev -aes256 -pass pass:mi1d2d3le
cmp a.txt aes256d.txt
rm -f aes256d.txt aes256e.txt

echo "test des *******************"
./openssl enc -in a.txt -out dese.txt -e -engine cryptodev -des -pass pass:mi1d2d3le
./openssl enc -in dese.txt -out desd.txt -d -engine cryptodev -des -pass pass:mi1d2d3le
cmp a.txt desd.txt 
rm -f desd.txt dese.txt

echo "test des-cbc*******************"
./openssl enc -in a.txt -out descbce.txt -e -engine cryptodev -des-cbc -pass pass:mi1d2d3le
./openssl enc -in descbce.txt -out descbcd.txt -d -engine cryptodev -des-cbc -pass pass:mi1d2d3le
cmp a.txt descbcd.txt
rm -f descbcd.txt descbce.txt

echo "test des-ecb*******************"
./openssl enc -in a.txt -out descbce.txt -e -engine cryptodev -des-ecb -pass pass:mi1d2d3le
./openssl enc -in descbce.txt -out descbcd.txt -d -engine cryptodev -des-ecb -pass pass:mi1d2d3le
cmp a.txt descbcd.txt
rm -f descbcd.txt descbce.txt


echo "test -des3-cbc*******************"
./openssl enc -in a.txt -out des3e.txt -e -engine cryptodev -des-ede3-cbc -pass pass:mi1d2d3le
./openssl enc -in des3e.txt -out des3d.txt -d -engine cryptodev -des-ede3-cbc -pass pass:mi1d2d3le
cmp a.txt des3d.txt 
rm -f des3d.txt des3e.txt

echo "test -des3*******************"
./openssl enc -in a.txt -out des3e.txt -e -engine cryptodev -des-ede3 -pass pass:mi1d2d3le
./openssl enc -in des3e.txt -out des3d.txt -d -engine cryptodev -des-ede3 -pass pass:mi1d2d3le
cmp a.txt des3d.txt
rm -f des3*.txt

echo "****************************************************************************"
echo "test md5 ********************"
echo "md5 test1   ------------------------------"
cat ./md5/test1
./openssl dgst -c -engine cryptodev -md5 ./md5/test1
echo "0c:c1:75:b9:c0:f1:b6:a8:31:c3:99:e2:69:77:26:61"

echo "md5 test2   ------------------------------"
cat ./md5/test2
./openssl dgst -c -engine cryptodev -md5 ./md5/test2
echo "90:01:50:98:3c:d2:4f:b0:d6:96:3f:7d:28:e1:7f:72"

echo "md5 test3   ------------------------------"
cat ./md5/test3
./openssl dgst -c -engine cryptodev -md5 ./md5/test3
echo "f9:6b:69:7d:7c:b7:93:8d:52:5a:2f:31:aa:f1:61:d0"

echo "md5 test4   ------------------------------"
cat ./md5/test4
./openssl dgst -c -engine cryptodev -md5 ./md5/test4
echo "c3:fc:d3:d7:61:92:e4:00:7d:fb:49:6c:ca:67:e1:3b"

echo "md5 test5   ------------------------------"
cat ./md5/test5
./openssl dgst -c -engine cryptodev -md5 ./md5/test5
echo "d1:74:ab:98:d2:77:d9:f5:a5:61:1c:2c:9f:41:9d:9f"

echo "md5 test6   ------------------------------"
cat ./md5/test6
./openssl dgst -c -engine cryptodev -md5 ./md5/test6
echo "57:ed:f4:a2:2b:e3:c9:55:ac:49:da:2e:21:07:b6:7a"

echo "***********************************"
echo "test sha1"
echo "sha1 test1   ------------------------------"
cat ./sha1/test1
./openssl dgst -c -engine cryptodev -sha1 ./sha1/test1
echo "a9:99:3e:36:47:06:81:6a:ba:3e:25:71:78:50:c2:6c:9c:d0:d8:9d"

echo "sha1 test2   ------------------------------"
cat ./sha1/test2
./openssl dgst -c -engine cryptodev -sha1 ./sha1/test2
echo "84:98:3e:44:1c:3b:d2:6e:ba:ae:4a:a1:f9:51:29:e5:e5:46:70:f1"


#time dd if=/dev/zero bs=1m count=1024 | openssl aes-256-cbc -pass
