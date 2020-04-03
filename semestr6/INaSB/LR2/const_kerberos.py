from datetime import datetime

KERBEROS_IP = '127.0.0.1'
KERBEROS_PORT = 5006
BUFFER_SIZE = 1024

KC = 'CHICHA'
KC_TGS = 'QWERTY'

TGS = 'AS'
T1 = str(datetime.now().hour) + str(datetime.now().microsecond)
P1 = 'infinity'
TGT = TGS + T1 + P1

T2 = str(datetime.now().hour) + str(datetime.now().microsecond)
ID = '5005'

AUT = T2 + ID
