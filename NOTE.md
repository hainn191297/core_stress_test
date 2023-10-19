# Server

## 1. Fix Bug
- makecall service for non-Vinaphone user. c42823ccaa20b4ac0c166e9e0177e4ae4099599a
- Call object not work, call HA. 754efbf1627d4f5d938231e9e6f3832ec0599c26
- Fix crash delete message. 326bfd73c9870c99f41d3cb01ce36c9b9d3aaa02
- Fix return list chat id empty. 0c1023edb5803fb1014e664aa4c141ee38b86948
- Fix list history call, message. a5d1f4b4d8dcf7f5a64d797defac76f270493327
## 2. Feature
- Send sms. c8840a71236fb943f70950dc3eb54036f6493429
- Add DelListCallHistory service. dce6be08f2a428efa861114341632b1471df1da7
## 3. Database
- 0 -> main database
- 1 -> mnp (danh sách telco, các số mnp) hm|telco
- 2 -> user tel (tổng hợp user tel) hm|user_tel
	token - session (mapping) hm|token_session 
	token voip - session (mapping) hm|token_voip_session
- 3 -> presence of friends |user|relateto|user id
- 4 -> call object
	user last active call
	caller - call id (end call)